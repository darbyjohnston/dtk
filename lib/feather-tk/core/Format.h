// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace feather_tk
{
    //! \name String Formatting
    ///@{
        
    //! String formatting.
    //!
    //! Example:
    //! std::string result = Format("Testing {2} {1} {0}").arg("one").arg("two").arg("three");
    //!
    //! Results in the string "Testing three two one".
    class Format
    {
    public:
        Format(const std::string&);

        //! \name Arguments
        //! Replace the next argument in the string with the given value.
        //! Arguments consist of an integer enclosed by curly brackets (eg., "{0}").
        //! The argument with the smallest integer will be replaced. The
        //! object is returned so that you can chain calls together.
        ///@{

        Format& arg(const std::string&);
        Format& arg(int, int width = 0, char pad = ' ');
        Format& arg(int8_t, int width = 0, char pad = ' ');
        Format& arg(uint8_t, int width = 0, char pad = ' ');
        Format& arg(int16_t, int width = 0, char pad = ' ');
        Format& arg(uint16_t, int width = 0, char pad = ' ');
        Format& arg(float, int precision = -1, int width = 0, char pad = ' ');
        Format& arg(double, int precision = -1, int width = 0, char pad = ' ');
        template<typename T>
        Format& arg(T);

        ///@}
            
        //! Get the string.
        const std::string& str() const;

        //! Does the formatting have an error?
        bool hasError() const;
            
        //! Get the error.
        const std::string& getError() const;

        operator std::string() const;

    private:
        std::string _text;
        std::string _error;
    };
        
    std::ostream& operator << (std::ostream&, const Format&);
        
    ///@}
}

#include <feather-tk/core/FormatInline.h>

