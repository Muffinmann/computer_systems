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

int tmult_ok_long_long(int x, int y) {
  long long p = (long long)x * y;
  // MUST cast before the multiplication due to !!! order of operations !!! Otherwise the operation is carries out in the "int" domain first
  // and then converts to the "long long" domain.
  return p == (int)p;
}

void practice_2_36() {
  printf("---practice 2.36---\n");
  int x, y;
  x = 0x10000000;
  y = 0x00000002;
  printf("x * y = %d * %d = %d ok? %d\n", x, y, x * y, tmult_ok_long_long(x, y));  // return 1

  x = 0x80000000;
  y = 0x00000002;
  printf("x * y = %d * %d = %d ok? %d\n", x, y, x * y, tmult_ok_long_long(x, y));  // return 0
}

// for the expression x*K, it can be a computed in the form:
// (x<<n+1) - (x<<m)
// where n is the highest bit position of 1, and m the lowest (in a run of 1 bits).
// how could we modify the expression for the case where bit position n is
// the most significant bit?
void practice_2_39() {
  printf("---practice 2.39---\n");
  short x, y;
  x = 4;
  y = 0x0007;                                                                        // 7
  printf("4 * y = %hi = (4<<2+1)-(x<<0) = %hi \n", x * y, (x << 3) - (x << 0));      // 28
  y = 0xf800;                                                                        // 0b1111 1000 0000 0000 << 2 -> 0b1110 0000 0000 0000
  printf("4 * y = %hi = (4<<15+1)-(x<<11) = %hi \n", x * y, (x << 16) - (x << 11));  // 0
  printf("x << 11 = %hi \n", -(x << 11));
  // Generally, when n is the most significant bit, (x<<n+1)-(x<<m) can be modified as:
  // -(x<<m)
  // Analytically, for a bit vector of word size "w", the most significant bit has the position w-1
  // which in term leads to the form (x<<w-1+1)-(x<<m)
  // Also, by a bit vector of word size w, shift the bits to the left for "w" times leads it to be a 0-vector.
}

// For each of the following values of K,find ways to express x*K using only the
// specified number of operations,where we consider both additions and subtractions to have comparable cost.
void practice_2_40() {
  printf("---practice 2.40---\n");
  int x = 3;
  // 6 = 0b110
  printf("k= 6, shifts 2, add/sub 1: x*6 = x*(4+2) = (x<<2)+(x<<1) = %d\n", (3 << 2) + (3 << 1));
  // 31 = 0b11111
  printf("k=31, shifts 1, add/sub 1: x*31 = x*(32-1) = (x<<5)-x =%d\n", (3 << 5) - 3);
  // -6 = 0b11...11010
  printf("k=-6, shifts 2, add/sub 1: x*(-6) = x*(2-8) = (x<<1) - (x<<3) = %d\n", (3 << 1) - (3 << 3));
  // 55 = 0b110111
  printf("k=55, shifts 2, add/sub 2: x*55 = x*(64-8-1) = (x<<6)-(x<<3)-x = %d\n", (3 << 6) - (3 << 3) - 3);
}

int div16(int x) {
  // if (x < 0) {
  //   return (x + (1 << 4) - 1) >> 4;
  // }
  // return x >> 4;
  //

  // x>>31 generate a word with either all ones or zeros.
  // By masking off the appropiate bits, we get the desired bias value.
  int bias = (x >> 31) & 0xf;
  return (x + bias) >> 4;
}

void practice_2_42() {
  printf("---practice 2.42---\n");
  int x;
  printf("32 / 16 = %d\n", div16(32));    // 2
  printf("38 / 16 = %d\n", div16(38));    // 2
  printf("-31 / 16 = %d\n", div16(-31));  // -1
  printf("-33 / 16 = %d\n", div16(-38));  //-2
}

void practice_2_44() {
  printf("---practice 2.44---\n");
  int x, y;  // arbitrary value
  x = 16;
  y = -128;
  unsigned ux = x;
  unsigned uy = y;
  // For each of the following C expressions, either (1) argue that it is true (evaluates to 1)
  // for all values of x and y, or (2) give values of x and y for which it is false
  // (evaluates to 0):

  // A. (x > 0) || (x-1 < 0) -> false when x == 0x80000000, x -1 will give a positive number due to overflow
  // B. (x & 7) != 7 || (x<<29<0) -> true, 0x00000007 << 29 == 0xe0000000
  // C. (x * x) >=0 -> false when x = 0x0000fffe; x * x == 0xfffc0004 < 0
  // D. x < 0 || -x <= 0 -> true
  // E. x > 0 || -x >= 0 -> false when x = TMin, in this case -x == x < 0
  // F. x+y == uy+ux -> true, compare signed with unsigned will turn signed into unsigned, and thus equal.
  // G. x*~y + uy*ux == -x -> true, ~y = -y -1, uy*ux=x*y, thus we have x*(-y)-x+x*y
  printf("x*y=%d*%d=%d\n", x, y, x * y);
  printf("ux*uy=%u*%u=%u\n", ux, uy, ux * uy);
  printf("uy=%u\n", uy);
}

void main() {
  practice_2_27();
  practice_2_30();
  practice_2_31();
  practice_2_32();
  practice_2_36();
  practice_2_39();
  practice_2_40();
  practice_2_42();
  practice_2_44();
}