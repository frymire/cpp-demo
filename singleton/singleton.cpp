
#include <iostream>
using std::cout;
using std::endl;

class Singleton {

private:

  // Prevent client code from instantiating this class by making the constructor private.
  Singleton() {}

  // Just to prove we can do it, declare a mutable private member variable. Without 
  // this, we could have just used a static function.
  char* m_message = (char*) "Hi, from the singleton.";

  // Provide the meat behind the public interface.
  void PrintMessageImpl() { cout << m_message << endl; }

public:

  // Provide access a singleton instance that is instantiated as a static variable within Get().
  static Singleton& Get() { 
    static Singleton s_instance;
    return s_instance; 
  }

  // Delete the copy constructor so you can't create a second instance like this...
  //   Singleton another_singleton = Singleton::Get();
  Singleton(const Singleton&) = delete; // C++11

  // Delete the assignment operator.
  Singleton& operator=(const Singleton&) = delete;

  // Since calling Singleton::Get() is a bit annoying, you can wrap up the ::Get()
  // into public methods that are paired with private implementation methods.
  static void PrintMessage() { return Get().PrintMessageImpl(); }
};


int main() {

  // Call methods directly on the singleton like this.
  Singleton::PrintMessage();

  // Or, make a variable to reference the singleton and treat it like any other instance.
  Singleton& s = Singleton::Get();
  s.PrintMessage();
}
