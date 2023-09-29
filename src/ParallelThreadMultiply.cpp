#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <tuple>
#include <cmath>
#include <functional>
#include <iostream>
#include "../include/ParallelThreadMultiply.h"

void partialMultiply(Matrix *matrixA, Matrix *matrixB, int baseRow, int baseColumn, unsigned int elementsPerThread, int threadIndex)
{
  std::fstream outputFile;
  std::string FILE_NAME = "data/resultado_multiplicacao_paralela_";
  FILE_NAME.append(std::to_string(threadIndex));
  FILE_NAME.append(".txt");
  outputFile.open(FILE_NAME, std::ios::out | std::ios::binary);
  outputFile << matrixA->getRowCount() << " " << matrixB->getColumnCount() << std::endl;

  auto startTime = std::chrono::high_resolution_clock::now();
  while (elementsPerThread > 0)
  {
    int *row = matrixA->getData()[baseRow];
    int result = 0;

    for (int j = 0; j < matrixB->getRowCount(); j++)
    {
      result += row[j] * matrixB->getData()[j][baseColumn];
    }

    outputFile << "c " << baseRow + 1 << " " << baseColumn + 1 << " " << result << std::endl;

    if (baseColumn == matrixB->getColumnCount() - 1)
    {
      baseColumn = 0;
      ++baseRow;

      if (baseRow == matrixA->getRowCount())
      {
        break;
      }
    }
    else
    {
      ++baseColumn;
    }

    elementsPerThread--;
  }

  auto endTime = std::chrono::high_resolution_clock::now();
  auto duration = endTime - startTime;

  outputFile << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  outputFile.close();
}

void parallelMultiply(Matrix *matrixA, Matrix *matrixB, unsigned int elementsPerThread)
{
  unsigned int THREADS_NUMBER = ceil((matrixA->getRowCount() * matrixB->getColumnCount()) / (double)elementsPerThread);

  std::vector<std::thread> workers;
  int baseRow = 0;
  int baseColumn = 0;

  for (int i = 0; i < THREADS_NUMBER; i++)
  {
    std::thread worker(partialMultiply, matrixA, matrixB, baseRow, baseColumn, elementsPerThread, i + 1);
    workers.push_back(std::move(worker));

    for (int i = 0; i < elementsPerThread; i++)
    {
      if (baseColumn == matrixB->getColumnCount() - 1)
      {
        baseColumn = 0;
        ++baseRow;
        continue;
      }

      ++baseColumn;
    }
  }

  for (int i = 0; i < workers.size(); i++)
  {
    workers[i].join();
  }
}
