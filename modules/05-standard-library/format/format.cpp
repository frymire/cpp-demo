// https://www.youtube.com/watch?v=teOe2IKGlC0&list=WL&index=2

// ReSharper disable CppUseDesignatedInitializers

#include <format>
using std::format;
using std::formatter;
using std::format_context;

#include <print>
using std::println;

#include <string>
using std::string;

#include <concepts>

namespace demo {
  namespace {

    class Point {
    public:
      Point(const int x, const int y) : m_x(x), m_y(y) {}
      [[nodiscard]] string to_string() const { return format("({}, {})", m_x, m_y); }

    private:
      int m_x, m_y;
    };

    struct Size {
      int w, h;
      [[nodiscard]] string to_string() const { return format("{} x {}", w, h); }
    };

    // The following concept and formatter, plus the specializations in namespace std, allow std::println to work
    // automatically, without to_string().

    template <class T>
    concept HasToString = requires(const T& t) {
      { t.to_string() } -> std::convertible_to<string>;
    };

    template <typename T> requires HasToString<T>
    struct TFormatter : formatter<string> {
      auto format(const T& value, format_context& context) const {
        return formatter::format(value.to_string(), context);
      }
    };

  }  // namespace
} // namespace demo

// Explicit specializations must be in namespace std.
namespace std {
  template <>
  struct formatter<demo::Point> : demo::TFormatter<demo::Point> {};

  template <>
  struct formatter<demo::Size> : demo::TFormatter<demo::Size> {};
} // namespace std

int main() {

  using demo::Point;
  using demo::Size;

  println("\npoint = {}", Point{3, 4}.to_string());
  println("size = {}", Size{1920, 1080}.to_string());

  // Add the TFormatter template and a specialization for each class to auto-convert to strings.
  println("\npoint = {}", Point{3, 4});
  println("size = {}", Size{1920, 1080});

  return 0;
}
