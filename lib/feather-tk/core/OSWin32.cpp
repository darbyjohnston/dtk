// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/core/OS.h>

#include <feather-tk/core/Memory.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX
#include <windows.h>
#include <shellapi.h>
#include <stdlib.h>
#include <VersionHelpers.h>

#include <array>
#include <codecvt>
#include <cstdlib>
#include <locale>
#include <thread>

namespace feather_tk
{
    namespace
    {
        enum class Windows
        {
            Unknown,
            _7,
            _8,
            _8_1,
            _10,

            Count
        };

        std::string getLabel(Windows value)
        {
            const std::array<std::string, static_cast<size_t>(Windows::Count)> data =
            {
                "Unknown",
                "Windows 7+",
                "Windows 8+",
                "Windows 8.1+",
                "Windows 10+"
            };
            return data[static_cast<size_t>(value)];
        }

        typedef void (WINAPI* PGNSI)(LPSYSTEM_INFO);

        Windows getWindowsVersion()
        {
            Windows out = Windows::Unknown;
#if _WIN32_WINNT >= 0x0A00
            if (IsWindows10OrGreater())
            {
                out = Windows::_10;
            }
            else
#endif
#if _WIN32_WINNT >= 0x0603
                if (IsWindows8Point1OrGreater())
                {
                    out = Windows::_8_1;
                }
                else
#endif
#if _WIN32_WINNT >= 0x0602
                    if (IsWindows8OrGreater())
                    {
                        out = Windows::_8;
                    }
                    else
#endif
#if _WIN32_WINNT >= 0x0601
                        if (IsWindows7OrGreater())
                        {
                            out = Windows::_7;
                        }
#endif
            return out;
        }

        size_t getRAMSize()
        {
            MEMORYSTATUSEX statex;
            statex.dwLength = sizeof(statex);
            GlobalMemoryStatusEx(&statex);
            return statex.ullTotalPhys;
        }
    }

    SystemInfo getSystemInfo()
    {
        SystemInfo out;
        out.name = getLabel(getWindowsVersion());
        out.cores = std::thread::hardware_concurrency();
        out.ram = getRAMSize();
        const auto d = std::lldiv(getRAMSize(), gigabyte);
        out.ramGB = d.quot + (d.rem ? 1 : 0);
        return out;
    }

    bool getEnv(const std::string& name, std::string& value)
    {
        bool out = false;
        size_t size = 0;
        wchar_t* p = 0;
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utf16;
        if (0 == _wdupenv_s(&p, &size, utf16.from_bytes(name).c_str()))
        {
            if (p)
            {
                value = utf16.to_bytes(p);
                out = true;
            }
        }
        if (p)
        {
            free(p);
        }
        return out;
    }

    bool setEnv(const std::string& name, const std::string& value)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utf16;
        return _wputenv_s(utf16.from_bytes(name).c_str(), utf16.from_bytes(value).c_str()) == 0;
    }

    bool delEnv(const std::string& name)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utf16;
        return _wputenv_s(utf16.from_bytes(name).c_str(), utf16.from_bytes(std::string()).c_str()) == 0;
    }

    void openURL(const std::string& value)
    {
        ShellExecute(0, 0, value.c_str(), 0, 0, SW_SHOW);
    }
}