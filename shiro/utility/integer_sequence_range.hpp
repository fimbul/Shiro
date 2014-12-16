#ifndef SHIRO_UTILITY_INTEGER_SEQUENCE_RANGE
#define SHIRO_UTILITY_INTEGER_SEQUENCE_RANGE

#include <utility>

namespace shiro {

template <typename T, T N, T M, T O = 1>
struct integer_sequence_range {
 private:
  template <T Shift, T... Indices>
  static std::integer_sequence<T, ((Indices * O) + Shift)...> eval(
      std::integer_sequence<T, Indices...>);

 public:
  using type = decltype(eval<N>(
      std::make_integer_sequence<T, (M - N) / O + ((M - N) % O > 0)>()));
};

template <std::size_t N, std::size_t M, std::size_t O = 1>
using index_sequence_range = integer_sequence_range<std::size_t, N, M, O>;

template <typename T, T N, T M, T O = 1>
using make_integer_sequence_range =
    typename integer_sequence_range<T, N, M, O>::type;

template <std::size_t N, std::size_t M, std::size_t O = 1>
using make_index_sequence_range =
    typename integer_sequence_range<std::size_t, N, M, O>::type;

}  // namespace shiro

#endif  // SHIRO_UTILITY_INTEGER_SEQUENCE_RANGE
