#include "graph_widget.h"

#include <iostream>

namespace s21 {
GraphWidget::GraphWidget(QWidget *parent) : QCustomPlot(parent) {
  SetDefaultSettings();
}

void GraphWidget::SetDefaultSettings() {
  this->setInteraction(QCP::iRangeZoom, true);
  this->setInteraction(QCP::iRangeDrag, true);
  this->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
  this->axisRect()->setRangeZoom(Qt::Horizontal);

  QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
  dateTicker->setDateTimeFormat("dd MMM yy");
  this->xAxis->setTicker(dateTicker);

  this->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
  this->xAxis->setLabel("Date");

  this->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
  this->yAxis->setLabel("Price");

  this->xAxis2->setVisible(true);
  this->yAxis2->setVisible(true);
  this->xAxis2->setTicks(false);
  this->yAxis2->setTicks(false);
  this->xAxis2->setTickLabels(false);
  this->yAxis2->setTickLabels(false);

  this->legend->setVisible(true);
  this->legend->setBrush(QColor(255, 255, 255, 150));
}

void GraphWidget::AddDotedGraph(const QVector<QCPGraphData> &timeData) {
  this->addGraph();
  this->graph()->setPen(QColor(0, 0, 0, 255));
  this->graph()->setLineStyle(QCPGraph::lsNone);
  this->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
  this->graph()->setName("Native data");
  this->graph()->data()->set(timeData);
  this->xAxis->setRange(timeData[0].key - 24 * 3600,
                        timeData.last().key + 24 * 3600);
  this->rescaleAxes();
  this->replot();
}

QCPGraph *GraphWidget::AddLinesGraph(const QVector<QCPGraphData> &timeData,
                                     const QString &graph_name) {
  QCPGraph *graph = this->addGraph();
  this->graph()->setLineStyle(QCPGraph::lsLine);
  this->graph()->setPen(QPen(colors_[graph_counter_]));
  this->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
  this->graph()->data()->set(timeData);
  this->graph()->setName(graph_name);
  this->xAxis->setRange(timeData[0].key - 24 * 3600,
                        timeData.last().key + 24 * 3600);
  this->rescaleAxes();
  this->replot();
  graphs_.push_back(graph);
  graph_counter_++;
  return graph;
}

bool GraphWidget::removeGraph(QCPGraph *graph) {
  graph_counter_--;
  return QCustomPlot::removeGraph(graph);
}

void GraphWidget::clearLinesGraphs() {
  for (auto &it : graphs_) {
    removeGraph(it);
  }
  graphs_.clear();
  replot();
}

void GraphWidget::clearGraphs() {
  graph_counter_ = 0;
  graphs_.clear();
  QCustomPlot::clearGraphs();
}

}  // namespace s21