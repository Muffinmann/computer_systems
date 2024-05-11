#include <stdio.h>

// determine whether arguments can be added without overflow
int uadd_ok(unsigned x, unsigned y) {
  if (x + y < x) {
    return 0;
  }
  return 1;
}
void practice_2_27() {
  printf("---practice 2.27---\n");
  printf(" ok? %d\n", uadd_ok(0xffffffff, 0x1));  // 0
  printf(" ok? %d\n", uadd_ok(0xf, 0x1));         // 1
}

// determine whether arguments can be added without overflow
int tadd_ok(int x, int y) {
  int sum = x + y;
  if (x < 0 && y < 0) {
    if (sum >= 0) {
      return 0;
    }
    return 1;
  }
  // x >= 0 || y >=0
  if (sum < 0) {
    return 0;
  }
  return 1;
}
void practice_2_30() {
  printf("---practice 2.30---\n");
  int x, y;
  x = 0x80000000;
  y = 0x80000000;
  printf("%d + %d -> ok? %d\n", x, y, tadd_ok(x, y));  // 0

  x = 0xffffffff;
  y = 0x80000000;
  printf("%d + %d -> ok? %d\n", x, y, tadd_ok(x, y));  // 0

  x = 0x70000000;
  y = 0x70000000;
  printf("%d + %d -> ok? %d\n", x, y, tadd_ok(x, y));  // 0

  x = 0x10000000;
  y = 0x10000000;
  printf("%d + %d -> ok? %d\n", x, y, tadd_ok(x, y));  // 1
}

int tadd_ok_buggy(int x, int y) {
  int sum = x + y;
  return (sum - x == y) && (sum - y == x);
  // This check will fail since subtraction will essentially revert the overflow (abelian group)
  // and leads the condition to always be true.
  // In other words:
  // when overflow happens, the sum(w+1 bits length) is either +2^(w) or -2^(w), and in both case, it is equal to +0 or -0
  // since we have only w bits length.
}
void practice_2_31() {
  printf("---practice 2.31---\n");
  int x, y;
  x = 0x80000000;
  y = 0x80000000;
  printf("x + y = %d + %d = %d ok? %d\n", x, y, x + y, tadd_ok_buggy(x, y));  // 1

  x = 0xffffffff;
  y = 0x80000000;
  printf("x + y = %d + %d = %d ok? %d\n", x, y, x + y, tadd_ok_buggy(x, y));  // 1

  x = 0x00000001;
  y = 0x7fffffff;
  printf("x + y = %d + %d =%d ok? %d\n", x, y, x + y, tadd_ok_buggy(x, y));  // 1
}

// Determine whether arguments can be subtracted (x-y) without overflow
int tsub_ok(int x, int y) {
  return tadd_ok(x, -y);
  // This check will fail if y is equal to -2^(w-1), since in this case
  // -y is equal to y, and tadd_ok would return 0 for any x < 0 since
  // negative overflow happens within the function.
  // But in fact, x - y does not overflow for these cases.
}

void practice_2_32() {
  printf("---practice 2.32---\n");
  int x, y;
  x = 0xffffffff;                                                      // -1
  y = 0x80000000;                                                      // -2147483648
  printf("x - y =%d - %d = %d ok? %d\n", x, y, x - y, tsub_ok(x, y));  // ok 0
  printf("y = %d\n", y);
  printf("-y = %d\n", -y);
}

// Determine whether arguments can be multiplied without overflow
int tmult_ok(int x, int y) {
  int p = x * y;
  // Either x is zero, or dividing p by x gives y
  return !x || p / x == y;
}

void practice_2_35() {
  // Prove that the function "tmult_ok" can use DIVISION to test overflow (while subtraction cannot, see practice_2_31):
  // 1. In case of x == 0 || y == 0, then the p is also 0, no overflow; Either x == 0 and the function directly returns 1
  // or y == 0 and p/x = 0 / x = 0 which also returns 1.
  //
  // 2. The product of x and y has a length of 2w-bits, and is written as "z". (This is not "p" ! Because of different bit length)
  // we can decompose the number into two parts, a unsigned number by the lower w-bits, and a signed number
  // by the upper w-bits:
  // z_(2w-1), ......, z_(w+1), z_w, z_(w-1), ......, z_1, z_0
  // |<------upper w-bits--------->| |<-------lower w-bits--->|
  // and we use "v" to represent the number of upper w-bits, and "u" to represent the number of the lower w-bits.
  // We know that by shifting the bits of a number i-times to the left is equal to multiply the number with 2^(i).
  // so we can write:
  // z = v*(2^w) + u
  // where u has the same bit pattern as "p".
  // We also know that converting an signed number to unsigned number:
  // T2U_2(x) = x_(w-1)*(2^w) + x
  // we can write:
  // u = p_(w-1)*(2^w) + p
  // which leads to:
  // z = v*(2^w) + p_(w-1)*(2^w) + p = (v + p_(w-1)) *(2^w) + p = t*(2^w) + p
  // from this equation, we can see that when t != 0, x*y !== p, thus it overflows.
  // and when t ==0, x*y == p, thus id does not overflow.
  //
  // 3. we know that p divided by x can be written as: p/x = p mod x + r, where r is the remainder and |r| < |x|
  // In other words, we have:
  // p = x*q + r, where q is the quotient
  // which leads to:
  // z = x*y = t*(2^w) + x*q + r
  //
  // 4. suppose q = y, we then have:
  // x*y = x*y + r + t*(2^w)
  // this equation only holds when r+t*(2^w) = 0, which means r = -t*(2^w).
  // Since r is the remainder and |r| < |x|, |r| = |-t*(2^w)| < |x| <= 2^w only holds when r=t=0.
  // suppose r=t=0,  then we have x*y = x*q, which implies y = q.
}

void main() {
  practice_2_27();
  practice_2_30();
  practice_2_31();
  practice_2_32();
}