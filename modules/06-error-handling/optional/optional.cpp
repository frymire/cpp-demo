
// Demo optional data (C++17).
// See here: https://www.youtube.com/watch?v=UAAiwObNhQ0&list=WL&index=24

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <string>
using std::string;
using std::getline;

#include <optional>
using std::optional;

optional<string> ReadFileAsString(const string & filepath) {

  ifstream stream(filepath);

  if (stream) { // or more explicitly, stream.is_open()
    string line;
    string result;

    while (getline(stream, line)) { 
      result += line;
      result += "\n";
    }
    stream.close();
    return result; // return valid data as usual
  }

  return {}; // empty optional, like None in Scala.
}


void PrintData(optional<string> data) {

  if (data) { // or more explicitly, data.has_value()
    cout << "File read successfully. Printing three ways...\n\n";
    cout << data.value() << endl;
    cout << *data << endl;
  } else {
    cout << "File could not be opened.\n";
  }

  // Can also get the data, if it's there, or use a default.
  cout << data.value_or("[no data]") << endl;
}

int main() {

  optional<string> data = ReadFileAsString("../resources/optional data.txt");
  PrintData(data);
  cout << endl;

  optional<string> missing_data = ReadFileAsString("missing_data.txt");
  PrintData(missing_data);
}
