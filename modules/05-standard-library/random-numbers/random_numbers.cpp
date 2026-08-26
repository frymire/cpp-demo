
// Demonstrate random numbers with the <random> library (C++11).
//
// The library splits the work into three parts. Keep them separate in your head:
//   1. A seed source gives a starting value that differs between runs.
//   2. An engine turns one seed into a long stream of raw bits.
//   3. A distribution maps those bits onto the numbers you actually want.
//
// Do not use rand(). See the note at the end of the file.

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::fixed;
using std::setprecision;
using std::setw;

#include <random>
using std::mt19937;
using std::normal_distribution;
using std::random_device;
using std::uniform_int_distribution;
using std::uniform_real_distribution;

#include <map>
using std::map;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <algorithm>
using std::ranges::shuffle;

namespace {

  // Draw many values and show how often each one appears, so you can see the shape.
  void print_histogram(const map<int, int>& outcome_to_count, const int n_draws) {
    for (const auto& [outcome, count]: outcome_to_count) {
      const int n_stars = count * 40 / n_draws;
      cout << setw(3) << outcome << " | " << string(n_stars, '*') << " " << count << endl;
    }
  }

}  // namespace

int main() {

  // Note: avoid rand(). Use this instead...
  random_device seed_source; // asks the OS for entropy, so each run of the program differs
  mt19937 engine(seed_source()); // holds the state, should be reused

  cout << fixed << setprecision(4);

  cout << "Random real numbers, uniform over [0.0, 1.0), upper bound excluded...\n";
  uniform_real_distribution draw_from_uniform(0.0, 1.0);
  for (int i = 0; i < 5; i++) { cout << draw_from_uniform(engine) << " "; }

  cout << "\n\nRandom real numbers, uniform over [-10.0, 10.0)...\n";
  uniform_real_distribution draw_from_scaled(-10.0, 10.0);
  for (int i = 0; i < 5; i++) { cout << draw_from_scaled(engine) << " "; }

  cout << "\n\nRandom integers, uniform over [1, 6], both bounds inclusive...\n";
  uniform_int_distribution draw_from_die(1, 6);
  for (int i = 0; i < 10; i++) { cout << draw_from_die(engine) << " "; }

  cout << "\n\nRoll the dice 60000 times to show that the values really are uniform...\n";
  constexpr int kNumRolls = 60000;
  map<int, int> outcome_to_count;
  for (int i = 0; i < kNumRolls; i++) { outcome_to_count[draw_from_die(engine)]++; }
  print_histogram(outcome_to_count, kNumRolls);

  cout << "\nA normal distribution, for comparison. Mean 0, standard deviation 2...\n";
  normal_distribution draw_from_normal(0.0, 2.0);
  map<int, int> normal_counts;
  for (int i = 0; i < kNumRolls; i++) { normal_counts[static_cast<int>(std::lround(draw_from_normal(engine)))]++; }
  print_histogram(normal_counts, kNumRolls);

  cout << "\nSeed with a fixed number to get the same sequence every run. Do this in tests...\n";
  mt19937 fixed_engine(42);
  uniform_int_distribution small(1, 100);
  for (int i = 0; i < 5; i++) { cout << small(fixed_engine) << " "; }
  cout << endl;

  cout << "\nShuffle a container. Pass the engine, so the shuffle is seeded like everything else...\n";
  vector cards = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  shuffle(cards, engine);
  for (const int card: cards) { cout << card << " "; }
  cout << endl;

  return 0;
}
