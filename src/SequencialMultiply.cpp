#include <fstream>
#include <chrono>
#include "../include/Matrix.h"

void SequencialMultiply(Matrix *matrixA, Matrix *matrixB)
{
  std::fstream outputFile;
  outputFile.open("data/resultado_multiplicacao_sequencial.txt", std::ios::out | std::ios::binary);
  outputFile << matrixA->getRowCount() << " " << matrixB->getColumnCount() << std::endl;

  Matrix *result = new Matrix(matrixA->getRowCount(), matrixB->getColumnCount());
  auto startTime = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < result->getRowCount(); i++)
  {
    for (int j = 0; j < result->getColumnCount(); j++)
    {
      result->getData()[i][j] = 0;

      for (int k = 0; k < matrixA->getColumnCount(); k++)
      {
        result->getData()[i][j] += matrixA->getData()[i][k] * matrixB->getData()[k][j];
      }

      outputFile << "c " << i + 1 << " " << j + 1 << " " << result->getData()[i][j] << std::endl;
    }
  }

  auto endTime = std::chrono::high_resolution_clock::now();
  auto duration = endTime - startTime;

  outputFile << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  outputFile.close();
}
