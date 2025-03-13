// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/Action.h>

namespace dtk
{
    struct Action::Private
    {
        std::shared_ptr<ObservableValue<std::string> > text;
        std::shared_ptr<ObservableValue<std::string> > icon;
        std::shared_ptr<ObservableValue<std::string> > checkedIcon;
        std::shared_ptr<ObservableValue<Key> > shortcut;
        std::shared_ptr<ObservableValue<int> > shortcutModifiers;
        std::function<void(void)> callback;
        std::shared_ptr<ObservableValue<bool> > checkable;
        std::shared_ptr<ObservableValue<bool> > checked;
        std::function<void(bool)> checkedCallback;
        std::shared_ptr<ObservableValue<bool> > enabled;
        std::shared_ptr<ObservableValue<std::string> > tooltip;
    };

    void Action::_init(
        const std::string& text,
        const std::string& icon,
        Key shortcut,
        int shortcutModifiers,
        const std::function<void(void)>& callback,
        const std::function<void(bool)>& checkedCallback)
    {
        DTK_P();

        p.text = ObservableValue<std::string>::create(text);
        p.icon = ObservableValue<std::string>::create(icon);
        p.checkedIcon = ObservableValue<std::string>::create();
        p.shortcut = ObservableValue<Key>::create(shortcut);
        p.shortcutModifiers = ObservableValue<int>::create(shortcutModifiers);
        p.callback = callback;
        p.checkable = ObservableValue<bool>::create(bool(checkedCallback));
        p.checked = ObservableValue<bool>::create(false);
        p.checkedCallback = checkedCallback;
        p.enabled = ObservableValue<bool>::create(true);
        p.tooltip = ObservableValue<std::string>::create();
    }

    Action::Action() :
        _p(new Private)
    {}

    Action::~Action()
    {}

    std::shared_ptr<Action> Action::create(
        const std::string& text,
        const std::function<void(void)>& callback)
    {
        auto out = std::shared_ptr<Action>(new Action);
        out->_init(
            text,
            "Empty",
            Key::Unknown,
            0,
            callback,
            nullptr);
        return out;
    }

    std::shared_ptr<Action> Action::create(
        const std::string& text,
        const std::string& icon,
        const std::function<void(void)>& callback)
    {
        auto out = std::shared_ptr<Action>(new Action);
        out->_init(
            text,
            icon,
            Key::Unknown,
            0,
            callback,
            nullptr);
        return out;
    }

    std::shared_ptr<Action> Action::create(
        const std::string& text,
        Key shortcut,
        int shortcutModifiers,
        const std::function<void(void)>& callback)
    {
        auto out = std::shared_ptr<Action>(new Action);
        out->_init(
            text,
            "Empty",
            shortcut,
            shortcutModifiers,
            callback,
            nullptr);
        return out;
    }

    std::shared_ptr<Action> Action::create(
        const std::string& text,
        const std::string& icon,
        Key shortcut,
        int shortcutModifiers,
        const std::function<void(void)>& callback)
    {
        auto out = std::shared_ptr<Action>(new Action);
        out->_init(
            text,
            icon,
            shortcut,
            shortcutModifiers,
            callback,
            nullptr);
        return out;
    }

    std::shared_ptr<Action> Action::create(
        const std::string& text,
        const std::function<void(bool)>& checkedCallback)
    {
        auto out = std::shared_ptr<Action>(new Action);
        out->_init(
            text,
            "Empty",
            Key::Unknown,
            0,
            nullptr,
            checkedCallback);
        return out;
    }

    std::shared_ptr<Action> Action::create(
        const std::string& text,
        const std::string& icon,
        const std::function<void(bool)>& checkedCallback)
    {
        auto out = std::shared_ptr<Action>(new Action);
        out->_init(
            text,
            icon,
            Key::Unknown,
            0,
            nullptr,
            checkedCallback);
        return out;
    }

