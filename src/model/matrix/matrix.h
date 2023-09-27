#ifndef TRADING_SRC_MODEL_MATRIX_MATRIX
#define TRADING_SRC_MODEL_MATRIX_MATRIX
#include <cmath>
#include <cstring>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

namespace s21 {
class Matrix {
 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix &other);
  Matrix(Matrix &&other) noexcept;
  Matrix &operator=(const Matrix &other);
  Matrix &operator=(Matrix &&other) noexcept;
  ~Matrix();

  [[nodiscard]] int GetRows() const;
  [[nodiscard]] int GetCols() const;

  void Fill(long double value);
  void Clear();

  long double &operator()(int row, int col) const;

 private:
  int rows_, cols_;
  long double **matrix_;
  void FreeMatrix();
  void CopyMatrixArr(const Matrix &source);
};

}  // namespace s21

#endif  // TRADING_SRC_MODEL_MATRIX_MATRIX
