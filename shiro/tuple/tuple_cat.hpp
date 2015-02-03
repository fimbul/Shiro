//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) fimbul 2014.
// https://github.com/fimbul/Shiro
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

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

template <typename Tuple1, typename Tuple2>
struct tuple_cat_return_impl2;
template <typename... Types1, typename... Types2>
struct tuple_cat_return_impl2<shiro::tuple<Types1...>, shiro::tuple<Types2...>> {
  using type = shiro::tuple<Types1..., Types2...>;
};

template <typename TypeTuple, typename Indices1, typename Indices2>
struct tuple_cat_return_impl;

template <typename TypeTuple, std::size_t L>
struct tuple_cat_return_impl<TypeTuple,
                             shiro::index_sequence_range<L, L>,
                             shiro::index_sequence_range<L, L>> {
  using type = shiro::tuple<>;
};

template <typename TypeTuple, std::size_t L>
struct tuple_cat_return_impl<TypeTuple,
                             shiro::index_sequence_range<L, L>,
                             shiro::index_sequence_range<L, L + 1>> {
  using type = shiro::tuple_element_t<L, TypeTuple>;
};

template <typename TypeTuple, std::size_t L, std::size_t M, std::size_t N>
struct tuple_cat_return_impl<TypeTuple,
                             shiro::index_sequence_range<L, M>,
                             shiro::index_sequence_range<M, N>> {
  using type = typename tuple_cat_return_impl2<
      typename tuple_cat_return_impl<
        TypeTuple,
        shiro::index_sequence_range<L, L + (M - L) / 2>,
        shiro::index_sequence_range<L + (M - L) / 2, M>
      >::type,
      typename tuple_cat_return_impl<
        TypeTuple,
        shiro::index_sequence_range<M, M + (N - M) / 2>,
        shiro::index_sequence_range<M + (N - M) / 2, N>
      >::type
    >::type;
};

template <typename... Tuples>
struct tuple_cat_return {
  using type = typename tuple_cat_return_impl<
      shiro::tuple<std::decay_t<Tuples>...>,
      shiro::index_sequence_range<0, sizeof...(Tuples) / 2>,
      shiro::index_sequence_range<sizeof...(Tuples) / 2, sizeof...(Tuples)>
    >::type;
};

template <typename IndexTuple1, typename IndexTuple2>
struct make_tuple_cat_index_impl2;
template <std::size_t... Indices1, std::size_t... Indices2>
struct make_tuple_cat_index_impl2<std::index_sequence<Indices1...>,
                                  std::index_sequence<Indices2...>> {
  using type = std::index_sequence<Indices1..., Indices2...>;
};

template <typename IndexTuples, typename Indices1, typename Indices2>
struct make_tuple_cat_index_impl;

template <typename IndexTuples, std::size_t L>
struct make_tuple_cat_index_impl<IndexTuples,
                           shiro::index_sequence_range<L, L>,
                           shiro::index_sequence_range<L, L>> {
  using type = std::index_sequence<>;
};

template <typename IndexTuples, std::size_t L>
struct make_tuple_cat_index_impl<IndexTuples,
                           shiro::index_sequence_range<L, L>,
                           shiro::index_sequence_range<L, L + 1>> {
  using type = shiro::tuple_element_t<L, IndexTuples>;
};

template <typename IndexTuples, std::size_t L, std::size_t M, std::size_t N>
struct make_tuple_cat_index_impl<IndexTuples,
                                 shiro::index_sequence_range<L, M>,
                                 shiro::index_sequence_range<M, N>> {
  using type = typename make_tuple_cat_index_impl2<
      typename make_tuple_cat_index_impl<
        IndexTuples,
        shiro::index_sequence_range<L, L + (M - L) / 2>,
        shiro::index_sequence_range<L + (M - L) / 2, M>
      >::type,
      typename make_tuple_cat_index_impl<
        IndexTuples,
        shiro::index_sequence_range<M, M + (N - M) / 2>,
        shiro::index_sequence_range<M + (N - M) / 2, N>
      >::type
    >::type;
};

template <typename... Tuples>
struct make_tuple_cat_index1 {
  using type = typename make_tuple_cat_index_impl<
      shiro::tuple<shiro::make_index_sequence<
        shiro::tuple_size<std::decay_t<Tuples>>::value>...>,
      shiro::index_sequence_range<0, sizeof...(Tuples) / 2>,
      shiro::index_sequence_range<sizeof...(Tuples) / 2, sizeof...(Tuples)>
    >::type;
};

template <std::size_t N, typename IndexTuple>
struct make_tuple_cat_index2_impl2;

template <std::size_t N, std::size_t... Indices>
struct make_tuple_cat_index2_impl2<N, std::index_sequence<Indices...>> {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-value"
  /* warning: left operand of comma operator has no effect [-Wunused-value] */
  using type = std::index_sequence<(Indices, N)...>; /* index_sequence<N, N, ..., N> */
#pragma GCC diagnostic pop
};

template <typename Indices, typename... IndexTuples>
struct make_tuple_cat_index2_impl;

template <std::size_t... Indices, typename... IndexTuples>
struct make_tuple_cat_index2_impl<std::index_sequence<Indices...>, IndexTuples...> {
  using type = shiro::tuple<typename make_tuple_cat_index2_impl2<Indices, IndexTuples>::type...>;
};

template <typename... Tuples>
struct make_tuple_cat_index2 {
  using type = typename make_tuple_cat_index_impl<
      typename make_tuple_cat_index2_impl<
        shiro::make_index_sequence<sizeof...(Tuples)>,
        shiro::make_index_sequence<
          shiro::tuple_size<std::decay_t<Tuples>>::value>...
        >::type,
      shiro::index_sequence_range<0, sizeof...(Tuples) / 2>,
      shiro::index_sequence_range<sizeof...(Tuples) / 2, sizeof...(Tuples)>
    >::type;
};

template <typename ReturnType, typename Tuples, std::size_t... Indices1, std::size_t... Indices2>
constexpr ReturnType tuple_cat(Tuples&& ts,
                               const std::index_sequence<Indices1...>&,
                               const std::index_sequence<Indices2...>&) {
  return ReturnType(shiro::get<Indices1>(shiro::get<Indices2>(ts))...);
}

}  // namespace tuple
}  // namespace detail

template <typename... Tuples>
constexpr typename shiro::detail::tuple::tuple_cat_return<Tuples...>::type
tuple_cat(Tuples&&... ts) {
  return shiro::detail::tuple::tuple_cat<
      typename shiro::detail::tuple::tuple_cat_return<Tuples...>::type
    >(shiro::forward_as_tuple(std::forward<Tuples>(ts)...),
      typename shiro::detail::tuple::make_tuple_cat_index1<Tuples...>::type{},
      typename shiro::detail::tuple::make_tuple_cat_index2<Tuples...>::type{});
}

}  // namespace shiro

#endif  // #ifndef SHIRO_TUPLE_TUPLE_CAT_HPP
