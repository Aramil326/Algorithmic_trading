#ifndef UNTITLED_CUBIC_SPLINE_H
#define UNTITLED_CUBIC_SPLINE_H

#include <cmath>

#include "../../libs/qcustomplot/qcustomplot.h"
#include "../matrix/matrix.h"

namespace s21 {
class CubicSpline {
 public:
  explicit CubicSpline(const QVector<QCPGraphData> &source_data);
  QVector<QCPGraphData> GetPredictedData(int number_of_points);
  double GetPredictedValue(const QDateTime &date_time);

 private:
  QVector<QCPGraphData> source_data_;
  QVector<QCPGraphData> delta_;
  Matrix spline_coefficients_;

  void SetSplineCoefficients();
  void CalcACoefficients();
  void CalcBCoefficients();
  void CalcCCoefficients();
  void CalcDCoefficients();
  void CalculateDelta();
  double GetY(double x);
};

}  // namespace s21

#endif  // UNTITLED_CUBIC_SPLINE_H
