// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkUI/Label.h>

namespace dtk
{
    namespace examples
    {
        namespace dnd
        {
            class DragAndDropData : public ui::DragAndDropData
            {
            public:
                DragAndDropData(int);

                virtual ~DragAndDropData();

                int getNumber() const;

            private:
                int _number = 0;
            };

            class DragAndDropWidget : public ui::IWidget
            {
            protected:
                void _init(
                    const std::shared_ptr<core::Context>&,
                    int number,
                    const std::shared_ptr<IWidget>& parent);

                DragAndDropWidget() = default;

            public:
                virtual ~DragAndDropWidget();

                static std::shared_ptr<DragAndDropWidget> create(
                    const std::shared_ptr<core::Context>&,
                    int number,
                    const std::shared_ptr<IWidget>& parent = nullptr);

                void setGeometry(const core::Box2I&) override;
                void sizeHintEvent(const ui::SizeHintEvent&) override;
                void drawEvent(const core::Box2I&, const ui::DrawEvent&) override;
                void mouseEnterEvent() override;
                void mouseLeaveEvent() override;
                void mouseMoveEvent(ui::MouseMoveEvent&) override;
                void mousePressEvent(ui::MouseClickEvent&) override;
                void mouseReleaseEvent(ui::MouseClickEvent&) override;
                void dragEnterEvent(ui::DragAndDropEvent&) override;
                void dragLeaveEvent(ui::DragAndDropEvent&) override;
                void dropEvent(ui::DragAndDropEvent&) override;

            private:
                void _textUpdate();

                int _number = 0;
                std::shared_ptr<ui::Label> _label;
                int _border = 0;
                int _dragLength = 0;
                bool _dropTarget = false;;
            };
        }
    }
}
