#include <type_traits>
#include <utility>

#include <shiro/utility.hpp>

int main() {
  /* index_sequence_range */
  {
    static_assert(
        std::is_same<typename shiro::index_sequence_range<0, 10>::type,
                     std::index_sequence<0, 1, 2, 3, 4, 5, 6, 7, 8, 9> >::value,
        "");
    static_assert(
        std::is_same<typename shiro::index_sequence_range<5, 10>::type,
                     std::index_sequence<5, 6, 7, 8, 9> >::value,
        "");
    static_assert(
        std::is_same<typename shiro::index_sequence_range<0, 10, 2>::type,
                     std::index_sequence<0, 2, 4, 6, 8> >::value,
        "");
    static_assert(
        std::is_same<typename shiro::index_sequence_range<0, 10, 3>::type,
                     std::index_sequence<0, 3, 6, 9> >::value,
        "");
    static_assert(
        std::is_same<typename shiro::index_sequence_range<2, 10, 2>::type,
                     std::index_sequence<2, 4, 6, 8> >::value,
        "");
    static_assert(
        std::is_same<typename shiro::index_sequence_range<2, 10, 3>::type,
                     std::index_sequence<2, 5, 8> >::value,
        "");
  }
}
