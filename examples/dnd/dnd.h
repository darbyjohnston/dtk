// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/Label.h>
#include <dtk/ui/RowLayout.h>

namespace dtk
{
    namespace examples
    {
        namespace dnd
        {
            class DragWidget;

            class DragAndDropData : public dtk::DragAndDropData
            {
            public:
                DragAndDropData(const std::shared_ptr<DragWidget>&);

                virtual ~DragAndDropData();

                const std::shared_ptr<DragWidget>& getWidget() const;

            private:
                std::shared_ptr<DragWidget> _widget;
            };

            class DragWidget : public IWidget
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    int,
                    const std::shared_ptr<IWidget>& parent);

                DragWidget() = default;

            public:
                virtual ~DragWidget();

                static std::shared_ptr<DragWidget> create(
                    const std::shared_ptr<Context>&,
                    int,
                    const std::shared_ptr<IWidget>& parent = nullptr);

                void setGeometry(const Box2I&) override;
                void sizeHintEvent(const SizeHintEvent&) override;
                void drawEvent(const Box2I&, const DrawEvent&) override;
                void mouseEnterEvent(MouseEnterEvent&) override;
                void mouseLeaveEvent() override;
                void mouseMoveEvent(MouseMoveEvent&) override;

            private:
                std::shared_ptr<Label> _label;
                int _number = 0;
                int _dragLength = 0;
            };

            class ContainerWidget : public IWidget
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>& parent);

                ContainerWidget() = default;

            public:
                virtual ~ContainerWidget();

                static std::shared_ptr<ContainerWidget> create(
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>& parent = nullptr);

                void addWidget(const std::shared_ptr<DragWidget>&);

                void setGeometry(const Box2I&) override;
                void sizeHintEvent(const SizeHintEvent&) override;
                void drawOverlayEvent(const Box2I&, const DrawEvent&) override;
                void dragEnterEvent(DragAndDropEvent&) override;
                void dragLeaveEvent(DragAndDropEvent&) override;
                void dragMoveEvent(DragAndDropEvent&) override;
                void dropEvent(DragAndDropEvent&) override;

            private:
                int _getDropIndex(const V2I&) const;
                Box2I _getDropGeom(int) const;

                std::shared_ptr<VerticalLayout> _layout;
                int _handle = 0;
                int _dropTarget = -1;
            };
        }
    }
}
