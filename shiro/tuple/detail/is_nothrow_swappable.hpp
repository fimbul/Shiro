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

#ifndef SHIRO_TUPLE_DETAIL_IS_NOTHROW_SWAPPABLE_HPP
#define SHIRO_TUPLE_DETAIL_IS_NOTHROW_SWAPPABLE_HPP

#include <utility>

namespace shiro {
namespace detail {
namespace tuple {

template <typename T1, typename T2>
struct is_nothrow_swappable {
 private:
  static constexpr bool eval() noexcept {
    using std::swap;
    return noexcept(swap(std::declval<T1&>(), std::declval<T2&>()));
  }

 public:
  static constexpr bool value = eval();
};

}  // namespace tuple
}  // namespace detail
}  // namespace shiro

#endif  // #ifndef SHIRO_TUPLE_DETAIL_IS_NOTHROW_SWAPPABLE_HPP
