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
  // This check will fail since subtraction will essentially revert the overflow
  // and leads the condition to always be true.
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
  return !x || p/x == y;
  // We can't use subtraction to test whether addition has overflowed (see function tadd_ok_buggy).
  // But we can use division to test whether multiplication has overflowed. This is because:
  // 1. In case of x == 0 || y == 0, then the p is also 0, no overflow; Either x == 0 and the function directly returns 1
  // or y == 0 and p/x = 0 / x = 0 which also returns 1.
  //
  // 2.
}

void main() {
  practice_2_27();
  practice_2_30();
  practice_2_31();
  practice_2_32();
}