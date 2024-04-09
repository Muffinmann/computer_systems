#include <stdio.h>

void main() {
  int x1 = 1, y1 = 2;
  printf("x1 < y1 ? %d\n", x1 < y1);         // 1
  printf("x1 -y1 < 0 ? %d\n", x1 - y1 < 0);  // 1
  int x2 = 1;
  unsigned int y2 = 2;
  printf("x2 < y2 ? %d\n", x2 < y2);         // 1
  printf("x2 -y2 < 0 ? %d\n", x2 - y2 < 0);  // 0; bit vector of the minus number is interpreted as unsigned number.

  unsigned char a = 255, b = 255;
  unsigned char c = a + b;
  printf("c: 0x%x = %d \n", c, c);  // c: 0xfe = 254;
}