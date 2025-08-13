from lldb import SBValue, SBType
import re

# define Array(T)      \
# struct {             \
#   T *contents;       \
#   uint32_t size;     \
#   uint32_t capacity; \
# }


class ArraySyntheticProvider:
    def __init__(self, valobj: SBValue, _dict):
        self.valobj: SBValue = valobj
        self.update()

    def num_children(self) -> int:
        return 2 + self.size.GetValueAsUnsigned()  # size, capacity, and elements

    def get_child_index(self, name: str) -> int:
        if name == "size":
            return 0
        elif name == "capacity":
            return 1
        else:
            if self.size.GetValueAsUnsigned() == 0:
                return 2
            index = name.lstrip("[").rstrip("]")
            if index.isdigit():
                return int(index)
            else:
                return -1

    def get_child_at_index(self, index: int) -> SBValue:
        if index == 0:
            return self.size
        elif index == 1:
            return self.capacity
        else:
            if self.size.GetValueAsUnsigned() == 0:
                return self.contents
            offset: int = index - 2
            start: int = self.contents.GetValueAsUnsigned()
            address: int = start + offset * self.element_type_size
            element: SBValue = self.contents.CreateValueFromAddress(
                "[%s]" % (offset), address, self.element_type
            )
            return element

    def update(self):
        self.contents: SBValue = self.valobj.GetChildMemberWithName("contents")
        self.size: SBValue = self.valobj.GetChildMemberWithName("size")
        self.capacity: SBValue = self.valobj.GetChildMemberWithName("capacity")

        self.element_type: SBType = self.contents.GetType().GetPointeeType()
        self.element_type_size: int = self.element_type.GetByteSize()

    def has_children(self) -> bool:
        return True


anon_re = re.compile(
    r"struct\s*{$\s*\w+ \*contents;$\s*uint32_t size;$\s*uint32_t capacity;$\s*}",
    re.MULTILINE,
)


# Used to recognize "anonymous" `Array(T)` types, i.e.:
# struct Foo {
#   Array(Bar) bars; // Render this field usign `ArraySyntheticProvider`
# };
def anon_array_recognizer(valobj: SBType, _dict) -> bool:
    type_name = valobj.GetName()
    if type_name == "(unnamed struct)":
        type_str = str(valobj)
        return anon_re.search(type_str) is not None
    else:
        return False
