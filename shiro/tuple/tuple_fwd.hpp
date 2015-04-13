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

#ifndef SHIRO_TUPLE_TUPLE_FWD_HPP
#define SHIRO_TUPLE_TUPLE_FWD_HPP

#include <type_traits>

namespace shiro {

template <typename... Types>
class tuple;

template <std::size_t I, typename Tuple>
class tuple_element;

namespace detail {
namespace tuple {

template <typename... Types>
class tuple_types;
 
template <typename Indices, typename TupleTypes>
class tuple_base;

template <std::size_t I, typename T,
          bool EBO = std::is_empty<T>::value and not std::is_final<T>::value
         >
class tuple_leaf;
 
}  // namespace tuple
}  // namespace detail
}  // namespace shiro

#endif  // #ifndef SHIRO_TUPLE_TUPLE_FWD_HPP
