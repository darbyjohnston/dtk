// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/DrivesModel.h>

#include <feather-tk/core/File.h>
#include <feather-tk/core/Time.h>
#include <feather-tk/core/Timer.h>

#include <atomic>
#include <mutex>
#include <thread>

namespace feather_tk
{
    namespace
    {
        const std::chrono::milliseconds timeout(100);
    }

    struct DrivesModel::Private
    {
        std::shared_ptr<ObservableList<std::filesystem::path> > drives;

        struct Mutex
        {
            std::vector<std::filesystem::path> drives;
            std::mutex mutex;
        };
        Mutex mutex;
        std::thread thread;
        std::atomic<bool> running;

        std::shared_ptr<Timer> timer;
    };

    void DrivesModel::_init(const std::shared_ptr<Context>& context)
    {
        FEATHER_TK_P();

        p.drives = ObservableList<std::filesystem::path>::create();

        p.running = true;
        p.thread = std::thread(
            [this]
            {
                FEATHER_TK_P();
                while (p.running)
                {
                    const auto drives = getDrives();
                    {
                        std::lock_guard<std::mutex> lock(p.mutex.mutex);
                        p.mutex.drives = drives;
                    }
                    sleep(timeout);
                }
            });

        p.timer = Timer::create(context);
        p.timer->setRepeating(true);
        p.timer->start(
            timeout,
            [this]
            {
                FEATHER_TK_P();
                std::vector<std::filesystem::path> drives;
                {
                    std::lock_guard<std::mutex> lock(p.mutex.mutex);
                    drives = p.mutex.drives;
                }
                p.drives->setIfChanged(drives);
            });
    }

    DrivesModel::DrivesModel() :
        _p(new Private)
    {}

    DrivesModel::~DrivesModel()
    {
        FEATHER_TK_P();
        p.running = false;
        if (p.thread.joinable())
        {
            p.thread.join();
        }
    }

    std::shared_ptr<DrivesModel> DrivesModel::create(
        const std::shared_ptr<Context>& context)
    {
        auto out = std::shared_ptr<DrivesModel>(new DrivesModel);
        out->_init(context);
        return out;
    }

    std::shared_ptr<IObservableList<std::filesystem::path> > DrivesModel::observeDrives() const
    {
        return _p->drives;
    }
}