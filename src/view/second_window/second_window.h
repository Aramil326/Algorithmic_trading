#ifndef TRADING_SRC_VIEW_SECOND_WINDOW
#define TRADING_SRC_VIEW_SECOND_WINDOW

#include <QWidget>
#include <algorithm>

#include "../../controller/controller.h"
#include "../error_handler.h"

namespace Ui {
class SecondWindow;
}

namespace s21 {
class SecondWindow : public QWidget {
  Q_OBJECT

 public:
  explicit SecondWindow(Controller* controller, QWidget* parent = nullptr);
  ~SecondWindow() override;

 public slots:
  void ShowSecondWindow();

 signals:
  void sOpenMainWindow();

 private slots:
  void on_printGraphButton_clicked();
  void on_mainWindowButton_clicked();
  void slotRangeChanged(const QCPRange& newRange);
  void on_clearButton_clicked();
  void on_loadDataButton_clicked();
  void on_calc_price_clicked();

 private:
  Ui::SecondWindow* ui_;
  Controller* controller_;
  ErrorHandler* error_handler_;
  bool is_graph_from_file_set = false;
  int graph_counter_;
  int last_added_days_;

  void Refresh();
  void SetFileName(const QString& path);
  void ActivatePrintButton();
  void DisablePrintButton();
  void ActivateCalculateSection();
  void DisableCalculateSection();
  void SetTimeInterval(const QVector<QCPGraphData>& data);
  void PrintGraphWithLines(const QVector<QCPGraphData>& data,
                           const QString& graph_name);
};
}  // namespace s21
#endif  // TRADING_SRC_VIEW_SECOND_WINDOW
