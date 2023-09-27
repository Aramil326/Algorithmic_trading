#include "file_reader.h"

#include <iostream>

namespace s21 {
FileReader &FileReader::GetInstance() {
  static FileReader instance;
  return instance;
}

bool FileReader::Open(const std::string &path) {
  if (in_ != nullptr && in_->is_open()) in_->close();
  delete in_;
  in_ = new std::ifstream(path);
  return in_->is_open();
}

std::pair<Error, QVector<QCPGraphData>> FileReader::GetData() {
  QVector<QCPGraphData> result;
  Error error = kOk;
  if (!in_->is_open() || in_->eof()) {
    return std::make_pair(kFileNotOpen, result);
  }
  std::string ignored;
  std::getline(*in_, ignored);
  int yy, mm, dd;
  double price;
  char ch;
  std::string line;
  QDateTime temp_date_time(QDate(1970, 1, 1), QTime());
  while (std::getline(*in_, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream iss(line);
    yy = mm = dd = -1;
    price = INFINITY;
    iss >> yy >> ch >> mm >> ch >> dd >> ch >> price;
    if (yy == -1 || mm == -1 || dd == -1 || price == INFINITY ||
        (ch != '.' && ch != ',')) {
      return std::make_pair(kWrongContent, result);
    }
    QDateTime date(QDate(yy, mm, dd), QTime());
    if (date <= temp_date_time) {
      return std::make_pair(kUnsortedData, result);
    }
    temp_date_time = date;
    QCPGraphData qcp_graph_data(date.toSecsSinceEpoch(), price);
    result.push_back(qcp_graph_data);
  }
  return std::make_pair(error, result);
}

FileReader::~FileReader() {
  if (in_ != nullptr && in_->is_open()) in_->close();
  delete in_;
}

}  // namespace s21