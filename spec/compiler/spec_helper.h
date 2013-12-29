#ifndef TreeSitter_SpecHelper_h
#define TreeSitter_SpecHelper_h

#include "bandit/bandit.h"
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
            builder << "equal to pointer " << snowhouse::Stringize(constraint.expected);
            return builder.str();
        }
    };

    template<typename ExpectedType>
    inline EqualsPointerConstraint<ExpectedType> EqualsPointer(const ExpectedType& expected) {
        return EqualsPointerConstraint<ExpectedType>(expected);
    }
}

namespace tree_sitter {
    namespace lr {
        std::ostream& operator<<(std::ostream &stream, const unordered_map<string, unordered_set<lr::ParseAction>> &map);
        std::ostream& operator<<(std::ostream &stream, const unordered_map<CharMatch, unordered_set<lr::LexAction>> &map);
    }
}

string src_dir();

#endif
