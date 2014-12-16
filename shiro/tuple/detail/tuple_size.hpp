#ifndef SHIRO_TUPLE_TUPLE_SIZE_SIZE_HPP
#define SHIRO_TUPLE_TUPLE_SIZE_SIZE_HPP

#include <type_traits>

#include <shiro/tuple/detail/tuple_types.hpp>
#include <shiro/tuple/tuple_fwd.hpp>

namespace shiro {

template <typename Tuple>
class tuple_size;
template <typename... Types>
class tuple_size<detail::tuple::tuple_types<
    Types...>> : public std::integral_constant<std::size_t,
                                               sizeof...(Types)> {};
template <typename... Types>
class tuple_size<const detail::tuple::tuple_types<
    Types...>> : public tuple_size<detail::tuple::tuple_types<Types...>> {};
template <typename... Types>
class tuple_size<volatile detail::tuple::tuple_types<
    Types...>> : public tuple_size<detail::tuple::tuple_types<Types...>> {};
template <typename... Types>
class tuple_size<const volatile detail::tuple::tuple_types<
    Types...>> : public tuple_size<detail::tuple::tuple_types<Types...>> {};

}  // namespace shiro

#endif  // SHIRO_TUPLE_TUPLE_SIZE_SIZE_HPP
