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

#ifndef SHIRO_TUPLE_APPLY_HPP
#define SHIRO_TUPLE_APPLY_HPP

#include <utility>
#include <type_traits>

#include <shiro/tuple/tuple.hpp>
#include <shiro/tuple/tuple_size.hpp>
#include <shiro/utility/integer_sequence_range.hpp>

namespace shiro {
namespace detail {
namespace tuple {

template <typename F, typename Tuple, size_t... Indices>
constexpr decltype(auto)
    apply_impl(F&& f, Tuple&& t, std::index_sequence<Indices...>) {
  return std::forward<F>(f)(shiro::get<Indices>(std::forward<Tuple>(t))...);
}

}  // namespace tuple
}  // namespace detail

template <typename F, typename Tuple>
constexpr decltype(auto) apply(F&& f, Tuple&& t) {
  using Indices =
      shiro::make_index_sequence<shiro::tuple_size<std::decay_t<Tuple>>::value>;
  return shiro::detail::tuple::apply_impl(std::forward<F>(f),
                                          std::forward<Tuple>(t), Indices{});
}

}  // namespace shiro

#endif  // #ifndef SHIRO_TUPLE_APPLY_HPP
