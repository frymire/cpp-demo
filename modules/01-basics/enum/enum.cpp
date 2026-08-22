
// ReSharper disable CppEnumeratorNeverUsed

#include <iostream>
using std::cout;
using std::endl;

namespace {

  void print_bool(bool b) { cout << (b ? "true" : "false") << endl; }

  // Default is to number from zero...
  enum UnscopedLevel { Error, Warning, Info };  // 0, 1, 2
  void print_level(const UnscopedLevel level) { cout << level << endl; }

  // Set a non-zero starting point like this...
  enum XYZ { X = 2, Y, Z };  // 2, 3, 4

  // Can use a different type (here an 8-bit char, rather than 32-bit int)
  enum CharEnum: char { i1 = 'M', i2 = 'E', i3 = 'F' };

  // Unscoped enums leak all values into the surrounding scope. Use "enum class" to enforce scopes.
  // enum LogTarget { Console, File, Error };  // compile error: Error is already declared.
  enum class Level { Error, Warning, Info };
  void print_level(const Level level) { cout << static_cast<int>(level) << endl; }  // must explicitly cast to int
}


int main() {

  constexpr UnscopedLevel unscoped_level = Info;
  cout << unscoped_level << endl;
  cout << (unscoped_level == 1) << endl;
  cout << (unscoped_level == Warning) << endl;
  // print_level(1);  // compile error
  print_level(Info);

  cout << "\nCompare two unrelated enums...\n";
  if (unscoped_level == XYZ::X) { cout << "Works, but a compile error would be better.\n"; }

  cout << "\nEnum with non-default values...\n";
  constexpr XYZ value2 = Y;
  cout << value2 << endl;
  cout << (value2 == 6) << endl;
  cout << (value2 == Y) << endl;

  cout << "\nChar based enum...\n";
  [[maybe_unused]] CharEnum value3 = i3;
  cout << i3 << endl;
  cout << (i3 == 'E') << endl;
  cout << (i3 == 'F') << endl;

  cout << "\nUsing enum classes to enforce scope...\n";
  // Level level = Error;  // compile error, enum classes require scopes
  Level level = Level::Error;
  print_level(Level::Info);
  // print_bool(level == unscoped_level);  // compile error, can't compare across scopes
  print_bool(level == Level::Error);  // compile error, can't compare across scopes

  return 0;
}
