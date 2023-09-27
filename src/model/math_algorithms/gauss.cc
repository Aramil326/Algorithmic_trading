#include "gauss.h"

namespace s21 {
void Gauss::MakeForwardElimination(const Matrix& matrix) {
  int n = matrix.GetRows();
  for (int k = 0; k < n; ++k) {
    for (int j = k + 1; j < n; ++j) {
      long double m = matrix(j, k) / matrix(k, k);
      for (int i = 0; i < n + 1; ++i) {
        matrix(j, i) = matrix(j, i) - m * matrix(k, i);
      }
    }
  }
}

std::vector<long double> Gauss::MakeBackSubstitution(const Matrix& matrix) {
  int n = matrix.GetRows();
  std::vector<long double> x(n);
  for (int i = n - 1; i >= 0; --i) {
    long double solved_value = 0;
    for (int c = n - 1; c > i; --c) {
      solved_value += matrix(i, c) * x[c];
    }
    x[i] = (matrix(i, n) - solved_value) / matrix(i, i);
  }
  return x;
}

std::vector<long double> Gauss::SolveSLE(const Matrix& matrix) {
  MakeForwardElimination(matrix);
  return MakeBackSubstitution(matrix);
}
}  // namespace s21