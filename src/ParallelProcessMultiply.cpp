#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <tuple>
#include <iostream>
#include <cmath>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/ParallelProcessMultiply.h"

void partialMultiply(Matrix *matrixA, Matrix *matrixB, int baseRow, int baseColumn, unsigned int elementsPerProcess, int processIndex)
{
  std::fstream outputFile;
  std::string FILE_NAME = "data/resultado_multiplicacao_paralela_processos_";
  FILE_NAME.append(std::to_string(processIndex));
  FILE_NAME.append(".txt");
  outputFile.open(FILE_NAME, std::ios::out | std::ios::binary);
  outputFile << matrixA->getRowCount() << " " << matrixB->getColumnCount() << std::endl;

  auto startTime = std::chrono::high_resolution_clock::now();
  while (elementsPerProcess > 0)
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

    elementsPerProcess--;
  }

  auto endTime = std::chrono::high_resolution_clock::now();
  auto duration = endTime - startTime;

  outputFile << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  outputFile.close();
}

void parallelMultiply(Matrix *matrixA, Matrix *matrixB, unsigned int elementsPerProcess)
{
  unsigned int PROCESSES_NUMBER = ceil((matrixA->getRowCount() * matrixB->getColumnCount()) / (double)elementsPerProcess);

  int baseRow = 0;
  int baseColumn = 0;

  for (int i = 0; i < PROCESSES_NUMBER; i++)
  {
    pid_t child_pid = fork();

    if (child_pid == 0)
    {
      partialMultiply(matrixA, matrixB, baseRow, baseColumn, elementsPerProcess, i + 1);
      exit(0);
    }
    else if (child_pid < 0)
    {
      std::cerr << "Fork failed." << std::endl;
      exit(1);
    }

    for (int i = 0; i < elementsPerProcess; i++)
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
}
