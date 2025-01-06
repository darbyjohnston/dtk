// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWidget.h>

namespace dtk
{
    //! \name Layouts
    ///@{

    //! Scroll type.
    enum class ScrollType
    {
        Both,
        Horizontal,
        Vertical,
        Menu,

        Count,
        First = Both
    };
    DTK_ENUM(ScrollType);

    //! Scroll area.
    class ScrollArea : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            ScrollType,
            const std::shared_ptr<IWidget>& parent);

        ScrollArea();

    public:
        virtual ~ScrollArea();

        //! Create a new widget.
        static std::shared_ptr<ScrollArea> create(
            const std::shared_ptr<Context>&,
            ScrollType = ScrollType::Both,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the scroll size.
        const Size2I& getScrollSize() const;

        //! Set the scroll size callback.
        void setScrollSizeCallback(const std::function<void(const Size2I&)>&);

        //! Get the scroll position.
        const V2I& getScrollPos() const;

        //! Set the scroll position.
        void setScrollPos(const V2I&, bool clamp = true);

        //! Scroll to make the given box visible.
        void scrollTo(const Box2I&);

        //! Set the scroll position callback.
        void setScrollPosCallback(const std::function<void(const V2I&)>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        DTK_PRIVATE();
    };

    ///@}
}