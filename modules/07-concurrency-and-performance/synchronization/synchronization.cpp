
// Demonstrate the tools that let several threads share data safely.

#include <iostream>
using std::cout;
using std::endl;

#include <syncstream>
using std::osyncstream;

#include <vector>
using std::vector;

#include <string>
using std::string;
using std::to_string;

#include <thread>
using std::jthread;
using std::this_thread::sleep_for;

#include <atomic>
using std::atomic;

#include <mutex>
using std::mutex;
using std::lock_guard;

#include <semaphore>
using std::counting_semaphore;

#include <latch>
using std::latch;

#include <barrier>
using std::barrier;

#include <chrono>
using namespace std::chrono;

namespace {

  constexpr int kNumThreads = 8;

  // Run one job on k_n_threads threads, and wait for all of them to finish.
  template<typename JobT>
  void run_on_all_threads(JobT job) {
    vector<jthread> threads;
    for (int i = 0; i < kNumThreads; i++) { threads.emplace_back(job, i); }
    for (auto& thread: threads) { thread.join(); }
  }

}  // namespace

int main() {

  constexpr int kIncrementsPerThread = 100'000;
  constexpr int kExpectedTotal = kNumThreads * kIncrementsPerThread;

  cout << "\nExpected total in every case below: " << kExpectedTotal << "\n" << endl;

  // THE PROBLEM. counter++ is really three steps: read, add one, write back. Two threads can read the same old value,
  // so one of the two increments disappears.The count comes out too low, and by a different amount on every run.
  {
    int counter = 0;
    run_on_all_threads([&counter](int) { for (int i = 0; i < kIncrementsPerThread; i++) { ++counter; } });
    cout << "1. plain int          = " << counter << "   <- WRONG, updates were lost" << endl;
  }

  // ATOMIC. ++ on an atomic is one indivisible step, so no update can be lost. Use this when a
  // single variable is the whole shared state. It needs no lock, so it is fast.
  {
    cout << endl;
    atomic counter = 0;
    run_on_all_threads([&counter](int) { for (int i = 0; i < kIncrementsPerThread; i++) { ++counter; } });
    cout << "2. atomic             = " << counter << "   <- correct" << endl;
  }

  // MUTEX. When several variables must stay consistent with each other, you need a lock around the whole group.
  // lock_guard locks on construction and unlocks in its destructor, so the lock is released on every exit path,
  // including an exception.
  {
    cout << endl;
    int counter1 = 0;
    int counter2 = 0;  // a second variable that must agree with the first
    mutex counter_mutex;
    run_on_all_threads([&](int) {
      for (int i = 0; i < kIncrementsPerThread; i++) {
        lock_guard lock(counter_mutex);  // held until the end of this iteration
        counter1++;
        counter2++;
      }
    });
    cout << "3. mutex + lock_guard = " << counter1 << "   <- correct, and counter2 agrees: " << counter2 << endl;
  }

  // COUNTING SEMAPHORE. A semaphore holds a number of permits. acquire() takes one, and blocks
  // when none are left. release() gives one back. Use it to cap how many threads may use a limited
  // resource at once, such as database connections or GPU slots. A mutex is the special case of one
  // permit, but a mutex must be released by the thread that took it, while a semaphore need not be.
  {
    cout << "\n4. Let 8 threads share only 3 permits...\n";
    counting_semaphore<3> permits(3);
    atomic num_in_section = 0;
    atomic peak_in_section = 0;

    run_on_all_threads([&](const int id) {

      permits.acquire();   // waits here when all 3 permits are taken
      const int now_inside = ++num_in_section;

      // Record the largest number of threads seen inside at one time.
      int previous_peak = peak_in_section.load();
      while (now_inside > previous_peak && !peak_in_section.compare_exchange_weak(previous_peak, now_inside)) {}

      osyncstream(cout) << "   thread " << id << " is inside (" << now_inside << " of 3)" << endl;
      sleep_for(200ms);
      --num_in_section;
      permits.release();  // let the next waiting thread in
    });

    cout << "   peak threads inside at once = " << peak_in_section << "   <- never above 3" << endl;
  }

  // LATCH. A one-shot gate. Each thread calls count_down() when it reaches the point, and any
  // thread calling wait() blocks until the count reaches zero. A latch cannot be reused.
  {
    cout << "\n5. Wait for all 8 threads to finish their setup...\n";
    latch setup_done(kNumThreads);
    run_on_all_threads([&setup_done](const int id) {
      sleep_for(milliseconds(20 * id));   // each thread takes a different amount of time
      osyncstream(cout) << "   thread " << id << " finished setup" << endl;
      setup_done.count_down();
    });
    setup_done.wait();   // returns only after all 8 have counted down
    cout << "   all threads are ready" << endl;
  }

  // BARRIER. Like a latch, but reusable. Every thread waits at the barrier until all of them
  // arrive, then they all continue into the next phase. The completion function runs once per
  // phase, on one thread, while the others are still blocked.
  {
    cout << "\n6. Move 8 threads through 3 phases together...\n";
    atomic<int> phase = 1;
    barrier sync_point(kNumThreads, [&phase]() noexcept {
      osyncstream(cout) << "   --- phase " << phase++ << " complete for all threads ---" << endl;
    });

    run_on_all_threads([&sync_point](const int id) {
      for (int p = 0; p < 3; p++) {
        sleep_for(milliseconds(10 * id));
        sync_point.arrive_and_wait();   // blocks until all 8 threads arrive
      }
    });
  }

  return 0;
}
