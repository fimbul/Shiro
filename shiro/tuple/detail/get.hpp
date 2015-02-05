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

#ifndef SHIRO_TUPLE_DETAIL_GETHPP
#define SHIRO_TUPLE_DETAIL_GETHPP

#include <utility>

#include <shiro/tuple/tuple_element.hpp>
#include <shiro/tuple/tuple_fwd.hpp>

namespace shiro {
namespace detail {
namespace tuple {

template <std::size_t I, typename T>
constexpr T& get(tuple_leaf<I, T, false>& l) noexcept {
  return l.value;
}
template <std::size_t I, typename T>
constexpr const T& get(const tuple_leaf<I, T, false>& l) noexcept {
  return l.value;
}
template <std::size_t I, typename T>
constexpr T&& get(tuple_leaf<I, T, false>&& l) noexcept {
  return std::forward<T>(l.value);
}
template <typename T, std::size_t I>
constexpr T& get(tuple_leaf<I, T, false>& l) noexcept {
  return l.value;
}
template <typename T, std::size_t I>
constexpr const T& get(const tuple_leaf<I, T, false>& l) noexcept {
  return l.value;
}
template <typename T, std::size_t I>
constexpr T&& get(tuple_leaf<I, T, false>&& l) noexcept {
  return std::forward<T>(l.value);
}
template <std::size_t I, typename T>
constexpr T& get(tuple_leaf<I, T, true>& l) noexcept {
  return l;
}
template <std::size_t I, typename T>
constexpr const T& get(const tuple_leaf<I, T, true>& l) noexcept {
  return l;
}
template <std::size_t I, typename T>
constexpr T&& get(tuple_leaf<I, T, true>&& l) noexcept {
  return std::forward<T>(l);
}
template <typename T, std::size_t I>
constexpr T& get(tuple_leaf<I, T, true>& l) noexcept {
  return l;
}
template <typename T, std::size_t I>
constexpr const T& get(const tuple_leaf<I, T, true>& l) noexcept {
  return l;
}
template <typename T, std::size_t I>
constexpr T&& get(tuple_leaf<I, T, true>&& l) noexcept {
  return std::forward<T>(l);
}

}  // namespace tuple
}  // namespace detail
}  // namespace shiro

#endif  // #ifndef SHIRO_TUPLE_DETAIL_GETHPP
