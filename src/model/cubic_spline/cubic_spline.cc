#include "cubic_spline.h"

namespace s21 {

CubicSpline::CubicSpline(const QVector<QCPGraphData>& source_data)
    : source_data_(source_data) {
  CalculateDelta();
  SetSplineCoefficients();
}

void CubicSpline::SetSplineCoefficients() {
  spline_coefficients_ = Matrix(source_data_.size() - 1, 4);
  CalcCCoefficients();
  CalcACoefficients();
  CalcBCoefficients();
  CalcDCoefficients();
}

void CubicSpline::CalcACoefficients() {
  for (int i = 0; i < source_data_.size() - 1; ++i) {
    spline_coefficients_(i, 0) = source_data_[i].value;
  }
}

void CubicSpline::CalcBCoefficients() {
  int size = spline_coefficients_.GetRows();
  for (int i = 0; i < size - 1; ++i) {
    spline_coefficients_(i, 1) =
        (delta_[i].value / delta_[i].key) -
        1 / 3. * delta_[i].key *
            (spline_coefficients_(i + 1, 2) + 2 * spline_coefficients_(i, 2));
  }
  spline_coefficients_(size - 1, 1) =
      (delta_.back().value / delta_.back().key) -
      2 / 3. * delta_.back().key * spline_coefficients_(size - 1, 2);
}

void CubicSpline::CalcCCoefficients() {
  int i, j;
  long double h, h_prev, r;
  int n = spline_coefficients_.GetRows();
  std::vector<long double> k(n, 0);
  std::vector<long double> l(n, 0);
  for (i = 1; i < n; ++i) {
    j = i - 1;
    h = delta_[i].key;
    h_prev = delta_[j].key;
    r = 2 * (h + h_prev) - h_prev * l[j];
    l[i] = h / r;
    k[i] =
        (3 * (delta_[i].value / h - delta_[j].value / h_prev) - h_prev * k[j]) /
        r;
  }
  spline_coefficients_(n - 1, 2) = k.back();
  for (i = n - 2; i >= 1; i--) {
    spline_coefficients_(i, 2) = k[i] - l[i] * spline_coefficients_(i + 1, 2);
  }
}

void CubicSpline::CalcDCoefficients() {
  int size = spline_coefficients_.GetRows();
  for (int i = 0; i < size - 1; ++i) {
    spline_coefficients_(i, 3) =
        (spline_coefficients_(i + 1, 2) - spline_coefficients_(i, 2)) /
        (3 * delta_[i].key);
  }
  spline_coefficients_(size - 1, 3) =
      (0 - spline_coefficients_(size - 1, 2)) / (3 * delta_.back().key);
}

QVector<QCPGraphData> CubicSpline::GetPredictedData(int number_of_points) {
  QVector<QCPGraphData> result(number_of_points);
  double x_first = source_data_.front().key;
  double x_last = source_data_.back().key;
  double step = (x_last - x_first) / (number_of_points - 1);
  for (int i = 0; i < number_of_points - 1; ++i) {
    double x_current = x_first + step * i;
    result[i].key = x_current;
    result[i].value = GetY(x_current);
  }
  result[result.size() - 1].key = x_last;
  result[result.size() - 1].value = source_data_.last().value;
  return result;
}

double CubicSpline::GetPredictedValue(const QDateTime& date_time) {
  auto epoch_time = static_cast<double>(date_time.toSecsSinceEpoch());
  return GetY(epoch_time);
}

void CubicSpline::CalculateDelta() {
  delta_.resize(source_data_.size() - 1);
  for (int i = 0; i < source_data_.size() - 1; ++i) {
    delta_[i].key = source_data_[i + 1].key - source_data_[i].key;
    delta_[i].value = source_data_[i + 1].value - source_data_[i].value;
  }
}

double CubicSpline::GetY(double x) {
  double result = 0;
  int i = 0;
  while (x > source_data_[i + 1].key) {
    i++;
  }
  for (int degree = 0; degree < 4; ++degree) {
    result += pow((x - source_data_[i].key), degree) *
              spline_coefficients_(i, degree);
  }
  return result;
}

}  // namespace s21
