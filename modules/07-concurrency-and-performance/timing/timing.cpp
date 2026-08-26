
// Demo a platform-independent method for timing code execution.
// See here: https://www.youtube.com/watch?v=oEx5vGNFrLk&list=WL&index=21
// And here: https://www.youtube.com/watch?v=YG4jexlSAjc&list=WL&index=20

// Note: I removed high_resolution_clock from this in favor of steady_clock, as 
// recommended here: https://en.cppreference.com/w/cpp/chrono/high_resolution_clock
// However, this makes the code Windows-dependent. On Linux, use system_clock instead.

#include <iostream>
using std::cout;
using std::endl;

#include <chrono>
using namespace std::chrono;

#include <thread>

namespace {

  // Leverage the object lifetime paradigm to automate timing.
  class Timer {
    time_point<steady_clock> m_start_time;
  public:
    Timer(): m_start_time(steady_clock::now()) {}
    ~Timer() {
      const duration<float> duration = steady_clock::now() - m_start_time;
      cout << duration.count() << " s" << endl;
    }
  };

  void do_work() {
    Timer timer; // this will automatically report timing when this function goes out of scope
    std::this_thread::sleep_for(2s);
  }

} // namespace

int main() {

  cout << "\nLong way (1 sec)..." << endl;
  const time_point<steady_clock> start = steady_clock::now();
  std::this_thread::sleep_for(1s);
  const duration<float> duration = steady_clock::now() - start;
  cout << duration.count() << " s" << endl;

  // Cast to microseconds.
  const auto start_us = time_point_cast<microseconds>(start).time_since_epoch().count();
  const auto stop_us = time_point_cast<microseconds>(steady_clock::now()).time_since_epoch().count();
  cout << stop_us - start_us << " us\n";
  
  // Benchmark some target code by wrapping it in a scope with a timer instance.
  // In general, it makes sense to do timing tests in Release mode. Note that when you 
  // do that for the following case, however, the compiler will optimize out the code 
  // in the for-loop below and just prints 20 million without computing in run-time. 
  // The lesson is that your timing code may not be measuring what you expect. Try 
  // inspecting the disassembly by running to a breakpoint and hitting Alt + G (or
  // right click on the code, and select "Go To Disassembly").
  cout << "\nBenchmarking...\n";
  int value = 0;
  {
    Timer timer;
    for (int i = 0; i < 10'000'000; i++) { value += 2; }
  }
  cout << value << endl;

  cout << "\nClean way using the object lifetime (2 sec)...\n";
  do_work();

  // FYI, here's a Windows-only function for adding a breakpoint.
  //__debugbreak(); 
}
