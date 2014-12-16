#ifndef SHIRO_TUPLE_SWAP_HPP
#define SHIRO_TUPLE_SWAP_HPP

#include <shiro/tuple/tuple_fwd.hpp>

namespace shiro {

template <typename... Types>
inline void swap(tuple<Types...>& t,
                 tuple<Types...>& u) noexcept(noexcept(t.swap(u))) {
  t.swap(u);
}

}  // namespace shiro

#endif  // SHIRO_TUPLE_SWAP_HPP
