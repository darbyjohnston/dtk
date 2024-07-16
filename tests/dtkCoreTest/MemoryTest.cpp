// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkCoreTest/MemoryTest.h>

#include <dtkCore/Assert.h>
#include <dtkCore/Format.h>
#include <dtkCore/Memory.h>

using namespace dtk::core;

namespace dtk
{
    namespace core_test
    {
        MemoryTest::MemoryTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::core_test::MemoryTest")
        {}

        MemoryTest::~MemoryTest()
        {}

        std::shared_ptr<MemoryTest> MemoryTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<MemoryTest>(new MemoryTest(context));
        }
        
        void MemoryTest::run()
        {
            _enums();
            _endian();
            _bits();
        }
        
        void MemoryTest::_enums()
        {
            DTK_TEST_ENUM(Endian);
        }
        
        void MemoryTest::_endian()
        {
            _print(Format("Current endian: {0}").arg(getEndian()));
            _print(Format("Opposite endian: {0}").arg(opposite(getEndian())));
            {
                std::vector<uint8_t> data(
                    { 0, 1, 2, 3 });
                const std::vector<uint8_t> result(
                    { 1, 0, 3, 2 });
                std::vector<uint8_t> out(result.size());
                endian(data.data(), out.data(), data.size() / 2, 2);
                DTK_ASSERT(result == out);
                endian(data.data(), data.size() / 2, 2);
                DTK_ASSERT(result == data);
            }
            {
                std::vector<uint8_t> data(
                    { 0, 1, 2, 3, 4, 5, 6, 7 });
                const std::vector<uint8_t> result(
                    { 3, 2, 1, 0, 7, 6, 5, 4 });
                std::vector<uint8_t> out(result.size());
                endian(data.data(), out.data(), data.size() / 4, 4);
                DTK_ASSERT(result == out);
                endian(data.data(), data.size() / 4, 4);
                DTK_ASSERT(result == data);
            }
            {
                std::vector<uint8_t> data(
                    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
                const std::vector<uint8_t> result(
                    { 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 11, 10, 9, 8 });
                std::vector<uint8_t> out(result.size());
                endian(data.data(), out.data(), data.size() / 8, 8);
                DTK_ASSERT(result == out);
                endian(data.data(), data.size() / 8, 8);
                DTK_ASSERT(result == data);
            }
        }
        
        void MemoryTest::_bits()
        {
            {
                uint8_t v = 0;
                v = setBit(v, 0);
                v = setBit(v, 3);
                v = setBit(v, 7);
                DTK_ASSERT(getBit(v, 0));
                DTK_ASSERT(getBit(v, 3));
                DTK_ASSERT(getBit(v, 7));
                v = clearBit(v, 0);
                v = clearBit(v, 3);
                v = clearBit(v, 7);
                DTK_ASSERT(!getBit(v, 0));
                DTK_ASSERT(!getBit(v, 3));
                DTK_ASSERT(!getBit(v, 7));
                v = toggleBit(v, 0);
                v = toggleBit(v, 3);
                v = toggleBit(v, 7);
                _print(Format("Bits: {0}").arg(getBitString(v)));
            }
            {
                uint16_t v = 0;
                v = setBit(v, 0);
                v = setBit(v, 7);
                v = setBit(v, 15);
                DTK_ASSERT(getBit(v, 0));
                DTK_ASSERT(getBit(v, 7));
                DTK_ASSERT(getBit(v, 15));
                v = clearBit(v, 0);
                v = clearBit(v, 7);
                v = clearBit(v, 15);
                DTK_ASSERT(!getBit(v, 0));
                DTK_ASSERT(!getBit(v, 7));
                DTK_ASSERT(!getBit(v, 15));
                v = toggleBit(v, 0);
                v = toggleBit(v, 7);
                v = toggleBit(v, 15);
                _print(Format("Bits: {0}").arg(getBitString(v)));
            }
        }
    }
}

