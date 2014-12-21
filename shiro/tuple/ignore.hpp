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

#ifndef SHIRO_TUPLE_IGNORE_HPP
#define SHIRO_TUPLE_IGNORE_HPP

namespace shiro {
namespace detail {
namespace tuple {

struct ignore_t {
  template <typename T>
  constexpr const ignore_t& operator=(const T&) const {
    return *this;
  }
};

}  // namespace detail
}  // namespace tuple

static constexpr shiro::detail::tuple::ignore_t ignore{};

}  // namespace shiro

#endif  // #ifndef SHIRO_TUPLE_IGNORE_HPP
