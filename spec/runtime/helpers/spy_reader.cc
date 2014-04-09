#include "helpers/spy_reader.h"
#include <algorithm>

using std::string;

static const char * spy_read(void *data, size_t *bytes_read) {
    SpyReader *reader = static_cast<SpyReader *>(data);
    size_t size = std::min(reader->chunk_size,
                           reader->content.length() - reader->position);
    const char *result = reader->content.data() + reader->position;
    reader->strings_read.back() += string(result, size);
    reader->position += size;
    *bytes_read = size;
    return result;
}

static int spy_seek(void *data, size_t position) {
    SpyReader *reader = static_cast<SpyReader *>(data);
    reader->strings_read.push_back("");
    reader->position = position;
    return 0;
}

static void spy_release(void *data) {
    SpyReader *reader = static_cast<SpyReader *>(data);
    delete reader;
}

SpyReader::SpyReader(string content, size_t chunk_size) :
    content(content),
    position(0),
    chunk_size(chunk_size),
    input({
        this,
        spy_read,
        spy_seek,
        spy_release,
    }) {}
