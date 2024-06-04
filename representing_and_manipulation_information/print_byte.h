#ifndef PRINT_BYTE_H
#define PRINT_BYTE_H

#include <stdio.h>

typedef unsigned char *byte_pointer;

void print_byte(byte_pointer start, int len);
void print_float_byte(float x);

#endif // PRINT_BYTE_H
