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
  x = 2.0;
  print_float_byte(x);  // 00 00 00 40 -> 0x40000000 -> 0100 0000 0000 0000 0...0
  x = 4.0;
  print_float_byte(x);  // 00 00 80 40 -> 0x40800000 -> 0100 0000 1000 0000 0...0
  x = 8.0;
  print_float_byte(x);  // 00 00 00 41 -> 0x41000000 -> 0100 0001 0000 0000 0...0
  x = 16.0;
  print_float_byte(x);  // 00 00 80 41 -> 0x41800000 -> 0100 0001 1000 0000 0...0
  x = 32.0;
  print_float_byte(x);  // 00 00 00 42 -> 0x42000000 -> 0100 0010 0000 0000 0...0
  x = 128.0;
  print_float_byte(x);  // 00 00 00 43 -> 0x43000000 -> 0100 0011 0000 0000 0...0

  x = 1.1;
  print_float_byte(x);  // cd cc 8c 3f -> 0x3f8ccccd -> 0011 1111 1000 1100 1100 1100 1100 1101
  x = 2.2;
  print_float_byte(x);  // cd cc 0c 40 -> 0x400ccccd -> 0100 0000 0000 1100 1100 1100 1100 1101
  x = 4.4;
  print_float_byte(x);  // cd cc 8c 40 -> 0x408ccccd -> 0100 0000 1000 1100 1100 1100 1100 1101
  x = 8.8;
  print_float_byte(x);  // cd cc 0c 41 -> 0x410ccccd -> 0100 0001 0000 1100 1100 1100 1100 1101
  x = 16.16;
  print_float_byte(x);  // ae 47 81 41 -> 0x418147ae -> 0100 0001 1000 0001 0100 0111 1010 1110
  x = 32.32;
  print_float_byte(x);  // ae 47 01 42 -> 0x420147ae -> 0100 0010 0000 0001 0100 0111 1010 1110
  x = 128.128;
  print_float_byte(x);  // c5 20 00 43 -> 0x430020c5 -> 0100 0011 0000 0000 0010 0000 1100 0101
}