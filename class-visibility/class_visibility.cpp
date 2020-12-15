
#include <iostream>
using std::cout;
using std::endl;

// You can declare public/private/protected multiple times to better organize class members.
class Log {
public:
  enum Level { kError, kWarning, kInfo };
private:
  Level m_log_level = kInfo;
private:
  void PrintIt(const char* label, const char* message) { cout << label << message << endl; }
public:
  void SetLevel(Level level) { m_log_level = level; }
  void Error(const char* message) { PrintIt("[ERROR]: ", message); }
  void Warn(const char* message) { PrintIt("[WARNING]: ", message); }
  void Info(const char* message) { PrintIt("[INFO]: ", message); }
};

// TODO: Friends

class Entity {
private:
  int m_private;
  void PrintPrivate() {}
protected:
  int m_protected;
  void PrintProtected() {}
public:
  int m_public;
  void PrintPublic() {}
};

// Player extends Entity
class Player: public Entity {
public:
  Player() {

    // Anyone can access public Entity data members and methods.
    m_public = 1;
    PrintPublic();

    // Player can access protected Entity data members and methods, because it extends Entity.
    m_protected = 2; 
    PrintProtected();

    // No one can access private Entity data members or methods.
    //m_private = 3;
    //PrintPrivate();
  }
};

int main() {

}
