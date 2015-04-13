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

#ifndef SHIRO_TUPLE_TUPLE_HPP
#define SHIRO_TUPLE_TUPLE_HPP

#include <type_traits>
#include <utility>

#include <shiro/tuple/detail/all_assignable.hpp>
#include <shiro/tuple/detail/all_constructible.hpp>
#include <shiro/tuple/detail/all_default_constructible.hpp>
#include <shiro/tuple/detail/is_nothrow_swappable.hpp>
#include <shiro/tuple/detail/is_tuple_convertible.hpp>
#include <shiro/tuple/detail/make_partial_tuple_types.hpp>
#include <shiro/tuple/detail/tuple_element.hpp>
#include <shiro/tuple/detail/tuple_types.hpp>
#include <shiro/tuple/tuple_element.hpp>
#include <shiro/tuple/get.hpp>
#include <shiro/tuple/swap.hpp>
#include <shiro/type_traits.hpp>
#include <shiro/utility.hpp>

namespace shiro {
namespace detail {
namespace tuple {

template <std::size_t Index, typename Type, bool EBO>
class tuple_leaf;

template <std::size_t Index, typename Type>
class tuple_leaf<Index, Type, false> {
 public:
  using type = Type;
  Type value;

  constexpr tuple_leaf() noexcept(noexcept(Type())) : value() {}

  template <typename UType>
  explicit constexpr tuple_leaf(UType&& uarg) noexcept(
      noexcept(Type(std::forward<UType>(uarg))))
      : value(std::forward<UType>(uarg)) {}
};

template <std::size_t Index, typename Type>
class tuple_leaf<Index, Type, true> : public Type {
 public:
  using type = Type;

  constexpr tuple_leaf() noexcept(noexcept(Type())) : Type() {}

