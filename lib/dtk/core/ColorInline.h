// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

namespace dtk
{
    template<int C, typename T>
    constexpr Color<C, T>::Color()
    {
        for (int i = 0; i < C; ++i)
        {
            e[i] = T(0);
        }
    }

    template<int C, typename T>
    constexpr T Color<C, T>::operator [] (int i) const
    {
        return e[i];
    }

    template<int C, typename T>
    constexpr T& Color<C, T>::operator [] (int i)
    {
        return e[i];
    }

    template<int C, typename T>
    constexpr const T* Color<C, T>::data() const
    {
        return e.data();
    }

    template<int C, typename T>
    constexpr T* Color<C, T>::data()
    {
        return e.data();
    }

    template<typename T>
    constexpr Color<1, T>::Color() :
        e({ 0 }),
        l(e[0])
    {}

    template<typename T>
    constexpr Color<1, T>::Color(T l) :
        e({ l }),
        l(e[0])
    {}

    template<typename T>
    constexpr Color<1, T>::Color(const Color<1, T>& v) :
        e(v.e),
        l(e[0])
    {}

    template<typename T>
    constexpr T Color<1, T>::operator [] (int i) const
    {
        return e[i];
    }

    template<typename T>
    constexpr T& Color<1, T>::operator [] (int i)
    {
        return e[i];
    }

    template<typename T>
    constexpr const T* Color<1, T>::data() const
    {
        return e.data();
    }

    template<typename T>
    constexpr T* Color<1, T>::data()
    {
        return e.data();
    }

    template<typename T>
    constexpr Color<1, T>& Color<1, T>::operator = (const Color<1, T>& v)
    {
        e = v.e;
        return *this;
    }

    template<typename T>
    constexpr Color<2, T>::Color() :
        e({ 0, 0 }),
        l(e[0]),
        a(e[1])
    {}

    template<typename T>
    constexpr Color<2, T>::Color(T l, T a) :
        e({ l, a }),
        l(e[0]),
        a(e[1])
    {}

    template<>
    constexpr Color<2, float>::Color(float l) :
        e({ l, 1.F }),
        l(e[0]),
        a(e[1])
    {}

    template<typename T>
    constexpr Color<2, T>::Color(const Color<2, T>& v) :
        e(v.e),
        l(e[0]),
        a(e[1])
    {}

    template<typename T>
    constexpr T Color<2, T>::operator [] (int i) const
    {
        return e[i];
    }

    template<typename T>
    constexpr T& Color<2, T>::operator [] (int i)
    {
        return e[i];
    }

    template<typename T>
    constexpr const T* Color<2, T>::data() const
    {
        return e.data();
    }

    template<typename T>
    constexpr T* Color<2, T>::data()
    {
        return e.data();
    }

    template<typename T>
    constexpr Color<2, T>& Color<2, T>::operator = (const Color<2, T>& v)
    {
        e = v.e;
        return *this;
    }

    template<typename T>
    constexpr Color<3, T>::Color() :
        e({ 0, 0, 0 }),
        r(e[0]),
        g(e[1]),
        b(e[2])
    {}

    template<typename T>
    constexpr Color<3, T>::Color(T r, T g, T b) :
        e({ r, g, b }),
        r(e[0]),
        g(e[1]),
        b(e[2])
    {}

    template<typename T>
    constexpr Color<3, T>::Color(const Color<3, T>& v) :
        e(v.e),
        r(e[0]),
        g(e[1]),
        b(e[2])
    {}

    template<typename T>
    constexpr T Color<3, T>::operator [] (int i) const
    {
        return e[i];
    }

    template<typename T>
    constexpr T& Color<3, T>::operator [] (int i)
    {
        return e[i];
    }

    template<typename T>
    constexpr const T* Color<3, T>::data() const
    {
        return e.data();
    }

    template<typename T>
    constexpr T* Color<3, T>::data()
    {
        return e.data();
    }

    template<typename T>
    constexpr Color<3, T>& Color<3, T>::operator = (const Color<3, T>& v)
    {
        e = v.e;
        return *this;
    }

    template<typename T>
    constexpr Color<4, T>::Color() :
        e({ 0, 0, 0, 0 }),
        r(e[0]),
        g(e[1]),
        b(e[2]),
        a(e[3])
    {}

    template<typename T>
    constexpr Color<4, T>::Color(T r, T g, T b, T a) :
        e({ r, g, b, a }),
        r(e[0]),
        g(e[1]),
        b(e[2]),
        a(e[3])
    {}

    template<>
    constexpr Color<4, float>::Color(float r, float g, float b) :
        e({ r, g, b, 1.F }),
        r(e[0]),
        g(e[1]),
        b(e[2]),
        a(e[3])
    {}

    template<typename T>
    constexpr Color<4, T>::Color(const Color<4, T>& v) :
        e(v.e),
        r(e[0]),
        g(e[1]),
        b(e[2]),
        a(e[3])
    {}

    template<typename T>
    constexpr T Color<4, T>::operator [] (int i) const
    {
        return e[i];
    }

    template<typename T>
    constexpr T& Color<4, T>::operator [] (int i)
    {
        return e[i];
    }

    template<typename T>
    constexpr const T* Color<4, T>::data() const
    {
        return e.data();
    }

    template<typename T>
    constexpr T* Color<4, T>::data()
    {
        return e.data();
    }

    template<typename T>
    constexpr Color<4, T>& Color<4, T>::operator = (const Color<4, T>& v)
    {
        e = v.e;
        return *this;
    }

    template<int C, typename T>
    constexpr bool operator == (const Color<C, T>& a, const Color<C, T>& b)
    {
        bool out = true;
        for (int i = 0; i < C; ++i)
        {
            out &= a[i] == b[i];
        }
        return out;
    }
        
    template<int C, typename T>
    constexpr bool operator != (const Color<C, T>& a, const Color<C, T>& b)
    {
        return !(a == b);
    }
        
    template<int C, typename T>
    inline std::ostream& operator << (std::ostream& os, const Color<C, T>& v)
    {
        int i = 0;
        for (; i < C - 1; ++i)
        {
            os << v[i] << " ";
        }
        os << v[i];
        return os;
    }
        
    template<int C, typename T>
    inline std::istream& operator >> (std::istream& is, Color<C, T>& v)
    {
        for (int i = 0; i < C; ++i)
        {
            is >> v[i];
        }
        return is;
    }
}
