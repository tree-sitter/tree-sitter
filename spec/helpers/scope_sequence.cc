#include "./scope_sequence.h"

#include "bandit/bandit.h"
#include <sstream>
#include "helpers/stream_methods.h"
#include "helpers/point_helpers.h"

using std::string;
using std::cout;

static void append_text_to_scope_sequence(ScopeSequence *sequence,
                                          ScopeStack *current_scopes,
                                          const std::string &text,
                                          size_t length) {
  for (size_t i = 0; i < length; i++) {
    string character(1, text[sequence->size()]);
    sequence->push_back(*current_scopes);
    sequence->back().push_back("'" + character + "'");
  }
}

static void append_to_scope_sequence(ScopeSequence *sequence,
                                     ScopeStack *current_scopes,
                                     TSNode node, TSDocument *document,
                                     const std::string &text) {
  append_text_to_scope_sequence(
    sequence, current_scopes, text, ts_node_start_byte(node) - sequence->size()
  );

  current_scopes->push_back(ts_node_type(node, document));

  for (size_t i = 0, n = ts_node_child_count(node); i < n; i++) {
    TSNode child = ts_node_child(node, i);
    append_to_scope_sequence(sequence, current_scopes, child, document, text);
  }

  append_text_to_scope_sequence(
    sequence, current_scopes, text, ts_node_end_byte(node) - sequence->size()
  );

  current_scopes->pop_back();
}

ScopeSequence build_scope_sequence(TSDocument *document, const std::string &text) {
  ScopeSequence sequence;
  ScopeStack current_scopes;
  TSNode node = ts_document_root_node(document);
  append_to_scope_sequence(&sequence, &current_scopes, node, document, text);
  return sequence;
}

bool operator<=(const TSPoint &left, const TSPoint &right) {
  if (left.row < right.row)
    return true;
  else if (left.row == right.row)
    return left.column <= right.column;
  else
    return false;
}

void verify_changed_ranges(const ScopeSequence &old_sequence, const ScopeSequence &new_sequence,
                           const string &text, TSRange *ranges, size_t range_count) {
  TSPoint current_position = {0, 0};
  for (size_t i = 0; i < old_sequence.size(); i++) {
    if (text[i] == '\n') {
      current_position.row++;
      current_position.column = 0;
      continue;
    }

    const ScopeStack &old_scopes = old_sequence[i];
    const ScopeStack &new_scopes = new_sequence[i];
    if (old_scopes != new_scopes) {
      bool found_containing_range = false;
      for (size_t j = 0; j < range_count; j++) {
        TSRange range = ranges[j];
        if (range.start <= current_position && current_position <= range.end) {
          found_containing_range = true;
          break;
        }
      }

      if (!found_containing_range) {
        std::stringstream message_stream;
        message_stream << "Found changed scope outside of any invalidated range;\n";
        message_stream << "Position: " << current_position << "\n";
        message_stream << "Byte index: " << i << "\n";
        size_t line_start_index = i - current_position.column;
        size_t line_end_index = text.find_first_of('\n', i);
        message_stream << "Line: " << text.substr(line_start_index, line_end_index - line_start_index) << "\n";
        for (size_t j = 0; j < current_position.column + string("Line: ").size(); j++)
          message_stream << " ";
        message_stream << "^\n";
        message_stream << "Old scopes: " << old_scopes << "\n";
        message_stream << "New scopes: " << new_scopes << "\n";
        message_stream << "Invalidated ranges:\n";
        for (size_t j = 0; j < range_count; j++) {
          message_stream << "  " << ranges[j] << "\n";
        }
        Assert::Failure(message_stream.str());
      }
    }

    current_position.column++;
  }
}
