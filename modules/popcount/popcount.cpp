#include <iostream>

using std::cout;
using std::endl;
using std::hex;
using std::dec;

#if defined(_MSC_VER)
#include <intrin.h>
#else
#include <bit> // C++20 popcount (optional)
#include <cstdint>
#endif

unsigned short popcount16(unsigned short x) {
#if defined(_MSC_VER)
  return __popcnt16(x);
#else
  return __builtin_popcount(x); // safe: promoted to int
#endif
}

unsigned int popcount32(unsigned int x) {
#if defined(_MSC_VER)
  return __popcnt(x);
#else
  return __builtin_popcount(x);
#endif
}

int main() {
  unsigned short uShortValues[3] = {0, 0xFF, 0xFFFF};
  for (int i = 0; i < 3; ++i) {
    unsigned short r = popcount16(uShortValues[i]);
    cout << "popcount16(0x" << hex << uShortValues[i] << ") = " << dec << r << endl;
  }

  unsigned int uIntValues[4] = {0, 0xFF, 0xFFFF, 0xFFFFFFFF};
  cout << endl;
  for (int i = 0; i < 4; ++i) {
    unsigned int r = popcount32(uIntValues[i]);
    cout << "popcount32(0x" << hex << uIntValues[i] << ") = " << dec << r << endl;
  }

  return 0;
}
