#include "../include/Matrix.h"

Matrix *Matrix::operator*(const Matrix &other)
{
  Matrix *result = new Matrix(this->rows, other.columns);

  for (int i = 0; i < result->rows; i++)
  {
    for (int j = 0; j < result->columns; j++)
    {
      result->data[i][j] = 0;
      for (int k = 0; k < this->columns; k++)
      {
        result->data[i][j] += this->data[i][k] * other.data[k][j];
      }
    }
  }

  return result;
}