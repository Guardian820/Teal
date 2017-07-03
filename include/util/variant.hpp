﻿// Copyright (C) 2017 Samy Bensaid
// This file is part of the TealDemo project.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VARIANT_HPP
#define VARIANT_HPP

#include <iostream>
#include <utility>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <algorithm>
#include "isoneof.hpp"

// https://gist.github.com/tibordp/6909880

namespace Detail
{

template<class... Ts>
struct VariantHelper;

template<class F, class... Ts>
struct VariantHelper<F, Ts...>
{
    inline static void destroy(const std::type_index& id, void* data);
    inline static void move(const std::type_index& old_t, void* old_v, void* new_v);
    inline static void copy(const std::type_index& old_t, const void* old_v, void* new_v);
};

template<> struct VariantHelper<>
{
    inline static void destroy(const std::type_index& id, void* data) {}
    inline static void move(const std::type_index& old_t, void* old_v, void* new_v) {}
    inline static void copy(const std::type_index& old_t, const void* old_v, void* new_v) {}
};

} // namespace Detail

template<class... Ts>
class Variant
{
public:
    inline Variant();
    inline ~Variant();

    inline Variant(const Variant<Ts...>& other);
    inline Variant(Variant<Ts...>&& other);


    inline Variant<Ts...>& operator= (const Variant<Ts...>& other);
    inline Variant<Ts...>& operator= (Variant<Ts...>&& other);


    template<class T>
    inline bool is() const;

    inline bool valid() const;


    template<class T, class... Args, class = typename std::enable_if<IsOneOf<T, Ts...>::value>::type>
    inline void set(Args&&... args);

    template<class T, class = typename std::enable_if<IsOneOf<T, Ts...>::value>::type>
    inline const T& get() const;

    template<class T, class = typename std::enable_if<IsOneOf<T, Ts...>::value>::type>
    inline T& get();

    inline void reset();

private:
    using Data = typename std::aligned_union<0, Ts...>::type;
    using Helper = Detail::VariantHelper<Ts...>;

    static inline std::type_index invalid_type();

    std::type_index m_typeid;
    Data m_data;
};

#include "variant.inl"

#endif // VARIANT_HPP