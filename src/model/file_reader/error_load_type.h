#ifndef TRADING_SRC_MODEL_FILE_READER_ERROR_LOAD_TYPE
#define TRADING_SRC_MODEL_FILE_READER_ERROR_LOAD_TYPE
namespace s21 {
enum Error {
  kOk = 0,
  kFileNotOpen,
  kWrongContent,
  kInsufficientData,
  kUnsortedData
};
}
#endif  // TRADING_SRC_MODEL_FILE_READER_ERROR_LOAD_TYPE
