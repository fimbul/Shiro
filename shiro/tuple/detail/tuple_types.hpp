#ifndef SHIRO_TUPLE_DETAIL_TUPLE_TYPES_HPP
#define SHIRO_TUPLE_DETAIL_TUPLE_TYPES_HPP

#include <type_traits>
#include <utility>

#include <shiro/tuple/detail/tuple_types.hpp>
#include <shiro/tuple/tuple_fwd.hpp>
#include <shiro/tuple/tuple_element.hpp>
#include <shiro/type_traits.hpp>
#include <shiro/utility.hpp>

namespace shiro {
namespace detail {
namespace tuple {

template <std::size_t N, typename T>
struct tuple_types_leaf {
  using type = T;
  static constexpr std::size_t value = N;
};

template <typename Indices, typename... Types>
struct tuple_types_base;
template <std::size_t... Indices, typename... Types>
struct tuple_types_base<
    std::index_sequence<Indices...>,
    Types...> : tuple_types_leaf<Indices, shiro::identity<Types>>... {};

template <typename... Types>
class tuple_types {
  using tuple_types_base_t =
      tuple_types_base<shiro::make_index_sequence<sizeof...(Types)>, Types...>;

 public:
  template <std::size_t N>
  struct at {
   private:
    template <typename T>
    static T eval(tuple_types_leaf<N, T>);

   public:
    using type =
        typename decltype(eval(std::declval<tuple_types_base_t>()))::type;
  };

  static constexpr std::size_t size = sizeof...(Types);
};

}  // namespace tuple
}  // namespace detail
}  // namespace shiro

#endif  // SHIRO_TUPLE_DETAIL_TUPLE_TYPES_HPP
