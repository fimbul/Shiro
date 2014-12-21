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

#ifndef SHIRO_TUPLE_DETAIL_ALL_DEFAULT_CONSTRUCTIBLE_HPP
#define SHIRO_TUPLE_DETAIL_ALL_DEFAULT_CONSTRUCTIBLE_HPP

#include <type_traits>
#include <utility>

#include <shiro/tuple/tuple_element.hpp>
#include <shiro/tuple/tuple_size.hpp>
#include <shiro/type_traits.hpp>

namespace shiro {
namespace detail {
namespace tuple {

template <typename TupleTypes>
struct all_default_constructible {
 private:
  template <std::size_t... Indices>
  static logical_and_c<
      true, std::is_default_constructible<
                shiro::tuple_element_t<Indices, TupleTypes>>::value...>
      eval(std::index_sequence<Indices...>);

 public:
  static constexpr bool value = decltype(eval(
      shiro::make_index_sequence<shiro::tuple_size<TupleTypes>::value>{}))::value;
};

}  // namespace tuple
}  // namespace detail
}  // namespace shiro

#endif  // #ifndef SHIRO_TUPLE_DETAIL_ALL_DEFAULT_CONSTRUCTIBLE_HPP
