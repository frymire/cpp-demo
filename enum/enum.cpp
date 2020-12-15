
#include <iostream>
using std::cout;
using std::endl;

// Default is to number from zero...
enum Level { Error, Warning, Info }; // 0, 1, 2
void PrintLevel(Level level) { cout << level << endl; }

// Set a non-zero starting point like this...
enum FiveBasedIntEnum { X = 5, Y, Z }; // 5, 6, 7

// Can use a different type (here an 8-bit char, rather than 32-bit int)
enum CharEnum: char { i1 = 'M', i2 = 'E', i3 = 'F' };


int main() {

  Level value1 = Info;
  cout << value1 << endl;
  cout << (value1 == 1) << endl;
  cout << (value1 == Warning) << endl;
  //PrintLevel(1); // compile error
  PrintLevel(Level::Info);
  cout << endl;

  FiveBasedIntEnum value2 = Y;
  cout << value2 << endl;
  cout << (value2 == 6) << endl;
  cout << (value2 == Y) << endl;
  cout << endl;

  CharEnum value3 = i3;
  cout << i3 << endl;
  cout << (i3 == 'E') << endl;
  cout << (i3 == 'F') << endl;
  cout << endl;
}
