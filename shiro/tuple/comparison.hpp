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

constexpr bool tuple_eq(bool ie, const shiro::tuple<>& t,
                        const shiro::tuple<>& u) {
  return ie;
}

template <std::size_t I, std::size_t L, typename... Types, typename... UTypes,
          std::enable_if_t<(L == 1)>*& = shiro::enabler>
constexpr bool tuple_eq(bool ie, const shiro::tuple<Types...>& t,
                        const shiro::tuple<UTypes...>& u) {
  return ie && (shiro::get<I>(t) == shiro::get<I>(u));
}

template <std::size_t I, std::size_t L, typename... Types, typename... UTypes,
          std::enable_if_t<(L > 1)>*& = shiro::enabler>
constexpr bool tuple_eq(bool ie, const shiro::tuple<Types...>& t,
                        const shiro::tuple<UTypes...>& u) {
  return ie ? tuple_eq<I * 2 + 1, L / 2>(tuple_eq<I * 2, L / 2>(ie, t, u), t, u)
            : ie;
}

template <typename... Types, typename... UTypes>
constexpr bool tuple_eq(bool ie, const shiro::tuple<Types...>& t,
                        const shiro::tuple<UTypes...>& u) {
  return tuple_eq<
      0, (sizeof...(Types) < sizeof...(UTypes) ? sizeof...(Types)
                                               : sizeof...(UTypes))>(ie, t, u);
}

constexpr bool tuple_lt(bool ie, const shiro::tuple<>& t,
                        const shiro::tuple<>& u) {
  return false;
}

template <std::size_t I, std::size_t L, typename... Types, typename... UTypes,
          std::enable_if_t<(L == 1)>*& = shiro::enabler>
constexpr std::pair<bool, bool> tuple_lt(const std::pair<bool, bool>& ie,
                                         const shiro::tuple<Types...>& t,
                                         const shiro::tuple<UTypes...>& u) {
  return ie.first ? ie : ie.second ? (shiro::get<I>(t) < shiro::get<I>(u))
      ? std::make_pair(true, true)
      : !(shiro::get<I>(u) < shiro::get<I>(t)) ? ie
                                               : std::make_pair(false, false)
      : ie;
}

template <std::size_t I, std::size_t L, typename... Types, typename... UTypes,
          std::enable_if_t<(L > 1)>*& = shiro::enabler>
constexpr std::pair<bool, bool> tuple_lt(const std::pair<bool, bool>& ie,
                                         const shiro::tuple<Types...>& t,
                                         const shiro::tuple<UTypes...>& u) {
  return ie.first == ie.second ? ie
                               : tuple_lt<I * 2 + 1, L / 2>(
                                     tuple_lt<I * 2, L / 2>(ie, t, u), t, u);
}

constexpr bool tuple_lt(const std::pair<bool, bool>& ie) {
  return ie.first && ie.second;
}

template <typename... Types, typename... UTypes>
constexpr bool tuple_lt(bool ie, const shiro::tuple<Types...>& t,
                        const shiro::tuple<UTypes...>& u) {
  return tuple_lt(
      tuple_lt<0, (sizeof...(Types) < sizeof...(UTypes) ? sizeof...(Types)
                                                        : sizeof...(UTypes))>(
          std::make_pair(false, ie), t, u));
}

}  // namespace tuple
}  // namespace detail

template <typename... Types, typename... UTypes>
constexpr bool operator==(const tuple<Types...>& t, const tuple<UTypes...>& u) {
  return shiro::detail::tuple::tuple_eq(sizeof...(Types) == sizeof...(UTypes),
                                        t, u);
}

template <typename... Types, typename... UTypes>
constexpr bool operator!=(const tuple<Types...>& t, const tuple<UTypes...>& u) {
  return !(t == u);
}

template <typename... Types, typename... UTypes>
constexpr bool operator<(const tuple<Types...>& t, const tuple<UTypes...>& u) {
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
