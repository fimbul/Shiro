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

#ifndef SHIRO_UTILITY_LOGICAL_AND_HPP
#define SHIRO_UTILITY_LOGICAL_AND_HPP

#include <type_traits>

namespace shiro {
namespace detail {
namespace utility {

template <typename... Ts>
struct logical_and_c : std::false_type {};
template <typename... Ts>
struct logical_and_c<Ts*...> : std::true_type {};

}  // namespace utility
}  // namespace detail

template <bool B = true, bool... Bs>
struct logical_and_c
    : detail::utility::logical_and_c<
          typename std::conditional<B, bool*, bool>::type,
          typename std::conditional<Bs, bool*, bool>::type...> {};

template <typename F = std::true_type, typename... Fn>
using logical_and = logical_and_c<F::value, Fn::value...>;

}  // namespace shiro

#endif  // #ifndef SHIRO_UTILITY_LOGICAL_AND_HPP
