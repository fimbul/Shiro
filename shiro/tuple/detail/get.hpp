#ifndef SHIRO_TUPLE_DETAIL_GETHPP
#define SHIRO_TUPLE_DETAIL_GETHPP

#include <utility>

#include <shiro/tuple/tuple_element.hpp>
#include <shiro/tuple/tuple_fwd.hpp>

namespace shiro {
namespace detail {
namespace tuple {

template <std::size_t I, typename T>
constexpr T& get(tuple_leaf<I, T>& l) noexcept {
  return l.value;
}
template <std::size_t I, typename T>
constexpr const T& get(const tuple_leaf<I, T>& l) noexcept {
  return l.value;
}
template <std::size_t I, typename T>
constexpr T&& get(tuple_leaf<I, T>&& l) noexcept {
  return std::forward<T>(l.value);
}
template <typename T, std::size_t I>
constexpr T& get(tuple_leaf<I, T>& l) noexcept {
  return l.value;
}
template <typename T, std::size_t I>
constexpr const T& get(const tuple_leaf<I, T>& l) noexcept {
  return l.value;
}
template <typename T, std::size_t I>
constexpr T&& get(tuple_leaf<I, T>&& l) noexcept {
  return std::forward<T>(l.value);
}

}  // namespace tuple
}  // namespace detail
}  // namespace shiro

#endif  // SHIRO_TUPLE_DETAIL_GETHPP
