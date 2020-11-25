
#include <iostream> 
#include <intrin.h> 
using std::cout;
using std::endl;
using std::hex;
using std::dec;

int main() {

  unsigned short uShortResult;
  unsigned short uShortValues[3] = {0, 0xFF, 0xFFFF};
  for (int i = 0; i < 3; i++) {
    uShortResult = __popcnt16(uShortValues[i]);
    cout << "__popcnt16(0x" << hex << uShortValues[i] << ") = " << dec << uShortResult << endl;
  }

  unsigned int uIntResult;
  unsigned int uIntValues[4] = {0, 0xFF, 0xFFFF, 0xFFFFFFFF};
  cout << endl;
  for (int i = 0; i < 4; i++) {
    uIntResult = __popcnt(uIntValues[i]);
    cout << "__popcnt(0x" << hex << uIntValues[i] << ") = " << dec << uIntResult << endl;
  }
}
