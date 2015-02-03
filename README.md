#Shiro

Shiro is an experimental library for C++14 or later.

##Supported compilers

- gcc4.9
- clang3.5

##Usage
###Tuple

shiro::tuple is a tuple utility that has interfaces like std::tuple. It is assumed to be used for complex meta-programming, etc.. The recursion depth of its operations are restrained so that it can treat a lot of arguments.

```cpp
#include <shiro/tuple.hpp>

constexpr auto ct = shiro::make_tuple(1, 'a', true, /* arguments... */ , 0);

static_assert(shiro::get<0>(ct) == 1, "");
static_assert(shiro::get<1>(ct) == 'a', "");
static_assert(shiro::get<2>(ct) == true, "");
/* ... */
static_assert(shiro::get<shiro::tuple_size<decltype(ct)>::value - 1>(ct) == 0, "");
```

####Performance
I compiled the following code. I used a MacBook Pro (2.4GHz Intel Core i5, 16GB ram) and clang3.5.

```cpp
#include <utility>
#include <shiro/tuple.hpp>  // or #include <tuple>

static constexpr std::size_t N = 100;  // N = 1, 10, 100, or 1000

template <std::size_t... Indices>
constexpr auto f(const std::index_sequence<Indices...>&) {
  return shiro::make_tuple(Indices...);  // or std::make_tuple
}

int main() {
  constexpr auto ct = f(std::make_index_sequence<N>{});
  static_assert(shiro::get<N - 1>(ct) == N - 1, "");  // or std::get
}
```
<table>
<tr><th>N</th><th>shiro::tuple</th><th>std::tuple (libc++)</th></tr>
<tr><td>1</td><td>0.23s user 0.02s system 98% cpu 0.256 total</td><td>0.09s user 0.02s system 95% cpu 0.108 total</td></tr>
<tr><td>10</td><td>0.28s user 0.03s system 98% cpu 0.309 total</td><td>0.12s user 0.02s system 97% cpu 0.142 total</td></tr>
<tr><td>100</td><td>0.46s user 0.03s system 98% cpu 0.500 total</td><td>1.57s user 0.07s system 99% cpu 1.659 total</td></tr>
<tr><td>1000</td><td>9.06s user 0.28s system 99% cpu 9.364 total</td><td>295.04s user 19.94s system 90% cpu 5:49.41 total</td</tr>
</table>

shiro::tuple has some performance overhead even if N is small. However, if N is large, shiro::tuple performs much better than std::tuple.

##License
Boost Software License - Version 1.0