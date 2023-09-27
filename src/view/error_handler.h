#ifndef TRADING_SRC_VIEW_ERROR_HANDLER
#define TRADING_SRC_VIEW_ERROR_HANDLER

#include <QMessageBox>
#include <QWidget>

#include "model/file_reader/error_load_type.h"

namespace s21 {

class ErrorHandler {
 public:
  ErrorHandler(QWidget* widget);
  void HandleLoadFromFileError(int error);

 private:
  QWidget* widget_;
  void ShowErrorMessage(const std::string& title, const std::string& msg);
};

}  // namespace s21

#endif  // TRADING_SRC_VIEW_ERROR_HANDLER
