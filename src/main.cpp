#include <iostream>
#include <tuple>
#include "../include/Matrix.h"

using namespace std;

Matrix *buildMatrix();

int main(int argc, char const *argv[])
{
  Matrix *matrix = buildMatrix();

  cout << matrix->toString();

  return 0;
}

Matrix *buildMatrix()
{
  tuple<int, int> matrixDimensions = make_tuple(0, 0);
  int input;

  cout << "Informe a quantidade de linhas: " << endl
       << ">> ";
  cin >> input;

  get<0>(matrixDimensions) = input;

  cout << "Informe a quantidade de colunas: " << endl
       << ">> ";
  cin >> input;

  get<1>(matrixDimensions) = input;

  Matrix *matrix = new Matrix(get<0>(matrixDimensions), get<1>(matrixDimensions));
  matrix->randomFill();

  return matrix;
}