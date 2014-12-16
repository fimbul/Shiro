#ifndef SHIRO_TYPE_TRAITS_LOGICAL_OR_HPP
#define SHIRO_TYPE_TRAITS_LOGICAL_OR_HPP

#include <type_traits>

namespace shiro {
namespace detail {
namespace type_traits {

template <typename... Ts>
struct logical_or_c : std::true_type {};
template <typename... Ts>
struct logical_or_c<Ts*...> : std::false_type {};

}  // namespace type_traits
}  // namespace detail

template <bool B = false, bool... Bs>
struct logical_or_c : detail::type_traits::logical_or_c<
                          typename std::conditional<B, bool, bool*>::type,
                          typename std::conditional<Bs, bool, bool*>::type...> {
};

template <typename F = std::false_type, typename... Fn>
using logical_or = logical_or_c<F::value, Fn::value...>;

}  // namespace shiro

#endif  // SHIRO_TYPE_TRAITS_LOGICAL_OR_HPP
