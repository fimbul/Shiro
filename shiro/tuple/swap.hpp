///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) fimbul 2014.
// https://github.com/fimbul/Shiro
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

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

#endif  // #ifndef SHIRO_TUPLE_SWAP_HPP
