#ifndef SHIRO_UTILITY_SWALLOW_HPP
#define SHIRO_UTILITY_SWALLOW_HPP

namespace shiro {

template <typename... Ignore>
constexpr void swallow(Ignore&&...) {}

}  // shiro

#endif  // SHIRO_UTILITY_SWALLOW_HPP
