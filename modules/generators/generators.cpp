// https://www.youtube.com/watch?v=7ZazVQB-RKc

#include <generator>
#include <print>
#include <ranges>
#include <utility>

std::generator<int> fibonacci() {
  int i = 0, j = 1;
  // ReSharper disable once CppDFAEndlessLoop
  while (true) {
    i = std::exchange(j, i + j);  // exchange() sets j to i + j, then returns the previous value of j
    co_yield i;  // without this, we'd be in an infinite loop
  }
}

int main() {
  for (const auto i : fibonacci() | std::views::take(10)) { std::print("{}\n", i); }
  return 0;
}
