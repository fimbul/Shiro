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

#ifndef SHIRO_TUPLE_DETAIL_MAKE_PARTIAL_TUPLE_TYPES_HPP
#define SHIRO_TUPLE_DETAIL_MAKE_PARTIAL_TUPLE_TYPES_HPP

#include <utility>

#include <shiro/tuple/detail/tuple_types.hpp>
#include <shiro/tuple/tuple_fwd.hpp>
#include <shiro/utility.hpp>

namespace shiro {
namespace detail {
namespace tuple {

template <std::size_t N, std::size_t M, typename T>
struct make_partial_tuple_types {
  static_assert(N <= M, "range is invalid");
 private:
  template <std::size_t... Indices>
  static tuple_types<shiro::tuple_element_t<Indices, T>...> eval(
      std::index_sequence<Indices...>);

 public:
  using type = decltype(eval(shiro::make_index_sequence_range<N, M>{}));
};

}  // namespace tuple
}  // namespace detail
}  // namespace shiro

#endif  // #ifndef SHIRO_TUPLE_DETAIL_MAKE_PARTIAL_TUPLE_TYPES_HPP
