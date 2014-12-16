#ifndef SHIRO_TUPLE_TUPLE_ELEMENT_HPP
#define SHIRO_TUPLE_TUPLE_ELEMENT_HPP

#include <shiro/tuple/detail/tuple_element.hpp>
#include <shiro/tuple/detail/tuple_types.hpp>
#include <shiro/tuple/tuple_fwd.hpp>

namespace shiro {

template <std::size_t I, typename Tuple>
class tuple_element;
template <std::size_t I, typename Tuple>
class tuple_element<I, const Tuple> : public tuple_element<I, Tuple> {};
template <std::size_t I, typename Tuple>
class tuple_element<I, volatile Tuple> : public tuple_element<I, Tuple> {};
template <std::size_t I, typename Tuple>
class tuple_element<I, const volatile Tuple> : public tuple_element<I, Tuple> {};

template <std::size_t I, typename... Types>
class tuple_element<I, tuple<Types...>> : public tuple_element<
                                              I, detail::tuple::tuple_types<
                                                     Types...>> {};

template <std::size_t I, typename Tuple>
using tuple_element_t = typename tuple_element<I, Tuple>::type;

}  // namespace shiro

#endif  // SHIRO_TUPLE_TUPLE_ELEMENT_HPP
