
// Demonstrate operator overloading.
// See here: https://www.youtube.com/watch?v=mS9755gF66w&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=41

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;


class Vector2 {

  float m_x, m_y;

public:

  Vector2(float x, float y): m_x(x), m_y(y) {}

  Vector2 operator+(const Vector2& that) const { 
    return Vector2(m_x + that.m_x, m_y + that.m_y); 
  }
  
  Vector2 Add(const Vector2& that) const { 
    return operator+(that); // you can call operator functions directly
  }

  Vector2 operator*(const Vector2& that) const { 
    return Vector2(m_x * that.m_x, m_y * that.m_y); 
  }

  bool operator==(const Vector2& that) const {
    return (m_x == that.m_x) && (m_y == that.m_y);
  }

  bool operator!=(const Vector2& that) const {
    return !(*this == that);
  }

  // Providing two parameters to an operator function implies "parameter1 operator parameter2", 
  // so you can support calls like "cout << Vector2", with the following code. Declare ostream 
  // as a friend, so that it can access Vector2 private members. 
  friend ostream& operator<<(ostream& stream, const Vector2& v) {
    return stream << v.m_x << " " << v.m_y;
  }
};

int main() {

  Vector2 position(4.0f, 4.0f);
  Vector2 speed(0.5f, 1.5f);
  Vector2 powerup(1.1f, 1.1f);
  Vector2 expected(4.55f, 5.65f);
  
  // Operator order is retained: *, +, <<, ==
  cout << position + powerup*speed << endl;
  cout << (position == Vector2(4.0f, 4.0f)) << endl;
  cout << (position != Vector2(4.0f, 4.0f)) << endl;
  cout << position.Add(speed) << endl;
}
