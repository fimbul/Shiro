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

#endif  // #ifndef SHIRO_TUPLE_FORWARD_AS_TUPLE_HPP
