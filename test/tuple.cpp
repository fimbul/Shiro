///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) fimbul 2014.
// https://github.com/fimbul/Shiro
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <functional>
#include <string>
#include <utility>

#include <shiro/tuple.hpp>

int main() {
  /* meta functions */
  {
    using t = shiro::tuple<const int, char*>;
    static_assert(std::is_same<typename shiro::tuple_element<0, t>::type,
                               const int>::value,
                  "");
    static_assert(
        std::is_same<typename shiro::tuple_element<1, t>::type, char*>::value,
        "");
    static_assert(shiro::tuple_size<t>::value == 2, "");
  }
  {
    using t = const shiro::tuple<const int, char*>;
    static_assert(std::is_same<typename shiro::tuple_element<0, t>::type,
                               const int>::value,
                  "");
    static_assert(
        std::is_same<typename shiro::tuple_element<1, t>::type, char*>::value,
        "");
    static_assert(shiro::tuple_size<t>::value == 2, "");
  }
  {
    using t = volatile shiro::tuple<const int, char*>;
    static_assert(std::is_same<typename shiro::tuple_element<0, t>::type,
                               const int>::value,
                  "");
    static_assert(
        std::is_same<typename shiro::tuple_element<1, t>::type, char*>::value,
        "");
    static_assert(shiro::tuple_size<t>::value == 2, "");
  }
  {
    using t = const volatile shiro::tuple<const int, char*>;
    static_assert(std::is_same<typename shiro::tuple_element<0, t>::type,
                               const int>::value,
                  "");
    static_assert(
        std::is_same<typename shiro::tuple_element<1, t>::type, char*>::value,
        "");
    static_assert(shiro::tuple_size<t>::value == 2, "");
  }

  /* ctor */
  // default ctor
  {
    constexpr shiro::tuple<int, char> ct;
    shiro::tuple<int, char> rt;
  }
  // move ctor 1
  {
    constexpr shiro::tuple<int, char> ct(1, 'a');
    shiro::tuple<int, char> rt(1, 'a');
  }
  // move ctor 2
  {
    constexpr shiro::tuple<int, char> ct(shiro::tuple<int, char>(1, 'a'));
    shiro::tuple<int, char> rt(shiro::tuple<int, char>(1, 'a'));
    static_cast<void>(ct);
    static_cast<void>(rt);
  }
  // move ctor 3
  {
    constexpr shiro::tuple<int, char> ct(std::pair<int, char>(1, 'a'));
    shiro::tuple<int, char> rt(std::pair<int, char>(1, 'a'));
  }
  // copy ctor 1
  {
    constexpr int i = 0;
    constexpr char c = 'a';
    constexpr shiro::tuple<int, char> ct(i, c);
    shiro::tuple<int, char> rt(i, c);
  }
  // copy ctor 2
  {
    constexpr shiro::tuple<int, char> tmp(1, 'a');
    constexpr shiro::tuple<int, char> ct(tmp);
    shiro::tuple<int, char> rt(tmp);
    static_cast<void>(ct);
    static_cast<void>(rt);
  }
  // copy ctor 3
  {
    constexpr std::pair<int, char> tmp(1, 'a');
    constexpr shiro::tuple<int, char> ct(tmp);
    shiro::tuple<int, char> rt(tmp);
  }
  // convertion ctor 1
  {
    shiro::tuple<std::string> rt("Hello world!");
    assert(shiro::get<0>(rt) == "Hello world!");
  }
  // convertion ctor
  {
    shiro::tuple<const char*> tmp("Hello world!");
    shiro::tuple<std::string> rt(tmp);
    assert(shiro::get<0>(rt) == "Hello world!");
  }
  // empty tuple
  {
    constexpr shiro::tuple<> ct;
    shiro::tuple<> rt;
  }
  // partial ctor
  {
    constexpr shiro::tuple<int, char> ct(1);
    shiro::tuple<int, char> rt(1);
  }
  // reference type tuple
  {
    static constexpr int i = 0;
    constexpr shiro::tuple<const int&> ct(i);
    shiro::tuple<const int&> rt(i);
  }

  /* assignment op */
  // move assignment
  {
    shiro::tuple<int, char> tmp(2, 'b');
    shiro::tuple<int, char> rt;
    rt = std::move(tmp);
    assert(shiro::get<0>(rt) == 2);
    assert(shiro::get<1>(rt) == 'b');
  }
  {
    std::pair<int, char> tmp(2, 'b');
    shiro::tuple<int, char> rt;
    rt = std::move(tmp);
    assert(shiro::get<0>(rt) == 2);
    assert(shiro::get<1>(rt) == 'b');
  }
  // copy assignment
  {
    shiro::tuple<int, char> tmp(2, 'b');
    shiro::tuple<int, char> rt;
    rt = tmp;
    assert(shiro::get<0>(rt) == 2);
    assert(shiro::get<1>(rt) == 'b');
  }
  {
    std::pair<int, char> tmp(2, 'b');
    shiro::tuple<int, char> rt;
    rt = tmp;
    assert(shiro::get<0>(rt) == 2);
    assert(shiro::get<1>(rt) == 'b');
  }

  /* get */
  {
    constexpr shiro::tuple<int, char> ct(1, 'a');
    static_assert(shiro::get<0>(ct) == 1, "");
    static_assert(shiro::get<1>(ct) == 'a', "");
    static_assert(shiro::get<int>(ct) == 1, "");
    static_assert(shiro::get<char>(ct) == 'a', "");
    assert(shiro::get<0>(ct) == 1);
    assert(shiro::get<1>(ct) == 'a');
    assert(shiro::get<int>(ct) == 1);
    assert(shiro::get<char>(ct) == 'a');

    shiro::tuple<int, char> rt(1, 'a');
    assert(shiro::get<0>(rt) == 1);
    assert(shiro::get<1>(rt) == 'a');
    assert(shiro::get<int>(rt) == 1);
    assert(shiro::get<char>(rt) == 'a');

    /* update values */
    shiro::get<0>(rt) = 2;
    shiro::get<1>(rt) = 'b';

    assert(shiro::get<0>(rt) == 2);
    assert(shiro::get<1>(rt) == 'b');
    assert(shiro::get<int>(rt) == 2);
    assert(shiro::get<char>(rt) == 'b');

    assert(shiro::get<0>(shiro::tuple<int, char>(2, 'b')) == 2);
    assert(shiro::get<1>(shiro::tuple<int, char>(2, 'b')) == 'b');

    int i = 5;
    assert(shiro::get<0>(shiro::tuple<int&>(i)) == 5);
  }

  /* swap */
  {
    shiro::tuple<int, char> rt1(2, 'b');
    shiro::tuple<int, char> rt2(3, 'c');
    assert(shiro::get<0>(rt1) == 2);
    assert(shiro::get<1>(rt1) == 'b');
    assert(shiro::get<0>(rt2) == 3);
    assert(shiro::get<1>(rt2) == 'c');
    rt1.swap(rt2);
    assert(shiro::get<0>(rt1) == 3);
    assert(shiro::get<1>(rt1) == 'c');
    assert(shiro::get<0>(rt2) == 2);
    assert(shiro::get<1>(rt2) == 'b');
    swap(rt1, rt2);
    assert(shiro::get<0>(rt1) == 2);
    assert(shiro::get<1>(rt1) == 'b');
    assert(shiro::get<0>(rt2) == 3);
    assert(shiro::get<1>(rt2) == 'c');
  }

  /* make_tuple */
  {
    constexpr auto ct = shiro::make_tuple(1, 'a');
    static_assert(shiro::get<0>(ct) == 1, "");
    static_assert(shiro::get<1>(ct) == 'a', "");

    /* reference_wrapper */
    int i = 5;
    const int j = 10;
    auto rt = shiro::make_tuple(std::ref(i), std::cref(j));
    assert(shiro::get<0>(rt) == 5);
    assert(shiro::get<1>(rt) == 10);
    static_assert(
        std::is_same<shiro::tuple<int&, const int&>, decltype(rt)>::value, "");
  }

  /* forward_as_tuple */
  {
    int i = 0;
    int j = 5;
    auto rt = shiro::forward_as_tuple(i, j);
    shiro::get<0>(rt) = 1;
    shiro::get<1>(rt) = 6;
    assert(i == 1);
    assert(j == 6);
  }

  /* tie */
  {
    shiro::tuple<int, bool, char> tmp(10, true, 'd');
    int i;
    char c;
    shiro::tie(i, shiro::ignore, c) = tmp;
    assert(i == 10);
    assert(c == 'd');
  }

  /* comparison */
  {
    constexpr shiro::tuple<int, char> ct1(1, 'a');
    constexpr shiro::tuple<int, char> ct2(1, 'a');
    static_assert(ct1 == ct2, "");
  }
  {
    constexpr shiro::tuple<int, int, int, int, int> ct1(1, 2, 3, 4, 5);
    constexpr shiro::tuple<int, int, int, int, int> ct2(1, 2, 3, 4, 5);
    static_assert(ct1 == ct2, "");
  }
  {
    constexpr shiro::tuple<> ct1;
    constexpr shiro::tuple<> ct2;
    static_assert(ct1 == ct2, "");
  }
  {
    constexpr shiro::tuple<int, char> ct1(1, 'a');
    constexpr shiro::tuple<int, char> ct2(2, 'a');
    static_assert(ct1 != ct2, "");
  }
  {
    constexpr shiro::tuple<int, char> ct1(1, 'a');
    constexpr shiro::tuple<int, char> ct2(1, 'b');
    static_assert(ct1 != ct2, "");
  }
  {
    constexpr shiro::tuple<int, char, int> ct1(1, 'a', 0);
    constexpr shiro::tuple<int, char, int> ct2(1, 'b', 0);
    static_assert(ct1 != ct2, "");
  }
  {
    constexpr shiro::tuple<int, char, int> ct1(1, 'a', 1);
    constexpr shiro::tuple<int, char, int> ct2(1, 'a', 2);
    static_assert(ct1 != ct2, "");
  }
  {
    constexpr shiro::tuple<int, char> ct1(1, 'a');
    constexpr shiro::tuple<int, char> ct2(2, 'a');
    static_assert(ct1 < ct2, "");
  }
  {
    constexpr shiro::tuple<int, char> ct1(1, 'a');
    constexpr shiro::tuple<int, char> ct2(1, 'b');
    static_assert(ct1 < ct2, "");
  }
  {
    constexpr shiro::tuple<int, char> ct1(1, 'b');
    constexpr shiro::tuple<int, char> ct2(2, 'b');
    static_assert(ct1 < ct2, "");
  }
  {
    constexpr shiro::tuple<int, char> ct1(3, 'a');
    constexpr shiro::tuple<int, char> ct2(3, 'b');
    static_assert(ct1 < ct2, "");
  }
  {
    constexpr shiro::tuple<int, char> ct1(2, 'b');
    constexpr shiro::tuple<int, char> ct2(2, 'b');
    static_assert(!(ct1 < ct2), "");
  }
  {
    constexpr shiro::tuple<> ct1;
    constexpr shiro::tuple<> ct2;
    static_assert(!(ct1 < ct2), "");
  }
  {
    constexpr shiro::tuple<int, char> ct1(2, 'a');
    constexpr shiro::tuple<int, char> ct2(1, 'a');
    static_assert(ct1 > ct2, "");
  }
  {
    constexpr shiro::tuple<int, char> ct1(2, 'a');
    constexpr shiro::tuple<int, char> ct2(1, 'b');
    static_assert(ct1 > ct2, "");
  }
  {
    constexpr shiro::tuple<int, char> ct1(2, 'b');
    constexpr shiro::tuple<int, char> ct2(2, 'b');
    static_assert(!(ct1 > ct2), "");
  }
  {
    constexpr shiro::tuple<int, char> ct1(2, 'b');
    constexpr shiro::tuple<int, char> ct2(2, 'b');
    static_assert(ct1 <= ct2, "");
  }
  {
    constexpr shiro::tuple<int, char> ct1(2, 'b');
    constexpr shiro::tuple<int, char> ct2(3, 'b');
    static_assert(ct1 <= ct2, "");
  }
  {
    constexpr shiro::tuple<int, char> ct1(2, 'b');
    constexpr shiro::tuple<int, char> ct2(2, 'b');
    static_assert(ct1 >= ct2, "");
  }
  {
    constexpr shiro::tuple<int, char> ct1(3, 'b');
    constexpr shiro::tuple<int, char> ct2(2, 'b');
    static_assert(ct1 >= ct2, "");
  }
  {
    constexpr shiro::tuple<int, char, char> ct1(3, 'b', 'd');
    constexpr shiro::tuple<int, char, char> ct2(3, 'b', 'a');
    static_assert(ct1 >= ct2, "");
  }
  {
    constexpr shiro::tuple<int, int, int, int, int> ct1(1, 2, 3, 4, 5);
    constexpr shiro::tuple<int, int, int, int, int> ct2(1, 2, 3, 4, 4);
    static_assert(ct1 >= ct2, "");
  }

  /* tuple_cat */
  {
    constexpr auto ct = shiro::tuple_cat(shiro::make_tuple(1, 2, 'a'),
                                         shiro::make_tuple(4, 5, 'b'),
                                         shiro::make_tuple(3.14, true));
    static_assert(shiro::get<0>(ct) == 1, "");
    static_assert(shiro::get<1>(ct) == 2, "");
    static_assert(shiro::get<2>(ct) == 'a', "");
    static_assert(shiro::get<3>(ct) == 4, "");
    static_assert(shiro::get<4>(ct) == 5, "");
    static_assert(shiro::get<5>(ct) == 'b', "");
    static_assert(shiro::get<6>(ct) == 3.14, "");
    static_assert(shiro::get<7>(ct) == true, "");
  }
}
