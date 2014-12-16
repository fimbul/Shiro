#ifndef SHIRO_TUPLE_TUPLE_FWD_HPP
#define SHIRO_TUPLE_TUPLE_FWD_HPP

namespace shiro {

template <typename... Types>
class tuple;

template <std::size_t I, typename Tuple>
class tuple_element;

namespace detail {
namespace tuple {

template <typename... Types>
class tuple_types;
 
template <typename Indices, typename TupleTypes>
class tuple_base;

template <std::size_t I, typename T>
class tuple_leaf;
 
}  // namespace tuple
}  // namespace detail

}  // namespace shiro

#endif  // SHIRO_TUPLE_TUPLE_FWD_HPP
