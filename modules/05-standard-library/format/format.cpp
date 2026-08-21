// https://www.youtube.com/watch?v=teOe2IKGlC0&list=WL&index=2

#include <format>
#include <print>
#include <string>
#include <concepts>

template <class T>
concept HasToString = requires(const T& t) {
    { t.to_string() } -> std::convertible_to<std::string>;
};

template<typename T> requires HasToString<T>
struct TFormatter : std::formatter<std::string> {
    auto format(const T& value, std::format_context& context) const {
        return std::formatter<std::string>::format(value.to_string(), context);
    }
};

namespace demo {

    class Point {
    public:
        Point(int x, int y) : x_(x), y_(y) {}
        [[nodiscard]] std::string to_string() const { return std::format("({}, {})", x_, y_); }
    private:
        int x_, y_;
    };

    struct Size {
        int w, h;
        [[nodiscard]] std::string to_string() const { return std::format("{} x {}", w, h); }
    };

} // namespace demo

// Explicit specializations must be in namespace std.
namespace std {
    template <>
    struct formatter<demo::Point> : TFormatter<demo::Point> {};
    template <>
    struct formatter<demo::Size> : TFormatter<demo::Size> {};
} // namespace std

int main() {

    std::println("\npoint = {}", demo::Point{3, 4}.to_string());
    std::println("size  = {}", demo::Size{1920, 1080}.to_string());

    // Add the TFormatter template and a specialization for each class to auto-convert to strings.
    std::println("\npoint = {}", demo::Point{3, 4});
    std::println("size  = {}", demo::Size{1920, 1080});

    return 0;
}
