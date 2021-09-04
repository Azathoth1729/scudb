#include "p0_starter.h"
#include <iostream>

using namespace std;

using matrix = scudb::RowMatrix<int>;
using matrixCal = scudb::RowMatrixOperations<int>;

template <class T> void display(const scudb::Matrix<T> &mat) {
  int rows = mat.GetRowCount();
  int cols = mat.GetColumnCount();
  std::cout << "rows: " << rows;
  std::cout << " ";
  std::cout << "cols: " << cols << std::endl;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++)
      std::cout << mat.GetElement(i, j) << "\t";

    std::cout << "\n" << std::endl;
  }
}

int main() {
  matrix mat1(2, 3), mat2(3, 2), mat3(2, 2), mat4(2, 3);

  mat1.FillFrom(vector<int>{1, 2, 3, 4, 5, 6});
  mat2.FillFrom(vector<int>{0, 0, 0, 0, 0, 0});
  mat3.FillFrom(vector<int>{2, 2, 2, 2});
  mat4.FillFrom(vector<int>{2, 2, 2, 2, 2, 2});

  std::cout << "initialization..." << std::endl << std::endl ;
  display(mat1);
  display(mat2);
  display(mat3);

  std::cout << "---------------------------------------------------" << std::endl;
  std::cout << "calculating..." << std::endl << std::endl ;
  display(*matrixCal::Add(&mat1, &mat4));
  display(*matrixCal::Multiply(&mat1, &mat2));
  display(*matrixCal::GEMM(&mat1, &mat2, &mat3));
  return 0;
}