#ifndef SHIRO_TUPLE_TIE_HPP
#define SHIRO_TUPLE_TIE_HPP

#include <shiro/tuple/tuple_fwd.hpp>

namespace shiro {

template <typename... Types>
constexpr tuple<Types&...> tie(Types&... args) noexcept {
  return tuple<Types&...>(args...);
}

}  // namespace shiro

#endif  // SHIRO_TUPLE_TIE_HPP
