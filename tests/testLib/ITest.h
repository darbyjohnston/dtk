// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/Util.h>

#include <memory>
#include <string>

namespace dtk
{
    namespace core
    {
        class Context;
    }

    namespace test
    {
        //! Base class for tests.
        class ITest : public std::enable_shared_from_this<ITest>
        {
            DTK_NON_COPYABLE(ITest);

        protected:
            ITest(
                const std::shared_ptr<core::Context>&,
                const std::string& name);

        public:
            virtual ~ITest() = 0;

            const std::string& getName() const;

            virtual void run() = 0;

        protected:
            void _print(const std::string&);
            void _error(const std::string&);

            std::weak_ptr<core::Context> _context;
            std::string _name;
        };
    }
}

#define DTK_TEST_ENUM(ENUM) \
    for (auto i : get##ENUM##Enums()) \
    { \
        _print(Format(#ENUM": {0}").arg(getLabel(i))); \
    } \
    { \
        const ENUM v = ENUM::First; \
        std::stringstream ss; \
        ss << v; \
        ENUM v2; \
        ss >> v2; \
        DTK_ASSERT(v == v2); \
    }

