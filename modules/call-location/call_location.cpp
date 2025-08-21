// Demo printing the signature of a function and where it was called from.

#include <print>
#include <source_location>

#if defined(__clang__) || defined(__GNUC__)
  #define FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
  #define FUNCTION_SIGNATURE __FUNCSIG__
#else
  #define FUNCTION_SIGNATURE __func__
#endif

template <typename T>
void print_call_location(
  [[maybe_unused]] const T& value,
  std::source_location where = std::source_location::current()
) {
  std::println("[{}:{}] {}", where.file_name(), where.line(), FUNCTION_SIGNATURE);
}

int main() {
  print_call_location(42);
  print_call_location(std::string{"hello"});
}