    std::shared_ptr<Action> Action::create(
        const std::string& text,
        Key shortcut,
        int shortcutModifiers,
        const std::function<void(bool)>& checkedCallback)
    {
        auto out = std::shared_ptr<Action>(new Action);
        out->_init(
            text,
            "Empty",
            shortcut,
            shortcutModifiers,
            nullptr,
            checkedCallback);
        return out;
    }

    std::shared_ptr<Action> Action::create(
        const std::string& text,
        const std::string& icon,
        Key shortcut,
        int shortcutModifiers,
        const std::function<void(bool)>& checkedCallback)
    {
        auto out = std::shared_ptr<Action>(new Action);
        out->_init(
            text,
            icon,
            shortcut,
            shortcutModifiers,
            nullptr,
            checkedCallback);
        return out;
    }

    const std::string& Action::getText() const
    {
        return _p->text->get();
    }

    std::shared_ptr<IObservableValue<std::string> > Action::observeText() const
    {
        return _p->text;
    }

    void Action::setText(const std::string& value)
    {
        _p->text->setIfChanged(value);
    }

    const std::string& Action::getIcon() const
    {
        return _p->icon->get();
    }

    const std::string& Action::getCheckedIcon() const
    {
        return _p->checkedIcon->get();
    }

    std::shared_ptr<IObservableValue<std::string> > Action::observeIcon() const
    {
        return _p->icon;
    }

    std::shared_ptr<IObservableValue<std::string> > Action::observeCheckedIcon() const
    {
        return _p->checkedIcon;
    }

    void Action::setIcon(const std::string& value)
    {
        _p->icon->setIfChanged(value);
    }

    void Action::setCheckedIcon(const std::string& value)
    {
        _p->checkedIcon->setIfChanged(value);
    }

    Key Action::getShortcut() const
    {
        return _p->shortcut->get();
    }

    int Action::getShortcutModifiers() const
    {
        return _p->shortcutModifiers->get();
    }

    std::shared_ptr<IObservableValue<Key> > Action::observeShortcut() const
    {
        return _p->shortcut;
    }

    std::shared_ptr<IObservableValue<int> > Action::observeShortcutModifiers() const
    {
        return _p->shortcutModifiers;
    }

    void Action::setShortcut(Key value)
    {
        _p->shortcut->setIfChanged(value);
    }

    void Action::setShortcutModifiers(int value)
    {
        _p->shortcutModifiers->setIfChanged(value);
    }

    void Action::doCallback()
    {
        if (_p->callback)
        {
            _p->callback();
        }
    }

    bool Action::isCheckable() const
    {
        return _p->checkable->get();
    }

    bool Action::isChecked() const
    {
        return _p->checked->get();
    }

    std::shared_ptr<IObservableValue<bool> > Action::observeCheckable() const
    {
        return _p->checkable;
    }

    std::shared_ptr<IObservableValue<bool> > Action::observeChecked() const
    {
        return _p->checked;
    }

    void Action::setCheckable(bool value)
    {
        DTK_P();
        p.checkable->setIfChanged(value);
    }

    void Action::setChecked(bool value)
    {
        DTK_P();
        p.checked->setIfChanged(value);
    }

    void Action::doCheckedCallback(bool value)
    {
        if (_p->checkedCallback)
        {
            _p->checkedCallback(value);
        }
    }

    bool Action::isEnabled() const
    {
        return _p->enabled->get();
    }

    std::shared_ptr<IObservableValue<bool> > Action::observeEnabled() const
    {
        return _p->enabled;
    }

    void Action::setEnabled(bool value)
    {
        DTK_P();
        p.enabled->setIfChanged(value);
    }

    const std::string& Action::getTooltip() const
    {
        return _p->tooltip->get();
    }

    std::shared_ptr<IObservableValue<std::string> > Action::observeTooltip() const
    {
        return _p->tooltip;
    }

    void Action::setTooltip(const std::string& value)
    {
        _p->tooltip->setIfChanged(value);
    }
}