#include <stdio.h>
#include <string.h>

typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, int len) {
  int i;
  for (i = 0; i < len; i++) {
    printf(" %.2x", start[i]);
  }
  printf("\n");
}

void show_int(int x) {
  printf("size of int = %lu \n", sizeof(int));
  show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x) {
  printf("size of float = %lu \n", sizeof(float));
  show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x) {
  printf("size of pointer = %lu \n", sizeof(void *));
  show_bytes((byte_pointer)&x, sizeof(void *));
}

void show_addr(int x) { printf("Var Copy Address %p \n", (void *)&x); }
void show_addr_ptr(int *x) { printf("Pointer Address %p \n", x); }

void practice_2_5() {
  printf("---practice 2.5--- \n");
  int val = 0x87654321;  // assign binary value with hexadecimal representation
  byte_pointer valp = (byte_pointer)&val;
  show_bytes(valp, 1);  // prints 21 in little endian machine, 87 in big endian machine.
  show_bytes(valp, 2);  // little endian: 21 43, big endian: 87 65
  show_bytes(valp, 3);  // little endian: 21 43 65, big endian: 87 65 43
}

void practice_2_6() {
  printf("---practice 2.6--- \n");
  int value = 3510593;
  show_int(value);    // 0x00359141 -> 0000 0000 0011 0101 1001 0001 0100 0001 => 0000 0000 001 101011001000101000001
                      // Matching part                                                          |||||||||||||||||||||
  show_float(value);  // 0x4a564504 -> 0100 1010 0101 0110 0100 0101 0000 0100 =>     010010100 101011001000101000001 00
}

void practice_2_7() {
  printf("---practice 2.7--- \n");
  const char *s = "abcdef";
  show_bytes((byte_pointer)s, strlen(s));  // 61 62 63 64 65 66; ASCII Code
}

// There is no performance advantage to this way of swapping.
void inplace_swap(int *x, int *y) {
  *y = *x ^ *y;
  *x = *x ^ *y;
  *y = *x ^ *y;
}

void practice_2_10() {
  printf("---practice 2.10--- \n");
  printf("Inplace swap \n");
  printf("a     b \n");
  printf("a     a^b \n");
  printf("a^a^b a^b \n");
  printf("0^b   0^b^a^b \n");
  printf("b     a \n");
}

void reverse_array(int a[], int cnt) {
  int first, last;
  for (first = 0, last = cnt - 1; first <= last; first++, last--) {
    inplace_swap(&a[first], &a[last]);
  }
}

void reverse_array_modified(int a[], int cnt) {
  int first, last;
  // for odd length cnt=2k + 1, due to its own additive inverse (a ^ a = 0)
  // simply ignore the middle element where first == last
  for (first = 0, last = cnt - 1; first < last; first++, last--) {
    inplace_swap(&a[first], &a[last]);
  }
}

void practice_2_11() {
  printf("---practice 2.11--- \n");
  int a1[] = {1, 2, 3, 4};
  int b1[] = {1, 2, 3, 4, 5};
  reverse_array(a1, 4);
  reverse_array(b1, 5);
  for (int i = 0; i < 4; i++) {
    printf("%d ", a1[i]);
  }
  printf("\n");

  for (int i = 0; i < 5; i++) {
    printf("%d ", b1[i]);
  }
  printf("\n");

  int a2[] = {1, 2, 3, 4};
  int b2[] = {1, 2, 3, 4, 5};
  reverse_array_modified(a2, 4);
  reverse_array_modified(b2, 5);
  for (int i = 0; i < 4; i++) {
    printf("%d ", a2[i]);
  }
  printf("\n");

  for (int i = 0; i < 5; i++) {
    printf("%d ", b2[i]);
  }
  printf("\n");
}

// The least significant byte of x, with all other bits set to 0
int mask_least_significant_byte(int x) {
  int mask = 0xff;
  return mask & x;
}

// All but the least significant byte of x complemented, with the
// least significant byte left unchanged.
int mask_least_significant_byte_left_complemented(int x) {
  int mask = 0xff;
  int least_significant_byte = mask & x;
  int left_of_least_significant_byte_complemented = ~mask & ~x;
  return left_of_least_significant_byte_complemented | least_significant_byte;
}

//  The least significant byte set to all 1s, and all other bytes of x left unchanged.
int mask_least_significant_byte_one(int x) {
  int mask = 0xff;
  return x | mask;
}

void practice_2_12() {
  printf("---practice 2.12--- \n");
  int x = 0x87654321;
  show_int(mask_least_significant_byte(x));                    // 21 00 00 00
  show_int(mask_least_significant_byte_left_complemented(x));  // 21 bc 9a 78
  show_int(mask_least_significant_byte_one(x));                // ff 43 65 87
}

// setting z to 1 at each bit position where m is 1
int bis(int x, int m) {
  return x | m;
};

// setting z to 0 at each bit position where m is 1
int bic(int x, int m) {
  return x & ~m;
};

// compute x|y and x^y using only calls to functions bis and bic
/*
 * A  B  A_bis  A_bic  B_bis  B_bic  OR  XOR
   0  0  0      0      0      0      0   0
   0  1  1      0      1      1      1   1
   1  0  1      1      1      0      1   1
   1  1  1      0      1      0      1   0
*/
// from the table, easy to see XOR is an OR operation on A_bic and B_bic
// which itself if identical to bis.

int bool_or(int x, int y) {
  int result = bis(x, y);
  return result;
}

int bool_xor(int x, int y) {
  int result = bis(bic(x, y), bic(y, x));
  return result;
}

void practice_2_13() {
  printf("---practice 2.13--- \n");
  int x = 0b1101;
  int y = 0b1001;
  int res_or = bool_or(x, y);
  int res_xor = bool_xor(x, y);
  show_int(res_or);   // 0d 00 00 00 -> 1101
  show_int(res_xor);  // 04 00 00 00 -> 0100
}

// Using only bit-level and logical operations, write a C expression that is equivalent
// to x == y. In other words, it will return 1 when x and y are equal, and 0 otherwise.
int equal(int x, int y) {
  return !(x ^ y);
}

void practice_2_15() {
  int res1 = equal(13, 13);
  int res2 = equal(11, 13);
  printf("res1 is equal: %d \n", res1);
  printf("res2 is equal: %d \n", res2);
}

void main() {
  practice_2_5();
  practice_2_6();
  practice_2_7();
  practice_2_10();
  practice_2_11();
  practice_2_12();
  practice_2_13();
  practice_2_15();
}