// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/Label.h>

namespace dtk
{
    namespace examples
    {
        namespace dnd
        {
            class DragAndDropData : public dtk::DragAndDropData
            {
            public:
                DragAndDropData(int);

                virtual ~DragAndDropData();

                int getNumber() const;

            private:
                int _number = 0;
            };

            class DragAndDropWidget : public IWidget
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    int number,
                    const std::shared_ptr<IWidget>& parent);

                DragAndDropWidget() = default;

            public:
                virtual ~DragAndDropWidget();

                static std::shared_ptr<DragAndDropWidget> create(
                    const std::shared_ptr<Context>&,
                    int number,
                    const std::shared_ptr<IWidget>& parent = nullptr);

                void setGeometry(const Box2I&) override;
                void sizeHintEvent(const SizeHintEvent&) override;
                void drawEvent(const Box2I&, const DrawEvent&) override;
                void mouseEnterEvent(MouseEnterEvent&) override;
                void mouseLeaveEvent() override;
                void mouseMoveEvent(MouseMoveEvent&) override;
                void mousePressEvent(MouseClickEvent&) override;
                void mouseReleaseEvent(MouseClickEvent&) override;
                void dragEnterEvent(DragAndDropEvent&) override;
                void dragLeaveEvent(DragAndDropEvent&) override;
                void dropEvent(DragAndDropEvent&) override;

            private:
                void _textUpdate();

                int _number = 0;
                std::shared_ptr<Label> _label;
                int _border = 0;
                int _dragLength = 0;
                bool _dropTarget = false;;
            };
        }
    }
}
