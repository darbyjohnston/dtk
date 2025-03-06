// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

//! Convenience macro for making a class non-copyable.
#define DTK_NON_COPYABLE(CLASS) \
    CLASS(const CLASS&) = delete; \
    CLASS& operator = (const CLASS&) = delete

//! Convenience macro for private implementations.
//! 
//! Required includes:
//! * memory
#define DTK_PRIVATE() \
    struct Private; \
    std::unique_ptr<Private> _p

//! Convenience macro for accessing private implementations.
#define DTK_P() \
    auto& p = *_p

//! Convenience macro for enum utilities.
//! 
//! Required includes:
//! * iostream
//! * string
//! * vector
#define DTK_ENUM(ENUM) \
    std::vector<ENUM> get##ENUM##Enums(); \
    std::vector<std::string> get##ENUM##Labels(); \
    std::string getLabel(ENUM); \
    std::string to_string(ENUM); \
    void from_string(const std::string&, ENUM&); \
    std::ostream& operator << (std::ostream&, ENUM); \
    std::istream& operator >> (std::istream&, ENUM&)

//! Implementation macro for enum utilities.
//! 
//! Required includes:
//! * dtk/core/Error.h
//! * dtk/core/String.h
//! * algorithm
//! * array
//! * sstream
#define DTK_ENUM_IMPL(ENUM, ...) \
    std::vector<ENUM> get##ENUM##Enums() \
    { \
        std::vector<ENUM> out; \
        for (std::size_t i = 0; i < static_cast<std::size_t>(ENUM::Count); ++i) \
        { \
            out.push_back(static_cast<ENUM>(i)); \
        } \
        return out; \
    } \
    \
    std::vector<std::string> get##ENUM##Labels() \
    { \
        return { __VA_ARGS__ }; \
    } \
    \
    std::string getLabel(ENUM value) \
    { \
        const std::array<std::string, static_cast<std::size_t>(ENUM::Count)> data = { __VA_ARGS__ }; \
        return data[static_cast<std::size_t>(value)]; \
    } \
    \
    std::string to_string(ENUM value) \
    { \
        return getLabel(value); \
    } \
    \
    void from_string(const std::string& s, ENUM& value) \
    { \
        try \
        { \
            std::stringstream ss(s); \
            ss >> value; \
        } \
        catch (const std::exception&) \
        {} \
    } \
    \
    std::ostream& operator << (std::ostream& os, ENUM in) \
    { \
        os << get##ENUM##Labels()[static_cast<std::size_t>(in)]; \
        return os; \
    } \
    \
    std::istream& operator >> (std::istream& is, ENUM& out) \
    { \
        std::string s; \
        is >> s; \
        const auto labels = get##ENUM##Labels(); \
        const auto i = std::find_if( \
            labels.begin(), \
            labels.end(), \
            [s](const std::string& value) \
            { \
                return dtk::compare(s, value, dtk::CaseCompare::Insensitive); \
            }); \
        if (i == labels.end()) \
        { \
            throw dtk::ParseError(); \
        } \
        out = static_cast<ENUM>(i - labels.begin()); \
        return is; \
    }
