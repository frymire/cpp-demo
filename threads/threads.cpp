
// Demo threads.
// See here: https://www.youtube.com/watch?v=wXBcwHwIt_I&list=WL&index=71

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <thread>
using std::thread;
using std::this_thread::sleep_for;

#include <chrono>
using namespace std::chrono_literals; // define time, for instance, as "1s"

static bool s_enter_was_pressed = false;

void DoWork() {

  cout << "Started thread ID = " << std::this_thread::get_id() << endl;

  while (!s_enter_was_pressed) { 
    cout << "Working...\n"; 
    sleep_for(1s);
  }

  cout << "Finished thread ID = " << std::this_thread::get_id() << endl;
}

int main() {

  cout << "Started thread ID = " << std::this_thread::get_id() << endl;

  // Start a worker thread.
  thread worker(DoWork);

  // Block on the main thread until the user presses enter.
  cin.get();
  s_enter_was_pressed = true;

  // Wait for worker to complete its work and rejoin the main thread.
  worker.join();
  cout << "Finished thread ID = " << std::this_thread::get_id() << endl;
}
