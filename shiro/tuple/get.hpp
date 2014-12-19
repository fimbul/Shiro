#ifndef SHIRO_TUPLE_GET_HPP
#define SHIRO_TUPLE_GET_HPP

#include <shiro/tuple/detail/get.hpp>
#include <shiro/tuple/tuple_element.hpp>
#include <shiro/tuple/tuple_fwd.hpp>

namespace shiro {

template <std::size_t I, typename... UTypes>
constexpr typename tuple_element<I, tuple<UTypes...>>::type& get(
    tuple<UTypes...>& t) noexcept {
  static_assert(0 <= I && I < sizeof...(UTypes), "tuple index out of range");
  return detail::tuple::get<I>(t.base);
}
template <std::size_t I, typename... UTypes>
constexpr const typename tuple_element<I, tuple<UTypes...>>::type& get(
    const tuple<UTypes...>& t) noexcept {
  static_assert(0 <= I && I < sizeof...(UTypes), "tuple index out of range");
  return detail::tuple::get<I>(t.base);
}
template <std::size_t I, typename... UTypes>
constexpr typename tuple_element<I, tuple<UTypes...>>::type&& get(
    tuple<UTypes...>&& t) noexcept {
  static_assert(0 <= I && I < sizeof...(UTypes), "tuple index out of range");
  return std::forward<typename tuple_element<I, tuple<UTypes...>>::type>(
      detail::tuple::get<I>(t.base));
}
template <class T, class... UTypes>
constexpr T& get(tuple<UTypes...>& t) noexcept {
  return detail::tuple::get<T>(t.base);
}
template <class T, class... UTypes>
constexpr const T& get(const tuple<UTypes...>& t) noexcept {
  return detail::tuple::get<T>(t.base);
}
template <class T, class... UTypes>
constexpr T&& get(tuple<UTypes...>&& t) noexcept {
  return std::forward<T>(detail::tuple::get<T>(t.base));
}

}  // namespace shiro

#endif  // SHIRO_TUPLE_GET_HPP
