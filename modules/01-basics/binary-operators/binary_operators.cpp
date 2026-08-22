
// Demonstrate bitwise and binary operators.
// See here: https://www.youtube.com/watch?v=KXwRt7og0gI&list=WL&index=46
// ...here: https://www.youtube.com/watch?v=HoQhw6_1NAA

#include <iostream>
using std::cout;
using std::endl;

#include <bitset> // represent values as bits
using std::bitset;

void print_bits(uint8_t byte) {
  cout << bitset<8>(byte) << endl;
}

int main() {

  constexpr uint8_t a = 0b00000101; // 5
  constexpr uint8_t b = 0b00001100; // 12
  cout << "a = " << static_cast<int>(a) << endl;
  cout << "b = " << static_cast<int>(b) << endl;
  cout << "a = "; print_bits(a);
  cout << "b = "; print_bits(b);

  // Bit shift left (doubles a). Disassembly shows "shl (shift left) eax, 1".
  cout << "(a << 1) = "; print_bits(a << 1); // 0000 1010

  // Three bit shifts to the left (a*(2^3) = 40)
  cout << "(a << 3) = "; print_bits(a << 3); // 0101 0000

  // Bit shift left (halves a)
  cout << "(a >> 1) = "; print_bits(a >> 1); // 0000 0010 (1) <- lost

  cout << "AND: (a & b) = "; print_bits(a & b); // 0000 0100
  cout << "OR: (a | b) = "; print_bits(a | b); // 0000 1101
  cout << "XOR: (a ^ b) = "; print_bits(a ^ b); // 0000 1001 (reports different bits)
  cout << "NOT: (~a) = "; print_bits(~a); // 1111 1010

  cout << "Get bit 5: (bool) (0b01100101 & (1 << 4)) = " << static_cast<bool>(0b01100101 & (1 << 4)); // 0
  cout << "\nGet bit 6: (bool) (0b01100101 & (1 << 5)) = " << static_cast<bool>(0b01100101 & (1 << 5)); // 1
  cout << "\nSet bit 4: 0b10100101 | (1 << 3) = "; print_bits(0b10100101 | (1 << 3));
  cout << "Clear bit position 6: 0b10100101 & ~(1 << 5) = "; print_bits(0b10100101 & ~(1 << 5));
  cout << "Clear the middle 4 bits: 0b10100101 (target) & ~0b00111100 (mask) = "; print_bits(0b10100101 & ~0b00111100);

  return 0;
}
