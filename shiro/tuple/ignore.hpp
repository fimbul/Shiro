#ifndef SHIRO_TUPLE_IGNORE_HPP
#define SHIRO_TUPLE_IGNORE_HPP

namespace shiro {
namespace detail {
namespace tuple {

struct ignore_t {
  template <typename T>
  constexpr const ignore_t& operator=(const T&) const {
    return *this;
  }
};

}  // namespace detail
}  // namespace tuple

static constexpr shiro::detail::tuple::ignore_t ignore{};

}  // namespace shiro

#endif  // SHIRO_TUPLE_IGNORE_HPP
