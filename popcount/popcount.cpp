
#include <iostream> 
#include <intrin.h> 
using std::cout;
using std::endl;
using std::hex;
using std::dec;

// Compute the popcount using the Visual Studio compilier intrinsic functions.
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

/* 
  TODO: add macros to compile the correct intrinsic for each compiler (GCC below vs. MSVC above).

#include <stdio.h>
#include <stdlib.h>

// https://www.geeksforgeeks.org/builtin-functions-gcc-compiler/
int builtin()
{
    int num = 4;
    int clz = 0;
    int ctz = 0;
    int pop = 0;
    int parity = 0;

    pop = __builtin_popcount(num);
    printf("Number of ones in %d is %d\n", num, pop);

    parity = __builtin_parity(num);
    printf("Parity of %d is %d\n", num, parity);

    clz = __builtin_clz(num);
    printf("Number of leading zeroes in %d is %d\n", num, clz);

    // It only works for unsigned values
    clz = __builtin_clz(-num);
    printf("Number of leading zeroes in %d is %d\n", -num, clz);

    ctz = __builtin_ctz(num);
    printf("Number of trailing zeroes in %d is %d\n", num, ctz);

    return 0;
}

*/