  template <typename UType>
  explicit constexpr tuple_leaf(UType&& uarg) noexcept(
      noexcept(Type(std::forward<UType>(uarg))))
      : Type(std::forward<UType>(uarg)) {}
};

template <typename Indices, typename TupleTypes>
class tuple_base;
template <std::size_t... Indices, typename TupleTypes>
class tuple_base<std::index_sequence<Indices...>,
                 TupleTypes> : public tuple_leaf<Indices,
                                                 shiro::tuple_element_t<
                                                     Indices, TupleTypes>>... {
 public:
  constexpr tuple_base() noexcept(
      shiro::logical_and_c<std::is_nothrow_default_constructible<
          shiro::tuple_element_t<Indices, TupleTypes>>::value...>::value) {};

  template <std::size_t... RIndices, typename RTypes, std::size_t... UIndices,
            typename... UTypes>
  constexpr tuple_base(
      const std::index_sequence<RIndices...>&, const RTypes&,
      const std::index_sequence<UIndices...>&,
      UTypes&&... uargs) noexcept(shiro::
                                      logical_and_c<
                                          noexcept(tuple_leaf<
                                              UIndices,
                                              shiro::tuple_element_t<
                                                  UIndices, TupleTypes>>(
                                              std::forward<UTypes>(uargs)))...,
                                          noexcept(tuple_leaf<
                                              RIndices,
                                              shiro::tuple_element_t<
                                                  RIndices,
                                                  TupleTypes>>())...>::value)
      : tuple_leaf<UIndices, shiro::tuple_element_t<UIndices, TupleTypes>>(
            std::forward<UTypes>(uargs))...,
        tuple_leaf<RIndices,
                   shiro::tuple_element_t<RIndices, TupleTypes>>()... {}

  template <typename... UTypes>
  constexpr tuple_base(const shiro::tuple<UTypes...>& t) noexcept(
      shiro::logical_and_c<noexcept(
          tuple_leaf<Indices, shiro::tuple_element_t<Indices, TupleTypes>>(
              shiro::get<Indices>(t)))...>::value)
      : tuple_leaf<Indices, shiro::tuple_element_t<Indices, TupleTypes>>(
            shiro::get<Indices>(t))... {}

  template <typename... UTypes>
  constexpr tuple_base(shiro::tuple<UTypes...>&& t) noexcept(
      shiro::logical_and_c<noexcept(
          tuple_leaf<Indices, shiro::tuple_element_t<Indices, TupleTypes>>(
              std::forward<UTypes>(shiro::get<Indices>(t))))...>::value)
      : tuple_leaf<Indices, shiro::tuple_element_t<Indices, TupleTypes>>(
            std::forward<UTypes>(shiro::get<Indices>(t)))... {}

  template <typename UIndices, typename UTypes>
  tuple_base&
  operator=(tuple_base<UIndices, UTypes>&& t) noexcept(shiro::logical_and_c<
      noexcept(shiro::detail::tuple::get<Indices>(std::declval<tuple_base&>()) =
                   std::forward<shiro::tuple_element_t<Indices, UTypes>>(
                       shiro::detail::tuple::get<Indices>(t)))...>::value) {
    swallow((shiro::detail::tuple::get<Indices>(*this) =
                 std::forward<shiro::tuple_element_t<Indices, UTypes>>(
                     shiro::detail::tuple::get<Indices>(t)))...);
    return *this;
  }

  template <typename... UTypes>
  tuple_base& operator=(const shiro::tuple<UTypes...>& t) noexcept(
      std::is_nothrow_copy_constructible<shiro::tuple<UTypes...>>::
          value and noexcept(std::declval<tuple_base&>() =
                                 std::move(shiro::tuple<UTypes...>(t).base))) {
    shiro::tuple<UTypes...> tmp(t);
    *this = std::move(tmp.base);
    return *this;
  }

  template <typename... UTypes>
  tuple_base& operator=(shiro::tuple<UTypes...>&& t) noexcept(
      noexcept(std::declval<tuple_base&>() = std::move(t.base))) {
    *this = std::move(t.base);
    return *this;
  }

  template <typename U1, typename U2>
  tuple_base& operator=(const std::pair<U1, U2>& p) noexcept(
      std::is_nothrow_copy_constructible<std::pair<U1, U2>>::value and noexcept(
          shiro::detail::tuple::get<0>(std::declval<tuple_base&>()) =
              std::forward<U1>(std::pair<U1, U2>(p).first))
      and noexcept(shiro::detail::tuple::get<1>(std::declval<tuple_base&>()) =
                       std::forward<U2>(std::pair<U1, U2>(p).second))) {
    std::pair<U1, U2> tmp(p);
    shiro::detail::tuple::get<0>(*this) = std::forward<U1>(tmp.first);
    shiro::detail::tuple::get<1>(*this) = std::forward<U2>(tmp.second);
    return *this;
  }

  template <typename U1, typename U2>
  tuple_base& operator=(std::pair<U1, U2>&& p) noexcept(
      noexcept(shiro::detail::tuple::get<0>(std::declval<tuple_base&>()) =
                   std::forward<U1>(p.first))
      and noexcept(shiro::detail::tuple::get<1>(std::declval<tuple_base&>()) =
                       std::forward<U2>(p.second))) {
    shiro::detail::tuple::get<0>(*this) = std::forward<U1>(p.first);
    shiro::detail::tuple::get<1>(*this) = std::forward<U2>(p.second);
    return *this;
  }

  void swap(tuple_base& t) noexcept(
      shiro::logical_and_c<shiro::detail::tuple::is_nothrow_swappable<
          shiro::tuple_element_t<Indices, TupleTypes>,
          shiro::tuple_element_t<Indices, TupleTypes>>::value...>::value) {
    using std::swap;
    shiro::swallow(
        (static_cast<void>(swap(shiro::detail::tuple::get<Indices>(*this),
                                shiro::detail::tuple::get<Indices>(t))),
         0)...);
  }
};

}  // namespace tuple
}  // namespace detail

template <typename... Types>
class tuple {
  using tuple_indices_t = shiro::make_index_sequence<sizeof...(Types)>;
  using tuple_types_t = shiro::detail::tuple::tuple_types<Types...>;
  using tuple_base_t =
      shiro::detail::tuple::tuple_base<tuple_indices_t, tuple_types_t>;

