#if !defined(PARALLEL_PROCESS_MULTIPLY_H)
#define PARALLEL_PROCESS_MULTIPLY_H

#include "../include/Matrix.h"

void partialMultiply(Matrix *, Matrix *, int, int, unsigned int, int);

void parallelMultiply(Matrix *, Matrix *, unsigned int);

#endif // PARALLEL_PROCESS_MULTIPLY_H
