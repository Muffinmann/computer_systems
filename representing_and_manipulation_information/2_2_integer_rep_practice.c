#include <stdio.h>

void practice_2_18() {
  int a, b, c, d, e, f, g, h, i, j;
  a = 0x1b8;
  b = 0x14;
  c = 0xfffffe58;  // x = [1 0000 0000] - [ffff fe58] = [0000 01a8] = 424; -x = -424
  d = 0xfffffe74;  // x = [0000018c] = 396; -x = -396
  e = 0x44;
  f = 0xfffffec8;  // x = [00000138] = 312; -x = -312
  g = 0x10;
  h = 0xc;
  i = 0xfffffeec;  // x = [00000114] = 276; -x = -276
  j = 0x20;
  printf("0x1b8 = %d \n", a);
  printf("0x14 = %d \n", b);
  printf("0xfffffe58 = %d \n", c);
  printf("0xfffffe74 = %d \n", d);
  printf("0x44 = %d \n", e);
  printf("0xfffffec8 = %d \n", f);
  printf("0x10 = %d \n", g);
  printf("0xc = %d \n", h);
  printf("0xfffffeec = %d \n", i);
  printf("0x20 = %d \n", j);
}

void main() {
  practice_2_18();
}