// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/DrivesModel.h>

#include <dtk/core/File.h>
#include <dtk/core/Time.h>
#include <dtk/core/Timer.h>

#include <atomic>
#include <mutex>
#include <thread>

namespace dtk
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
        DTK_P();

        p.drives = ObservableList<std::filesystem::path>::create();

        p.running = true;
        p.thread = std::thread(
            [this]
            {
                DTK_P();
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
                DTK_P();
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
        DTK_P();
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