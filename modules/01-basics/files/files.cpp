
#pragma warning (disable : 4996) // to use potentially unsafe *scanf function

#include <iostream>
using std::cout;
using std::endl;

#include <stdio.h>

#include <memory>
using std::unique_ptr;
using std::make_unique;

#include <fstream>
using std::ifstream;

namespace {

  struct Triple {
    int x, y, z;
    void print() const { printf("%d %d %d\n", x, y, z); }
  };

  struct FileCloser { void operator()(FILE* f) const { cout << "FileCloser closing file.\n"; fclose(f); } };

}

int main() {

  // PROJECT_ROOT is defined in the top-level CMakeLists.txt file, and putting two strings together concatenates them.
  const char* path = PROJECT_ROOT "/resources/files data.txt";
  Triple t;

  cout << "\nWithout RAII...\n";
  FILE* p_file = fopen(path, "r");
  if(!p_file) {
    printf("Error opening file.\n");
    return 1;  // don't use exit(1), it doesn't unwind the stack, RAII is bypassed
  }
  while (fscanf(p_file, "%d,%d,%d", &t.x, &t.y, &t.z) == 3) { t.print(); }
  cout << "Closing file directly.\n";
  fclose(p_file);

  cout << "\nWith RAII, by overriding the unique pointer default deleter...\n";
  const unique_ptr<FILE, FileCloser> file(fopen(path, "r"));  // can't use make_unique with a custom deleter
  if(!file) {
    printf("Error opening file.\n");
    return 1;
  }
  while (fscanf(file.get(), "%d,%d,%d", &t.x, &t.y, &t.z) == 3) { t.print(); }

  cout << "\nWith ifstream, which is inherently RAII...\n";
  ifstream file_stream(path);
  if(!file_stream) {
    printf("Error opening file.\n");
    return 1;
  }
  char comma;
  while (file_stream >> t.x >> comma >> t.y >> comma >> t.z) { t.print(); }

  cout << endl;
  cout << "ifstream closes file automatically.\n";
  return 0;
}
