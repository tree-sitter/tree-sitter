#include "helpers/spy_logger.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

static void spy_log(void *data, TSLogType type, const char *msg) {
  SpyLogger *logger = static_cast<SpyLogger *>(data);
  logger->messages.push_back(msg);
}

TSLogger SpyLogger::logger() {
  TSLogger result;
  result.payload = (void *)this;
  result.log = spy_log;
  return result;
}

void SpyLogger::clear() {
  messages.clear();
}
