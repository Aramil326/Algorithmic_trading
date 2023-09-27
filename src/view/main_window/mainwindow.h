#ifndef TRADING_SRC_VIEW_MAIN_WINDOW
#define TRADING_SRC_VIEW_MAIN_WINDOW
#include <QMainWindow>
#include <iostream>

#include "../../controller/controller.h"
#include "../second_window/second_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(Controller *controller, QWidget *parent = nullptr);
  void SetSecondWindow(SecondWindow *second_window);
  ~MainWindow() override;

 private slots:
  void slotRangeChanged(const QCPRange &newRange);
  void on_PrintGraph_clicked();
  void on_secondWindowButton_clicked();
  void ShowMainWindow();
  void on_Clear_clicked();
  void on_LoadButton_clicked();
  void on_calc_price_clicked();

  void on_date_to_calc_userDateChanged(const QDate &date);

 private:
  Ui::MainWindow *ui_;
  Controller *controller_;
  SecondWindow *second_window_;
  ErrorHandler *error_handler_;
  int graph_counter_;
  bool is_graph_from_file_set = false;
  QDate max_date_;

  void SetFileName(const QString &path);
  void ActivatePrintButton();
  void DisablePrintButton();
  void ActivateCalculateSection();
  void DisableCalculateSection();
  void SetTimeInterval(const QVector<QCPGraphData> &data);
  void PrintGraphWithLines(const QVector<QCPGraphData> &data,
                           const QString &graph_name);
  void HandleLoadFromFileError(int error);
  void ShowErrorMessage(const std::string &title, const std::string &msg);
};
}  // namespace s21
#endif  // TRADING_SRC_VIEW_MAIN_WINDOW
