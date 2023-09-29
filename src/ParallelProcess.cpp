#include <iostream>
#include <fstream>
#include <string>
#include "../include/Matrix.h"
#include "../include/MatrixBuilder.h"
#include "../include/ParallelProcessMultiply.h"

using namespace std;

int main(int argc, char const *argv[])
{
  buildMatrix(std::stoi(argv[1]), std::stoi(argv[2]), 1);
  buildMatrix(std::stoi(argv[3]), std::stoi(argv[4]), 2);

  int elementsPerProcess = std::stoi(argv[5]);

  Matrix *matrixA = new Matrix();

  fstream inputFile;
  inputFile.open("tmp/data-matrix_1.dat", ios::in | ios::binary);
  inputFile.read((char *)&matrixA, sizeof(Matrix *));
  inputFile.close();

  Matrix *matrixB = new Matrix();

  inputFile.open("tmp/data-matrix_2.dat", ios::in | ios::binary);
  inputFile.read((char *)&matrixB, sizeof(Matrix *));
  inputFile.close();

  parallelMultiply(matrixA, matrixB, elementsPerProcess);

  return 0;
}
