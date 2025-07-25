// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/Util.h>

#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace feather_tk
{
    //! Base class for command line options.
    class ICmdLineOption : public std::enable_shared_from_this<ICmdLineOption>
    {
        FEATHER_TK_NON_COPYABLE(ICmdLineOption);

    protected:
        ICmdLineOption(
            const std::vector<std::string>& names,
            const std::string& help,
            const std::string& group = std::string());

    public:
        virtual ~ICmdLineOption() = 0;
            
        //! Parse the option.
        virtual void parse(std::vector<std::string>& args) = 0;

        //! Get the help.
        const std::string& getHelp() const;

        //! Get the group.
        const std::string& getGroup() const;

        //! Get the option name that was matched.
        const std::string& getMatchedName() const;

    protected:
        std::vector<std::string> _names;
        std::string _help;
        std::string _group;
        std::string _matchedName;
    };

    //! Command line flag option.
    class CmdLineFlagOption : public ICmdLineOption
    {
    protected:
        CmdLineFlagOption(
            const std::vector<std::string>& names,
            const std::string& help,
            const std::string& group);

    public:
        //! Create a new command line flag option.
        static std::shared_ptr<CmdLineFlagOption> create(
            const std::vector<std::string>& names,
            const std::string& help,
            const std::string& group = std::string());

        //! Get whether the flag was found.
        bool found() const;

        void parse(std::vector<std::string>& args) override;

    private:
        bool _found = false;
    };

    //! Command line value option.
    template<typename T>
    class CmdLineValueOption : public ICmdLineOption
    {
    protected:
        CmdLineValueOption(
            const std::vector<std::string>& names,
            const std::string& help,
            const std::string& group,
            const std::optional<T>& defaultValue,
            const std::string& possibleValues);

    public:
        //! Create a new command line value option.
        static std::shared_ptr<CmdLineValueOption<T> > create(
            const std::vector<std::string>& names,
            const std::string& help,
            const std::string& group = std::string(),
            const std::optional<T>& defaultValue = std::optional<T>(),
            const std::string& possibleValues = std::string());

        //! Get whether there is a value. The value is either from the command
        //! line or the default value.
        bool hasValue() const;

        //! Get the value.
        const T& getValue() const;

        void parse(std::vector<std::string>& args) override;

    private:
        std::optional<T> _value;
        std::optional<T> _defaultValue;
        std::string _possibleValues;
    };

    //! Base class for command line arguments.
    class ICmdLineArg : public std::enable_shared_from_this<ICmdLineArg>
    {
    protected:
        ICmdLineArg(
            const std::string& name,
            const std::string& help,
            bool optional);

    public:
        virtual ~ICmdLineArg() = 0;

        //! Parse the argument.
        virtual void parse(std::vector<std::string>& args) = 0;

        //! Get the argument name.
        const std::string& getName() const;

        //! Get the help.
        const std::string& getHelp() const;

        //! Get whether this argument is optional.
        bool isOptional() const;

    protected:
        std::string _name;
        std::string _help;
        bool _optional = false;
    };

    //! Command line value argument.
    template<typename T>
    class CmdLineValueArg : public ICmdLineArg
    {
    protected:
        CmdLineValueArg(
            const std::string& name,
            const std::string& help,
            bool optional);

    public:
        //! Create a new command line argument.
        static std::shared_ptr<CmdLineValueArg<T> > create(
            const std::string& name,
            const std::string& help,
            bool optional = false);

        //! Get whether there is a value.
        bool hasValue() const;

        //! Get the value.
        const T& getValue() const;

        void parse(std::vector<std::string>& args) override;

    private:
        std::optional<T> _value;
    };

    //! Command line list argument. This argument should come last since it
    //! will take all of the remaining arguments.
    template<typename T>
    class CmdLineListArg : public ICmdLineArg
    {
    protected:
        CmdLineListArg(
            const std::string& name,
            const std::string& help,
            bool optional);

    public:
        //! Create a new command line argument.
        static std::shared_ptr<CmdLineListArg<T> > create(
            const std::string& name,
            const std::string& help,
            bool optional = false);

        //! Get the list.
        const std::vector<T>& getList() const;

        void parse(std::vector<std::string>& args) override;

    private:
        std::vector<T> _list;
    };

    bool cmdLineParse(std::vector<std::string>&, std::vector<std::string>::iterator&, std::string&);
    bool cmdLineParse(std::vector<std::string>&, std::vector<std::string>::iterator&, bool&);
    bool cmdLineParse(std::vector<std::string>&, std::vector<std::string>::iterator&, int&);
    bool cmdLineParse(std::vector<std::string>&, std::vector<std::string>::iterator&, float&);
    template<typename T>
    bool cmdLineParse(std::vector<std::string>&, std::vector<std::string>::iterator&, T&);
}

#include <feather-tk/core/CmdLineInline.h>
