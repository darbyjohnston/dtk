// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/core/Random.h>

#include <ctime>
#include <random>

namespace feather_tk
{
    struct Random::Private
    {
        std::random_device rd;
        std::unique_ptr<std::mt19937> rng;
    };

    Random::Random() :
        _p(new Private)
    {
        FEATHER_TK_P();
        p.rng = std::make_unique<std::mt19937>(p.rd());
    }

    Random::~Random()
    {}

    float Random::getF()
    {
        FEATHER_TK_P();
        std::uniform_int_distribution<uint32_t> uint_dist;
        return uint_dist(*(p.rng)) / static_cast<float>(uint_dist.max());
    }

    float Random::getF(float value)
    {
        return value * getF();
    }

    float Random::getF(float min, float max)
    {
        return min + (max - min) * getF();
    }

    int Random::getI(int value)
    {
        FEATHER_TK_P();
        std::uniform_int_distribution<uint32_t> uint_dist;
        const float r =
            static_cast<float>(uint_dist(*(p.rng))) /
            static_cast<float>(uint_dist.max());
        return static_cast<int>(static_cast<float>(value + 1) * r);
    }

    int Random::getI(int min, int max)
    {
        FEATHER_TK_P();
        std::uniform_int_distribution<uint32_t> uint_dist;
        const float r =
            static_cast<float>(uint_dist(*(p.rng))) /
            static_cast<float>(uint_dist.max());
        return min + static_cast<int>(static_cast<float>(max - min + 1) * r);
    }

    void Random::setSeed(unsigned int value)
    {
        _p->rng->seed(value);
    }

    void Random::setSeed()
    {
        FEATHER_TK_P();
        const std::time_t t = std::time(nullptr);
        std::tm tm;
#if defined(_WINDOWS)
        localtime_s(&tm, &t);
#else // _WINDOWS
        localtime_r(&t, &tm);
#endif // _WINDOWS
        setSeed(tm.tm_sec);
    }
}