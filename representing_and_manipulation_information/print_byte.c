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
