
// Demonstrate async (i.e. C++ futures and promises).
// Adapted from here: https://thispointer.com/c11-multithreading-part-9-stdasync-tutorial-example/

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <thread>
using std::this_thread::sleep_for;

#include <future>
using std::future;
using std::async;
using std::launch;

#include <chrono>
using namespace std::chrono;
using namespace std::chrono_literals; // define time, for instance, as "1s"

string RunTask1(string data) {
  sleep_for(5s);
  return "Task 1: " + data;
}

string RunTask2(string data) {
  sleep_for(5s);
  return "Task 2: " + data;
}

int main() {

  // Run two tasks, the first asychronously.
  cout << "Starting...\n";
  system_clock::time_point startTime = system_clock::now();
  future<string> task1_future = async(launch::async, RunTask1, "data1");
  string task2_result = RunTask2("data2");

  // Block until the result is available from the Task 1 future.
  string task1_result = task1_future.get();
  system_clock::time_point stopTime = system_clock::now();

  long long duration = duration_cast<seconds> (stopTime - startTime).count();
  cout << task1_result << endl << task2_result << endl;
  cout << "Duration = " << duration << " s" << endl;
}
