#include <iostream>
#include <fstream>
#include <tuple>
#include "../include/Matrix.h"

using namespace std;

Matrix *buildMatrix();

int main(int argc, char const *argv[])
{
  for (int i = 1; i <= 2; i++) {
    Matrix *matrix = buildMatrix();

    std::string FILE_NAME = "tmp/data-matrix_";
    FILE_NAME.append(to_string(i));
    FILE_NAME.append(".dat");
    
    fstream outputFile;
    outputFile.open(FILE_NAME, ios::out | ios::binary);

    if (!outputFile)
    {
      throw new invalid_argument("Falha ao abrir o arquivo.");
      return 1;
    }

    outputFile.write((char*) &matrix, sizeof(Matrix*));
    outputFile.close();
  }

  // fstream inputFile;
  // inputFile.open("tmp/data-matrix.dat", ios::in | ios::binary);
  // inputFile.read((char*) &readedMatrix, sizeof(Matrix*));
  // inputFile.close();

  // cout << readedMatrix->toString();

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