  tuple_base_t base;

  template <typename Indices, typename TupleTypes>
  friend class shiro::detail::tuple::tuple_base;
  template <std::size_t I, typename... Utypes>
  friend constexpr typename tuple_element<I, tuple<Utypes...>>::type& get(
      tuple<Utypes...>&) noexcept;
  template <std::size_t I, typename... Utypes>
  friend constexpr const typename tuple_element<I, tuple<Utypes...>>::type& get(
      const tuple<Utypes...>&) noexcept;
  template <std::size_t I, typename... Utypes>
  friend constexpr typename tuple_element<I, tuple<Utypes...>>::type&& get(
      tuple<Utypes...>&&) noexcept;
  template <class T, class... Utypes>
  friend constexpr T& get(tuple<Utypes...>& t) noexcept;
  template <class T, class... Utypes>
  friend constexpr const T& get(const tuple<Utypes...>& t) noexcept;
  template <class T, class... Utypes>
  friend constexpr T&& get(tuple<Utypes...>&& t) noexcept;

 public:
  template <bool Dummy = true,
            std::enable_if_t<Dummy and shiro::logical_and_c<
                std::is_default_constructible<Types>::value...>::value>*& =
                shiro::enabler>
  constexpr tuple() noexcept(
      shiro::logical_and_c<noexcept(Types())...>::value) {}

  template <
      bool Dummy = true,
      std::enable_if_t<Dummy and(sizeof...(Types) > 0) and shiro::logical_and_c<
          std::is_copy_constructible<Types>::value...>::value>*& =
          shiro::enabler>
  explicit constexpr tuple(const Types&... args) noexcept(shiro::logical_and_c<
      std::is_nothrow_copy_constructible<Types>::value...>::value)
      : base(std::index_sequence<>{}, shiro::detail::tuple::tuple_types<>{},
             tuple_indices_t{}, args...) {}

  template <
      typename... UTypes,
      std::enable_if_t<
          sizeof...(UTypes) <=
          sizeof...(Types)and shiro::detail::tuple::all_constructible<
              typename shiro::detail::tuple::make_partial_tuple_types<
                  0, sizeof...(UTypes), tuple_types_t>::type,
              shiro::detail::tuple::tuple_types<UTypes&&...>>::value and
              shiro::detail::tuple::all_default_constructible<
                  typename shiro::detail::tuple::make_partial_tuple_types<
                      sizeof...(UTypes), sizeof...(Types),
                      tuple_types_t>::type>::value and
                  shiro::detail::tuple::is_tuple_convertible<
                      typename shiro::detail::tuple::make_partial_tuple_types<
                          0, sizeof...(UTypes), tuple_types_t>::type,
                      shiro::detail::tuple::tuple_types<UTypes...>>::value>*& =
          shiro::enabler>
  explicit constexpr tuple(UTypes&&... uargs) noexcept(noexcept(tuple_base_t(
      shiro::make_index_sequence_range<sizeof...(UTypes), sizeof...(Types)>{},
      typename shiro::detail::tuple::make_partial_tuple_types<
          sizeof...(UTypes), sizeof...(Types), tuple_types_t>::type{},
      shiro::make_index_sequence<sizeof...(UTypes)>{},
      std::forward<UTypes>(uargs)...)))
      : base(shiro::make_index_sequence_range<sizeof...(UTypes),
                                              sizeof...(Types)>{},
             typename shiro::detail::tuple::make_partial_tuple_types<
                 sizeof...(UTypes), sizeof...(Types), tuple_types_t>::type{},
             shiro::make_index_sequence<sizeof...(UTypes)>{},
             std::forward<UTypes>(uargs)...) {}

