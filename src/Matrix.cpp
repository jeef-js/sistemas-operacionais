#include "../include/Matrix.h"
#include <cstdlib>

Matrix::Matrix(int rows, int columns)
{
  this->rows = rows;
  this->columns = columns;

  this->data = new int *[rows];

  for (int i = 0; i < this->rows; i++)
  {
    this->data[i] = new int[columns];
  }
}

Matrix::~Matrix()
{
  clear();
}

void Matrix::clear()
{
  this->rows = 0;
  this->columns = 0;

  for (int i = 0; i < this->rows; i++)
  {
    delete[] this->data[i];
  }

  this->data = nullptr;
}

void Matrix::randomFill()
{
  for (int i = 0; i < this->rows; i++)
  {
    srand((unsigned)time(NULL));

    for (int j = 0; j < this->columns; j++)
    {
      this->data[i][j] = rand();
    }
  }
}

int Matrix::getRowCount()
{
  return this->rows;
}

int Matrix::getColumnCount()
{
  return this->columns;
}

int **Matrix::getData()
{
  return this->data;
}

std::string Matrix::toString()
{
  std::string matrix_str;

  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->columns; j++)
    {
      matrix_str.append(std::to_string(this->data[i][j]));
      j == this->columns - 1 ? matrix_str.append("\r\n") : matrix_str.append(",");
    }
  }

  return matrix_str;
}