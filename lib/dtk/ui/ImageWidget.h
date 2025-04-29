// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWidget.h>

#include <dtk/core/Image.h>

namespace dtk
{
    //! \name Images
    ///@{
        
    //! Image widget.
    class ImageWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        ImageWidget();

    public:
        virtual ~ImageWidget();

        //! Create a new widget.
        static std::shared_ptr<ImageWidget> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the image.
        const std::shared_ptr<Image>& getImage() const;

        //! Set the image.
        void setImage(const std::shared_ptr<Image>&);

        //! Get the margin role.
        SizeRole getMarginRole() const;

        //! Set the margin role.
        void setMarginRole(SizeRole);

        void sizeHintEvent(const SizeHintEvent&) override;
        void drawEvent(const Box2I&, const DrawEvent&) override;

    private:
        DTK_PRIVATE();
    };
        
    ///@}
}
