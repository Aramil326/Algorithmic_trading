#include "error_handler.h"

namespace s21 {

ErrorHandler::ErrorHandler(QWidget *widget) { widget_ = widget; }

void ErrorHandler::HandleLoadFromFileError(int error) {
  switch (error) {
    case Error::kFileNotOpen:
      ShowErrorMessage("Open file error", "File can't be open.");
      break;
    case Error::kWrongContent:
      ShowErrorMessage("Content error", "Incorrect content format.");
      break;
    case Error::kInsufficientData:
      ShowErrorMessage("Content error", "Insufficient Data.");
      break;
    case Error::kUnsortedData:
      ShowErrorMessage("Content error", "Unsorted Data.");
      break;
    default:
      ShowErrorMessage("Unknown error", "Unknown error");
  }
}

void ErrorHandler::ShowErrorMessage(const std::string &title,
                                    const std::string &msg) {
  QMessageBox::critical(widget_, QString::fromStdString(title),
                        QString::fromStdString(msg));
}

}  // namespace s21
