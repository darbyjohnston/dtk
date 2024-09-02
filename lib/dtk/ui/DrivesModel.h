// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/ObservableList.h>

#include <filesystem>

namespace dtk
{
    class Context;

    namespace ui
    {
        //! \name File Widgets
        ///@{
        
        //! File system drives model.
        class DrivesModel : public std::enable_shared_from_this<DrivesModel>
        {
            DTK_NON_COPYABLE(DrivesModel);

        protected:
            void _init(const std::shared_ptr<Context>&);

            DrivesModel();

        public:
            ~DrivesModel();

            //! Create a new model.
            static std::shared_ptr<DrivesModel> create(
                const std::shared_ptr<Context>&);

            //! Observe the list of drives.
            std::shared_ptr<IObservableList<std::filesystem::path> > observeDrives() const;

        private:
            DTK_PRIVATE();
        };
        
        ///@}
    }
}