  template <typename... UTypes,
            std::enable_if_t<shiro::logical_and_c<std::is_constructible<
                Types, const UTypes&>::value...>::value>*& = shiro::enabler>
  constexpr tuple(const tuple<UTypes...>& t) noexcept(noexcept(tuple_base_t(t)))
      : base(t) {}

  template <typename... UTypes,
            std::enable_if_t<shiro::logical_and_c<std::is_constructible<
                Types, UTypes&&>::value...>::value>*& = shiro::enabler>
  constexpr tuple(tuple<UTypes...>&& t) noexcept(
      noexcept(tuple_base_t(std::move(t))))
      : base(std::move(t)) {}

  template <typename U1, typename U2, bool Dummy = true,
            std::enable_if_t<Dummy and sizeof...(Types) ==
                             2 and shiro::detail::tuple::all_constructible<
                                 tuple, tuple<const U1&, const U2&>>::value>*& =
                shiro::enabler>
  constexpr tuple(const std::pair<U1, U2>& uarg) noexcept(
      noexcept(tuple(uarg.first, uarg.second)))
      : tuple(uarg.first, uarg.second) {}

  template <
      typename U1, typename U2, bool Dummy = true,
      std::enable_if_t<Dummy and sizeof...(Types) ==
                       2 and shiro::detail::tuple::all_constructible<
                           tuple, tuple<U1&&, U2&&>>::value>*& = shiro::enabler>
  constexpr tuple(std::pair<U1, U2>&& uarg) noexcept(noexcept(
      tuple(std::forward<U1>(uarg.first), std::forward<U2>(uarg.second))))
      : tuple(std::forward<U1>(uarg.first), std::forward<U2>(uarg.second)) {}

  template <typename... UTypes,
            std::enable_if_t<
                sizeof...(Types) ==
                sizeof...(UTypes)and shiro::detail::tuple::all_assignable<
                    tuple<Types&...>, tuple<const UTypes&...>>::value>*& =
                shiro::enabler>
  tuple& operator=(const tuple<UTypes...>& t) noexcept(noexcept(base = t)) {
    base = t;
    return *this;
  }

  template <
      typename... UTypes,
      std::enable_if_t<sizeof...(Types) == sizeof...(UTypes)
                       and shiro::detail::tuple::all_assignable<
                           tuple<Types&...>, tuple<UTypes&&...>>::value>*& =
          shiro::enabler>
  tuple& operator=(tuple<UTypes...>&& t) noexcept(noexcept(base =
                                                               std::move(t))) {
    base = std::move(t);
    return *this;
  }

  template <typename U1, typename U2,
            std::enable_if_t<shiro::detail::tuple::all_assignable<
                tuple<Types&...>, tuple<const U1&, const U2&>>::value>*& =
                shiro::enabler>
  tuple& operator=(const std::pair<U1, U2>& p) noexcept(noexcept(base = p)) {
    base = p;
    return *this;
  }

  template <typename U1, typename U2,
            std::enable_if_t<shiro::detail::tuple::all_assignable<
                tuple<Types&...>, tuple<U1&&, U2&&>>::value>*& = shiro::enabler>
  tuple& operator=(std::pair<U1, U2>&& p) noexcept(noexcept(base =
                                                                std::move(p))) {
    base = std::move(p);
    return *this;
  }

  void swap(tuple& t) noexcept(noexcept(base.swap(t.base))) {
    base.swap(t.base);
  }
};

template <>
class tuple<> {
 public:
  constexpr tuple() noexcept {}

  constexpr tuple(const tuple&) noexcept = default;

  constexpr tuple(tuple&&) noexcept = default;

  tuple& operator=(const tuple&) noexcept = default;

  tuple& operator=(tuple&&) noexcept = default;

  void swap(tuple& t) noexcept {}
};

}  // namespace shiro

#endif  // #ifndef SHIRO_TUPLE_TUPLE_HPP
