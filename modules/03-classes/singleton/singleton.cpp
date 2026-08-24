
#include <iostream>
using std::cout;
using std::endl;

namespace {

  class Singleton {

  private:

    // Prevent client code from instantiating this class by making the constructor private.
    Singleton() {}

    // Just to prove we can do it, declare a mutable private member variable (m_message itself is still mutable).
    // Without this, we could have just used a static function.
    const char* m_message = "Hi, from the singleton.";

    // Provide the meat behind the public interface.
    void print_impl() const { cout << m_message << endl; }

  public:

    // Provide access a singleton instance that is instantiated as a static variable within Get().
    static Singleton& get() {
      static Singleton s_instance;
      return s_instance;
    }

    // Delete the copy constructor so you can't create a second instance as shown below. This also suppresses the
    // compiler's implicit move constructor, so you don't need to delete that explicitly.
    //   Singleton another_singleton = Singleton::Get();
    Singleton(const Singleton&) = delete; // C++11

    // Delete the assignment operator. This also suppresses the compiler's implicit move assignment operator.
    Singleton& operator=(const Singleton&) = delete;

    // Since calling Singleton::get() is a bit annoying, you can wrap up the ::get()
    // into public methods that are paired with private implementation methods.
    static void print() { return get().print_impl(); }
  };

} // namespace


int main() {

  // Call methods directly on the singleton like this.
  Singleton::print();

  // Or, make a variable to reference the singleton and treat it like any other instance.
  Singleton& s = Singleton::get();
  s.print();
}
