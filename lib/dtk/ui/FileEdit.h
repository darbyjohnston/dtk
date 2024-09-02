// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWidget.h>

#include <filesystem>

namespace dtk
{
    namespace ui
    {
        //! \name File Widgets
        ///@{

        //! File edit widget.
        class FileEdit : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<IWidget>& parent);

            FileEdit();

        public:
            virtual ~FileEdit();

            //! Create a new widget.
            static std::shared_ptr<FileEdit> create(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the path.
            const std::filesystem::path& getPath() const;

            //! Set the path.
            void setPath(const std::filesystem::path&);

            //! Set the callback.
            void setCallback(const std::function<void(const std::filesystem::path&)>&);

            void setGeometry(const Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            void _openDialog();

            DTK_PRIVATE();
        };

        ///@}
    }
}