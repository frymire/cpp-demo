
// Demo a platform-independent method for getting timing.
// See here: https://www.youtube.com/watch?v=oEx5vGNFrLk&list=WL&index=21

#include <iostream>
using std::cout;
using std::endl;

#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::steady_clock;
using std::chrono::duration;
using namespace std::literals::chrono_literals;

#include <thread>

// Leverage object lifetime paradigm to automate timing.
struct Timer {

  time_point<steady_clock> start; 

  Timer(): start(high_resolution_clock::now()) {}

  ~Timer() { 
    duration<float> duration = high_resolution_clock::now() - start;
    cout << duration.count() << " s" << endl;
  }
};

void MyFunction() {
  Timer timer;
  std::this_thread::sleep_for(2s);
}

int main() {

  // Long way...
  cout << "\nLong way (1 sec)..." << endl;
  auto start = high_resolution_clock::now();
  std::this_thread::sleep_for(1s);
  duration<float> duration = high_resolution_clock::now() - start;
  cout << duration.count() << " s" << endl;

  // Clean way using object lifetime...
  cout << "Semi-automatic way (2 sec)...\n";
  MyFunction();
}
