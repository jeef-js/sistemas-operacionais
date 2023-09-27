#include <iostream>
#include <fstream>
#include <tuple>
#include "../include/Matrix.h"

Matrix *createNewInstance();

void buildMatrices()
{
  for (int i = 1; i <= 2; i++)
  {
    Matrix *matrix = createNewInstance();

    std::string FILE_NAME = "tmp/data-matrix_";
    FILE_NAME.append(std::to_string(i));
    FILE_NAME.append(".dat");

    std::fstream outputFile;
    outputFile.open(FILE_NAME, std::ios::out | std::ios::binary);

    if (!outputFile)
    {
      throw new std::invalid_argument("Falha ao abrir o arquivo.");
      return;
    }

    outputFile.write((char *)&matrix, sizeof(Matrix *));
    outputFile.close();
  }
}

Matrix *createNewInstance()
{
  std::tuple<int, int> matrixDimensions = std::make_tuple(0, 0);
  int input;

  std::cout << "Informe a quantidade de linhas: " << std::endl
            << ">> ";
  std::cin >> input;

  std::get<0>(matrixDimensions) = input;

  std::cout << "Informe a quantidade de colunas: " << std::endl
            << ">> ";
  std::cin >> input;

  std::get<1>(matrixDimensions) = input;

  Matrix *matrix = new Matrix(std::get<0>(matrixDimensions), std::get<1>(matrixDimensions));
  matrix->randomFill();

  return matrix;
}