#include <fstream>
#include <chrono>
#include <thread>
#include <functional>
#include <vector>
#include "../include/Matrix.h"

void partialMultiply(int firstRow, int rowNumber)
{

}

Matrix *parallelMultiply(Matrix *matrixA, Matrix *matrixB)
{
    int THREADS_NUMBER = 8;
    int LINES_PER_THREAD[THREADS_NUMBER];

    int index = 0;

    for (int i = 0; i < matrixA->getRowCount(); i++)
    {
        ++LINES_PER_THREAD[index];
        index == 5 ? index = 0 : ++index;
    }

    std::vector<std::thread> workers;

    int firstRow = 0;

    for (int i = 0; i < THREADS_NUMBER; i++)
    {
        std::thread worker(std::bind(partialMultiply ,firstRow, LINES_PER_THREAD[i]));
        firstRow += LINES_PER_THREAD[i];
    }

    for (int i = 0; i < workers.size(); i++)
    {
        workers[i].join();
    }


//   std::fstream outputFile;
//   outputFile.open("data/resultado_multiplicacao_sequencial.txt", std::ios::out | std::ios::binary);
//   outputFile << this->rows << " " << other.columns << std::endl;

//   Matrix *result = new Matrix(this->rows, other.columns);
//   auto startTime = std::chrono::high_resolution_clock::now();

//   for (int i = 0; i < result->rows; i++)
//   {
//     for (int j = 0; j < result->columns; j++)
//     {
//       result->data[i][j] = 0;
//       for (int k = 0; k < this->columns; k++)
//       {
//         result->data[i][j] += this->data[i][k] * other.data[k][j];
//       }

//       outputFile << "c" << i + 1 << j + 1 << " " << result->data[i][j] << std::endl;
//     }
//   }

//   auto endTime = std::chrono::high_resolution_clock::now();
//   auto duration = endTime - startTime;

//   outputFile << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms";
//   outputFile.close();

  return nullptr;
}