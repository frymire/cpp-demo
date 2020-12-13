
#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <cmath>

#include <chrono>
using std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration;
using namespace std::literals::chrono_literals;

#include <thread>
using std::thread;

#include "instrumentor.h"

// You can say whether we're profiling inline here...
//#define PROFILING 1

// ...or define the PROFILING symbol in Project Properties
//   Project Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions: {add "PROFILING={0|1}"}

#if PROFILING
  #define PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__(name)
  // Use __func__ here instead for cleaner output, but it wouldn't include namespaces or differentiate overloaded functions.
  #define PROFILE_FUNCTION InstrumentationTimer timer##__LINE__(__func__)
//#define PROFILE_FUNCTION InstrumentationTimer timer##__LINE__(__FUNCSIG__)
#else
  #define PROFILE_SCOPE(name)
  #define PROFILE_FUNCTION
#endif

namespace MyAPI {

  void Function1(int x) {
    PROFILE_FUNCTION;
    for (int i = 0; i < 1000; i++) { cout << "Hello world #" << i << endl; }
  }

  void Function1(double x) {
    PROFILE_FUNCTION;
    for (int i = 0; i < 1000; i++) { cout << "Hello world #" << sqrt(i) << endl; }
  }

  void Function2() {
    PROFILE_FUNCTION;
    for (int i = 0; i < 1000; i++) { cout << "Hello world #" << sqrt(i) << endl; }
  }

  void RunBenchmarks() {
    PROFILE_FUNCTION;
    cout << "Running benchmarks...\n";
    thread thread1([]() { Function1(3); });
    Function1(3.4);
    Function2();
    thread1.join();
  }
}

int main() {

  Instrumentor::Get().BeginSession("Profile");
  MyAPI::RunBenchmarks();
  {
    PROFILE_SCOPE("Scope within main()");
    MyAPI::RunBenchmarks();
  }
  Instrumentor::Get().EndSession();
  // In Google Chrome, go to chrome://tracing, click "Load", and select "results.json" that was 
  // just created in the project folder. Or drag and drop the file into the Chrome window.
}
