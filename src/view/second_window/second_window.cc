#include "second_window.h"

#include "./ui_second_window.h"

namespace s21 {
SecondWindow::SecondWindow(Controller *controller, QWidget *parent)
    : QWidget(parent),
      ui_(new Ui::SecondWindow),
      error_handler_(new ErrorHandler(this)) {
  ui_->setupUi(this);
  last_added_days_ = 0;
  graph_counter_ = 0;
  controller_ = controller;
  ui_->date_to_calc->setCalendarPopup(true);
  connect(ui_->graphWidget->xAxis, SIGNAL(rangeChanged(QCPRange)), this,
          SLOT(slotRangeChanged(QCPRange)));
}

SecondWindow::~SecondWindow() {
  delete error_handler_;
  delete ui_;
}

void SecondWindow::slotRangeChanged(const QCPRange &newRange) {
  QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
  dateTicker->setDateTimeFormat((newRange.size() <= 86400) ? "hh:mm"
                                                           : "dd MMM yy");
  ui_->graphWidget->xAxis->setTicker(dateTicker);
}

void SecondWindow::on_loadDataButton_clicked() {
  std::string path = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "",
                                                  "(*.csv) *.csv")
                         .toStdString();
  if (!path.empty()) {
    int error = controller_->LoadApproximationDataFromFile(path);
    if (!error) {
      ui_->graphWidget->clearGraphs();
      ui_->graphWidget->replot();
      graph_counter_ = 0;
      QVector<QCPGraphData> data = controller_->GetNativeData();
      ui_->pointsNumberSpinBox->setMinimum((int)data.size());
      ui_->degreeSpinBox->setMaximum(std::min((int)(data.size()) - 1, 15));
      SetFileName(QString::fromStdString(path));
      ActivatePrintButton();
      ActivateCalculateSection();
      SetTimeInterval(data);
      is_graph_from_file_set = true;
      ui_->graphWidget->AddDotedGraph(data);
    } else {
      error_handler_->HandleLoadFromFileError(error);
    }
  }
}

void SecondWindow::on_printGraphButton_clicked() {
  int degree = ui_->degreeSpinBox->value();
  int points = ui_->pointsNumberSpinBox->value();
  int days = ui_->daysNumberSpinBox->value();
  if (days != last_added_days_) {
    Refresh();
    last_added_days_ = days;
  }
  QVector<QCPGraphData> data =
      controller_->GetApproximationData(degree, points, days);
  PrintGraphWithLines(data, "Graph_" + QString::number(graph_counter_) +
                                ": Degree of polynomial - " +
                                QString::number(degree));
}

void SecondWindow::PrintGraphWithLines(const QVector<QCPGraphData> &data,
                                       const QString &graph_name) {
  ui_->graphWidget->AddLinesGraph(data, graph_name);
  graph_counter_++;
  if (graph_counter_ == 5) {
    DisablePrintButton();
  }
}

void SecondWindow::on_mainWindowButton_clicked() {
  hide();
  emit sOpenMainWindow();
}

void SecondWindow::ShowSecondWindow() { show(); }

void SecondWindow::on_clearButton_clicked() { Refresh(); }

void SecondWindow::Refresh() {
  ui_->graphWidget->clearLinesGraphs();
  graph_counter_ = 0;
  if (is_graph_from_file_set) {
    ActivatePrintButton();
  }
}

void SecondWindow::SetFileName(const QString &path) {
  QString file_name = path.section('/', -1);
  ui_->file_name->setText("file name: " + file_name);
}

void SecondWindow::ActivatePrintButton() {
  ui_->printGraphButton->setEnabled(true);
}

void SecondWindow::DisablePrintButton() {
  ui_->printGraphButton->setEnabled(false);
}

void SecondWindow::ActivateCalculateSection() {
  ui_->date_to_calc->setEnabled(true);
  ui_->time_to_calc->setEnabled(true);
  ui_->calc_price->setEnabled(true);
}

void SecondWindow::DisableCalculateSection() {
  ui_->date_to_calc->setEnabled(false);
  ui_->time_to_calc->setEnabled(false);
  ui_->calc_price->setEnabled(false);
}

void SecondWindow::SetTimeInterval(const QVector<QCPGraphData> &data) {
  double first_date = data.first().key;
  ui_->date_to_calc->setMinimumDate(
      QDateTime::fromSecsSinceEpoch(first_date).date());
}

void SecondWindow::on_calc_price_clicked() {
  QDate date = ui_->date_to_calc->date();
  QTime time = ui_->time_to_calc->time();
  QDateTime date_time(date, time);

  double result = controller_->GetApproximationValue(
      date_time, ui_->degreeSpinBox->value());
  ui_->price_result->setText(QString::number(result));
}
}  // namespace s21
