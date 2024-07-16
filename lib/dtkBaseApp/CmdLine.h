// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkCore/Util.h>

#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace dtk
{
    namespace app
    {
        //! Base class for command line options.
        class ICmdLineOption : public std::enable_shared_from_this<ICmdLineOption>
        {
            DTK_NON_COPYABLE(ICmdLineOption);

        protected:
            ICmdLineOption(
                const std::vector<std::string>& names,
                const std::string& help);

        public:
            virtual ~ICmdLineOption() = 0;
            
            //! Parse the option.
            virtual void parse(std::vector<std::string>& args) = 0;

            //! Get the option name that was matched.
            const std::string& getMatchedName() const;

            //! Get the help.
            virtual std::vector<std::string> getHelp() const = 0;

        protected:
            std::vector<std::string> _names;
            std::string _matchedName;
            std::string _help;
        };

        //! Command line flag option.
        class CmdLineFlagOption : public ICmdLineOption
        {
        protected:
            CmdLineFlagOption(
                bool& value,
                const std::vector<std::string>& names,
                const std::string& help);

        public:
            //! Create a new command line flag option.
            static std::shared_ptr<CmdLineFlagOption> create(
                bool& value,
                const std::vector<std::string>& names,
                const std::string& help);

            void parse(std::vector<std::string>& args) override;
            std::vector<std::string> getHelp() const override;

        private:
            bool& _value;
        };

        //! Command line value option.
        template<typename T>
        class CmdLineValueOption : public ICmdLineOption
        {
        protected:
            CmdLineValueOption(
                T& value,
                const std::vector<std::string>& names,
                const std::string& help,
                const std::string& defaultValue,
                const std::string& possibleValues);

        public:
            //! Create a new command line value option.
            static std::shared_ptr<CmdLineValueOption<T> > create(
                T& value,
                const std::vector<std::string>& names,
                const std::string& help,
                const std::string& defaultValue = std::string(),
                const std::string& possibleValues = std::string());

            void parse(std::vector<std::string>& args) override;
            std::vector<std::string> getHelp() const override;

        private:
            T& _value;
            std::string _defaultValue;
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
                T& value,
                const std::string& name,
                const std::string& help,
                bool optional);

        public:
            //! Create a new command line argument.
            static std::shared_ptr<CmdLineValueArg<T> > create(
                T& value,
                const std::string& name,
                const std::string& help,
                bool optional = false);

            void parse(std::vector<std::string>& args) override;

        private:
            T& _value;
        };
    }
}

#include <dtkBaseApp/CmdLineInline.h>
