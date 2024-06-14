#include <math.h>
#include <stdio.h>

typedef unsigned char *byte_pointer;

void print_byte(byte_pointer start, int len) {
  int i;
  for (i = 0; i < len; i++) {
    printf(" %.2x", start[i]);
  }
  printf("\n");
}

void print_float_byte(float x) {
  print_byte((byte_pointer)&x, sizeof(float));
}

void print_int_byte(int x) {
  print_byte((byte_pointer)&x, sizeof(int));
}
void main() {
  float x;

  //
  // normalized values
  //
  x = 5.0;              // 1.25 * 2^2
  print_float_byte(x);  // 00 00 a0 40 -> 0x40a00000 -> 0100 0000 1010 0000 0...0
  // e = 100 0000 1
  // In the normalized case (e is neither all zeros nor all ones), the exponent value E is equal to:
  // E = e - bias = 2^7 + 1 - 127 = 2
  // For single floating-point numbers, the exponent ranges from [-126, 127]
  // fractional value 0100...0 -> binary point representation: 0.0100...0
  // M = 1 + f = 1 + 1/4 = 1.25
  // This is an "implied leading 1" representation, because we can view M to be the number with binary representation:
  // 1.f_(n-1)f_(n-2).....f_1f_0
  // This is a trick for getting an additional bit of precision for free, since we can always adjust the exponent E so that
  // significand M is in the range [1, 2), assuming there is no overflow.
  // Thus it's not necessary to explicitly represent the leading bit. (always equals 1)

  //
  // denormalized values
  //
  x = 0x0.cp-126;
  print_float_byte(x);  // 00 00 60 00 -> 0000 0000 0110 0000 0...0 = 0.25 * 2 ^(-126)
  printf("%a\n", x);    // 0x1.8p-127
  // In this case, E = 1 - bias and M = f (without an implied leading 1)

  x = +0.0;
  print_float_byte(x);  // 00 00 00 00 -> 0x00000000 -> 0000 0000 0000 0000 0...0
  x = -0.0;
  print_float_byte(x);  // 00 00 00 80 -> 0x80000000 -> 1000 0000 0000 0000 0...0
  // float number has a different bit representation for +0 and -0 with IEEE format.
  int i;
  i = +0;
  print_int_byte(i);  // 00 00 00 00 -> 0x00000000 -> 0000 0000 0000 0000 0...0
  i = -0;
  print_int_byte(i);  // 00 00 00 00 -> 0x00000000 -> 0000 0000 0000 0000 0...0
  // for integer, the bit vectors are equal

  //
  // Special values
  //
  x = INFINITY;
  // when the fraction field is all zeros
  print_float_byte(x);  // 00 00 80 7f -> 0x7f800000 -> 0111 1111 1000 0000 0...0

  x = NAN;
  // when the fraction field it nonzero
  print_float_byte(x);  // 00 00 c0 7f -> 0x7fc00000 -> 0111 1111 1100 0000 0...0
  //
}