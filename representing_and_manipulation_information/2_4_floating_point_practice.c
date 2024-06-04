#include <stdio.h>

// approximate 0.1 with x = 0.00011001100110011001100
void practice_2_46(){
  // the difference 0.1 - x = 0.0......011[0011]... // binary representation
  //                            |- 23 -|
  // takes the first two 1s into account, the delta is 3/(2^25)
  // more precisely, this is 0.1>>20 (23 - 3 = 20 where 3 is the length of 0s before first 1)
  // Since this is a delta of 0.1s, for 100 hours, the delta will become
  // 100 * 60 * 60 * 10 * (3/(2^23))
  // this is approximately 0.322 seconds
  // for a speed of 2000m/s, this difference will lead to an error of 644m
  printf("%f\n", (float)(100*60*60*10*3)/(1<<25)); // 0.321865
}

void main() {
  practice_2_46();
}