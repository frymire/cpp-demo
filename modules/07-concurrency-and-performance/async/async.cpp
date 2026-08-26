
// Demonstrate async (i.e. C++ futures and promises).
// Adapted from here: https://thispointer.com/c11-multithreading-part-9-stdasync-tutorial-example/

#include <iostream>
using std::cout;
using std::endl;

#include <syncstream>
using std::osyncstream;

#include <string>
using std::string;
using std::to_string;

#include <array>
using std::array;

#include <thread>
using std::this_thread::sleep_for;

#include <future>
using std::future;
using std::async;
using std::launch;

#include <chrono>
using namespace std::chrono;

namespace {

  string run_task(const string& data) {
    osyncstream(cout) << "Running " << data << " task..." << endl;  // osyncstream keeps << calls together
    sleep_for(3s);
    return "Done: " + data;
  }

} // namespace

int main() {

  constexpr int kNumTasks = 10;
  cout << "Starting...\n";
  const steady_clock::time_point start_time = steady_clock::now();

  array<future<string>, kNumTasks> futures;
  for (int i = 0; i < kNumTasks; i++) { futures[i] = async(launch::async, run_task, "data" + to_string(i)); }

  array<string, kNumTasks> results;
  for (int i = 0; i < kNumTasks; i++) { results[i] = futures[i].get(); }
  const steady_clock::time_point stop_time = steady_clock::now();
  const long long duration = duration_cast<milliseconds> (stop_time - start_time).count();

  cout << endl;
  for (const auto& result : results) { cout << result << endl; }
  cout << "Duration = " << duration << " ms" << endl;
}
