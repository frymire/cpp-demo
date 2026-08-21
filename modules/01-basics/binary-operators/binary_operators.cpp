
// Demonstrate bitwise and binary operators.
// See here: https://www.youtube.com/watch?v=KXwRt7og0gI&list=WL&index=46
// ...here: https://www.youtube.com/watch?v=HoQhw6_1NAA

#include <iostream>
using std::cout;
using std::endl;

#include <bitset> // represent values as bits
using std::bitset;

int main(void) {

  unsigned int a = 0b00000101; // 5
  unsigned int b = 0b00001100; // 12
  cout << "a = " << bitset<8>(a) << endl;
  cout << "b = " << bitset<8>(b) << endl;

  // Bit shift left (doubles a). Disassembly shows "shl (shift left) eax, 1".
  cout << "(a << 1) = " << bitset<8>(a << 1) << endl; // 0000 1010

  // Three bit shifts to the left (a*(2^3) = 40)
  cout << "(a << 3) = " << bitset<8>(a << 3) << endl; // 0101 0000

  // Bit shift left (halves a)
  cout << "(a >> 1) = " << bitset<8>(a >> 1) << endl; // 0000 0010 (1) <- lost

  cout << "AND: (a & b) = " << bitset<8>(a & b) << endl; // 0000 0100
  cout << "OR: (a | b) = " << bitset<8>(a | b) << endl; // 0000 1101
  cout << "XOR: (a ^ b) = " << bitset<8>(a ^ b) << " (reports different bits)" << endl; // 0000 1001
  cout << "NOT: (~a) = " << bitset<8>(~a) << endl; // 1111 1010

  cout << "Get bit position 4 (zero-based): (bool) (0b01100101 & (1 << 4)) = " << (bool) (0b01100101 & (1 << 4)) << endl; // 0
  cout << "Get bit position 5 (zero-based): (bool) (0b01100101 & (1 << 5)) = " << (bool) (0b01100101 & (1 << 5)) << endl; // 1
  cout << "Set bit position 4: 0b10100101 | (1 << 3) = " << bitset<8>(0b10100101 | (1 << 3)) << endl;
  cout << "Clear bit position 6: 0b10100101 & ~(1 << 5) = " << bitset<8>(0b10100101 & ~(1 << 5)) << endl;
  cout << "Clear the middle 4 bits: 0b10100101 (target) & 0b11000011 (mask) = " << bitset<8>(0b10100101 & 0b11000011) << endl;  
}
