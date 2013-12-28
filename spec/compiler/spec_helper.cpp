#include "spec_helper.h"

namespace tree_sitter {
    namespace lr {
        template<typename TKey, typename TValue>
        std::ostream & stream_map_of_sets(std::ostream &stream, const unordered_map<TKey, unordered_set<TValue>> &map) {
            stream << string("{");
            bool started = false;
            for (auto pair : map) {
                if (started) stream << string(", ");
                stream << pair.first;
                stream << string(" => [");
                bool started_set = false;
                for (TValue action : pair.second) {
                    if (started_set) stream << ", ";
                    stream << action;
                    started_set = true;
                }
                stream << string("]}");
                started = true;
            }
            return stream;
        }
        
        std::ostream& operator<<(std::ostream &stream, const unordered_map<string, unordered_set<ParseAction>> &map) {
            return stream_map_of_sets(stream, map);
        }

        std::ostream& operator<<(std::ostream &stream, const unordered_map<CharMatch, unordered_set<LexAction>> &map) {
            return stream_map_of_sets(stream, map);
        }
    }
}

string src_dir() {
    return string(getenv("TREESITTER_SRC_DIR"));
}