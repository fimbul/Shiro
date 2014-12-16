#include <shiro/type_traits.hpp>

int main() {
  /* logical_and */
  {
    static_assert(shiro::logical_and_c<true>::value, "");
    static_assert(!shiro::logical_and_c<false>::value, "");
    static_assert(shiro::logical_and_c<true, true, true>::value, "");
    static_assert(!shiro::logical_and_c<true, true, false>::value, "");
    static_assert(!shiro::logical_and_c<true, false, true>::value, "");
    static_assert(!shiro::logical_and_c<true, false, false>::value, "");
    static_assert(!shiro::logical_and_c<false, true, true>::value, "");
    static_assert(!shiro::logical_and_c<false, true, false>::value, "");
    static_assert(!shiro::logical_and_c<false, false, true>::value, "");
    static_assert(!shiro::logical_and_c<false, false, false>::value, "");
    static_assert(shiro::logical_and<std::true_type, std::true_type,
                                     std::true_type>::value,
                  "");
    static_assert(!shiro::logical_and<std::true_type, std::true_type,
                                      std::false_type>::value,
                  "");
    static_assert(!shiro::logical_and<std::true_type, std::false_type,
                                      std::true_type>::value,
                  "");
    static_assert(!shiro::logical_and<std::true_type, std::false_type,
                                      std::false_type>::value,
                  "");
    static_assert(!shiro::logical_and<std::false_type, std::true_type,
                                      std::true_type>::value,
                  "");
    static_assert(!shiro::logical_and<std::false_type, std::true_type,
                                      std::false_type>::value,
                  "");
    static_assert(!shiro::logical_and<std::false_type, std::false_type,
                                      std::true_type>::value,
                  "");
    static_assert(!shiro::logical_and<std::false_type, std::false_type,
                                      std::false_type>::value,
                  "");
  }

  /* logical_or */
  {
    static_assert(shiro::logical_or_c<true>::value, "");
    static_assert(!shiro::logical_or_c<false>::value, "");
    static_assert(shiro::logical_or_c<true, true, true>::value, "");
    static_assert(shiro::logical_or_c<true, true, false>::value, "");
    static_assert(shiro::logical_or_c<true, false, true>::value, "");
    static_assert(shiro::logical_or_c<true, false, false>::value, "");
    static_assert(shiro::logical_or_c<false, true, true>::value, "");
    static_assert(shiro::logical_or_c<false, true, false>::value, "");
    static_assert(shiro::logical_or_c<false, false, true>::value, "");
    static_assert(!shiro::logical_or_c<false, false, false>::value, "");
    static_assert(shiro::logical_or<std::true_type>::value, "");
    static_assert(!shiro::logical_or<std::false_type>::value, "");
    static_assert(shiro::logical_or<std::true_type>::value, "");
    static_assert(!shiro::logical_or<std::false_type>::value, "");
    static_assert(shiro::logical_or<std::true_type, std::true_type,
                                    std::true_type>::value,
                  "");
    static_assert(shiro::logical_or<std::true_type, std::true_type,
                                    std::false_type>::value,
                  "");
    static_assert(shiro::logical_or<std::true_type, std::false_type,
                                    std::true_type>::value,
                  "");
    static_assert(shiro::logical_or<std::true_type, std::false_type,
                                    std::false_type>::value,
                  "");
    static_assert(shiro::logical_or<std::false_type, std::true_type,
                                    std::true_type>::value,
                  "");
    static_assert(shiro::logical_or<std::false_type, std::true_type,
                                    std::false_type>::value,
                  "");
    static_assert(shiro::logical_or<std::false_type, std::false_type,
                                    std::true_type>::value,
                  "");
    static_assert(!shiro::logical_or<std::false_type, std::false_type,
                                     std::false_type>::value,
                  "");
  }
}
