#ifndef TRADING_SRC_VIEW_GRAPH_WIDGET_GRAPH_WIDGET
#define TRADING_SRC_VIEW_GRAPH_WIDGET_GRAPH_WIDGET

#include "../../libs/qcustomplot/qcustomplot.h"
namespace s21 {

class GraphWidget : public QCustomPlot {
 public:
  explicit GraphWidget(QWidget* parent = nullptr);
  QCPGraph* AddLinesGraph(const QVector<QCPGraphData>& timeData,
                          const QString& graph_name);
  void AddDotedGraph(const QVector<QCPGraphData>& timeData);
  bool removeGraph(QCPGraph* graph);
  void clearGraphs();
  void clearLinesGraphs();

 private:
  QVector<QCPGraph*> graphs_;
  int graph_counter_ = 0;
  QColor colors_[5] = {QColor(255, 0, 0), QColor(255, 139, 0),
                       QColor(0, 0, 255), QColor(255, 0, 255),
                       QColor(68, 139, 111)};
  void SetDefaultSettings();
};

}  // namespace s21

#endif  // TRADING_SRC_VIEW_GRAPH_WIDGET_GRAPH_WIDGET
