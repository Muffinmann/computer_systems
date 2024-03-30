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

void main() {
  int i1, i2;
  i1 = 1;
  i2 = 2;
  show_addr(i1);  // print 0x7ffd11a9542c
  show_addr(i2);  // print 0x7ffd11a9542c
  // The two functions print the same address because show_addr creates a local
  // copy for the argument, and inside the function, the printf actually prints
  // the address of that copy.

  show_addr_ptr(&i1);  // print 0x7ffd11a95440
  show_addr_ptr(&i2);  // print 0x7ffd11a95444
  // In this case, instead creating a copy, the variable is passed directly to
  // the show_addr_ptr function, thus different addresses.

  printf("Print Address in main: %p \n", (void *)&i1);
  printf("Print Address in main:  %p \n", (void *)&i2);

  void *p1;
  void *p2;
  p1 = &i1;
  p2 = &i2;
  show_pointer(p1);  // print 40 54 a9 11 fd 7f 00 00
  show_pointer(p2);  // print 44 54 a9 11 fd 7f 00 00
  // 8 bytes, little endian since run program on a 64-bit x86 machine.
  // data type int take places 4 bytes in C, thus 40 + 4 = 44.

  int i3 = 1039;  // 1024 + 15; 4 bytes: 0000 0000 0000 0000 0000 0100 0000 1111
  int i4 = 11;
  char *ptr1 = (char *)&i3;
  int *ptr2 = &i3;
  printf("array[0] notation ptr1 value of i3: %d\n", ptr1[0]);  // prints 15
  printf("array[1] notation ptr1 value of i3: %d\n", ptr1[1]);  // prints 4
  printf("array[2] notation ptr1 value of i3: %d\n", ptr1[2]);  // prints 0
  printf("array[3] notation ptr1 value of i3: %d\n", ptr1[3]);  // prints 0
  printf("array[4] notation ptr1 value of i3: %d\n", ptr1[4]);  // prints 11 (value of "i4")
  printf("array[0] notation ptr2 value of i3: %d\n", ptr2[0]);  // prints 1039
  printf("array[1] notation ptr2 value of i3: %d\n", ptr2[1]);  // prints 11
  // In C, we can dereference a pointer with array notation.
  // Array notation (ptr[i]) allows us to access the value at an offset from the memory location pointed to by a pointer.
  // (The value of a pointer in C is the virtual address of the FIRST BYTE of some block of storage!!!)
  // This allows to navigate through memory. (That's why ptr1[4] refers to "i4")

  printf("ptr1 value of i3: %d\n", *ptr1);  // prints 15
  printf("ptr2 value of i3: %d\n", *ptr2);  // prints 1039
  // By assign the type of a pointer, we determine how many bytes are accessed when dereferencing it.
}