// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/core/Error.h>
#include <feather-tk/core/String.h>

#include <algorithm>

namespace feather_tk
{
    inline const std::string& ICmdLineOption::getMatchedName() const
    {
        return _matchedName;
    }

    template<typename T>
    inline CmdLineValueOption<T>::CmdLineValueOption(
        T& value,
        const std::vector<std::string>& names,
        const std::string& help,
        const std::string& defaultValue,
        const std::string& possibleValues) :
        ICmdLineOption(names, help),
        _value(value),
        _defaultValue(defaultValue),
        _possibleValues(possibleValues)
    {}
        
    template<typename T>
    inline std::shared_ptr<CmdLineValueOption<T> > CmdLineValueOption<T>::create(
        T& value,
        const std::vector<std::string>& names,
        const std::string& help,
        const std::string& defaultValue,
        const std::string& possibleValues)
    {
        return std::shared_ptr<CmdLineValueOption<T> >(new CmdLineValueOption<T>(
            value,
            names,
            help,
            defaultValue,
            possibleValues));
    }

    template<typename T>
    inline void CmdLineValueOption<T>::parse(std::vector<std::string>& args)
    {
        for (const auto& name : _names)
        {
            auto i = std::find(args.begin(), args.end(), name);
            if (i != args.end())
            {
                _matchedName = name;
                i = args.erase(i);
                if (!cmdLineParse(args, i, _value))
                {
                    throw ParseError();
                }
            }
        }
    }

    template<>
    inline void CmdLineValueOption<std::string>::parse(std::vector<std::string>& args)
    {
        for (const auto& name : _names)
        {
            auto i = std::find(args.begin(), args.end(), name);
            if (i != args.end())
            {
                _matchedName = name;
                i = args.erase(i);
                if (i != args.end())
                {
                    _value = *i;
                    i = args.erase(i);
                }
                else
                {
                    throw ParseError();
                }
            }
        }
    }

    template<typename T>
    inline std::vector<std::string> CmdLineValueOption<T>::getHelp() const
    {
        std::vector<std::string> out;
        out.push_back(join(_names, ", ") + " (value)");
        out.push_back(_help);
        if (!_defaultValue.empty())
        {
            out.push_back("Default value: " + _defaultValue);
        }
        if (!_possibleValues.empty())
        {
            out.push_back("Possible values: " + _possibleValues);
        }
        return out;
    }

    inline ICmdLineArg::ICmdLineArg(
        const std::string& name,
        const std::string& help,
        bool optional) :
        _name(name),
        _help(help),
        _optional(optional)
    {}

    inline ICmdLineArg::~ICmdLineArg()
    {}

    inline const std::string& ICmdLineArg::getName() const
    {
        return _name;
    }

    inline const std::string& ICmdLineArg::getHelp() const
    {
        return _help;
    }

    inline bool ICmdLineArg::isOptional() const
    {
        return _optional;
    }

    template<typename T>
    inline CmdLineValueArg<T>::CmdLineValueArg(
        T& value,
        const std::string& name,
        const std::string& help,
        bool optional) :
        ICmdLineArg(name, help, optional),
        _value(value)
    {}

    template<typename T>
    inline std::shared_ptr<CmdLineValueArg<T> > CmdLineValueArg<T>::create(
        T& value,
        const std::string& name,
        const std::string& help,
        bool optional)
    {
        return std::shared_ptr<CmdLineValueArg<T> >(new CmdLineValueArg<T>(value, name, help, optional));
    }

    template<typename T>
    inline void CmdLineValueArg<T>::parse(std::vector<std::string>& args)
    {
        auto i = args.begin();
        if (!cmdLineParse(args, i, _value))
        {
            throw ParseError();
        }
    }

    template<>
    inline void CmdLineValueArg<std::string>::parse(std::vector<std::string>& args)
    {
        auto i = args.begin();
        if (i != args.end())
        {
            _value = *i;
            i = args.erase(i);
        }
        else
        {
            throw ParseError();
        }
    }

    template<typename T>
    inline CmdLineListArg<T>::CmdLineListArg(
        std::vector<T>& list,
        const std::string& name,
        const std::string& help,
        bool optional) :
        ICmdLineArg(name, help, optional),
        _list(list)
    { }

    template<typename T>
    inline std::shared_ptr<CmdLineListArg<T> > CmdLineListArg<T>::create(
        std::vector<T>& list,
        const std::string& name,
        const std::string& help,
        bool optional)
    {
        return std::shared_ptr<CmdLineListArg<T> >(new CmdLineListArg<T>(list, name, help, optional));
    }

    template<typename T>
    inline void CmdLineListArg<T>::parse(std::vector<std::string>& args)
    {
        auto i = args.begin();
        while (i != args.end())
        {
            T value;
            if (!cmdLineParse(args, i, value))
            {
                throw ParseError();
            }
            _list.push_back(value);
        }
    }

    template<typename T>
    inline bool cmdLineParse(std::vector<std::string>& args, std::vector<std::string>::iterator& it, T& value)
    {
        bool out = false;
        if (it != args.end())
        {
            std::stringstream ss(*it);
            ss >> value;
            it = args.erase(it);
            out = true;
        }
        return out;
    }
}
