#ifndef TRADING_SRC_MODEL_FILE_READER_FILE_READER
#define TRADING_SRC_MODEL_FILE_READER_FILE_READER
#include <fstream>
#include <sstream>
#include <string>

#include "error_load_type.h"
#include "libs/qcustomplot/qcustomplot.h"

namespace s21 {

class FileReader {
 public:
  static FileReader& GetInstance();
  bool Open(const std::string& path);
  std::pair<Error, QVector<QCPGraphData>> GetData();

  ~FileReader();

 private:
  std::ifstream* in_;
  FileReader() = default;
};

}  // namespace s21

#endif  // TRADING_SRC_MODEL_FILE_READER_FILE_READER
