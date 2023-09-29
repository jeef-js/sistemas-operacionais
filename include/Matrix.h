#if !defined(MATRIX_H)
#define MATRIX_H

#include <string>

class Matrix
{
private:
  int rows;
  int columns;
  int **data;

public:
  Matrix();
  Matrix(int, int);
  ~Matrix();

  void clear();

  void randomFill();

  int getRowCount();

  int getColumnCount();

  int **getData();

  std::string toString();
};

#endif // MATRIX_H
