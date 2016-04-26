#ifndef COMPILER_BUILD_TABLES_REMOVE_DUPLICATE_STATES_H_
#define COMPILER_BUILD_TABLES_REMOVE_DUPLICATE_STATES_H_

#include <map>
#include <vector>

namespace tree_sitter {
namespace build_tables {

template <typename StateType, typename ActionType>
std::map<size_t, size_t> remove_duplicate_states(std::vector<StateType> *states) {
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

    std::map<size_t, size_t> new_replacements;
    for (size_t i = 0, size = states->size(); i < size; i++) {
      size_t new_state_index = i;
      auto duplicate = duplicates.find(i);
      if (duplicate != duplicates.end())
        new_state_index = duplicate->second;

      size_t prior_removed = 0;
      for (const auto &duplicate : duplicates) {
        if (duplicate.first >= new_state_index)
          break;
        prior_removed++;
      }

      new_state_index -= prior_removed;
      new_replacements.insert({ i, new_state_index });
      replacements.insert({ i, new_state_index });
      for (auto &replacement : replacements)
        if (replacement.second == i)
          replacement.second = new_state_index;
    }

    for (StateType &state : *states)
      state.each_advance_action([&new_replacements](ActionType *action) {
        auto new_replacement = new_replacements.find(action->state_index);
        if (new_replacement != new_replacements.end())
          action->state_index = new_replacement->second;
      });

    for (auto i = duplicates.rbegin(); i != duplicates.rend(); ++i)
      states->erase(states->begin() + i->first);
  }

  return replacements;
}

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_REMOVE_DUPLICATE_STATES_H_
