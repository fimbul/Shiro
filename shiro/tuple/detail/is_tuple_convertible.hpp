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

#ifndef SHIRO_TUPLE_DETAIL_TUPLE_CONVERSION_HPP
#define SHIRO_TUPLE_DETAIL_TUPLE_CONVERSION_HPP

#include <type_traits>
#include <utility>

#include <shiro/tuple/tuple_fwd.hpp>
#include <shiro/type_traits.hpp>
#include <shiro/utility.hpp>

namespace shiro {
namespace detail {
namespace tuple {

template <typename Tuple, typename... UTuple>
struct is_tuple_convertible {
  static constexpr bool value = false;
};
template <typename... Types, typename... UTypes>
struct is_tuple_convertible<tuple_types<Types...>, tuple_types<UTypes...>> {
  static constexpr bool value =
      shiro::logical_and_c<std::is_convertible<Types, UTypes>::value...>::value;
};
template <typename... Types, typename... UTypes>
struct is_tuple_convertible<
    tuple_types<Types...>,
    const tuple_types<UTypes...>> : is_tuple_convertible<tuple_types<Types...>,
                                                         tuple_types<
                                                             UTypes...>> {};
template <typename... Types, typename... UTypes>
struct is_tuple_convertible<
    tuple_types<Types...>,
    volatile tuple_types<
        UTypes...>> : is_tuple_convertible<tuple_types<Types...>,
                                           tuple_types<UTypes...>> {};
template <typename... Types, typename... UTypes>
struct is_tuple_convertible<
    tuple_types<Types...>,
    const volatile tuple_types<
        UTypes...>> : is_tuple_convertible<tuple_types<Types...>,
                                           tuple_types<UTypes...>> {};

}  // namespace tuple
}  // namespace detail
}  // namespace shiro

#endif  // #ifndef SHIRO_TUPLE_DETAIL_TUPLE_CONVERSION_HPP
