#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <tuple>
#include <cmath>
#include <functional>
#include <iostream>
#include "../include/ParallelThreadMultiply.h"

void partialMultiply(Matrix *matrixA, Matrix *matrixB, int *baseRow, int *baseColumn, unsigned int elementsPerThread)
{
    while (elementsPerThread > 0)
    {
        int *row = matrixA->getData()[*baseRow];
        int result = 0;

        for (int j = 0; j < matrixB->getColumnCount(); j++)
        {
            result += row[j] * matrixB->getData()[j][*baseColumn];
        }

        std::cout << "[" << *baseRow << ", " << *baseColumn << "]: " << result << std::endl;
        *baseRow == matrixA->getRowCount() - 1 ? *baseRow = 0 : ++*baseRow;
        *baseColumn == matrixB->getColumnCount() - 1 ? *baseColumn = 0 : ++*baseColumn;
        elementsPerThread--;
    }

    delete baseRow;
    delete baseColumn;
}

Matrix *parallelMultiply(Matrix *matrixA, Matrix *matrixB, unsigned int elementsPerThread)
{
    unsigned int THREADS_NUMBER = ceil((matrixA->getRowCount() * matrixB->getColumnCount()) / (double)elementsPerThread);

    std::vector<std::thread> workers;
    int baseRow = 0;
    int baseColumn = 0;

    for (int i = 0; i < THREADS_NUMBER; i++)
    {
        int *baseRowPtr = new int(baseRow);
        int *baseColumnPtr = new int(baseColumn);

        std::thread worker([&]()
                           { partialMultiply(matrixA, matrixB, baseRowPtr, baseColumnPtr, elementsPerThread); });
        workers.push_back(std::move(worker));

        baseRow = baseRow + ((elementsPerThread - baseRow) / matrixB->getColumnCount());
        baseColumn = (baseColumn + elementsPerThread) % matrixB->getColumnCount();
    }

    for (int i = 0; i < workers.size(); i++)
    {
        workers[i].join();
    }

    return nullptr;
}