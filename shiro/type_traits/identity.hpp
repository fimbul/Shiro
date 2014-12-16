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

#endif  // SHIRO_TYPE_TRAITS_IDENTITY_HPP
