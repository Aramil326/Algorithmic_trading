#include "matrix.h"

namespace s21 {

Matrix::Matrix() : Matrix(1, 1) {}

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows > 0 && cols > 0) {
    matrix_ = new long double *[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new long double[cols_]();
    }
  } else
    throw std::out_of_range("Incorrect size of matrix");
}

Matrix::Matrix(const Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
  CopyMatrixArr(other);
}

Matrix::Matrix(Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

Matrix &Matrix::operator=(const Matrix &other) {
  if (this != &other) {
    FreeMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    CopyMatrixArr(other);
  }
  return *this;
}

Matrix &Matrix::operator=(Matrix &&other) noexcept {
  FreeMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
  return *this;
}

Matrix::~Matrix() { FreeMatrix(); }

int Matrix::GetRows() const { return rows_; }

int Matrix::GetCols() const { return cols_; }

long double &Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Index is out of range");
  }
  return matrix_[row][col];
}

void Matrix::FreeMatrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

void Matrix::CopyMatrixArr(const Matrix &source) {
  if (source.matrix_ != nullptr) {
    matrix_ = new long double *[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new long double[cols_];
      std::memcpy(matrix_[i], source.matrix_[i],
                  source.cols_ * sizeof(long double));
    }
  } else {
    matrix_ = nullptr;
  }
}

void Matrix::Fill(long double value) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = value;
    }
  }
}

void Matrix::Clear() { Fill(0); }

}  // namespace s21
