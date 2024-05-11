#include <stdio.h>

void main() {
  int x1 = 1, y1 = 2;
  printf("x1 < y1 ? %d\n", x1 < y1);         // 1
  printf("x1 -y1 < 0 ? %d\n", x1 - y1 < 0);  // 1
  int x2 = 1;
  unsigned int y2 = 2;
  printf("x2 < y2 ? %d\n", x2 < y2);         // 1
  printf("x2 -y2 < 0 ? %d\n", x2 - y2 < 0);  // 0; bit vector of the minus number is interpreted as unsigned number.

  // unsigned addition overflow
  unsigned char a = 255, b = 255;
  unsigned char c = a + b;
  printf("c: 0x%x = %d \n", c, c);  // c: 0xfe = 254;

  // two's complement addition overflow
  int x3, y3;
  x3 = 0x80000000;                                    // -2147483648
  y3 = 0x80000000;                                    // -2147483648
  printf("x + y = %d + %d = %d\n", x3, y3, x3 + y3);  // x + y = 0

  x3 = 0xffffffff;                                    // -1
  y3 = 0x80000000;                                    // -2147483648
  printf("x + y = %d + %d = %d\n", x3, y3, x3 + y3);  // x + y = 2147483647
  // For a given word size w, the minimum value in two's complement is -2^(w-1)
  // If the sum is over this value, the overflow would yield a value which is equal
  // to x + y + 2^(w)

  x3 = 0x40000000;                                    // 1073741824
  y3 = 0x40000000;                                    // 1073741824
  printf("x + y = %d + %d = %d\n", x3, y3, x3 + y3);  // x + y = -2147483648

  x3 = 0x7fffffff;                                    // 2147483647
  y3 = 0x00000001;                                    // 1
  printf("x + y = %d + %d = %d\n", x3, y3, x3 + y3);  // x + y = -2147483648
  // For a given word size w, the maximum value in two's complement is 2^(w-1) - 1
  // If the sum is over this value, the overflow would yield a value which is equal
  // to x + y - 2^(w)

  // two's complement negation
  int x4 = 0x80000000;                    // -2147483648
  printf("-x = -(%d) = %d \n", x4, -x4);  // -2147483648

  x4 = 0x7fffffff;                        // 2147483647
  printf("-x = -(%d) = %d \n", x4, -x4);  // -2147483647; 0x80000001

  x4 = 0xfffffffa;                        // -6
  printf("-x = -(%d) = %d \n", x4, -x4);  // 6; 0x00000006
  // for x in the range (-2^(w-1), 2^(w-1)], the two's complement negation
  // is simply -x, for the case x = -2^(w-1), or x =Tmin, then the negation
  // of x is again -2^(w-1)
  // In general, -x = ~x + 1

  // tow's complement multiplication
  short x5, y5;
  x5 = 0x8000;
  y5 = 0x8000;
  // result product: 0x40000000
  printf("x * y = %hi * %hi = %hi\n", x5, y5, x5 * y5);  // x * y = 0 = 0x0000

  x5 = 0x7fff;
  y5 = 0x7fff;
  // result product: 0x3fff0001
  printf("x * y = %hi * %hi = %hi\n", x5, y5, x5 * y5);  // x * y = 1 = 0x0001

  x5 = 0x8000;
  y5 = 0x7fff;
  // result product: 0xc0008000
  printf("x * y = %hi * %hi = %hi\n", x5, y5, x5 * y5);  // x * y = -32768 = 0x8000

  x5 = 1143;
  y5 = 1987367;
  // result product: 0x87654321
  printf("x * y = %hi * %hi = %hi\n", x5, y5, x5 * y5);  // x * y = 17185 = 0x4321

  x5 = 9;
  y5 = 89;
  // result product: 0x00000321
  printf("x * y = %hi * %hi = %hi\n", x5, y5, x5 * y5);  // x * y = 801 = 0x0321
  // an overflow in multiplication of 2w bits will be simply truncated to w bits for either signed and unsigned values.
}