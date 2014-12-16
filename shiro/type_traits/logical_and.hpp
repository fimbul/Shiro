#ifndef SHIRO_TYPE_TRAITS_LOGICAL_AND_HPP
#define SHIRO_TYPE_TRAITS_LOGICAL_AND_HPP

#include <type_traits>

namespace shiro {
namespace detail {
namespace type_traits {

template <typename... Ts>
struct logical_and_c : std::false_type {};
template <typename... Ts>
struct logical_and_c<Ts*...> : std::true_type {};

}  // namespace type_traits
}  // namespace detail

template <bool B = true, bool... Bs>
struct logical_and_c
    : detail::type_traits::logical_and_c<
      typename std::conditional<B, bool*, bool>::type,    
      typename std::conditional<Bs, bool*, bool>::type...> {};

template <typename F = std::true_type, typename... Fn>
using logical_and = logical_and_c<F::value, Fn::value...>;

}  // namespace shiro

#endif  // SHIRO_TYPE_TRAITS_LOGICAL_AND_HPP
