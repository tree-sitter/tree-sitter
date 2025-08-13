import lldb

# Even though these are "unused", we still need them in scope in order for the classes
# to exist when we register them with the debugger
from ts_tree import TSTreeSyntheticProvider
from table_entry import TableEntrySyntheticProvider
from ts_array import ArraySyntheticProvider, anon_array_recognizer


class TreeSitterType(object):
    TS_TREE: str = "TSTree"
    SUBTREE_ARRAY: str = "SubtreeArray"
    MUTABLE_SUBTREE_ARRAY: str = "MutableSubtreeArray"
    STACK_SLICE_ARRAY: str = "StackSliceArray"
    STACK_SUMMARY: str = "StackSummary"
    STACK_ENTRY: str = "StackEntry"
    REUSABLE_NODE: str = "ReusableNode"
    REDUCE_ACTION_SET: str = "ReduceActionSet"
    TABLE_ENTRY: str = "TableEntry"
    TS_RANGE_ARRAY: str = "TSRangeArray"
    CAPTURE_QUANTIFIERS: str = "CaptureQuantifiers"
    CAPTURE_LIST: str = "CaptureList"
    ANALYSIS_STATE_SET: str = "AnalysisStateSet"
    ANALYSIS_SUBGRAPH_ARRAY: str = "AnalysisSubgraphArray"
    STACK_NODE_ARRAY: str = "StackNodeArray"
    STRING_DATA: str = "StringData"


def ts_type_to_regex(type: str) -> str:
    return f"^{type}$|^struct {type}$|^typedef {type}$"


# Holds all tree-sitter types defined via the `Array` macro. These types will
# all share the same `ArrayTypeSyntheticProvider` synthetic provider
TS_ARRAY_TYPES = [
    TreeSitterType.REDUCE_ACTION_SET,
    TreeSitterType.TS_RANGE_ARRAY,
    TreeSitterType.CAPTURE_QUANTIFIERS,
    TreeSitterType.ANALYSIS_STATE_SET,
    TreeSitterType.CAPTURE_LIST,
    TreeSitterType.ANALYSIS_SUBGRAPH_ARRAY,
    TreeSitterType.STACK_SLICE_ARRAY,
    TreeSitterType.STACK_SUMMARY,
    TreeSitterType.SUBTREE_ARRAY,
    TreeSitterType.MUTABLE_SUBTREE_ARRAY,
    TreeSitterType.STRING_DATA,
    TreeSitterType.STACK_NODE_ARRAY,
]


def __lldb_init_module(debugger: lldb.SBDebugger, _dict):
    debugger.HandleCommand(
        f"type synthetic add -l tree_sitter_types.TSTreeSyntheticProvider -x '{ts_type_to_regex(TreeSitterType.TS_TREE)}'"
    )
    debugger.HandleCommand(
        f"type synthetic add -l tree_sitter_types.TableEntrySyntheticProvider -x '{ts_type_to_regex(TreeSitterType.TABLE_ENTRY)}'"
    )
    debugger.HandleCommand(
        f"type synthetic add -l tree_sitter_types.ArraySyntheticProvider --recognizer-function tree_sitter_types.anon_array_recognizer"
    )
    for type in TS_ARRAY_TYPES:
        debugger.HandleCommand(
            f"type synthetic add -l tree_sitter_types.ArraySyntheticProvider -x '{ts_type_to_regex(type)}'"
        )
