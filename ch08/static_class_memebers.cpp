#include <iostream>
#include <list>

using namespace std;

class MyVector {
 public:
  MyVector(int size);

 private:
  int vector_size;
  list<int> contents;
};

MyVector::MyVector(int size) : vector_size(size) {
  for (int i = 0; i < vector_size; ++i) {
    contents.push_back(0);
  }
}

class Matrix {
 public:
  Matrix(int row, int col);
  ~Matrix();

 private:
  int row_count;
  int col_count;
  list<MyVector*> contents;
};

Matrix::Matrix(int row, int col)
    : row_count(row), col_count(col) {
  for (int i = 0; i < row_count; ++i) {
    MyVector* new_vector = new MyVector(col_count);
    contents.push_back(new_vector);
  }
}

Matrix::~Matrix() {
  for (auto item : contents) {
    delete item;
  }
}

class LinearAlgebra {
 public:
  static void matrix_multiply(Matrix& operand1, Matrix& operand2);
  static void dot_product(MyVector& operand1, MyVector& operand2);

 private:
  static void matrix_vector_multiply(Matrix& operand1, MyVector& operand2);
};

void LinearAlgebra::matrix_multiply(Matrix& operand1, Matrix& operand2) {
  cout << "두 개의 행렬곱을 계산합니다." << endl;
}

void LinearAlgebra::matrix_vector_multiply(Matrix& operand1,
                                           MyVector& operand2) {
  cout << "행렬과 벡터의 곱을 계산합니다." << endl;
}

void LinearAlgebra::dot_product(MyVector& operand1, MyVector& operand2) {
  cout << "백터의 내적을 계산합니다." << endl;
}

void do_matrix_multiply(Matrix& matrix_1, Matrix& matrix_2) {
  LinearAlgebra::matrix_multiply(matrix_1, matrix_2);
}

void do_matrix_vector_multiply(Matrix& matrix_1, MyVector& vector_1) {}

void do_vector_innerproduct(MyVector& vector_1, MyVector& vector_2) {
  LinearAlgebra::dot_product(vector_1, vector_2);
}

int main() {
  Matrix matrix_1(10, 10), matrix_2(10, 10);
  MyVector vector_1(10), vector_2(10);

  do_matrix_multiply(matrix_1, matrix_2);
  do_matrix_vector_multiply(matrix_1, vector_2);
  do_vector_innerproduct(vector_1, vector_2);

  return 0;
}