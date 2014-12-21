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

#ifndef SHIRO_UTILITY_SWALLOW_HPP
#define SHIRO_UTILITY_SWALLOW_HPP

namespace shiro {

template <typename... Ignore>
constexpr void swallow(Ignore&&...) {}

}  // shiro

#endif  // #ifndef SHIRO_UTILITY_SWALLOW_HPP
