#include "mainwindow.h"

#include "./ui_mainwindow.h"

namespace s21 {
MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : controller_(controller),
      QMainWindow(parent),
      ui_(new Ui::MainWindow),
      error_handler_(new ErrorHandler(this)) {
  ui_->setupUi(this);
  graph_counter_ = 0;
  ui_->date_to_calc->setCalendarPopup(true);
}

void MainWindow::SetSecondWindow(SecondWindow *second_window) {
  second_window_ = second_window;
  connect(second_window_, &SecondWindow::sOpenMainWindow, this,
          &MainWindow::ShowMainWindow);
  connect(ui_->QGraphWidget->xAxis, SIGNAL(rangeChanged(QCPRange)), this,
          SLOT(slotRangeChanged(QCPRange)));
}

MainWindow::~MainWindow() {
  delete error_handler_;
  delete ui_;
}

void MainWindow::slotRangeChanged(const QCPRange &newRange) {
  QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
  dateTicker->setDateTimeFormat((newRange.size() <= 86400) ? "hh:mm"
                                                           : "dd MMM yy");
  ui_->QGraphWidget->xAxis->setTicker(dateTicker);
}

void MainWindow::on_PrintGraph_clicked() {
  int points = ui_->pointsNumberSpinBox->value();
  QVector<QCPGraphData> data = controller_->GetInterpolationData(points);
  PrintGraphWithLines(data, "Graph_" + QString::number(points) +
                                ": count of points - " +
                                QString::number(points));
}

void MainWindow::on_secondWindowButton_clicked() {
  hide();
  second_window_->move(pos().x(), pos().y());
  second_window_->ShowSecondWindow();
}

void MainWindow::ShowMainWindow() {
  move(second_window_->pos().x(), second_window_->pos().y());
  show();
}

void MainWindow::on_Clear_clicked() {
  ui_->QGraphWidget->clearLinesGraphs();
  graph_counter_ = 0;
  if (is_graph_from_file_set) {
    ActivatePrintButton();
  }
}

void MainWindow::on_LoadButton_clicked() {
  std::string path = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "",
                                                  "(*.csv) *.csv")
                         .toStdString();
  if (!path.empty()) {
    int error = controller_->LoadInterpolationDataFromFile(path);
    if (!error) {
      ui_->QGraphWidget->clearGraphs();
      ui_->QGraphWidget->replot();
      graph_counter_ = 0;
      QVector<QCPGraphData> data = controller_->GetNativeData();
      ui_->pointsNumberSpinBox->setMinimum((int)data.size());
      SetFileName(QString::fromStdString(path));
      ActivatePrintButton();
      ActivateCalculateSection();
      SetTimeInterval(data);
      is_graph_from_file_set = true;
      ui_->QGraphWidget->AddDotedGraph(data);
    } else {
      error_handler_->HandleLoadFromFileError(error);
    }
  }
}

void MainWindow::SetFileName(const QString &path) {
  QString file_name = path.section('/', -1);
  ui_->file_name->setText("file name: " + file_name);
}

void MainWindow::ActivatePrintButton() { ui_->PrintGraph->setEnabled(true); }

void MainWindow::DisablePrintButton() { ui_->PrintGraph->setEnabled(false); }

void MainWindow::ActivateCalculateSection() {
  ui_->date_to_calc->setEnabled(true);
  ui_->time_to_calc->setEnabled(true);
  ui_->calc_price->setEnabled(true);
}

void MainWindow::DisableCalculateSection() {
  ui_->date_to_calc->setEnabled(false);
  ui_->time_to_calc->setEnabled(false);
  ui_->calc_price->setEnabled(false);
}

void MainWindow::SetTimeInterval(const QVector<QCPGraphData> &data) {
  double first_date = data.first().key;
  double last_date = data.last().key;
  max_date_ = QDateTime::fromSecsSinceEpoch(last_date).date();
  ui_->date_to_calc->setMinimumDate(
      QDateTime::fromSecsSinceEpoch(first_date).date());
  ui_->date_to_calc->setMaximumDate(max_date_);
}

void MainWindow::PrintGraphWithLines(const QVector<QCPGraphData> &data,
                                     const QString &graph_name) {
  ui_->QGraphWidget->AddLinesGraph(data, graph_name);
  graph_counter_++;
  if (graph_counter_ == 5) {
    DisablePrintButton();
  }
}

void MainWindow::on_calc_price_clicked() {
  QDate date = ui_->date_to_calc->date();
  QTime time = ui_->time_to_calc->time();
  QDateTime date_time(date, time);
  double result = controller_->GetInterpolationValue(date_time);
  ui_->price_result->setText(QString::number(result));
}

void MainWindow::on_date_to_calc_userDateChanged(const QDate &date) {
  if (date == max_date_) {
    ui_->time_to_calc->setMaximumTime(QTime(0, 0, 0, 0));
  } else {
    ui_->time_to_calc->setMaximumTime(QTime(23, 59, 59, 0));
  }
}

}  // namespace s21
