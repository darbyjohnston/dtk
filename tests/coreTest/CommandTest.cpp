// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/CommandTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Command.h>

namespace feather_tk
{
    namespace core_test
    {
        CommandTest::CommandTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::CommandTest")
        {}

        CommandTest::~CommandTest()
        {}

        std::shared_ptr<CommandTest> CommandTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<CommandTest>(new CommandTest(context));
        }
        
        namespace
        {
            struct Data
            {
                int value = 0;
            };

            class AddCommand : public ICommand
            {
            public:
                AddCommand(
                    int value,
                    const std::shared_ptr<Data>& data) :
                    _value(value),
                    _data(data)
                {}

                virtual ~AddCommand() {}

                void exec() override
                {
                    _data->value += _value;
                }
                void undo() override
                {
                    _data->value -= _value;
                }

            private:
                int _value = 0;
                std::shared_ptr<Data> _data;
            };
        }

        void CommandTest::run()
        {
            {
                auto data = std::make_shared<Data>();

                auto commandStack = CommandStack::create();
                bool hasUndo = false;
                bool hasRedo = false;
                auto undoObserver = ValueObserver<bool>::create(
                    commandStack->observeHasUndo(),
                    [&hasUndo](bool value)
                    {
                        hasUndo = value;
                    });
                auto redoObserver = ValueObserver<bool>::create(
                    commandStack->observeHasRedo(),
                    [&hasRedo](bool value)
                    {
                        hasRedo = value;
                    });
                FEATHER_TK_ASSERT(!hasUndo);
                FEATHER_TK_ASSERT(!hasRedo);

                commandStack->push(std::make_shared<AddCommand>(1, data));
                commandStack->push(std::make_shared<AddCommand>(2, data));
                commandStack->push(std::make_shared<AddCommand>(3, data));
                FEATHER_TK_ASSERT(6 == data->value);
                FEATHER_TK_ASSERT(hasUndo);

                commandStack->undo();
                FEATHER_TK_ASSERT(3 == data->value);
                FEATHER_TK_ASSERT(hasRedo);
                commandStack->redo();
                FEATHER_TK_ASSERT(6 == data->value);
                commandStack->undo();
                FEATHER_TK_ASSERT(3 == data->value);

                commandStack->undo();
                FEATHER_TK_ASSERT(1 == data->value);
                commandStack->undo();
                FEATHER_TK_ASSERT(0 == data->value);
                FEATHER_TK_ASSERT(!hasUndo);

                commandStack->redo();
                FEATHER_TK_ASSERT(1 == data->value);
                commandStack->redo();
                FEATHER_TK_ASSERT(3 == data->value);
                commandStack->redo();
                FEATHER_TK_ASSERT(6 == data->value);

                commandStack->clear();
                FEATHER_TK_ASSERT(!hasUndo);
                FEATHER_TK_ASSERT(!hasRedo);
            }
        }
    }
}

