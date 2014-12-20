#ifndef SHIRO_UTILITY_INTEGER_SEQUENCE_RANGE
#define SHIRO_UTILITY_INTEGER_SEQUENCE_RANGE

#include <type_traits>
#include <utility>

namespace shiro {
namespace detail {
namespace utility {

template <typename T, typename IndexSeq, T Next>
struct integer_sequence_range_next;
template <typename T, T... Indices, T Next>
struct integer_sequence_range_next<T, std::integer_sequence<T, Indices...>,
                                   Next> {

  using type = std::integer_sequence<T, Indices..., (Indices + Next)...>;
};

template <typename T, typename IndexSeq, T Next, T Tail>
struct integer_sequence_range_next2;
template <typename T, T... Indices, T Next, T Tail>
struct integer_sequence_range_next2<T, std::integer_sequence<T, Indices...>,
                                    Next, Tail> {

  using type = std::integer_sequence<T, Indices..., (Indices + Next)..., Tail>;
};

template <typename T, T First, T Step, T N, typename Enable = void>
struct integer_sequence_range_impl;
template <typename T, T First, T Step, T N>
struct integer_sequence_range_impl<T, First, Step, N,
                                   typename std::enable_if<(N == 0)>::type> {

  using type = std::integer_sequence<T>;
};
template <typename T, T First, T Step, T N>
struct integer_sequence_range_impl<T, First, Step, N,
                                   typename std::enable_if<(N == 1)>::type> {

  using type = std::integer_sequence<T, First>;
};
template <typename T, T First, T Step, T N>
struct integer_sequence_range_impl<
    T, First, Step, N,
    typename std::enable_if<(N > 1 && N % 2 == 0)>::
        type> : integer_sequence_range_next<T,
                                            typename integer_sequence_range_impl<
                                                T, First, Step, N / 2>::type,
                                            First + N / 2 * Step> {};
template <typename T, T First, T Step, T N>
struct integer_sequence_range_impl<
    T, First, Step, N,
    typename std::enable_if<(N > 1 && N % 2 == 1)>::
        type> : integer_sequence_range_next2<T,
                                             typename integer_sequence_range_impl<
                                                 T, First, Step, N / 2>::type,
                                             First + N / 2 * Step,
                                             First + (N - 1) * Step> {};

template <typename T, T First, typename IndexSeq>
struct integer_sequence_range_helper;
template <typename T, T First, T... Indices>
struct integer_sequence_range_helper<T, First,
                                     std::integer_sequence<T, Indices...>> {

  using type = std::integer_sequence<T, (Indices + First)...>;
};

}  // namespace utility
}  // namespace detail

template <typename T, T First, T Last, T Step = 1>
struct integer_sequence_range
    : detail::utility::integer_sequence_range_helper<
          T, First,
          typename detail::utility::integer_sequence_range_impl<
              T, 0, Step, ((Last - First) + (Step - 1)) / Step>::type> {};

template <std::size_t N, std::size_t M, std::size_t Step = 1>
using index_sequence_range = integer_sequence_range<std::size_t, N, M, Step>;

template <typename T, T N, T Step = 1>
using make_integer_sequence =
    typename integer_sequence_range<T, 0, N, Step>::type;

template <std::size_t N, std::size_t Step = 1>
using make_index_sequence =
    typename integer_sequence_range<std::size_t, 0, N, Step>::type;

template <typename T, T N, T M, T Step = 1>
using make_integer_sequence_range =
    typename integer_sequence_range<T, N, M, Step>::type;

template <std::size_t N, std::size_t M, std::size_t Step = 1>
using make_index_sequence_range =
    typename integer_sequence_range<std::size_t, N, M, Step>::type;

}  // namespace shiro

#endif  // SHIRO_UTILITY_INTEGER_SEQUENCE_RANGE
