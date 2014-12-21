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

#ifndef SHIRO_TUPLE_MAKE_TUPLE_HPP
#define SHIRO_TUPLE_MAKE_TUPLE_HPP

#include <functional>
#include <type_traits>
#include <utility>

#include <shiro/tuple/tuple_fwd.hpp>

namespace shiro {
namespace detail {
namespace tuple {

template <typename T>
struct make_tuple_return_impl {
  using type = T;
};

template <typename T>
struct make_tuple_return_impl<std::reference_wrapper<T>> {
  using type = T&;
};

template <typename T>
struct make_tuple_return {
  using type = typename make_tuple_return_impl<std::decay_t<T>>::type;
};

}  // namespace tuple
}  // namespace detail

template <typename... Types>
constexpr tuple<
    typename shiro::detail::tuple::make_tuple_return<Types>::type...>
make_tuple(Types&&... args) {
  return tuple<
      typename shiro::detail::tuple::make_tuple_return<Types>::type...>(
      std::forward<Types>(args)...);
}

}  // namespace shiro

#endif  // #ifndef SHIRO_TUPLE_MAKE_TUPLE_HPP
