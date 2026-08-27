// Demo threads.
// See here: https://www.youtube.com/watch?v=wXBcwHwIt_I&list=WL&index=71

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <syncstream>
using std::osyncstream;

#include <vector>
using std::vector;

#include <thread>
using std::thread;
using std::this_thread::sleep_for;

#include <atomic>
using std::atomic;

#include <chrono>
using namespace std::chrono_literals; // define time, for instance, as "1s"

namespace {

  atomic s_enter_was_pressed = false;

  void do_work(const int id) {
    osyncstream(cout) << "Started local thread ID = " << id << endl;
    while (!s_enter_was_pressed) {
      osyncstream(cout) << "Thread " << id << " working...\n";
      sleep_for(3s);
    }
    osyncstream(cout) << "Finished local thread ID = " << id << endl;
  }

} // namespace

int main() {

  constexpr int kNumThreads = 4;

  cout << "Started main thread.\n";
  cout << "Press [Enter] to interrupt." << endl;

  // Start some worker threads.

  vector<thread> threads;
  for (int id = 0; id < kNumThreads; ++id) { threads.emplace_back(do_work, id); }

  // Or, to start a single thread...
  thread late_worker{do_work, kNumThreads};

  // Block on the main thread until the user presses enter.
  cin.get();
  s_enter_was_pressed = true;

  // Wait for the workers to complete their work and rejoin the main thread.
  for (thread& thread: threads) { thread.join(); }
  late_worker.join();
  cout << "Finished main thread." << endl;
}
