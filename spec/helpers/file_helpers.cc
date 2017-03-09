#include "helpers/file_helpers.h"
#include <sys/stat.h>
#include <errno.h>
#include <fstream>
#include <dirent.h>

using std::string;
using std::ifstream;
using std::istreambuf_iterator;
using std::ofstream;
using std::vector;

bool file_exists(const string &path) {
  struct stat file_stat;
  return stat(path.c_str(), &file_stat) == 0;
}

int get_modified_time(const string &path) {
  struct stat file_stat;
  if (stat(path.c_str(), &file_stat) != 0) {
    if (errno != ENOENT)
      fprintf(stderr, "Error in stat() for path: %s\n", + path.c_str());
    return 0;
  }
  return file_stat.st_mtime;
}

string read_file(const string &path) {
  ifstream file(path);
  istreambuf_iterator<char> file_iterator(file), end_iterator;
  string content(file_iterator, end_iterator);
  file.close();
  return content;
}

void write_file(const string &path, const string &content) {
  ofstream file(path);
  file << content;
  file.close();
}

vector<string> list_directory(const string &path) {
  vector<string> result;

  DIR *dir = opendir(path.c_str());
  if (!dir) {
    printf("\nTest error - no such directory '%s'", path.c_str());
    return result;
  }

  struct dirent *dir_entry;
  while ((dir_entry = readdir(dir))) {
    string name(dir_entry->d_name);
    if (name != "." && name != "..") {
      result.push_back(name);
    }
  }

  closedir(dir);
  return result;
}