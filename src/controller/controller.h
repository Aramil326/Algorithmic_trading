#ifndef TRADING_SRC_MODEL_CUBIC_SPLINE_CUBIC_SPLINE
#define TRADING_SRC_MODEL_CUBIC_SPLINE_CUBIC_SPLINE

#include "model/facade/facade.h"
namespace s21 {

class Controller {
 public:
  explicit Controller(Facade* model_);

  int LoadInterpolationDataFromFile(const std::string& file);

  int LoadApproximationDataFromFile(const std::string& file);

  QVector<QCPGraphData> GetNativeData();

  QVector<QCPGraphData> GetApproximationData(int polynomial_degree,
                                             int number_of_points,
                                             int predict_days);

  QVector<QCPGraphData> GetInterpolationData(int number_of_points);

  double GetInterpolationValue(const QDateTime& date_time);

  double GetApproximationValue(const QDateTime& date_time,
                               int polynomial_degree);

 private:
  Facade* model_;
};

}  // namespace s21

#endif  // TRADING_SRC_MODEL_CUBIC_SPLINE_CUBIC_SPLINE