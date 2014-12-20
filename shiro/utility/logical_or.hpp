#ifndef SHIRO_UTILITY_LOGICAL_OR_HPP
#define SHIRO_UTILITY_LOGICAL_OR_HPP

#include <type_traits>

namespace shiro {
namespace detail {
namespace utility {

template <typename... Ts>
struct logical_or_c : std::true_type {};
template <typename... Ts>
struct logical_or_c<Ts*...> : std::false_type {};

}  // namespace utility
}  // namespace detail

template <bool B = false, bool... Bs>
struct logical_or_c : detail::utility::logical_or_c<
                          typename std::conditional<B, bool, bool*>::type,
                          typename std::conditional<Bs, bool, bool*>::type...> {
};

template <typename F = std::false_type, typename... Fn>
using logical_or = logical_or_c<F::value, Fn::value...>;

}  // namespace shiro

#endif  // SHIRO_UTILITY_LOGICAL_OR_HPP
