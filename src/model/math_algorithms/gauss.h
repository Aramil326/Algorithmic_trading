#ifndef TRADING_SRC_MODEL_MATH_ALGORITHMS_GAUSS
#define TRADING_SRC_MODEL_MATH_ALGORITHMS_GAUSS
#include <vector>

#include "model/matrix/matrix.h"
namespace s21 {

class Gauss {
 public:
  static std::vector<long double> SolveSLE(const Matrix& matrix);

 private:
  static void MakeForwardElimination(const Matrix& matrix);
  static std::vector<long double> MakeBackSubstitution(const Matrix& matrix);
};

}  // namespace s21

#endif  // TRADING_SRC_MODEL_MATH_ALGORITHMS_GAUSS
