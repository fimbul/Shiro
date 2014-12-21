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

#ifndef SHIRO_TYPE_TRAITS_IDENTITY_HPP
#define SHIRO_TYPE_TRAITS_IDENTITY_HPP

namespace shiro {

template <typename T>
struct identity {
  using type = T;
};

template <typename T>
struct make_identity {
  using type = identity<T>;
};

}  // namespace shiro

#endif  // #ifndef SHIRO_TYPE_TRAITS_IDENTITY_HPP
