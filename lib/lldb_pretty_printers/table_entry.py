from lldb import SBValue

# typedef struct {
#   const TSParseAction *actions;
#   uint32_t action_count;
#   bool is_reusable;
# } TableEntry;

# TODO: Same inline issue as with `TSTreeSyntheticProvider`.


class TableEntrySyntheticProvider:
    def __init__(self, valobj: SBValue, _dict):
        self.valobj: SBValue = valobj
        self.update()

    def num_children(self) -> int:
        # is_reusable, action_count, actions
        return 2 + max(1, self.action_count.GetValueAsUnsigned())

    def get_child_index(self, name: str) -> int:
        if name == "is_reusable":
            return 0
        elif name == "action_count":
            return 1
        else:
            if self.action_count.GetValueAsUnsigned() == 0:
                return 2
            index = name.lstrip("actions[").rstrip("]")
            if index.isdigit():
                return int(index)
            else:
                return -1

    def get_child_at_index(self, index: int) -> SBValue:
        if index == 0:
            return self.is_reusable
        elif index == 1:
            return self.action_count
        else:
            if self.action_count.GetValueAsUnsigned() == 0:
                return self.actions
            offset: int = index - 3
            start: int = self.actions.GetValueAsUnsigned()
            address: int = start + offset * self.element_type_size
            element: SBValue = self.actions.CreateValueFromAddress(
                "action[%s]" % (offset), address, self.element_type
            )
            return element

    def update(self):
        self.is_reusable: SBValue = self.valobj.GetChildMemberWithName("is_reusable")
        self.action_count: SBValue = self.valobj.GetChildMemberWithName("action_count")
        self.actions: SBValue = self.valobj.GetChildMemberWithName("actions")

        self.element_type: SBType = self.actions.GetType().GetPointeeType()
        self.element_type_size: int = self.element_type.GetByteSize()

    def has_children(self) -> bool:
        return True
