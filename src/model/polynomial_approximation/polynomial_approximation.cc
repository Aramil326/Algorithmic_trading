#include "polynomial_approximation.h"

namespace s21 {
PolynomialApproximation::PolynomialApproximation(
    const QVector<QCPGraphData>& input_data) {
  input_data_ = input_data;
  scaling_shift_ = input_data_.first().key;
  ShiftDate();
  current_polynomial_degree_ = -1;
}

void PolynomialApproximation::ShiftDate() {
  for (auto& graph_data : input_data_) {
    graph_data.key -= scaling_shift_;
  }
}

QVector<QCPGraphData> PolynomialApproximation::GetPredictedData(
    int polynomial_degree, int number_of_points, int predict_days) {
  CheckPolynomialDegree(polynomial_degree);
  return CalcPredictedData(number_of_points, predict_days);
}

void PolynomialApproximation::CheckPolynomialDegree(int polynomial_degree) {
  if (current_polynomial_degree_ != polynomial_degree) {
    current_polynomial_degree_ = polynomial_degree;
    polynomial_coefficients_ = GetPolynomialCoefficients(polynomial_degree);
  }
}

std::vector<long double> PolynomialApproximation::GetPolynomialCoefficients(
    int polynomial_degree) {
  Matrix SLE(polynomial_degree + 1, polynomial_degree + 2);
  PrepareSLE(SLE);
  return Gauss::SolveSLE(SLE);
}

void PolynomialApproximation::PrepareSLE(Matrix& SLE) {
  int i, j, k;
  int size = SLE.GetRows();
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      SLE(i, j) = 0;
      for (k = 0; k < input_data_.size(); k++) {
        SLE(i, j) += pow(input_data_[k].key, i + j);
      }
    }
  }
  for (i = 0; i < size; i++) {
    for (k = 0; k < input_data_.size(); k++) {
      SLE(i, size) += pow(input_data_[k].key, i) * input_data_[k].value;
    }
  }
}

QVector<QCPGraphData> PolynomialApproximation::CalcPredictedData(
    int number_of_points, int predict_days) {
  double x_first = input_data_.first().key;
  double x_last = input_data_.last().key + predict_days * 24 * 3600;
  double step = (x_last - x_first) / (number_of_points - 1);

  QVector<QCPGraphData> result(number_of_points);
  for (int i = 0; i < number_of_points; ++i) {
    double x_current = x_first + step * i;
    result[i].key = x_current + scaling_shift_;
    result[i].value = CalcPredictedValue(x_current);
  }
  return result;
}

double PolynomialApproximation::CalcPredictedValue(double x_current) {
  long double result = polynomial_coefficients_.front();
  long double temp_x_pow_factor = 1;
  for (int degree = 1; degree < polynomial_coefficients_.size(); ++degree) {
    temp_x_pow_factor *= x_current;
    result += temp_x_pow_factor * polynomial_coefficients_[degree];
  }
  return (double)(result);
}

double PolynomialApproximation::GetPredictedValue(const QDateTime& date_time,
                                                  int polynomial_degree) {
  CheckPolynomialDegree(polynomial_degree);
  auto epoch_time = static_cast<double>(date_time.toSecsSinceEpoch());
  return CalcPredictedValue(epoch_time - scaling_shift_);
}

}  // namespace s21
