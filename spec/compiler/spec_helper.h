#ifndef TreeSitter_SpecHelper_h
#define TreeSitter_SpecHelper_h

#include "bandit/bandit.h"
#include <iostream>
#include "transition_map.h"
#include "rules.h"
#include "item.h"
#include "item_set.h"
#include "grammar.h"
#include "parse_table.h"
#include "table_builder.h"
#include "../fixtures/grammars/arithmetic.h"

using namespace tree_sitter;
using namespace std;
using namespace bandit;

#define START_TEST go_bandit([]() {
#define END_TEST });

namespace std {
    template<typename T>
    inline std::ostream& operator<<(std::ostream &stream, const unordered_set<T> &set) {
        stream << string("#<set: ");
        bool started = false;
        for (auto item : set) {
            if (started) stream << string(", ");
            stream << item;
            started = true;
        }
        return stream << ">";
    }
    
    template<typename TKey, typename TValue>
    inline std::ostream& operator<<(std::ostream &stream, const unordered_map<TKey, TValue> &map) {
        stream << string("#<map: ");
        bool started = false;
        for (auto pair : map) {
            if (started) stream << string(", ");
            stream << pair.first;
            stream << string(" => ");
            stream << pair.second;
            started = true;
        }
        return stream << ">";
    }
}

namespace snowhouse {
    template<typename ExpectedType>
    struct EqualsPointerConstraint : Expression<EqualsPointerConstraint<ExpectedType>>
    {
        EqualsPointerConstraint(const ExpectedType& expected) : expected(expected) {}
        
        template<typename ActualType>
        bool operator()(const ActualType& actual) const {
            return *expected == *actual;
        }
        
        ExpectedType expected;
    };
    
    template<typename ExpectedType>
    struct Stringizer<EqualsPointerConstraint<ExpectedType>>
    {
        static std::string ToString(const EqualsPointerConstraint<ExpectedType>& constraint) {
            std::ostringstream builder;
            builder << "pointer to " << snowhouse::Stringize(constraint.expected);
            return builder.str();
        }
    };

    template<typename ExpectedType>
    inline EqualsPointerConstraint<ExpectedType> EqualsPointer(const ExpectedType& expected) {
        return EqualsPointerConstraint<ExpectedType>(expected);
    }
    
}

string src_dir();

#endif
