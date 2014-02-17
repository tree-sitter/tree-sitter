#ifndef __tree_sitter_spec_helper_h__
#define __tree_sitter_spec_helper_h__

#include "bandit/bandit.h"
#include "stream_methods.h"
#include <iostream>
#include "compiler.h"

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
        static string ToString(const EqualsPointerConstraint<ExpectedType>& constraint) {
            ostringstream builder;
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
