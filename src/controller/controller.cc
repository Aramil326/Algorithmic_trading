#include "controller.h"

namespace s21 {
Controller::Controller(Facade* model_) : model_(model_) {}

int Controller::LoadInterpolationDataFromFile(const std::string& file) {
  int error = model_->LoadDataFromFile(file);
  if (error == 0) {
    model_->RefreshCubicSpline();
  }

  return error;
}

int Controller::LoadApproximationDataFromFile(const std::string& file) {
  int error = model_->LoadDataFromFile(file);
  if (error == 0) {
    model_->RefreshPolynomialApproximation();
  }
  return error;
}

QVector<QCPGraphData> Controller::GetNativeData() {
  return model_->GetNativeData();
}

QVector<QCPGraphData> Controller::GetApproximationData(int polynomial_degree,
                                                       int number_of_points,
                                                       int predict_days) {
  return model_->GetApproximationData(polynomial_degree, number_of_points,
                                      predict_days);
}

QVector<QCPGraphData> Controller::GetInterpolationData(int number_of_points) {
  return model_->GetInterpolationData(number_of_points);
}

double Controller::GetInterpolationValue(const QDateTime& date_time) {
  return model_->GetInterpolationValue(date_time);
}

double Controller::GetApproximationValue(const QDateTime& date_time,
                                         int polynomial_degree) {
  return model_->GetApproximationValue(date_time, polynomial_degree);
}

}  // namespace s21
