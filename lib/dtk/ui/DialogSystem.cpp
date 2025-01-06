// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/DialogSystem.h>

#include <dtk/ui/ConfirmDialog.h>
#include <dtk/ui/MessageDialog.h>

namespace dtk
{
    struct DialogSystem::Private
    {
        std::shared_ptr<MessageDialog> messageDialog;
        std::shared_ptr<ConfirmDialog> confirmDialog;
    };

    DialogSystem::DialogSystem(const std::shared_ptr<Context>& context) :
        ISystem(context, "dtk::DialogSystem"),
        _p(new Private)
    {}

    DialogSystem::~DialogSystem()
    {}

    std::shared_ptr<DialogSystem> DialogSystem::create(const std::shared_ptr<Context>& context)
    {
        return std::shared_ptr<DialogSystem>(new DialogSystem(context));
    }

    void DialogSystem::message(
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWindow>& window)
    {
        DTK_P();
        if (auto context = _context.lock())
        {
            p.messageDialog = MessageDialog::create(context, title, text);
            p.messageDialog->open(window);
            p.messageDialog->setCallback(
                [this]
                {
                    _p->messageDialog->close();
                });
            p.messageDialog->setCloseCallback(
                [this]
                {
                    _p->messageDialog.reset();
                });
        }
    }

    void DialogSystem::confirm(
        const std::string& title,
        const std::string& text,
        const std::shared_ptr<IWindow>& window,
        const std::function<void(bool)>& callback)
    {
        DTK_P();
        if (auto context = _context.lock())
        {
            p.confirmDialog = ConfirmDialog::create(context, title, text);
            p.confirmDialog->open(window);
            p.confirmDialog->setCallback(
                [this, callback](bool value)
                {
                    callback(value);
                    _p->confirmDialog->close();
                });
            p.confirmDialog->setCloseCallback(
                [this]
                {
                    _p->confirmDialog.reset();
                });
        }
    }
}