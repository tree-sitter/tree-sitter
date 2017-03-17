#ifndef COMPILER_UTIL_MAKE_VISITOR_H_
#define COMPILER_UTIL_MAKE_VISITOR_H_

namespace tree_sitter {
namespace util {

template <typename... Fns>
struct visitor;

template <typename Fn>
struct visitor<Fn> : Fn {
  using Fn::operator();
  visitor(Fn fn) : Fn(fn) {}
};

template <typename Fn, typename... Fns>
struct visitor<Fn, Fns...> : Fn, visitor<Fns...> {
  using Fn::operator();
  using visitor<Fns...>::operator();
  visitor(Fn fn, Fns... fns) : Fn(fn), visitor<Fns...>(fns...) {}
};

template <typename... Fns>
visitor<Fns...> make_visitor(Fns... fns) {
  return visitor<Fns...>(fns...);
}

}  // namespace util
}  // namespace tree_sitter

#endif  // COMPILER_UTIL_MAKE_VISITOR_H_
