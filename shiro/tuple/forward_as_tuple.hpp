#ifndef SHIRO_TUPLE_FORWARD_AS_TUPLE_HPP
#define SHIRO_TUPLE_FORWARD_AS_TUPLE_HPP

#include <utility>

#include <shiro/tuple/tuple_fwd.hpp>

namespace shiro {

template <typename... Types>
constexpr tuple<Types&&...> forward_as_tuple(Types&&... args) noexcept {
  return tuple<Types&&...>(std::forward<Types>(args)...);
}

}  // namespace shiro

#endif  // SHIRO_TUPLE_FORWARD_AS_TUPLE_HPP
