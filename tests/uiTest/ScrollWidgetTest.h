// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/ScrollWidget.h>

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class ScrollWidgetTest : public test::ITest
        {
        protected:
            ScrollWidgetTest(const std::shared_ptr<Context>&);

        public:
            virtual ~ScrollWidgetTest();

            static std::shared_ptr<ScrollWidgetTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _test(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<Window>&,
                ScrollType);
        };
    }
}

