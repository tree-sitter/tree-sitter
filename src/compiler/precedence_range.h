#ifndef COMPILER_PRECEDENCE_RANGE_H_
#define COMPILER_PRECEDENCE_RANGE_H_

namespace tree_sitter {

struct PrecedenceRange {
  PrecedenceRange();
  explicit PrecedenceRange(int value);
  PrecedenceRange(int min, int max);

  void add(int value);
  void add(const PrecedenceRange &);
  bool operator==(const PrecedenceRange &other) const;
  bool operator<(const PrecedenceRange &other) const;

  int min;
  int max;
  bool empty;
};

}  // namespace tree_sitter

#endif  // COMPILER_PRECEDENCE_RANGE_H_
