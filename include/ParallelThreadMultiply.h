#if !defined(PARALLEL_THREAD_MULTIPLY_H)
#define PARALLEL_THREAD_MULTIPLY_H

#include "../include/Matrix.h"

void partialMultiply(Matrix *, Matrix *, std::tuple<unsigned int, unsigned int>, unsigned int);

Matrix *parallelMultiply(Matrix *, Matrix *, unsigned int);

#endif // PARALLEL_THREAD_MULTIPLY_H
