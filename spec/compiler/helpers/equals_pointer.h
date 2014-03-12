#ifndef HELPERS_EQUALS_POINTER_H_
#define HELPERS_EQUALS_POINTER_H_

#include <string>

namespace snowhouse {
    using namespace std;

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

#endif  // HELPERS_EQUALS_POINTER_H_
