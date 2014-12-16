#ifndef SHIRO_TUPLE_TUPLE_SIZE_HPP
#define SHIRO_TUPLE_TUPLE_SIZE_HPP

#include <type_traits>

#include <shiro/tuple/detail/tuple_size.hpp>
#include <shiro/tuple/tuple_fwd.hpp>

namespace shiro {

template <typename Tuple>
class tuple_size;
template <typename Tuple>
class tuple_size<const Tuple> : public tuple_size<Tuple> {};
template <typename Tuple>
class tuple_size<volatile Tuple> : public tuple_size<Tuple> {};
template <typename Tuple>
class tuple_size<const volatile Tuple> : public tuple_size<Tuple> {};

template <typename... Types>
class tuple_size<tuple<Types...>> : public std::integral_constant<
                                        std::size_t, sizeof...(Types)> {};
}  // namespace shiro

#endif  // SHIRO_TUPLE_TUPLE_SIZE_HPP
