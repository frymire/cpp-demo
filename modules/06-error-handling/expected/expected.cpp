// https://www.youtube.com/watch?v=Vz40rDiWnN8&list=WL&index=4

#include <expected>
#include <iostream>

std::expected<int, std::string> divide(int a, int b) {
    if (b == 0) { return std::unexpected("Division by zero."); }
    return a / b;
}

std::expected<int, std::string> handle_error(const std::string& error) {
    std::cout << "error: " << error << "\n";
    return std::expected<int, std::string>({0});
}

int main() {

    auto result1 = divide(10, 2);
    if (!result1) { std::expected<int, std::string> default_value = handle_error(result1.error()); }
    std::cout << "result: " << *result1 << "\n";

    auto result2 = divide(24, 3)
      .and_then([](int result) { return divide(result, 4); })  // chain multiple operations
      .or_else(handle_error);
    std::cout << "result: " << *result2 << "\n";

    return 0;
}
