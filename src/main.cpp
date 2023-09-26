#include <iostream>
#include "../include/Matrix.h"

int main(int argc, char const *argv[])
{
  Matrix *matrix = new Matrix(3, 3);
  matrix->randomFill();

  std::cout << matrix->toString();

  return 0;
}
