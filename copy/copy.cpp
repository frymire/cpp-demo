
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

struct Vector2 { 
  float x, y;  
  void Print() { cout << x << " " << y << endl; }
};

class MyString {

private: 
  
  char* m_buffer;
  unsigned int m_size;

public:

  MyString(const char* string) {
    m_size = strlen(string);
    m_buffer = new char[m_size + 1];
    memcpy(m_buffer, string, m_size);
    m_buffer[m_size] = 0;
  }

  // The implicit copy constructor makes a shallow copy of the member variables. It would look like...
  //MyString(const MyString& that): m_buffer(that.m_buffer), m_size(that.m_size) {}

  // You could delete the copy constructor to prevent copies altogether.
  //MyStringNoCopy(const MyString& that) = delete;

  // Deep copy constructor.
  MyString(const MyString& that): m_size(that.m_size) {
    m_buffer = new char[m_size + 1];
    memcpy(m_buffer, that.m_buffer, m_size);
    m_buffer[m_size] = 0;
    cout << "Copied MyString instance.\n";
  }

  ~MyString() { delete[] m_buffer; }

  // If a shallow copied MyString instance goes out of scope after the destructor is called on any 
  // previous instance, the delete[] call would cause an error. Break the link to avoid that.
  void ClearBufferLink() { m_buffer = nullptr; }

  char& operator[](unsigned int index) { return m_buffer[index]; }

  friend ostream& operator<<(ostream& stream, const MyString& string) {
    return stream << string.m_buffer;
  }
};

// If you call a function with MyString as a pass-by-value parameter, the copy constructor 
// is called. Pass by reference to avoid that when possible.
void PrintByValue(MyString string) { cout << string << endl; }
void PrintByReference(const MyString& string) { cout << string << endl; }

int main() {

  Vector2 a1 = {1, 2};
  Vector2 b1 = a1; // copy
  b1.x = 5;
  a1.Print(); // still 1 2

  Vector2* a2 = new Vector2({1, 2});
  Vector2* b2 = a2; // copies address of a2 to b2
  b2->x = 5;
  a2->Print(); // now 5 2

  cout << "\nMake a string...\n";
  MyString original = "Mark";
  cout << original << endl;

  cout << "\nMake a copy...\n";
  MyString copy = original; // compile error if copy constructor is deleted

  // With the default copy constructor, declaring a second string that copies
  // the original only copies the primitive member variables. That gives us two pointers 
  // to the data created on the heap for m_buffer. Updating the buffer memory via either 
  // variable will be reflected when accessing via the other.
  cout << "\nChange the data via the copy...\n";
  copy[1] = 'o';
  cout << original << endl; // Mark, but the default copy constructor would say Mork
  cout << copy << endl; // Mork

  cout << "\nPass by value...\n";
  PrintByValue(original);
  cout << "\nPass by reference...\n";
  PrintByReference(original);

  // If we were using the default copy constructor, the data created on the heap for 
  // original.m_buffer gets deleted when the destructor is called by original. The subsequent 
  // destructor call by copy would be deleting invalid memory. Set the m_buffer point to 
  // nullptr to avoid that.
  //copy.ClearBufferLink();
}
