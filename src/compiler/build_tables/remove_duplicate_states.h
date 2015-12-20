#ifndef COMPILER_BUILD_TABLES_REMOVE_DUPLICATE_STATES_H_
#define COMPILER_BUILD_TABLES_REMOVE_DUPLICATE_STATES_H_

#include <map>
#include <vector>

namespace tree_sitter {
namespace build_tables {

template <typename StateType, typename ActionType, int advance_action>
std::map<size_t, size_t> remove_duplicate_states(
  std::vector<StateType> *states) {
  std::map<size_t, size_t> replacements;

  while (true) {
    std::map<size_t, size_t> duplicates;
    for (size_t i = 0, size = states->size(); i < size; i++)
      for (size_t j = 0; j < i; j++)
        if (states->at(i) == states->at(j)) {
          duplicates.insert({ i, j });
          break;
        }

    if (duplicates.empty())
      break;

    for (StateType &state : *states)
      state.each_action([&duplicates, &replacements](ActionType *action) {
        if (action->type == advance_action) {
          size_t state_index = action->state_index;
          auto replacement = duplicates.find(action->state_index);
          if (replacement != duplicates.end())
            state_index = replacement->second;

          size_t prior_removed = 0;
          for (const auto &replacement : duplicates) {
            if (replacement.first >= state_index)
              break;
            prior_removed++;
          }

          state_index -= prior_removed;
          replacements.insert({ action->state_index, state_index });
          action->state_index = state_index;
        }
      });

    for (auto i = duplicates.rbegin(); i != duplicates.rend(); ++i)
      states->erase(states->begin() + i->first);
  }

  return replacements;
}

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_REMOVE_DUPLICATE_STATES_H_
