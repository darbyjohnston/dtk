// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/ListItemsWidgetPrivate.h>

#include <dtk/ui/ButtonGroup.h>
#include <dtk/ui/RowLayout.h>

namespace dtk
{
    namespace ui
    {
        ListItem::ListItem(
            const std::string& text,
            const std::string& tooltip) :
            text(text),
            tooltip(tooltip)
        {}

        bool ListItem::operator == (const ListItem& other) const
        {
            return
                text == other.text &&
                tooltip == other.tooltip;
        }

        bool ListItem::operator != (const ListItem& other) const
        {
            return !(*this == other);
        }

        struct ListItemsWidget::Private
        {
            ui::ButtonGroupType type = ui::ButtonGroupType::Click;
            std::vector<ListItem> items;
            std::vector<std::shared_ptr<ListItemButton> > buttons;
            std::shared_ptr<ButtonGroup> buttonGroup;
            std::shared_ptr<VerticalLayout> layout;
            std::function<void(int, bool)> callback;
            std::shared_ptr<ObservableValue<int> > current;
            std::string search;
        };

        void ListItemsWidget::_init(
            const std::shared_ptr<Context>& context,
            ButtonGroupType type,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "dtk::ui::ListItemsWidget", parent);
            DTK_P();

            setAcceptsKeyFocus(true);

            p.buttonGroup = ButtonGroup::create(context, type);

            p.layout = VerticalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::None);

            _itemsUpdate();

            switch (type)
            {
            case ButtonGroupType::Click:
                p.buttonGroup->setClickedCallback(
                    [this](int index)
                    {
                        takeKeyFocus();
                        _setCurrent(index);
                        if (_p->callback)
                        {
                            _p->callback(index, true);
                        }
                    });
                break;
            default:
                p.buttonGroup->setCheckedCallback(
                    [this](int index, bool value)
                    {
                        takeKeyFocus();
                        _setCurrent(index);
                        if (_p->callback)
                        {
                            _p->callback(index, value);
                        }
                    });
                break;
            }

            p.current = ObservableValue<int>::create(-1);
        }

        ListItemsWidget::ListItemsWidget() :
            _p(new Private)
        {}

        ListItemsWidget::~ListItemsWidget()
        {}

        std::shared_ptr<ListItemsWidget> ListItemsWidget::create(
            const std::shared_ptr<Context>& context,
            ButtonGroupType type,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ListItemsWidget>(new ListItemsWidget);
            out->_init(context, type, parent);
            return out;
        }

        const std::vector<ListItem>& ListItemsWidget::getItems() const
        {
            return _p->items;
        }

        void ListItemsWidget::setItems(const std::vector<ListItem>& value)
        {
            DTK_P();
            if (value == p.items)
                return;
            p.items = value;
            _itemsUpdate();
            p.current->setIfChanged(clamp(p.current->get(), 0, static_cast<int>(p.items.size()) - 1));
        }

        void ListItemsWidget::setItems(const std::vector<std::string>& value)
        {
            std::vector<ListItem> items;
            for (const auto& i : value)
            {
                items.push_back(ListItem(i));
            }
            setItems(items);
        }

        bool ListItemsWidget::getChecked(int index) const
        {
            DTK_P();
            bool out = false;
            if (index >= 0 && index < p.buttons.size())
            {
                out = p.buttons[index]->isChecked();
            }
            return out;
        }

        void ListItemsWidget::setChecked(int index, bool value)
        {
            _p->buttonGroup->setChecked(index, value);
        }

        void ListItemsWidget::setCallback(const std::function<void(int, bool)>& value)
        {
            _p->callback = value;
        }

        std::shared_ptr<IObservableValue<int> > ListItemsWidget::observeCurrent() const
        {
            return _p->current;
        }

        const std::string& ListItemsWidget::getSearch() const
        {
            return _p->search;
        }

        void ListItemsWidget::setSearch(const std::string& value)
        {
            DTK_P();
            if (value == p.search)
                return;
            p.search = value;
            _itemsUpdate();
        }

        void ListItemsWidget::clearSearch()
        {
            DTK_P();
            if (!p.search.empty())
            {
                p.search = std::string();
                _itemsUpdate();
            }
        }

        Box2I ListItemsWidget::getRect(int index) const
        {
            DTK_P();
            Box2I out;
            if (index >= 0 && index < p.buttons.size())
            {
                out = p.buttons[index]->getGeometry();
                out = move(out, -p.layout->getGeometry().min);
            }
            return out;
        }

        void ListItemsWidget::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->layout->setGeometry(value);
        }

        void ListItemsWidget::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_p->layout->getSizeHint());
        }

        void ListItemsWidget::keyFocusEvent(bool value)
        {
            IWidget::keyFocusEvent(value);
            _currentUpdate();
        }

        void ListItemsWidget::keyPressEvent(KeyEvent& event)
        {
            DTK_P();
            if (0 == event.modifiers)
            {
                switch (event.key)
                {
                case Key::Enter:
                {
                    event.accept = true;
                    takeKeyFocus();
                    const int current = p.current->get();
                    if (current >= 0 && current < p.buttons.size())
                    {
                        p.buttons[current]->click();
                    }
                    break;
                }
                case Key::Up:
                    event.accept = true;
                    takeKeyFocus();
                    _setCurrent(p.current->get() - 1);
                    break;
                case Key::Down:
                    event.accept = true;
                    takeKeyFocus();
                    _setCurrent(p.current->get() + 1);
                    break;
                case Key::Home:
                    event.accept = true;
                    takeKeyFocus();
                    _setCurrent(0);
                    break;
                case Key::End:
                    event.accept = true;
                    takeKeyFocus();
                    _setCurrent(static_cast<int>(p.items.size()) - 1);
                    break;
                case Key::Escape:
                    event.accept = true;
                    releaseKeyFocus();
                    break;
                default: break;
                }
            }
            if (!event.accept)
            {
                IWidget::keyPressEvent(event);
            }
        }

        void ListItemsWidget::keyReleaseEvent(KeyEvent& event)
        {
            IWidget::keyReleaseEvent(event);
            event.accept = true;
        }

        void ListItemsWidget::_itemsUpdate()
        {
            DTK_P();
            
            for (const auto& button : p.buttons)
            {
                button->setParent(nullptr);
            }
            p.buttons.clear();
            p.buttonGroup->clearButtons();

            if (auto context = _getContext().lock())
            {
                for (const auto& item : p.items)
                {
                    auto button = ListItemButton::create(context, item.text, p.layout);
                    button->setTooltip(item.tooltip);
                    p.buttons.push_back(button);
                    p.buttonGroup->addButton(button);
                }
            }
        }

        void ListItemsWidget::_setCurrent(int value)
        {
            DTK_P();
            const int tmp = clamp(value, 0, static_cast<int>(p.items.size()) - 1);
            if (p.current->setIfChanged(tmp))
            {
                _currentUpdate();
            }
        }

        void ListItemsWidget::_currentUpdate()
        {
            DTK_P();
            const int current = p.current->get();
            const bool focus = hasKeyFocus();
            for (size_t i = 0; i < p.buttons.size(); ++i)
            {
                p.buttons[i]->setCurrent(current == i && focus);
            }
        }
    }
}
