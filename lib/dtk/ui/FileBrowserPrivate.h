// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/FileBrowser.h>

#include <dtk/ui/IButton.h>

namespace dtk
{
    class FileBrowserPath : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        FileBrowserPath();

    public:
        virtual ~FileBrowserPath();

        static std::shared_ptr<FileBrowserPath> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setPath(const std::filesystem::path&);

        void setCallback(const std::function<void(const std::filesystem::path&)>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        void _widgetUpdate();

        DTK_PRIVATE();
    };

    class FileBrowserShortcuts : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        FileBrowserShortcuts();

    public:
        virtual ~FileBrowserShortcuts();

        static std::shared_ptr<FileBrowserShortcuts> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setCallback(const std::function<void(const std::filesystem::path&)>&);

        void setRecentFilesModel(const std::shared_ptr<RecentFilesModel>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        void _widgetUpdate();

        DTK_PRIVATE();
    };

    struct FileBrowserInfo
    {
        std::filesystem::path           path;
        bool                            isDir = false;
        size_t                          size  = 0;
        std::filesystem::file_time_type time;
    };

    class FileBrowserView : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        FileBrowserView();

    public:
        virtual ~FileBrowserView();

        static std::shared_ptr<FileBrowserView> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        const std::filesystem::path& getPath() const;
        void setPath(const std::filesystem::path&);

        void reload();

        void setCallback(const std::function<void(const std::filesystem::path&)>&);

        const FileBrowserOptions& getOptions() const;
        void setOptions(const FileBrowserOptions&);

        std::shared_ptr<IObservableValue<int> > observeCurrent() const;

        Box2I getRect(int) const;

        void sizeHintEvent(const SizeHintEvent&) override;
        void drawEvent(const Box2I& drawRect, const DrawEvent&) override;
        void mouseEnterEvent(MouseEnterEvent&) override;
        void mouseLeaveEvent() override;
        void mouseMoveEvent(MouseMoveEvent&) override;
        void mousePressEvent(MouseClickEvent&) override;
        void mouseReleaseEvent(MouseClickEvent&) override;
        void keyFocusEvent(bool) override;
        void keyPressEvent(KeyEvent&) override;
        void keyReleaseEvent(KeyEvent&) override;

    private:
        void _directoryUpdate();
        void _setCurrent(int);
        void _click(int);

        DTK_PRIVATE();
    };
}
