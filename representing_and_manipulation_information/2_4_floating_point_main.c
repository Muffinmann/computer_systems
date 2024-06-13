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
  int i;
  i = +0;
  print_int_byte(i);  // 00 00 00 00 -> 0x00000000 -> 0000 0000 0000 0000 0...0
  i = -0;
  print_int_byte(i);  // 00 00 00 00 -> 0x00000000 -> 0000 0000 0000 0000 0...0

  float x;
  x = +0.0;
  print_float_byte(x);  // 00 00 00 00 -> 0x00000000 -> 0000 0000 0000 0000 0...0
  x = -0.0;
  print_float_byte(x);  // 00 00 00 80 -> 0x80000000 -> 1000 0000 0000 0000 0...0
  // float number has a different bit representation for +0 and -0 with IEEE format.

  x = 5.0;              // 1.25 * 2^2
  print_float_byte(x);  // 00 00 10 40 -> 0x40a00000 -> 0100 0000 1010 0000 0...0
  // e = 100 0000 1
  // In the normalized case, the exponent value E is equal to:
  // E = e - bias = 2^7 + 1 - 127 = 2

  x = 1.625;
  print_float_byte(x);  // 00 00 d0 3f -> 0x3fd00000 -> 0011 1111 1101 0000 0...0
  x = 1.375;
  print_float_byte(x);  // 00 00 b0 3f -> 0x3fb00000 -> 0011 1111 1011 0000 0...0
  x = 0.5;              // 1/2
  print_float_byte(x);  // 00 00 00 3f -> 0x3f000000 -> 0011 1111 0000 0000 0...0
  x = 0.25;             // 1/4
  print_float_byte(x);  // 00 00 80 3e -> 0x3e800000 -> 0011 1110 1000 0000 0...0
  x = 0.75;             // 3/4
  print_float_byte(x);  // 00 00 40 3f -> 0x3f400000 -> 0011 1111 0100 0000 0...0

  //
}