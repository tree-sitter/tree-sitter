#ifndef tree_sitter_stream_methods_h
#define tree_sitter_stream_methods_h

#include <iostream>
#include <set>
#include <unordered_set>
#include <unordered_map>

using std::cout;

namespace std {
    template<typename T>
    inline std::ostream& operator<<(std::ostream &stream, const std::unordered_set<T> &set) {
        stream << std::string("#<set: ");
        bool started = false;
        for (auto item : set) {
            if (started) stream << std::string(", ");
            stream << item;
            started = true;
        }
        return stream << ">";
    }
    
    template<typename T>
    inline std::ostream& operator<<(std::ostream &stream, const std::set<T> &set) {
        stream << std::string("#<set: ");
        bool started = false;
        for (auto item : set) {
            if (started) stream << std::string(", ");
            stream << item;
            started = true;
        }
        return stream << ">";
    }
    
    template<typename TKey, typename TValue>
    inline std::ostream& operator<<(std::ostream &stream, const std::unordered_map<TKey, TValue> &map) {
        stream << std::string("#<map: ");
        bool started = false;
        for (auto pair : map) {
            if (started) stream << std::string(", ");
            stream << pair.first;
            stream << std::string(" => ");
            stream << pair.second;
            started = true;
        }
        return stream << ">";
    }
}

#endif
