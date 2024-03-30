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

void main() {
  practice_2_5();
  practice_2_6();
  practice_2_7();
  practice_2_10();
  practice_2_11();
}