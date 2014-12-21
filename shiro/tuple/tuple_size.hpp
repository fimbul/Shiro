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

#ifndef SHIRO_TUPLE_TUPLE_SIZE_HPP
#define SHIRO_TUPLE_TUPLE_SIZE_HPP

#include <type_traits>

#include <shiro/tuple/detail/tuple_size.hpp>
#include <shiro/tuple/tuple_fwd.hpp>

namespace shiro {

template <typename Tuple>
class tuple_size;
template <typename Tuple>
class tuple_size<const Tuple> : public tuple_size<Tuple> {};
template <typename Tuple>
class tuple_size<volatile Tuple> : public tuple_size<Tuple> {};
template <typename Tuple>
class tuple_size<const volatile Tuple> : public tuple_size<Tuple> {};

template <typename... Types>
class tuple_size<tuple<Types...>> : public std::integral_constant<
                                        std::size_t, sizeof...(Types)> {};
}  // namespace shiro

#endif  // #ifndef SHIRO_TUPLE_TUPLE_SIZE_HPP
