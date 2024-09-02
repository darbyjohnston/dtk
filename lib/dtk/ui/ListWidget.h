// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/ListItemsWidget.h>

namespace dtk
{
    namespace ui
    {
        //! \name List Widgets
        ///@{

        //! List widget.
        class ListWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                ButtonGroupType,
                const std::shared_ptr<IWidget>& parent);

            ListWidget();

        public:
            virtual ~ListWidget();

            //! Create a new widget.
            static std::shared_ptr<ListWidget> create(
                const std::shared_ptr<core::Context>&,
                ButtonGroupType,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the items.
            const std::vector<ListItem>& getItems() const;

            //! Set the items.
            void setItems(const std::vector<ListItem>&);

            //! Set the items.
            void setItems(const std::vector<std::string>&);

            //! Get whether an item is checked.
            bool getChecked(int) const;

            //! Set the checked item.
            void setChecked(int, bool = true);

            //! Set the callback.
            void setCallback(const std::function<void(int, bool)>&);

            //! Get the search.
            const std::string& getSearch() const;

            //! Set the search.
            void setSearch(const std::string&);

            //! Clear the search.
            void clearSearch();

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            DTK_PRIVATE();
        };

        ///@}
    }
}
