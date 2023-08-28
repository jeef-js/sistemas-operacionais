#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 3
#define COLS 3

struct Matrix
{
  int rows;
  int cols;
  int **data;
  void (*show)(struct Matrix *);
  void (*randomFill)(struct Matrix *);
};

void printMatrix(struct Matrix *matrix)
{
  for (int i = 0; i < matrix->rows; i++)
  {
    for (int j = 0; j < matrix->cols; j++)
    {
      printf("%d ", matrix->data[i][j]);
    }
    
    printf("\n");
  }
}

void randomFillMatrix(struct Matrix *matrix)
{
  srand(time(NULL) + clock());

  for (int i = 0; i < matrix->rows; i++)
  {
    for (int j = 0; j < matrix->cols; j++)
    {
      matrix->data[i][j] = rand() % 100;
    }
  }
}

struct Matrix *newMatrix(int rows, int cols)
{
  struct Matrix *matrix = (struct Matrix *)malloc(sizeof(struct Matrix));
  matrix->rows = rows;
  matrix->cols = cols;
  matrix->data = (int **)malloc(rows * sizeof(int *));
  matrix->show = &printMatrix;
  matrix->randomFill = &randomFillMatrix;

  for (int i = 0; i < rows; i++)
  {
    matrix->data[i] = (int *)malloc(cols * sizeof(int));
  }

  return matrix;
}

struct Matrix *multiply(struct Matrix *matrixA, struct Matrix *matrixB)
{
  if (matrixA->cols != matrixB->rows)
  {
    printf("Não é possível multiplicar as matrizes.");
  }

  struct Matrix *resultMatrix = newMatrix(matrixA->rows, matrixB->cols);

  for (int i = 0; i < resultMatrix->rows; i++)
  {
    for (int j = 0; j < resultMatrix->cols; j++)
    {
      resultMatrix->data[i][j] = 0;
      for (int k = 0; k < matrixA->cols; k++) {
        resultMatrix->data[i][j] += matrixA->data[i][k] * matrixB->data[k][j];
      }
    }
  }

  return resultMatrix;
}

int main(int argc, char const *argv[])
{
  struct Matrix *matrixA = newMatrix(ROWS, COLS);
  struct Matrix *matrixB = newMatrix(ROWS, COLS);

  matrixA->randomFill(matrixA);
  matrixB->randomFill(matrixB);

  printf("Matriz A:\n");
  matrixA->show(matrixA);
  printf("\n");

  printf("Matriz B:\n");
  matrixB->show(matrixB);
  printf("\n");

  struct Matrix *matrixResult = multiply(matrixA, matrixB);

  printf("Matriz Resultante:\n");
  matrixResult->show(matrixResult);
  printf("\n");

  return 0;
}
