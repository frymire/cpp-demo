// https://www.youtube.com/watch?v=Vz40rDiWnN8&list=WL&index=4

#include <iostream>
using std::cout;

#include <expected>
using std::expected;
using std::unexpected;

#include <string>
using std::string;

namespace {

    expected<int, string> divide(const int a, const int b) {
        if (b == 0) { return unexpected("Division by zero."); }
        return a / b;
    }

    expected<int, string> handle_error(const string& error) {
        cout << "error: " << error << "\n";
        return expected<int, string>({0});  // return default value
    }

}  // namespace

int main() {

    {
        cout << "\nExpected result...\n";
        expected<int, string> /*auto*/ result = divide(10, 3);
        if (!result) { result = handle_error(result.error()); }
        cout << "result: " << *result << "\n";
    }

    {
        cout << "\nUnexpected result...\n";
        auto result = divide(10, 0);
        if (!result) { result = handle_error(result.error()); }
        cout << "result: " << *result << "\n";
    }

    {
        cout << "\nMore succinctly...\n";
        cout << "result: " << *divide(10, 3).or_else(handle_error) << "\n";
        cout << "result: " << *divide(10, 0).or_else(handle_error) << "\n";
    }

    {
        cout << "\nChain multiple operations: 24 / 3 / 4...\n";
        const auto result = divide(24, 3)
         .and_then([](const int x) { return divide(x, 4); })
         .or_else(handle_error);
        cout << "result: " << *result << "\n";
    }

    return 0;
}
