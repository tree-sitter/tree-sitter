#ifndef HELPERS_FILE_HELPERS_H_
#define HELPERS_FILE_HELPERS_H_

#include <string>
#include <vector>
#include <sys/stat.h>

bool file_exists(const std::string &path);
int get_modified_time(const std::string &path);
std::string read_file(const std::string &path);
void write_file(const std::string &path, const std::string &content);
std::vector<std::string> list_directory(const std::string &path);

#endif  // HELPERS_FILE_HELPERS_H_
