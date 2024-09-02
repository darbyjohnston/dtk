// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "popups.h"

#include <dtk/ui/App.h>
#include <dtk/ui/Action.h>
#include <dtk/ui/ComboBox.h>
#include <dtk/ui/ColorSwatch.h>
#include <dtk/ui/GroupBox.h>
#include <dtk/ui/Menu.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/ScrollWidget.h>

using namespace dtk::core;
using namespace dtk::ui;

namespace dtk
{
    namespace examples
    {
        namespace popups
        {
            void Window::_init(
                const std::shared_ptr<Context>& context,
                const std::string& name,
                const Size2I& size)
            {
                ui::Window::_init(context, name, size);

                // Create the menu bar.
                auto menuLayout = VerticalLayout::create(context, shared_from_this());
                menuLayout->setSpacingRole(SizeRole::None);
                _menuBar = MenuBar::create(context, menuLayout);
                auto menu = Menu::create(context);
                menu->addItem(std::make_shared<Action>(
                    "Action 1",
                    [] { std::cout << "Action 1" << std::endl; }));
                menu->addItem(std::make_shared<Action>(
                    "Action 2",
                    "FileOpen",
                    [] { std::cout << "Action 2" << std::endl; }));
                menu->addDivider();
                menu->addItem(std::make_shared<Action>(
                    "Action 3",
                    Key::_3,
                    static_cast<int>(KeyModifier::Control),
                    [] { std::cout << "Action 3" << std::endl; }));
                menu->addDivider();
                menu->addItem(std::make_shared<Action>(
                    "Action 4",
                    "FileClose",
                    Key::_4,
                    static_cast<int>(KeyModifier::Control),
                    [] { std::cout << "Action 4" << std::endl; }));
                _menuBar->addMenu("Menu 1", menu);
                menu = Menu::create(context);
                menu->addItem(std::make_shared<Action>(
                    "Action 5",
                    [](bool value) { std::cout << "Action 5: " << value << std::endl; }));
                menu->addItem(std::make_shared<Action>(
                    "Action 6",
                    "Next",
                    [](bool value) { std::cout << "Action 6: " << value << std::endl; }));
                menu->addItem(std::make_shared<Action>(
                    "Action 7",
                    Key::_7,
                    static_cast<int>(KeyModifier::Control),
                    [](bool value) { std::cout << "Action 7: " << value << std::endl; }));
                menu->addItem(std::make_shared<Action>(
                    "Action 8",
                    "Prev",
                    Key::_8,
                    static_cast<int>(KeyModifier::Control),
                    [](bool value) { std::cout << "Action 8: " << value << std::endl; }));
                _menuBar->addMenu("Menu 2", menu);

                menu = Menu::create(context);
                menu->addItem(std::make_shared<Action>(
                    "Action 9",
                    [] { std::cout << "Action 9" << std::endl; }));
                auto subMenu = menu->addSubMenu("Sub Menu 1");
                subMenu->addItem(std::make_shared<Action>(
                    "Action 10",
                    [] { std::cout << "Action 10" << std::endl; }));
                subMenu = menu->addSubMenu("Sub Menu 2");
                subMenu->addItem(std::make_shared<Action>(
                    "Action 11",
                    [] { std::cout << "Action 11" << std::endl; }));
                subMenu->addItem(std::make_shared<Action>(
                    "Action 12",
                    [] { std::cout << "Action 12" << std::endl; }));
                subMenu = menu->addSubMenu("Sub Menu 3");
                subMenu->addItem(std::make_shared<Action>(
                    "Action 13",
                    [] { std::cout << "Action 13" << std::endl; }));
                subMenu->addItem(std::make_shared<Action>(
                    "Action 14",
                    [] { std::cout << "Action 14" << std::endl; }));
                subMenu->addItem(std::make_shared<Action>(
                    "Action 15",
                    [] { std::cout << "Action 15" << std::endl; }));
                menu->addItem(std::make_shared<Action>(
                    "Action 16",
                    [] { std::cout << "Action 16" << std::endl; }));
                _menuBar->addMenu("Menu 3", menu);

                // Create the layout.
                auto layout = VerticalLayout::create(context);
                layout->setMarginRole(SizeRole::Margin);
                auto scrollWidget = ScrollWidget::create(context, ScrollType::Both, menuLayout);
                scrollWidget->setStretch(Stretch::Expanding);
                scrollWidget->setWidget(layout);

                // Create combo boxes.
                auto groupBox = GroupBox::create(context, "Combo Boxes", layout);
                auto vLayout = VerticalLayout::create(context, groupBox);
                auto comboBox = ComboBox::create(context, vLayout);
                comboBox->setItems(
                {
                    ComboBoxItem("Stop", "PlaybackStop"),
                    ComboBoxItem("Forward", "PlaybackForward"),
                    ComboBoxItem("Reverse", "PlaybackReverse")
                });
                comboBox->setTooltip("Playback");
                comboBox = ComboBox::create(context, getImageTypeLabels(), vLayout);
                comboBox->setTooltip("Image types");

                // Create color swatches.
                groupBox = GroupBox::create(context, "Color Popups", layout);
                auto hLayout = HorizontalLayout::create(context, groupBox);
                const std::vector<Color4F> colors =
                {
                    Color4F(1.F, .5F, .5F),
                    Color4F(.5F, 1.F, .5F),
                    Color4F(.5F, .5F, 1.F),
                    Color4F(1.F, 1.F, .5F),
                    Color4F(.5F, 1.F, 1.F),
                    Color4F(1.F, .5F, 1.F)
                };
                for (const auto& color : colors)
                {
                    auto colorSwatch = ColorSwatch::create(context, hLayout);
                    colorSwatch->setColor(color);
                    colorSwatch->setEditable(true);
                }
            }

            Window::~Window()
            {}

            std::shared_ptr<Window> Window::create(
                const std::shared_ptr<Context>& context,
                const std::string& name,
                const Size2I& size)
            {
                auto out = std::shared_ptr<Window>(new Window);
                out->_init(context, name, size);
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

DTK_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = convert(argc, argv);
        auto app = App::create(context, args, "popups", "Popups example");
        if (app->getExit() != 0)
            return app->getExit();

        auto window = dtk::examples::popups::Window::create(
            context,
            "popups",
            Size2I(1280, 960));
        app->addWindow(window);
        window->show();
        app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

