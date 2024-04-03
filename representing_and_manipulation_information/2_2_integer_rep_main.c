#include <stdio.h>

void main() {
  char c0 = 0x00;  // 0000 0000
  char c1 = 0x7f;  // 0111 1111
  char c2 = 0x80;  // 1000 0000
  char c3 = 0xff;  // 1111 1111

  // first bit is the sign bit
  printf("signed \n");
  printf("%d \n", c0);  // 0
  printf("%d \n", c1);  // 127
  printf("%d \n", c2);  // -128
  printf("%d \n", c3);  // -1
  // signed number in represented as two's-complement form. It interprets
  // the most significant bit of the word to have negative weight.
  // 0xff -> -1*2^7 + 1*2^6 + 1*2^5 + ... + 1*2^0.
  //
  // The term "two's complement" arises from the fact that for nonnegative x, we compute a
  // w-bit representation of -x as 2^w - x.
  // For example, when w = 4, the number "3" is represented as [0011], the number "-3" is
  // represented as [1101] which is exactly equal to [10000] - [0011].
  //
  // More about negative number in binary form:
  // If we represent [00...0] as +0, [11...1] as -0, then for any nonnegative number x
  // we can compute -x as [11...1]-x.
  // For example, +1 is represented as [0001] and -1 is represented as [1000]
  // This approach is called "Ones' Complement".
  //
  // Or, we can use the most significant bit to determine whether the remaining bits should
  // be given negative or positive.
  // This is to say, we use [00...0] and [10...0] to represent +0 and -0 respectively.
  // The number "3" can be represented as [0011] and the number "-3" is [1011].
  // This approach is called "Sign-Magnitude"
  //
  // The drawback of the last two approaches is clear, that they have two different encodings
  // of the number 0.

  unsigned char uc0 = 0x00;  // 0000 0000
  unsigned char uc1 = 0x7f;  // 0111 1111
  unsigned char uc2 = 0x80;  // 1000 0000
  unsigned char uc3 = 0xff;  // 1111 1111
  short int i = 0xfffa;      // 1111 1111 1111 1010
  unsigned short int ui = 0xfffa;

  printf("unsigned \n");
  printf("%u \n", uc0);  // 0
  printf("%u \n", uc1);  // 127
  printf("%d \n", uc2);  // 128
  printf("%d \n", uc3);  // 255
  printf("%d \n", i);    // -6
  printf("%u \n", ui);   // 65530

  // By changing from unsigned to singed with two's complement, the weight of the first
  // bit has been changed from 2^(w-1) to -2^(w-1), which leads to a difference of 2^w.
  // For example, for a word size of 16-bit(short int), 65530 becomes -6, 65535 becomes -1.

  // Question: How C truncates a value by type conversion
  int v = 0x12345678;
  short int sv = v;
  int j = sv;

  printf("%x \n", v);   // 12345678
  printf("%x \n", sv);  // 5678
  printf("%x \n", j);   // 5678
  // Answer: Seems the high-order bits are discarded.

  int x = -1;
  unsigned u = 2147483648;
  printf("x = %u = %d\n", x, x);
  printf("u = %u = %d\n", u, u);
}