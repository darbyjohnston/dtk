// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "Window.h"

#include "App.h"

#include <dtk/ui/FileBrowser.h>
#include <dtk/ui/Menu.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/ScrollWidget.h>

using namespace dtk;
using namespace dtk::ui;

namespace dtk
{
    namespace examples
    {
        namespace textedit
        {
            void Window::_init(
                const std::shared_ptr<Context>& context,
                const std::shared_ptr<App>& app,
                const std::string& name,
                const Size2I& size)
            {
                ui::Window::_init(context, name, size);
                    
                _menus["File"] = Menu::create(context);
                auto appWeak = std::weak_ptr<App>(app);
                _actions["File/Open"] = std::make_shared<Action>(
                    "Open",
                    "FileOpen",
                    Key::O,
                    static_cast<int>(KeyModifier::Control),
                    [this, appWeak]
                    {
                        if (auto context = _getContext().lock())
                        {
                            if (auto fileBrowserSystem = context->getSystem<FileBrowserSystem>())
                            {
                                fileBrowserSystem->open(
                                    getWindow(),
                                    [appWeak](const std::filesystem::path& value)
                                    {
                                        if (auto app = appWeak.lock())
                                        {
                                            app->open(value);
                                        }
                                    });
                            }
                        }
                    });
                _menus["File"]->addItem(_actions["File/Open"]);
                _actions["File/Close"] = std::make_shared<Action>(
                    "Close",
                    "FileClose",
                    Key::E,
                    static_cast<int>(KeyModifier::Control),
                    [this]
                    {
                        _textWidget->setText(std::string());
                    });
                _menus["File"]->addItem(_actions["File/Close"]);
                _menus["File"]->addDivider();
                _actions["File/Exit"] = std::make_shared<Action>(
                    "Exit",
                    Key::Q,
                    static_cast<int>(KeyModifier::Control),
                    [appWeak]
                    {
                        if (auto app = appWeak.lock())
                        {
                            app->exit();
                        }
                    });
                _menus["File"]->addItem(_actions["File/Exit"]);

                _menus["Edit"] = Menu::create(context);
                _menus["Edit/Font"] = _menus["Edit"]->addSubMenu("Font");
                _actions["Edit/Font/Monospace"] = std::make_shared<Action>(
                    "Monospace",
                    [appWeak]
                    {
                        if (auto app = appWeak.lock())
                        {
                            app->setFont(FontRole::Mono);
                        }
                    });
                _menus["Edit/Font"]->addItem(_actions["Edit/Font/Monospace"]);
                _actions["Edit/Font/Regular"] = std::make_shared<Action>(
                    "Regular",
                    [appWeak]
                    {
                        if (auto app = appWeak.lock())
                        {
                            app->setFont(FontRole::Label);
                        }
                    });
                _menus["Edit/Font"]->addItem(_actions["Edit/Font/Regular"]);

                auto layout = VerticalLayout::create(context, shared_from_this());
                layout->setSpacingRole(SizeRole::None);

                _menuBar = MenuBar::create(context, layout);
                _menuBar->addMenu("File", _menus["File"]);
                _menuBar->addMenu("Edit", _menus["Edit"]);

                _textWidget = Label::create(context);
                _textWidget->setMarginRole(SizeRole::MarginInside);
                _textWidget->setVAlign(VAlign::Top);
                auto scrollWidget = ScrollWidget::create(context, ScrollType::Both, layout);
                scrollWidget->setStretch(Stretch::Expanding);
                scrollWidget->setWidget(_textWidget);

                _fontObserver = ValueObserver<FontRole>::create(
                    app->observeFont(),
                    [this](FontRole value)
                    {
                        _menus["Edit/Font"]->setItemChecked(
                            _actions["Edit/Font/Monospace"],
                            FontRole::Mono == value);
                        _menus["Edit/Font"]->setItemChecked(
                            _actions["Edit/Font/Regular"],
                            FontRole::Label == value);
                        _textWidget->setFontRole(value);
                    });

                _textObserver = ValueObserver<std::string>::create(
                    app->observeText(),
                    [this](const std::string& value)
                    {
                        _textWidget->setText(value);
                    });
            }

            Window::~Window()
            {}

            std::shared_ptr<Window> Window::create(
                const std::shared_ptr<Context>& context,
                const std::shared_ptr<App>& app,
                const std::string& name,
                const Size2I& size)
            {
                auto out = std::shared_ptr<Window>(new Window);
                out->_init(context, app, name, size);
                return out;
            }

            void Window::keyPressEvent(ui::KeyEvent& event)
            {
                event.accept = _menuBar->shortcut(event.key, event.modifiers);
            }

            void Window::keyReleaseEvent(ui::KeyEvent& event)
            {
                event.accept = true;
            }
        }
    }
}
