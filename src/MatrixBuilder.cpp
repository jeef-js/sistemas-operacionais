#include <iostream>
#include <fstream>
#include <tuple>
#include <chrono>
#include "../include/Matrix.h"
#include "../include/MatrixBuilder.h"

void buildMatrix(unsigned int rows, unsigned int cols, int id)
{
  Matrix *matrix = new Matrix(rows, cols);
  matrix->randomFill();

  std::string FILE_NAME = "tmp/data-matrix_";
  FILE_NAME.append(std::to_string(id));
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
