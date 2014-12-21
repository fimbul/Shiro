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

#ifndef SHIRO_TUPLE_COMPARISON_HPP
#define SHIRO_TUPLE_COMPARISON_HPP

#include <type_traits>
#include <utility>

#include <shiro/tuple/forward_as_tuple.hpp>
#include <shiro/tuple/get.hpp>
#include <shiro/tuple/tuple.hpp>
#include <shiro/tuple/tuple_size.hpp>
#include <shiro/utility.hpp>

namespace shiro {
namespace detail {
namespace tuple {

template <typename... Types, typename... UTypes>
constexpr bool tuple_eq(bool ie, const shiro::tuple<Types...>& t,
                        const shiro::tuple<UTypes...>& u);
template <typename T, typename U>
constexpr bool tuple_eq(bool ie, const shiro::tuple<T>& t,
                        const shiro::tuple<U>& u);
constexpr bool tuple_eq(bool ie, const shiro::tuple<>&, const shiro::tuple<>&);

template <typename Tuple, typename UTuple, std::size_t... LIndices,
          std::size_t... RIndices>
constexpr bool tuple_eq(bool ie, const Tuple& t, const UTuple& u,
                        std::index_sequence<LIndices...>,
                        std::index_sequence<RIndices...>) {
  return tuple_eq(
      tuple_eq(ie, shiro::forward_as_tuple(shiro::get<LIndices>(t)...),
               shiro::forward_as_tuple(shiro::get<LIndices>(u)...)),
      shiro::forward_as_tuple(shiro::get<RIndices>(t)...),
      shiro::forward_as_tuple(shiro::get<RIndices>(u)...));
}

template <typename T, typename U>
constexpr bool tuple_eq(bool ie, const shiro::tuple<T>& t,
                        const shiro::tuple<U>& u) {
  return ie && (shiro::get<0>(t) == shiro::get<0>(u));
}

constexpr bool tuple_eq(bool ie, const shiro::tuple<>&, const shiro::tuple<>&) {
  return ie;
}

template <typename... Types, typename... UTypes>
constexpr bool tuple_eq(bool ie, const shiro::tuple<Types...>& t,
                        const shiro::tuple<UTypes...>& u) {
  return ie ? tuple_eq(
                  ie, t, u,
                  shiro::make_index_sequence_range<0, sizeof...(Types) / 2>{},
                  shiro::make_index_sequence_range<sizeof...(Types) / 2,
                                                   sizeof...(Types)>{})
            : ie;
}

template <typename... Types, typename... UTypes>
constexpr std::pair<bool, bool> tuple_lt(const std::pair<bool, bool>& ie,
                                         const shiro::tuple<Types...>& t,
                                         const shiro::tuple<UTypes...>& u);
template <typename T, typename U>
constexpr std::pair<bool, bool> tuple_lt(const std::pair<bool, bool>& ie,
                                         const shiro::tuple<T>& t,
                                         const shiro::tuple<U>& u);
constexpr std::pair<bool, bool> tuple_lt(const std::pair<bool, bool>& ie,
                                         const shiro::tuple<>&,
                                         const shiro::tuple<>&);

template <typename Tuple, typename UTuple, std::size_t... LIndices,
          std::size_t... RIndices>
constexpr std::pair<bool, bool> tuple_lt(const std::pair<bool, bool>& ie,
                                         const Tuple& t, const UTuple& u,
                                         std::index_sequence<LIndices...>,
                                         std::index_sequence<RIndices...>) {
  return tuple_lt(
      tuple_lt(ie, shiro::forward_as_tuple(shiro::get<LIndices>(t)...),
               shiro::forward_as_tuple(shiro::get<LIndices>(u)...)),
      shiro::forward_as_tuple(shiro::get<RIndices>(t)...),
      shiro::forward_as_tuple(shiro::get<RIndices>(u)...));
}

template <typename T, typename U>
constexpr std::pair<bool, bool> tuple_lt(const std::pair<bool, bool>& ie,
                                         const shiro::tuple<T>& t,
                                         const shiro::tuple<U>& u) {
  return ie.first ? ie : ie.second ? (shiro::get<0>(t) < shiro::get<0>(u))
      ? std::make_pair(true, true)
      : !(shiro::get<0>(u) < shiro::get<0>(t)) ? ie
                                               : std::make_pair(false, false)
      : ie;
}

constexpr std::pair<bool, bool> tuple_lt(const std::pair<bool, bool>& ie,
                                         const shiro::tuple<>&,
                                         const shiro::tuple<>&) {
  return ie;
}

template <typename... Types, typename... UTypes>
constexpr std::pair<bool, bool> tuple_lt(const std::pair<bool, bool>& ie,
                                         const shiro::tuple<Types...>& t,
                                         const shiro::tuple<UTypes...>& u) {
  return ie.first == ie.second
             ? ie
             : tuple_lt(
                   ie, t, u,
                   shiro::make_index_sequence_range<0, sizeof...(Types) / 2>{},
                   shiro::make_index_sequence_range<sizeof...(Types) / 2,
                                                    sizeof...(Types)>{});
}

constexpr bool tuple_lt(const std::pair<bool, bool>& ie) {
  return ie.first && ie.second;
}

template <typename... Types, typename... UTypes>
constexpr bool tuple_lt(bool ie, const shiro::tuple<Types...>& t,
                        const shiro::tuple<UTypes...>& u) {
  return tuple_lt(tuple_lt(std::make_pair(false, ie), t, u));
}

}  // namespace tuple
}  // namespace detail

template <typename... Types, typename... UTypes>
constexpr bool operator==(const tuple<Types...>& t, const tuple<UTypes...>& u) {
  static_assert(sizeof...(Types) == sizeof...(UTypes),
                "tuple objects can only be compared if they have equal sizes.");
  return shiro::detail::tuple::tuple_eq(sizeof...(Types) == sizeof...(UTypes),
                                        t, u);
}

template <typename... Types, typename... UTypes>
constexpr bool operator!=(const tuple<Types...>& t, const tuple<UTypes...>& u) {
  return !(t == u);
}

template <typename... Types, typename... UTypes>
constexpr bool operator<(const tuple<Types...>& t, const tuple<UTypes...>& u) {
  static_assert(sizeof...(Types) == sizeof...(UTypes),
                "tuple objects can only be compared if they have equal sizes.");
  return shiro::detail::tuple::tuple_lt(sizeof...(Types) == sizeof...(UTypes),
                                        t, u);
}

template <typename... Types, typename... UTypes>
constexpr bool operator>(const tuple<Types...>& t, const tuple<UTypes...>& u) {
  return u < t;
}

template <typename... Types, typename... UTypes>
constexpr bool operator>=(const tuple<Types...>& t, const tuple<UTypes...>& u) {
  return !(t < u);
}

template <typename... Types, typename... UTypes>
constexpr bool operator<=(const tuple<Types...>& t, const tuple<UTypes...>& u) {
  return !(u < t);
}

}  // namespace shiro

#endif  // #ifndef SHIRO_TUPLE_COMPARISON_HPP
