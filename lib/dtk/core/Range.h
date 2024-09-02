// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <cstddef>

namespace dtk
{
    namespace core
    {
        //! \name Ranges
        ///@{
        
        //! Numeric range.
        template<typename T>
        class Range
        {
        public:
            constexpr Range();
            constexpr Range(T min, T max);

            constexpr T min() const;
            constexpr T max() const;

            constexpr bool operator == (const Range<T>&) const;
            constexpr bool operator != (const Range<T>&) const;
            constexpr bool operator < (const Range<T>&) const;

        private:
            T _min;
            T _max;
        };

        typedef Range<int> RangeI;
        typedef Range<std::size_t> RangeSizeT;
        typedef Range<float> RangeF;
        typedef Range<double> RangeD;

        //! Does the range contain the given number?
        template<typename T>
        bool contains(const Range<T>&, T);

        //! Does the range interset the given range?
        template<typename T>
        bool intersects(const Range<T>&, const Range<T>&);

        //! Expand the range to include the given number.
        template<typename T>
        Range<T> expand(const Range<T>&, T);

        //! Expand the range to include the given range.
        template<typename T>
        Range<T> expand(const Range<T>&, const Range<T>&);

        ///@}

    }
}

#include <dtk/core/RangeInline.h>
