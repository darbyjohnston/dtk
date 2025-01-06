// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <array>
#include <iostream>

namespace dtk
{
    //! \name Colors
    ///@{

    //! Color.
    template<int C, typename T>
    class Color
    {
    public:
        constexpr Color();

        constexpr T operator [] (int) const;
        constexpr T& operator [] (int);
            
        constexpr const T* data() const;
        constexpr T* data();

        std::array<T, C> e;
    };

    //! One channel color (luminance).
    template<typename T>
    class Color<1, T>
    {
    public:
        constexpr Color();
        explicit constexpr Color(T);
        constexpr Color(const Color<1, T>&);

        constexpr T operator [] (int) const;
        constexpr T& operator [] (int);
            
        constexpr const T* data() const;
        constexpr T* data();
            
        std::array<T, 1> e;
        T& l;

        constexpr Color<1, T>& operator = (const Color<1, T>&);
    };

    //! Two channel color (luminance and alpha).
    template<typename T>
    class Color<2, T>
    {
    public:
        constexpr Color();
        explicit constexpr Color(T);
        constexpr Color(T, T);
        constexpr Color(const Color<2, T>&);

        constexpr T operator [] (int) const;
        constexpr T& operator [] (int);
            
        constexpr const T* data() const;
        constexpr T* data();
            
        std::array<T, 2> e;
        T& l;
        T& a;

        constexpr Color<2, T>& operator = (const Color<2, T>&);
    };

    //! Three channel color (RGB).
    template<typename T>
    class Color<3, T>
    {
    public:
        constexpr Color();
        constexpr Color(T, T, T);
        constexpr Color(const Color<3, T>&);

        constexpr T operator [] (int) const;
        constexpr T& operator [] (int);
            
        constexpr const T* data() const;
        constexpr T* data();
            
        std::array<T, 3> e;
        T& r;
        T& g;
        T& b;

        constexpr Color<3, T>& operator = (const Color<3, T>&);
    };

    //! Four channel color (RGBA).
    template<typename T>
    class Color<4, T>
    {
    public:
        constexpr Color();
        constexpr Color(T, T, T);
        constexpr Color(T, T, T, T);
        constexpr Color(const Color<4, T>&);

        constexpr T operator [] (int) const;
        constexpr T& operator [] (int);
            
        constexpr const T* data() const;
        constexpr T* data();
            
        std::array<T, 4> e;
        T& r;
        T& g;
        T& b;
        T& a;

        constexpr Color<4, T>& operator = (const Color<4, T>&);
    };

    typedef Color<1, float> Color1F;
    typedef Color<2, float> Color2F;
    typedef Color<3, float> Color3F;
    typedef Color<4, float> Color4F;
        
    template<int C, typename T>
    constexpr bool operator == (const Color<C, T>&, const Color<C, T>&);
    template<int C, typename T>
    constexpr bool operator != (const Color<C, T>&, const Color<C, T>&);
                
    template<int C, typename T>
    std::ostream& operator << (std::ostream&, const Color<C, T>&);
    template<int C, typename T>
    std::istream& operator >> (std::istream&, Color<C, T>&);

    ///@}
}

#include <dtk/core/ColorInline.h>

