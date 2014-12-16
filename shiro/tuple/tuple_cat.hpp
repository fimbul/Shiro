#ifndef SHIRO_TUPLE_TUPLE_CAT_HPP
#define SHIRO_TUPLE_TUPLE_CAT_HPP

#include <type_traits>
#include <utility>

#include <shiro/tuple/forward_as_tuple.hpp>
#include <shiro/tuple/tuple_element.hpp>
#include <shiro/tuple/tuple_size.hpp>
#include <shiro/tuple/tuple.hpp>
#include <shiro/utility.hpp>

namespace shiro {
namespace detail {
namespace tuple {

template <typename TupleTypes1, typename TupleTypes2>
struct tuple_cat_return_impl4;
template <typename... TupleTypes1, typename... TupleTypes2>
struct tuple_cat_return_impl4<shiro::tuple<TupleTypes1...>,
                              shiro::tuple<TupleTypes2...>> {
  using type = shiro::tuple<TupleTypes1..., TupleTypes2...>;
};

template <typename TupleTypes, typename LIndices, typename RIndices>
struct tuple_cat_return_impl3;
template <typename T>
struct tuple_cat_return_impl3<shiro::tuple<T>, std::index_sequence<>,
                              std::index_sequence<0>> {
  using type = T;
};
template <>
struct tuple_cat_return_impl3<shiro::tuple<>, std::index_sequence<>,
                              std::index_sequence<>> {
  using type = shiro::tuple<>;
};
template <typename TupleTypes, std::size_t... LIndices, std::size_t... RIndices>
struct tuple_cat_return_impl3<TupleTypes, std::index_sequence<LIndices...>,
                              std::index_sequence<RIndices...>> {
  using type = typename tuple_cat_return_impl4<
      typename tuple_cat_return_impl3<
          shiro::tuple<shiro::tuple_element_t<LIndices, TupleTypes>...>,
          shiro::make_index_sequence_range<0, sizeof...(LIndices) / 2>,
          shiro::make_index_sequence_range<sizeof...(LIndices) / 2,
                                           sizeof...(LIndices)>>::type,
      typename tuple_cat_return_impl3<
          shiro::tuple<shiro::tuple_element_t<RIndices, TupleTypes>...>,
          shiro::make_index_sequence_range<0, sizeof...(RIndices) / 2>,
          shiro::make_index_sequence_range<sizeof...(RIndices) / 2,
                                           sizeof...(RIndices)>>::type>::type;
};

template <typename Tuple, typename Indices>
struct tuple_cat_return_impl2;
template <typename Tuple, std::size_t... Indices>
struct tuple_cat_return_impl2<Tuple, std::index_sequence<Indices...>> {
  using type = shiro::tuple<shiro::tuple_element_t<Indices, Tuple>...>;
};

template <typename... Tuples>
struct tuple_cat_return_impl {
  using type = typename tuple_cat_return_impl3<
      shiro::tuple<Tuples...>,
      shiro::make_index_sequence_range<0, sizeof...(Tuples) / 2>,
      shiro::make_index_sequence_range<sizeof...(Tuples) / 2,
                                       sizeof...(Tuples)>>::type;
};

template <typename... Tuples>
struct tuple_cat_return {
  using type = typename tuple_cat_return_impl<typename tuple_cat_return_impl2<
      std::remove_reference_t<Tuples>,
      std::make_index_sequence<shiro::tuple_size<
          std::remove_reference_t<Tuples>>::value>>::type...>::type;
};

template <typename Indices1, typename Indices2>
struct tuple_cat_indices_impl3;
template <std::size_t... Indices1, std::size_t... Indices2>
struct tuple_cat_indices_impl3<std::index_sequence<Indices1...>,
                               std::index_sequence<Indices2...>> {
  using type = std::index_sequence<Indices1..., Indices2...>;
};

template <typename TupleIndices, typename LIndices, typename RIndices>
struct tuple_cat_indices_impl2;
template <typename T>
struct tuple_cat_indices_impl2<shiro::tuple<T>, std::index_sequence<>,
                               std::index_sequence<0>> {
  using type = T;
};
template <typename T>
struct tuple_cat_indices_impl2<shiro::tuple<T>, std::index_sequence<>,
                               std::index_sequence<>> {
  using type = std::index_sequence<>;
};
template <typename TupleIndices, std::size_t... LIndices,
          std::size_t... RIndices>
struct tuple_cat_indices_impl2<TupleIndices, std::index_sequence<LIndices...>,
                               std::index_sequence<RIndices...>> {
  using type = typename tuple_cat_indices_impl3<
      typename tuple_cat_indices_impl2<
          shiro::tuple<shiro::tuple_element_t<LIndices, TupleIndices>...>,
          shiro::make_index_sequence_range<0, sizeof...(LIndices) / 2>,
          shiro::make_index_sequence_range<sizeof...(LIndices) / 2,
                                           sizeof...(LIndices)>>::type,
      typename tuple_cat_indices_impl2<
          shiro::tuple<shiro::tuple_element_t<RIndices, TupleIndices>...>,
          shiro::make_index_sequence_range<0, sizeof...(RIndices) / 2>,
          shiro::make_index_sequence_range<sizeof...(RIndices) / 2,
                                           sizeof...(RIndices)>>::type>::type;
};

template <typename... TupleIndices>
struct tuple_cat_indices_impl {
  using type = typename tuple_cat_indices_impl2<
      shiro::tuple<TupleIndices...>,
      shiro::make_index_sequence_range<0, sizeof...(TupleIndices) / 2>,
      shiro::make_index_sequence_range<sizeof...(TupleIndices) / 2,
                                       sizeof...(TupleIndices)>>::type;
};

template <typename... Tuples>
struct tuple_cat_indices {
  using type = typename tuple_cat_indices_impl<std::make_index_sequence<
      shiro::tuple_size<std::remove_reference_t<Tuples>>::value>...>::type;
};

template <std::size_t N, typename Indices>
struct tuple_cat_indices2_impl2;
template <std::size_t N, std::size_t... Indices>
struct tuple_cat_indices2_impl2<N, std::index_sequence<Indices...>> {
  using type = std::index_sequence<(static_cast<void>(Indices), N)...>;
};

template <typename Indices, typename... TupleIndices>
struct tuple_cat_indices2_impl;
template <std::size_t... Indices, typename... TupleIndices>
struct tuple_cat_indices2_impl<std::index_sequence<Indices...>,
                               TupleIndices...> {
  using type = typename tuple_cat_indices_impl<
      typename tuple_cat_indices2_impl2<Indices, TupleIndices>::type...>::type;
};

template <typename... Tuples>
struct tuple_cat_indices2 {
  using type = typename tuple_cat_indices2_impl<
      std::make_index_sequence<sizeof...(Tuples)>,
      std::make_index_sequence<
          shiro::tuple_size<std::remove_reference_t<Tuples>>::value>...>::type;
};

template <typename RTypes, typename Tuples, std::size_t... Indices1,
          std::size_t... Indices2>
constexpr RTypes tuple_cat(Tuples&& ts, const std::index_sequence<Indices1...>&,
                           const std::index_sequence<Indices2...>&) {
  return RTypes(std::forward<shiro::tuple_element_t<
      Indices1, std::remove_reference_t<shiro::tuple_element_t<
                    Indices2, std::remove_reference_t<Tuples>>>>>(
      shiro::get<Indices1>(shiro::get<Indices2>(ts)))...);
}

}  // namespace tuple
}  // namespace detal

template <typename... Tuples>
constexpr typename shiro::detail::tuple::tuple_cat_return<Tuples...>::type
tuple_cat(Tuples&&... ts) {
  return shiro::detail::tuple::tuple_cat<
      typename shiro::detail::tuple::tuple_cat_return<Tuples...>::type>(
      shiro::forward_as_tuple(std::forward<Tuples>(ts)...),
      typename shiro::detail::tuple::tuple_cat_indices<Tuples...>::type{},
      typename shiro::detail::tuple::tuple_cat_indices2<Tuples...>::type{});
}

}  // namespace shiro

#endif  // SHIRO_TUPLE_TUPLE_CAT_HPP
