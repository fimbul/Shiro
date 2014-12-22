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

#ifndef SHIRO_TUPLE_IS_TUPLE_HPP
#define SHIRO_TUPLE_IS_TUPLE_HPP

#include <type_traits>

#include <shiro/tuple/tuple_fwd.hpp>

namespace shiro {

template <typename T>
struct is_tuple : std::false_type {};

template <typename... Types>
struct is_tuple<shiro::tuple<Types...>> : std::true_type {};

template <typename... Types>
struct is_tuple<const shiro::tuple<Types...>> : is_tuple<
                                                    shiro::tuple<Types...>> {};

template <typename... Types>
struct is_tuple<
    volatile shiro::tuple<Types...>> : is_tuple<shiro::tuple<Types...>> {};

template <typename... Types>
struct is_tuple<const volatile shiro::tuple<Types...>> : is_tuple<shiro::tuple<
                                                             Types...>> {};

}  // namespace shiro

#endif  // ifndef SHIRO_TUPLE_IS_TUPLE_HPP
