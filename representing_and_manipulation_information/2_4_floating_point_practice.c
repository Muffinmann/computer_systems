#include <stdio.h>

// approximate 0.1 with x = 0.00011001100110011001100
void practice_2_46() {
  // the difference 0.1 - x = 0.0......011[0011]... // binary representation
  //                            |- 23 -|
  // takes the first two 1s into account, the delta is 3/(2^25)
  // more precisely, this is 0.1>>20 (23 - 3 = 20 where 3 is the length of 0s before first 1)
  // Since this is a delta of 0.1s, for 100 hours, the delta will become
  // 100 * 60 * 60 * 10 * (3/(2^23))
  // this is approximately 0.322 seconds
  // for a speed of 2000m/s, this difference will lead to an error of 644m
  printf("%f\n", (float)(100 * 60 * 60 * 10 * 3) / (1 << 25));  // 0.321865
}

// A. For a floating-point format with an n-bit fraction, give a formula for the
// smallest positive integer that cannot be represented exactly (because it
// would require an n+1-bit fraction to be exact). Assume the exponent field
// size k is large enough that the range of representable exponents does not
// provide a limitation for this problem.
// B. What is the numeric value of this integer for single-precision format (n =23)?
void practice_2_49() {
  printf("---practice 2.49---\n");
  // A trailing zero is ignored, so this is the number 1 0....0 1 where the length of zeros is n.
  // which equals 2^(n+1) + 1
  // when n = 23, N = 2 ^(23 + 1) + 1 = 16777217
}

// Assume variables x, f, and d are of type int, float, and double, respectively.
// Their values are arbitrary, except that neither f nor d equals +∞, −∞, or NaN.
// For each of the following C expressions, either argue that it will always be true
// (i.e., evaluate to 1) or give a value for the variables such that it is not true (i.e.,
// evaluates to 0).
// A. x == (int)(double) x
// B. x == (int)(float) x
// C. d == (double)(float) d
// D. f == (float)(double) f
// E. f == -(-f)
// F. 1.0/2 == 1/2.0
// G. d*d >= 0.0
// H. (f+d)-f == d
void practice_2_54() {
  printf("---practice 2.54---\n");
  int x;
  float f;
  double d;
  // B is not true when x is 
  x = 2147483647;// TMax = (1 << 31) - 1;
  printf("x = %d\n",x);
  printf("(float)x = %a\n", (float)x); // 0x1p+31
  printf("(int)(float)x=%d\n", (int)(float)x); // -2147483648

}

void main() {
  practice_2_46();
  practice_2_54();
}