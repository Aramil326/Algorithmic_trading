#ifndef TRADING_SRC_MODEL_POLYNOMIAL_APPROXIMATION
#define TRADING_SRC_MODEL_POLYNOMIAL_APPROXIMATION

#include <vector>

#include "../../libs/qcustomplot/qcustomplot.h"
#include "../matrix/matrix.h"
#include "model/math_algorithms/gauss.h"

namespace s21 {
class PolynomialApproximation {
 public:
  explicit PolynomialApproximation(const QVector<QCPGraphData> &input_data);

  QVector<QCPGraphData> GetPredictedData(int polynomial_degree,
                                         int number_of_points,
                                         int predict_days);
  double GetPredictedValue(const QDateTime &date_time, int polynomial_degree);

 private:
  QVector<QCPGraphData> input_data_;
  double scaling_shift_;
  int current_polynomial_degree_;
  std::vector<long double> polynomial_coefficients_;

  void ShiftDate();
  QVector<QCPGraphData> CalcPredictedData(int number_of_points,
                                          int predict_days);
  double CalcPredictedValue(double x_current);
  void CheckPolynomialDegree(int polynomial_degree);
  std::vector<long double> GetPolynomialCoefficients(int polynomial_degree);
  void PrepareSLE(Matrix &SLE);
};

}  // namespace s21

#endif  // TRADING_SRC_MODEL_POLYNOMIAL_APPROXIMATION
