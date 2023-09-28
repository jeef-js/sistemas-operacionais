#include <iostream>
#include <fstream>
#include <tuple>
#include "../include/Matrix.h"
#include "../include/MatricesBuilder.h"
#include "../include/ParallelThreadMultiply.h"

using namespace std;

int main(int argc, char const *argv[])
{
  cout << "Iniciando geração de matrizes" << endl;

  buildMatrices();

  cout << "Matrizes geradas com sucesso." << endl;

  cout << "Lendo a primeira matriz..." << endl;

  Matrix *matrixA = new Matrix();

  fstream inputFile;
  inputFile.open("tmp/data-matrix_1.dat", ios::in | ios::binary);
  inputFile.read((char *)&matrixA, sizeof(Matrix *));
  inputFile.close();

  cout << "Leitura finalizada." << endl
       << "====== Matriz A ======" << endl
       << matrixA->toString() << endl
       << "====================" << endl;

  cout << "Lendo a segunda matriz..." << endl;

  Matrix *matrixB = new Matrix();

  inputFile.open("tmp/data-matrix_2.dat", ios::in | ios::binary);
  inputFile.read((char *)&matrixB, sizeof(Matrix *));
  inputFile.close();

  cout << "Leitura finalizada." << endl
       << "====== Matriz B ======" << endl
       << matrixB->toString() << endl
       << "====================" << endl;

  cout << "Efetuando multiplicação..." << endl;

  Matrix *matrixC = (*matrixA) * (*matrixB);

  cout << "====== Matriz C ======" << endl
       << matrixC->toString() << endl
       << "====================" << endl;

  Matrix *matrixD = parallelMultiply(matrixA, matrixB, 8);

  // cout << "====== Matriz D ======" << endl
  //      << matrixD->toString() << endl
  //      << "====================" << endl;

  return 0;
}
