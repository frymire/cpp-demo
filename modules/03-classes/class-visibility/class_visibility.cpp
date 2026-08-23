// ReSharper disable CppClassNeverUsed
// ReSharper disable CppDeclaratorNeverUsed
// ReSharper disable CppEnumeratorNeverUsed
// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppRedundantAccessSpecifier

#include <iostream>
using std::cout;
using std::endl;

namespace {

  // You can declare public/private/protected multiple times to better organize class members.
  class Log {

  public:
    enum Level { kError, kWarning, kInfo };

  private:
    Level m_log_level = kInfo;

  private:
    static void print_it(const char* label, const char* message) { cout << label << message << endl; }

  public:
    void set_level(const Level level) { m_log_level = level; }
    static void error(const char* message) { print_it("[ERROR]: ", message); }
    static void warn(const char* message) { print_it("[WARNING]: ", message); }
    static void info(const char* message) { print_it("[INFO]: ", message); }
  };


  // TODO: Friends

  class Entity {

  private:
    int m_private = 10;
    void print_private() const { cout << m_private << endl; }

  protected:
    int m_protected = 20;
    void print_protected() const { cout << m_protected << endl; }

  public:
    int m_public = 30;
    void print_public() const { cout << m_public << endl; }
  };

  // Player extends Entity
  class Player : public Entity {
  public:
    Player() {

      // Anyone can access public Entity data members and methods.
      m_public = 1;
      print_public();

      // Player can access protected Entity data members and methods, because it extends Entity.
      m_protected = 2;
      print_protected();

      // No one can access private Entity data members or methods.
      // m_private = 3;  // compile error, member is inaccessible
      // print_private(); // compile error, member is inaccessible
    }
  };

}

int main() {
  Player player;
}
