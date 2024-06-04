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
void main() {
  float x;
  x = 1.0;
  print_float_byte(x);  // 00 00 80 3f -> 0x3f800000 -> 0011 1111 1000 0000 0...0
  x = 1.5;
  print_float_byte(x);  // 00 00 c0 3f -> 0x3fc00000 -> 0011 1111 1100 0000 0...0
  x = 1.25;
  print_float_byte(x);  // 00 00 a0 3f -> 0x3fa00000 -> 0011 1111 1010 0000 0...0
  x = 1.125;
  print_float_byte(x);  // 00 00 90 3f -> 0x3f900000 -> 0011 1111 1001 0000 0...0
  x = 1.625;
  print_float_byte(x);  // 00 00 d0 3f -> 0x3fd00000 -> 0011 1111 1101 0000 0...0
  x = 1.375;
  print_float_byte(x);  // 00 00 b0 3f -> 0x3fb00000 -> 0011 1111 1011 0000 0...0
  x = 0.5; // 1/2
  print_float_byte(x);  // 00 00 00 3f -> 0x3f000000 -> 0011 1111 0000 0000 0...0
  x = 0.25; // 1/4
  print_float_byte(x);  // 00 00 80 3e -> 0x3e800000 -> 0011 1110 1000 0000 0...0
  x = 0.75; // 3/4
  print_float_byte(x);  // 00 00 40 3f -> 0x3f400000 -> 0011 1111 0100 0000 0...0
 
  //
}