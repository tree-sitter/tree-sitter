#include "spec_helper.h"


namespace tree_sitter {
    namespace lr {
        std::ostream& operator<<(std::ostream &stream, const unordered_map<string, unordered_set<ParseAction>> &map) {
            stream << string("{");
            bool started = false;
            for (auto pair : map) {
                if (started) stream << string(", ");
                stream << string("{") << pair.first << string(", [");
                bool started_set = false;
                for (ParseAction action : pair.second) {
                    if (started_set) stream << ", ";
                    stream << action;
                    started_set = true;
                }
                stream << string("]}");
                started = true;
            }
            stream << string("}");
            return stream;
        }
    }
}

string src_dir() {
    return string(getenv("TREESITTER_SRC_DIR"));
}