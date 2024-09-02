// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/MessageDialog.h>

#include <dtk/ui/Label.h>
#include <dtk/ui/PushButton.h>
#include <dtk/ui/RowLayout.h>

namespace dtk
{
    class MessageDialogWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent);

        MessageDialogWidget();

    public:
        virtual ~MessageDialogWidget();

        static std::shared_ptr<MessageDialogWidget> create(
            const std::shared_ptr<Context>&,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

        void setCallback(const std::function<void(void)>&);

    private:
        std::shared_ptr<Label> _titleLabel;
        std::shared_ptr<Label> _label;
        std::shared_ptr<PushButton> _okButton;
        std::shared_ptr<VerticalLayout> _layout;
        std::function<void(void)> _callback;
    };

    class ConfirmDialogWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent);

        ConfirmDialogWidget();

    public:
        virtual ~ConfirmDialogWidget();

        static std::shared_ptr<ConfirmDialogWidget> create(
            const std::shared_ptr<Context>&,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setCallback(const std::function<void(bool)>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        std::shared_ptr<Label> _titleLabel;
        std::shared_ptr<Label> _label;
        std::shared_ptr<PushButton> _okButton;
        std::shared_ptr<PushButton> _cancelButton;
        std::shared_ptr<VerticalLayout> _layout;
        std::function<void(bool)> _callback;
    };
}