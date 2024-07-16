// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <string>
#include <vector>

namespace dtk
{
    namespace core
    {
        //! \name Strings
        ///@{
        
        //! Arbitrary C string size.
        constexpr size_t cStringSize = 4096;

        //! String split options.
        enum class SplitOptions
        {
            DiscardEmpty,
            KeepEmpty
        };

        //! Split a string.
        std::vector<std::string> split(
            const std::string&,
            char delimeter,
            SplitOptions = SplitOptions::DiscardEmpty);

        //! Split a string.
        std::vector<std::string> split(
            const std::string&,
            const std::vector<char>& delimeters,
            SplitOptions = SplitOptions::DiscardEmpty);

        //! Join a list of strings.
        std::string join(const std::vector<std::string>&, char delimeter);

        //! Join a list of strings.
        std::string join(const std::vector<std::string>&, const std::string& delimeter);

        //! Convert to upper case.
        std::string toUpper(const std::string&);

        //! Convert to lower case.
        std::string toLower(const std::string&);

        //! Remove trailing newlines.
        void removeTrailingNewlines(std::string&);

        //! Elide a string.
        std::string elide(const std::string&, size_t = 32);

        enum class Compare
        {
            CaseSensitive,
            CaseInsensitive
        };

        //! Compare strings.
        bool compare(
            const std::string&,
            const std::string&,
            Compare = Compare::CaseSensitive);

        //! Does a string contain the sub string?
        bool contains(
            const std::string&,
            const std::string& substr,
            Compare = Compare::CaseSensitive);

        //! Convert a regular string to a wide string.
        std::wstring toWide(const std::string&);

        //! Convert a wide string to a regular string.
        std::string fromWide(const std::wstring&);

        ///@}
    }
}
