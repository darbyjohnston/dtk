// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/RecentFilesModel.h>

#include <dtk/ui/Settings.h>

#include <dtk/core/Context.h>

#include <nlohmann/json.hpp>

namespace dtk
{
    struct RecentFilesModel::Private
    {
        std::shared_ptr<Settings> settings;
        std::string settingsName;
        std::shared_ptr<ObservableValue<size_t> > recentMax;
        std::shared_ptr<ObservableList<std::filesystem::path> > recent;
    };

    void RecentFilesModel::_init(
        const std::shared_ptr<Context>& context,
        const std::string& settingsName)
    {
        DTK_P();

        p.settings = context->getSystem<Settings>();
        p.settingsName = settingsName;
        p.recentMax = ObservableValue<size_t>::create(10);

        std::vector<std::filesystem::path> recent;
        try
        {
            const auto json = std::any_cast<nlohmann::json>(p.settings->get(p.settingsName));
            for (auto i = json.begin(); i != json.end(); ++i)
            {
                if (i->is_string())
                {
                    recent.push_back(i->get<std::string>());
                }
            }
        }
        catch (const std::exception&)
        {}
        p.recent = ObservableList<std::filesystem::path>::create(recent);
    }

    RecentFilesModel::RecentFilesModel() :
        _p(new Private)
    {}

    RecentFilesModel::~RecentFilesModel()
    {
        DTK_P();
        nlohmann::json json;
        for (const auto& recent : p.recent->get())
        {
            json.push_back(recent);
        }
        p.settings->set(p.settingsName, json);
    }

    std::shared_ptr<RecentFilesModel> RecentFilesModel::create(
        const std::shared_ptr<Context>& context,
        const std::string& settingsName)
    {
        auto out = std::shared_ptr<RecentFilesModel>(new RecentFilesModel);
        out->_init(context, settingsName);
        return out;
    }

    size_t RecentFilesModel::getRecentMax() const
    {
        return _p->recentMax->get();
    }

    std::shared_ptr<IObservableValue<size_t> > RecentFilesModel::observeRecentMax() const
    {
        return _p->recentMax;
    }

    void RecentFilesModel::setRecentMax(size_t value)
    {
        DTK_P();
        if (p.recentMax->setIfChanged(value))
        {
            if (p.recent->getSize() > p.recentMax->get())
            {
                auto recent = p.recent->get();
                while (recent.size() > p.recentMax->get())
                {
                    recent.erase(recent.begin());
                }
                p.recent->setIfChanged(recent);
            }
        }
    }

    const std::vector<std::filesystem::path>& RecentFilesModel::getRecent() const
    {
        return _p->recent->get();
    }

    std::shared_ptr<IObservableList<std::filesystem::path> > RecentFilesModel::observeRecent() const
    {
        return _p->recent;
    }

    void RecentFilesModel::setRecent(const std::vector<std::filesystem::path>& value)
    {
        DTK_P();
        auto recent = value;
        while (recent.size() > p.recentMax->get())
        {
            recent.erase(recent.begin());
        }
        p.recent->setIfChanged(recent);
    }

    void RecentFilesModel::addRecent(const std::filesystem::path& value)
    {
        DTK_P();
        auto recent = p.recent->get();
        auto i = recent.begin();
        while (i != recent.end())
        {
            if (*i == value)
            {
                i = recent.erase(i);
            }
            else
            {
                ++i;
            }
        }
        recent.push_back(value);
        while (recent.size() > p.recentMax->get())
        {
            recent.erase(recent.begin());
        }
        p.recent->setIfChanged(recent);
    }
}