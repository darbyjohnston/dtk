// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/FileBrowser.h>

namespace feather_tk
{
    struct FileBrowserModel::Private
    {
        std::vector<std::filesystem::path> paths;
        int currentPath = -1;
        std::shared_ptr<ObservableValue<std::filesystem::path> > path;
        std::shared_ptr<ObservableValue<bool> > hasForward;
        std::shared_ptr<ObservableValue<bool> > hasBack;
        std::shared_ptr<ObservableValue<FileBrowserOptions> > options;
        std::shared_ptr<ObservableList<std::string> > extensions;
        std::shared_ptr<ObservableValue<std::string> > extension;
    };

    FileBrowserModel::FileBrowserModel(const std::shared_ptr<Context>&) :
        _p(new Private)
    {
        FEATHER_TK_P();
        const std::filesystem::path path = std::filesystem::current_path();
        p.paths.push_back(path);
        p.currentPath = 0;
        p.path = ObservableValue<std::filesystem::path>::create(path);
        p.hasForward = ObservableValue<bool>::create(false);
        p.hasBack = ObservableValue<bool>::create(false);
        p.options = ObservableValue<FileBrowserOptions>::create();
        p.extensions = ObservableList<std::string>::create();
        p.extension = ObservableValue<std::string>::create();
    }

    FileBrowserModel::~FileBrowserModel()
    {}

    std::shared_ptr<FileBrowserModel> FileBrowserModel::create(const std::shared_ptr<Context>& context)
    {
        return std::shared_ptr<FileBrowserModel>(new FileBrowserModel(context));
    }

    const std::filesystem::path& FileBrowserModel::getPath() const
    {
        return _p->path->get();
    }

    std::shared_ptr<IObservableValue<std::filesystem::path> > FileBrowserModel::observePath() const
    {
        return _p->path;
    }

    void FileBrowserModel::setPath(const std::filesystem::path& value)
    {
        FEATHER_TK_P();
        while (p.currentPath < static_cast<int>(p.paths.size()) - 1)
        {
            p.paths.pop_back();
        }
        if (p.paths.empty() ||
            (!p.paths.empty() && value != p.paths[p.paths.size() - 1]))
        {
            p.paths.push_back(value);
            p.currentPath++;

            p.path->setIfChanged(value);
            p.hasForward->setIfChanged(p.currentPath < p.paths.size() - 1);
            p.hasBack->setIfChanged(p.currentPath > 0);
        }
    }

    void FileBrowserModel::forward()
    {
        FEATHER_TK_P();
        if (!p.paths.empty() && p.currentPath < p.paths.size() - 1)
        {
            p.currentPath = p.currentPath + 1;
            p.path->setIfChanged(p.paths[p.currentPath]);
            p.hasForward->setIfChanged(p.currentPath < p.paths.size() - 1);
            p.hasBack->setIfChanged(p.currentPath > 0);
        }
    }

    std::shared_ptr<IObservableValue<bool> > FileBrowserModel::observeHasForward() const
    {
        return _p->hasForward;
    }

    void FileBrowserModel::back()
    {
        FEATHER_TK_P();
        if (p.currentPath > 0)
        {
            p.currentPath = p.currentPath - 1;
            p.path->setIfChanged(p.paths[p.currentPath]);
            p.hasForward->setIfChanged(p.currentPath < p.paths.size() - 1);
            p.hasBack->setIfChanged(p.currentPath > 0);
        }
    }

    std::shared_ptr<IObservableValue<bool> > FileBrowserModel::observeHasBack() const
    {
        return _p->hasBack;
    }

    const FileBrowserOptions& FileBrowserModel::getOptions() const
    {
        return _p->options->get();
    }

    std::shared_ptr<IObservableValue<FileBrowserOptions> > FileBrowserModel::observeOptions() const
    {
        return _p->options;
    }

    void FileBrowserModel::setOptions(const FileBrowserOptions& value)
    {
        _p->options->setIfChanged(value);
    }

    const std::vector<std::string>& FileBrowserModel::getExtensions() const
    {
        return _p->extensions->get();
    }

    std::shared_ptr<IObservableList<std::string> > FileBrowserModel::observeExtensions() const
    {
        return _p->extensions;
    }

    void FileBrowserModel::setExtensions(const std::vector<std::string>& value)
    {
        _p->extensions->setIfChanged(value);
    }

    const std::string& FileBrowserModel::getExtension() const
    {
        return _p->extension->get();
    }

    std::shared_ptr<IObservableValue<std::string> > FileBrowserModel::observeExtension() const
    {
        return _p->extension;
    }

    void FileBrowserModel::setExtension(const std::string& value)
    {
        _p->extension->setIfChanged(value);
    }
}