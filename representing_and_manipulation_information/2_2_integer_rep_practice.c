#include <limits.h>
#include <stdio.h>

void practice_2_18() {
  printf("---practice 2.18--- \n");
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

void practice_2_21() {
  printf("---practice 2.21--- \n");
  printf("INT_MAX = %d\n", INT_MAX);  // 2147483647 #define INT_MAX __INT_MAX__
  printf("INT_MIN = %d\n", INT_MIN);  // -2147483648 #define INT_MIN (-INT_MAX - 1)

  int max_i = 2147483647;      // 0x7fffffff
  int min_i = -2147483647;     // 0x80000001
  int min_i_ng = -2147483648;  // 0x80000000

  printf("%d \n", min_i - 1 == 2147483648);   // 0
  printf("%d \n", min_i - 1 == 2147483648u);  // 1
  // when comparing signed and unsigned values, the signed value will
  // be implicitly converted into unsigned

  printf("%d \n", min_i - 1 < max_i);         // 1
  printf("%d \n", min_i - 1u < max_i);        // 0; 2147483648 < 2147483647
  printf("%d \n", -2147483647 - 1u < max_i);  // 0

  printf("%d \n", min_i - 1 < min_i);         // 1
  printf("%d \n", min_i - 1u < min_i);        // 1; 0x80000000 < 0x80000001
  printf("%d \n", -2147483647 - 1u < min_i);  // 1
}

int fun1(unsigned word) {
  return (int)((word << 24) >> 24);
}
int fun2(unsigned word) {
  return ((int)word << 24) >> 24;
}
void practice_2_23() {
  printf("---practice 2.23--- \n");
  int i1, i2, i3, i4;
  i1 = 0x00000076;
  i2 = 0x87654321;
  i3 = 0x000000c9;
  i4 = 0xedcba987;
  printf("i1: f1=%d, f2=%d\n", fun1(i1), fun2(i1));  // f1=118, f2=118, 118=0x76
  printf("i2: f1=%d, f2=%d\n", fun1(i2), fun2(i2));  // f1=33, f2=33, 33=0x21
  printf("i3: f1=%d, f2=%d\n", fun1(i3), fun2(i3));  // f1=201, f2=-55, 201=0xc9, -55=0xffffffc9
  printf("i4: f1=%d, f2=%d\n", fun1(i4), fun2(i4));  // f1=135, f2=-121, 135=0x87, -121=0xffffff87
}

void main() {
  practice_2_18();
  practice_2_21();
  practice_2_23();
}