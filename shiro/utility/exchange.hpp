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

#ifndef SHIRO_UTILITY_EXCHANGE_HPP
#define SHIRO_UTILITY_EXCHANGE_HPP

#include <type_traits>
#include <utility>

namespace shiro {

template <typename T, typename U = T>
constexpr T exchange(T& obj, U&& new_value) {
  T old_value = std::move(obj);
  obj = std::forward<U>(new_value);
  return old_value;
}

}  // namespace shiro

#endif  // SHIRO_UTILITY_EXCHANGE_HPP
