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
  // -y is e
}

void practice_2_32() {
  printf("---practice 2.32---\n");
  int x, y;
  x = 0xffffffff;                                                      // -1
  y = 0x80000000;                                                      // -2147483648
  printf("x - y =%d - %d = %d ok? %d\n", x, y, x + y, tsub_ok(x, y));  // ok 0
  printf("y = %d\n", y);
  printf("-y = %d\n", -y);
}

void main() {
  practice_2_27();
  practice_2_30();
  practice_2_31();
  practice_2_32();
}