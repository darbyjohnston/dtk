// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWidget.h>

namespace dtk
{
    //! \name Layouts
    ///@{
        
    //! Bellows widget.
    class Bellows : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        Bellows();

    public:
        virtual ~Bellows();

        //! Create a new widget.
        static std::shared_ptr<Bellows> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Create a new widget.
        static std::shared_ptr<Bellows> create(
            const std::shared_ptr<Context>&,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the text.
        const std::string& getText() const;

        //! Set the text.
        void setText(const std::string&);

        //! Get the widget.
        const std::shared_ptr<IWidget>& getWidget() const;

        //! Set the widget.
        void setWidget(const std::shared_ptr<IWidget>&);

        //! Get whether the bellows is open.
        bool isOpen() const;

        //! Set whether the bellows is open.
        void setOpen(bool);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        DTK_PRIVATE();
    };
        
    ///@}
}
