// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/FileBrowserPrivate.h>

#include <dtk/ui/ButtonGroup.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/String.h>

#include <filesystem>

namespace dtk
{
    namespace ui
    {        
        struct FileBrowserDirectoryWidget::Private
        {
            std::filesystem::path path;
            FileBrowserOptions options;
            std::vector<FileBrowserInfo> info;
            std::vector<std::shared_ptr<FileBrowserButton> > buttons;
            std::shared_ptr<ButtonGroup> buttonGroup;
            std::shared_ptr<VerticalLayout> layout;
            std::function<void(const std::filesystem::path&)> callback;
            std::shared_ptr<ObservableValue<int> > current;

            struct SizeData
            {
                int spacing = 0;
            };
            SizeData size;
        };

        void FileBrowserDirectoryWidget::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "dtk::ui::FileBrowserDirectoryWidget", parent);
            DTK_P();

            setAcceptsKeyFocus(true);
            setBackgroundRole(ColorRole::Base);

            p.buttonGroup = ButtonGroup::create(context, ButtonGroupType::Click);

            p.layout = VerticalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::None);

            p.buttonGroup->setClickedCallback(
                [this](int value)
                {
                    DTK_P();
                    takeKeyFocus();
                    if (value >= 0 && value < p.info.size())
                    {
                        const FileBrowserInfo info = p.info[value];
                        if (p.callback)
                        {
                            p.callback(info.path);
                        }
                        if (info.isDir)
                        {
                            p.path = info.path;
                            _directoryUpdate();
                        }
                    }
                });

            p.current = ObservableValue<int>::create(-1);
        }

        FileBrowserDirectoryWidget::FileBrowserDirectoryWidget() :
            _p(new Private)
        {}

        FileBrowserDirectoryWidget::~FileBrowserDirectoryWidget()
        {}

        std::shared_ptr<FileBrowserDirectoryWidget> FileBrowserDirectoryWidget::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<FileBrowserDirectoryWidget>(new FileBrowserDirectoryWidget);
            out->_init(context, parent);
            return out;
        }

        const std::filesystem::path& FileBrowserDirectoryWidget::getPath() const
        {
            return _p->path;
        }

        void FileBrowserDirectoryWidget::setPath(const std::filesystem::path& path)
        {
            DTK_P();
            if (path == p.path)
                return;
            p.path = path;
            _directoryUpdate();
        }

        void FileBrowserDirectoryWidget::reload()
        {
            _directoryUpdate();
        }

        void FileBrowserDirectoryWidget::setCallback(const std::function<void(const std::filesystem::path&)>& value)
        {
            _p->callback = value;
        }

        const FileBrowserOptions& FileBrowserDirectoryWidget::getOptions() const
        {
            return _p->options;
        }

        void FileBrowserDirectoryWidget::setOptions(const FileBrowserOptions& value)
        {
            DTK_P();
            if (value == p.options)
                return;
            p.options = value;
            _directoryUpdate();
        }

        std::shared_ptr<IObservableValue<int> > FileBrowserDirectoryWidget::observeCurrent() const
        {
            return _p->current;
        }

        Box2I FileBrowserDirectoryWidget::getRect(int index) const
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

        void FileBrowserDirectoryWidget::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            DTK_P();
            std::vector<int> columns;
            for (const auto& button : p.buttons)
            {
                if (columns.empty())
                {
                    columns = button->getTextWidths();
                }
                else
                {
                    const auto textWidths = button->getTextWidths();
                    for (size_t i = 0; i < columns.size() && i < textWidths.size(); ++i)
                    {
                        columns[i] = std::max(columns[i], textWidths[i]);
                    }
                }
            }
            if (!columns.empty())
            {
                for (size_t i = 0; i < columns.size() - 1; ++i)
                {
                    columns[i] += p.size.spacing;
                }
            }
            for (const auto& button : p.buttons)
            {
                button->setColumns(columns);
            }
            _p->layout->setGeometry(value);
        }

        void FileBrowserDirectoryWidget::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            DTK_P();

            p.size.spacing = event.style->getSizeRole(SizeRole::Spacing, event.displayScale);

            std::vector<int> columns;
            for (const auto& button : p.buttons)
            {
                if (columns.empty())
                {
                    columns = button->getTextWidths();
                }
                else
                {
                    const auto textWidths = button->getTextWidths();
                    for (size_t i = 0; i < columns.size() && i < textWidths.size(); ++i)
                    {
                        columns[i] = std::max(columns[i], textWidths[i]);
                    }
                }
            }
            if (!columns.empty())
            {
                for (size_t i = 0; i < columns.size() - 1; ++i)
                {
                    columns[i] += p.size.spacing;
                }
            }
            for (const auto& button : p.buttons)
            {
                button->setColumns(columns);
            }

            Size2I sizeHint = p.layout->getSizeHint();
            for (size_t i = 0; i < columns.size(); ++i)
            {
                sizeHint.w += columns[i];
            }
            _setSizeHint(sizeHint);
        }

        void FileBrowserDirectoryWidget::keyFocusEvent(bool value)
        {
            IWidget::keyFocusEvent(value);
            _currentUpdate();
        }

        void FileBrowserDirectoryWidget::keyPressEvent(KeyEvent& event)
        {
            DTK_P();
            if (0 == event.modifiers)
            {
                switch (event.key)
                {
                case Key::Up:
                    event.accept = true;
                    _setCurrent(p.current->get() - 1);
                    break;
                case Key::Down:
                    event.accept = true;
                    _setCurrent(p.current->get() + 1);
                    break;
                case Key::Home:
                    event.accept = true;
                    _setCurrent(0);
                    break;
                case Key::End:
                    event.accept = true;
                    _setCurrent(static_cast<int>(p.buttons.size()) - 1);
                    break;
                case Key::Enter:
                {
                    const int current = p.current->get();
                    if (current >= 0 && current < p.buttons.size())
                    {
                        event.accept = true;
                        takeKeyFocus();
                        auto button = p.buttons[current];
                        button->click();
                    }
                    break;
                }
                case Key::Escape:
                    if (hasKeyFocus())
                    {
                        event.accept = true;
                        releaseKeyFocus();
                    }
                    break;
                default: break;
                }
            }
            if (!event.accept)
            {
                IWidget::keyPressEvent(event);
            }
        }

        void FileBrowserDirectoryWidget::keyReleaseEvent(KeyEvent& event)
        {
            IWidget::keyReleaseEvent(event);
            event.accept = true;
        }
        
        namespace
        {
            void list(
                const std::filesystem::path& path,
                const FileBrowserOptions& options,
                std::vector<FileBrowserInfo>& out)
            {
                try
                {
                    for (const auto& i : std::filesystem::directory_iterator(path))
                    {
                        const auto& path = i.path();
                        const std::string fileName = path.filename().string();
                        bool keep = true;
                        if (!options.search.empty())
                        {
                            keep = contains(
                                fileName,
                                options.search,
                                CaseCompare::Insensitive);
                        }
                        const bool isDir = std::filesystem::is_directory(path);
                        std::string extension;
                        if (!isDir)
                        {
                            extension = path.extension().string();
                        }
                        if (!isDir && !options.extension.empty())
                        {
                            keep = compare(
                                extension,
                                options.extension,
                                CaseCompare::Insensitive);
                        }
                        if (keep)
                        {
                            out.push_back({
                                path,
                                isDir,
                                isDir ? 0 : std::filesystem::file_size(path),
                                std::filesystem::last_write_time(path) });
                        }
                    }
                }
                catch (const std::exception&)
                {}

                std::function<int(const FileBrowserInfo& a, const FileBrowserInfo& b)> sort;
                switch (options.sort)
                {
                case FileBrowserSort::Name:
                    sort = [](const FileBrowserInfo& a, const FileBrowserInfo& b)
                    {
                        return a.path.filename() < b.path.filename();
                    };
                    break;
                case FileBrowserSort::Extension:
                    sort = [](const FileBrowserInfo& a, const FileBrowserInfo& b)
                    {
                        return a.path.extension() < b.path.extension();
                    };
                    break;
                case FileBrowserSort::Size:
                    sort = [](const FileBrowserInfo& a, const FileBrowserInfo& b)
                    {
                        return a.size < b.size;
                    };
                    break;
                case FileBrowserSort::Time:
                    sort = [](const FileBrowserInfo& a, const FileBrowserInfo& b)
                    {
                        return a.time < b.time;
                    };
                    break;
                default: break;
                }
                if (sort)
                {
                    if (options.reverseSort)
                    {
                        std::sort(out.rbegin(), out.rend(), sort);
                    }
                    else
                    {
                        std::sort(out.begin(), out.end(), sort);
                    }
                }
                std::stable_sort(
                    out.begin(),
                    out.end(),
                    [](const FileBrowserInfo& a, const FileBrowserInfo& b)
                    {
                        return a.isDir > b.isDir;
                    });
            }
        }

        void FileBrowserDirectoryWidget::_directoryUpdate()
        {
            DTK_P();
            for (const auto& button : p.buttons)
            {
                button->setParent(nullptr);
            }
            p.buttons.clear();
            p.buttonGroup->clearButtons();
            p.info.clear();
            list(p.path, p.options, p.info);
            if (auto context = _getContext().lock())
            {
                for (const auto& info : p.info)
                {
                    auto button = FileBrowserButton::create(context, info);
                    button->setParent(p.layout);
                    p.buttons.push_back(button);
                    p.buttonGroup->addButton(button);
                }
            }
            _setCurrent(0);
            _currentUpdate();
        }

        void FileBrowserDirectoryWidget::_setCurrent(int value)
        {
            DTK_P();
            const int tmp = clamp(value, 0, static_cast<int>(p.buttons.size()) - 1);
            if (p.current->setIfChanged(tmp))
            {
                _currentUpdate();
            }
        }

        void FileBrowserDirectoryWidget::_currentUpdate()
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
