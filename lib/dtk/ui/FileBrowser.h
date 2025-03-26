// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IDialog.h>

#include <dtk/core/ISystem.h>

#include <filesystem>

namespace dtk
{
    class RecentFilesModel;

    //! \name File Widgets
    ///@{

    //! File browser mode.
    enum class FileBrowserMode
    {
        File,
        Dir,

        Count,
        First = File
    };
    DTK_ENUM(FileBrowserMode);

    //! File browser directory sorting.
    enum class FileBrowserSort
    {
        Name,
        Extension,
        Size,
        Time,

        Count,
        First = Name
    };
    DTK_ENUM(FileBrowserSort);

    //! File browser options.
    struct FileBrowserOptions
    {
        bool                        leftPanel   = true;
        bool                        pathEdit    = false;
        FileBrowserSort             sort        = FileBrowserSort::Name;
        bool                        reverseSort = false;
        std::map<std::string, bool> bellows =
        {
            { "Drives", true },
            { "Shortcuts", true },
            { "Recent", true }
        };

        bool operator == (const FileBrowserOptions&) const;
        bool operator != (const FileBrowserOptions&) const;
    };

    //! File browser widget.
    class FileBrowserWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::filesystem::path&,
            FileBrowserMode,
            const std::shared_ptr<IWidget>& parent);

        FileBrowserWidget();

    public:
        virtual ~FileBrowserWidget();

        //! Create a new widget.
        static std::shared_ptr<FileBrowserWidget> create(
            const std::shared_ptr<Context>&,
            const std::filesystem::path&,
            FileBrowserMode = FileBrowserMode::File,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Set the callback.
        void setCallback(const std::function<void(const std::filesystem::path&)>&);

        //! Set the cancel callback.
        void setCancelCallback(const std::function<void(void)>&);

        //! Get the path.
        std::filesystem::path getPath() const;

        //! Get the options.
        const FileBrowserOptions& getOptions() const;

        //! Observe the options.
        std::shared_ptr<IObservableValue<FileBrowserOptions> > observeOptions() const;

        //! Set the options.
        void setOptions(const FileBrowserOptions&);

        //! Set the extensions.
        void setExtensions(
            const std::vector<std::string>&,
            const std::string& current = std::string());

        //! Get the recent files model.
        const std::shared_ptr<RecentFilesModel>& getRecentFilesModel() const;

        //! Set the recent files model.
        void setRecentFilesModel(const std::shared_ptr<RecentFilesModel>&);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        void _setPath(const std::filesystem::path&);

        void _pathUpdate();
        void _optionsUpdate();
        void _extensionsUpdate();

        DTK_PRIVATE();
    };

    //! File browser dialog.
    class FileBrowser : public IDialog
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::filesystem::path&,
            FileBrowserMode,
            const std::shared_ptr<IWidget>& parent);

        FileBrowser();

    public:
        virtual ~FileBrowser();

        //! Create a new dialog.
        static std::shared_ptr<FileBrowser> create(
            const std::shared_ptr<Context>&,
            const std::filesystem::path&,
            FileBrowserMode = FileBrowserMode::File,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Set the callback.
        void setCallback(const std::function<void(const std::filesystem::path&)>&);

        //! Get the path.
        std::filesystem::path getPath() const;

        //! Get the options.
        const FileBrowserOptions& getOptions() const;

        //! Observe the options.
        std::shared_ptr<IObservableValue<FileBrowserOptions> > observeOptions() const;

        //! Set the options.
        void setOptions(const FileBrowserOptions&);

        //! Set the extensions.
        void setExtensions(
            const std::vector<std::string>&,
            const std::string& current = std::string());

        //! Get the recent files model.
        const std::shared_ptr<RecentFilesModel>& getRecentFilesModel() const;

        //! Set the recent files model.
        void setRecentFilesModel(const std::shared_ptr<RecentFilesModel>&);

    private:
        DTK_PRIVATE();
    };

    //! File browser system.
    class FileBrowserSystem : public ISystem
    {
    protected:
        FileBrowserSystem(const std::shared_ptr<Context>&);

    public:
        virtual ~FileBrowserSystem();

        //! Create a new system.
        static std::shared_ptr<FileBrowserSystem> create(
            const std::shared_ptr<Context>&);

        //! Open the file browser.
        void open(
            const std::shared_ptr<IWindow>&,
            const std::function<void(const std::filesystem::path&)>&,
            FileBrowserMode = FileBrowserMode::File,
            const std::shared_ptr<RecentFilesModel>& = nullptr);

        //! Get whether the native file dialog is used.
        bool isNativeFileDialog() const;

        //! Set whether the native file dialog is used.
        void setNativeFileDialog(bool);

        //! Get the path.
        const std::filesystem::path& getPath() const;

        //! Set the path.
        void setPath(const std::filesystem::path&);

        //! Get the options.
        const FileBrowserOptions& getOptions() const;

        //! Set the options.
        void setOptions(const FileBrowserOptions&);

        //! Set the extensions.
        void setExtensions(
            const std::vector<std::string>&,
            const std::string& current = std::string());

    private:
        DTK_PRIVATE();
    };

    void to_json(nlohmann::json&, const FileBrowserOptions&);

    void from_json(const nlohmann::json&, FileBrowserOptions&);

    ///@}
}
