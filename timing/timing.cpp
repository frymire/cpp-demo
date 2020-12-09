
// Demo a platform-independent method for getting timing.
// See here: https://www.youtube.com/watch?v=oEx5vGNFrLk&list=WL&index=21
// Note: I removed high_resolution_clock from this in favor of steady_clock, as 
// recommended here: https://en.cppreference.com/w/cpp/chrono/high_resolution_clock

#include <iostream>
using std::cout;
using std::endl;

#include <chrono>
using std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace std::literals::chrono_literals;

#include <thread>

// Leverage object lifetime paradigm to automate timing.
struct Timer {

  time_point<steady_clock> start; 

  Timer(): start(steady_clock::now()) {}

  ~Timer() { 
    duration<float> duration = steady_clock::now() - start;
    cout << duration.count() << " s" << endl;
  }
};

void MyFunction() {
  Timer timer; // automatically report timing when this function goes out of scope.
  std::this_thread::sleep_for(2s);
}

int main() {

  // Long way...
  cout << "\nLong way (1 sec)..." << endl;
  time_point<steady_clock> start = steady_clock::now();
  std::this_thread::sleep_for(1s);
  duration<float> duration = steady_clock::now() - start;
  cout << duration.count() << " s" << endl;

  // Clean way using object lifetime...
  cout << "Semi-automatic way (2 sec)...\n";
  MyFunction();
}
