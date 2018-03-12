Normally, when there are invisible rules (rules whose names start with an `_`) that simply
wrap another rule, there is an optimization at parser-generation time called *Unit Reduction Elimination* that avoids creating nodes for those rules at runtime. One case where this
optimization must *not* be applied is when those invisible rules are going to be aliased
within their parent rule. In that situation, eliminating the invisible node could cause
the alias to be incorrectly applied to its child.
