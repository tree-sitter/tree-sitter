from lldb import SBType, SBValue

# struct TSTree {
#   Subtree root;
#   const TSLanguage *language;
#   TSRange *included_ranges;
#   unsigned included_range_count;
# };

# TODO: Ideally, we'd display the elements of `included_ranges` as
# children of `included_ranges` rather than separate items, i.e.:

# (TSTree) {
#   root = ...
#   language = ...
#   included_range_count = ...
#   included_ranges = {
#     [0] = {
#       ...
#     }
#     [1] = {
#       ...
#     }
#     ...
#   }
# }
#
#  instead of the current behavior:
#
# (TSTree) {
#   root = ...
#   language = ...
#   included_range_count = ...
#   included_ranges[0] = {
#     ...
#   }
#   included_ranges[1] = {
#     ...
#   }
# }
#


class TSTreeSyntheticProvider:
    def __init__(self, valobj: SBValue, _dict):
        self.valobj: SBValue = valobj
        self.update()

    def num_children(self) -> int:
        # root, language, included_range_count, included_ranges
        return 3 + self.included_range_count.GetValueAsUnsigned()

    def get_child_index(self, name: str) -> int:
        if name == "root":
            return 0
        elif name == "language":
            return 1
        elif name == "included_range_count":
            return 2
        else:
            if self.included_range_count.GetValueAsUnsigned() == 0:
                return 3
            index = name.lstrip("included_ranges[").rstrip("]")
            if index.isdigit():
                return int(index)
            else:
                return -1

    def get_child_at_index(self, index: int) -> SBValue:
        if index == 0:
            return self.root
        elif index == 1:
            return self.language
        elif index == 2:
            return self.included_range_count
        else:
            if self.included_range_count.GetValueAsUnsigned() == 0:
                return self.included_ranges
            offset: int = index - 3
            start: int = self.included_ranges.GetValueAsUnsigned()
            address: int = start + offset * self.element_type_size
            element: SBValue = self.included_ranges.CreateValueFromAddress(
                "included_ranges[%s]" % (offset), address, self.element_type
            )
            return element

    def update(self):
        self.root: SBValue = self.valobj.GetChildMemberWithName("root")
        self.language: SBValue = self.valobj.GetChildMemberWithName("language")
        self.included_range_count: SBValue = self.valobj.GetChildMemberWithName(
            "included_range_count"
        )
        self.included_ranges: SBValue = self.valobj.GetChildMemberWithName(
            "included_ranges"
        )

        self.element_type: SBType = self.included_ranges.GetType().GetPointeeType()
        self.element_type_size: int = self.element_type.GetByteSize()

    def has_children(self) -> bool:
        return True
