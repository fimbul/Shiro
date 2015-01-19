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
#include <shiro/type_traits/enabler.hpp>
#include <shiro/utility.hpp>

namespace shiro {
namespace detail {
namespace tuple {

template <typename... Types, typename... UTypes, std::size_t M, std::size_t N,
          std::enable_if_t<N - M != 1>*& = shiro::enabler>
constexpr bool tuple_eq(bool ie, const shiro::tuple<Types...>& t,
                        const shiro::tuple<UTypes...>& u,
                        shiro::index_sequence_range<M, N>);
template <typename Tuple, typename UTuple, std::size_t N>
constexpr bool tuple_eq(bool ie, const Tuple& t, const UTuple& u,
                        shiro::index_sequence_range<N, N + 1>);
constexpr bool tuple_eq(bool ie, const shiro::tuple<>&, const shiro::tuple<>&,
                        shiro::index_sequence_range<0, 0>);

template <typename Tuple, typename UTuple,
          std::size_t L, std::size_t M, std::size_t N>
constexpr bool tuple_eq(bool ie, const Tuple& t, const UTuple& u,
                        shiro::index_sequence_range<L, M> l,
                        shiro::index_sequence_range<M, N> r) {
  return tuple_eq(tuple_eq(ie, t, u, l), t, u, r);
}

template <typename Tuple, typename UTuple, std::size_t N>
constexpr bool tuple_eq(bool ie, const Tuple& t, const UTuple& u,
                        shiro::index_sequence_range<N, N + 1>) {
  return ie && (shiro::get<N>(t) == shiro::get<N>(u));
}

constexpr bool tuple_eq(bool ie, const shiro::tuple<>&, const shiro::tuple<>&,
                        shiro::index_sequence_range<0, 0>) {
  return ie;
}

template <typename... Types, typename... UTypes, std::size_t M, std::size_t N,
          std::enable_if_t<N - M != 1>*&>
constexpr bool tuple_eq(bool ie, const shiro::tuple<Types...>& t,
                        const shiro::tuple<UTypes...>& u,
                        shiro::index_sequence_range<M, N>) {
  return ie ? tuple_eq(
                  ie, t, u,
                  shiro::index_sequence_range<M, M + (N - M) / 2>{},
                  shiro::index_sequence_range<M + (N - M) / 2, N>{})
            : ie;
}

template <typename... Types, typename... UTypes>
constexpr bool tuple_eq(bool ie, const shiro::tuple<Types...>& t,
                        const shiro::tuple<UTypes...>& u) {
  return tuple_eq(ie, t, u,
                  shiro::index_sequence_range<0, sizeof...(Types)>{});
}

template <typename... Types, typename... UTypes, std::size_t M, std::size_t N,
          std::enable_if_t<N - M != 1>*& = shiro::enabler>
constexpr std::pair<bool, bool> tuple_lt(const std::pair<bool, bool>& ie,
                                         const shiro::tuple<Types...>& t,
                                         const shiro::tuple<UTypes...>& u,
                                         shiro::index_sequence_range<M, N>);
template <typename Tuple, typename UTuple, std::size_t N>
constexpr std::pair<bool, bool> tuple_lt(const std::pair<bool, bool>& ie,
                                         const Tuple& t,
                                         const UTuple& u,
                                         shiro::index_sequence_range<N, N+1>);
constexpr std::pair<bool, bool> tuple_lt(const std::pair<bool, bool>& ie,
                                         const shiro::tuple<>&,
                                         const shiro::tuple<>&,
                                         shiro::index_sequence_range<0, 0>);

template <typename Tuple, typename UTuple,
          std::size_t L, std::size_t M, std::size_t N>
constexpr std::pair<bool, bool> tuple_lt(
    const std::pair<bool, bool>& ie, const Tuple& t, const UTuple& u,
    shiro::index_sequence_range<L, M> l,
    shiro::index_sequence_range<M, N> r) {
  return tuple_lt(tuple_lt(ie, t, u, l), t, u, r);
}

template <typename Tuple, typename UTuple, std::size_t N>
constexpr std::pair<bool, bool> tuple_lt(const std::pair<bool, bool>& ie,
                                         const Tuple& t,
                                         const UTuple& u,
                                         shiro::index_sequence_range<N, N + 1>) {
  return ie.first ? ie : ie.second ? (shiro::get<N>(t) < shiro::get<N>(u))
      ? std::make_pair(true, true)
      : !(shiro::get<N>(u) < shiro::get<N>(t)) ? ie
                                               : std::make_pair(false, false)
      : ie;
}

constexpr std::pair<bool, bool> tuple_lt(const std::pair<bool, bool>& ie,
                                         const shiro::tuple<>&,
                                         const shiro::tuple<>&,
                                         shiro::index_sequence_range<0, 0>) {
  return ie;
}

template <typename... Types, typename... UTypes, std::size_t M, std::size_t N,
          std::enable_if_t<N - M != 1>*&>
constexpr std::pair<bool, bool> tuple_lt(const std::pair<bool, bool>& ie,
                                         const shiro::tuple<Types...>& t,
                                         const shiro::tuple<UTypes...>& u,
                                         shiro::index_sequence_range<M, N>) {
  return ie.first == ie.second
             ? ie
             : tuple_lt(
                   ie, t, u,
                   shiro::index_sequence_range<M, M + (N - M) / 2>{},
                   shiro::index_sequence_range<M + (N - M) / 2, N>{});
}

constexpr bool tuple_lt(const std::pair<bool, bool>& ie) {
  return ie.first && ie.second;
}

template <typename... Types, typename... UTypes>
constexpr bool tuple_lt(bool ie, const shiro::tuple<Types...>& t,
                        const shiro::tuple<UTypes...>& u) {
  return tuple_lt(tuple_lt(std::make_pair(false, ie), t, u,
                           shiro::index_sequence_range<0, sizeof...(Types)>{}));
}

}  // namespace tuple
}  // namespace detail

template <typename... Types, typename... UTypes>
constexpr bool operator==(const tuple<Types...>& t, const tuple<UTypes...>& u) {
  static_assert(sizeof...(Types) == sizeof...(UTypes),
                "tuple objects can only be compared if they have equal sizes");
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
                "tuple objects can only be compared if they have equal sizes");
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
