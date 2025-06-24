// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/FileIOTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/FileIO.h>
#include <feather-tk/core/Format.h>

#include <limits>

namespace feather_tk
{
    namespace core_test
    {
        FileIOTest::FileIOTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::FileIOTest")
        {}

        FileIOTest::~FileIOTest()
        {}

        std::shared_ptr<FileIOTest> FileIOTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FileIOTest>(new FileIOTest(context));
        }
        
        void FileIOTest::run()
        {
            _enums();
            _members();
            _functions();
            _operators();
        }
        
        void FileIOTest::_enums()
        {
            FEATHER_TK_TEST_ENUM(FileMode);
            FEATHER_TK_TEST_ENUM(FileRead);
        }
        
        void FileIOTest::_members()
        {
            for (auto fileRead : getFileReadEnums())
            {
                {
                    const std::filesystem::path path = "FileIOTest";
                    auto fileIO = FileIO::create(path, FileMode::Write);
                    FEATHER_TK_ASSERT(fileIO->isOpen());
                    FEATHER_TK_ASSERT(path == fileIO->getPath());
                    FEATHER_TK_ASSERT(0 == fileIO->getPos());
                    fileIO->write("Hello");
                    fileIO->setPos(0);
                    FEATHER_TK_ASSERT(0 == fileIO->getPos());
                    fileIO->seek(1);
                    fileIO->seek(1);
                    FEATHER_TK_ASSERT(2 == fileIO->getPos());
                    FEATHER_TK_ASSERT(!fileIO->isEOF());
                    fileIO->setPos(5);                    
                    FEATHER_TK_ASSERT(fileIO->isEOF());
                    fileIO.reset();
                    
                    fileIO = FileIO::create(path, FileMode::Append);
                    fileIO->write(" world");
                    fileIO.reset();

                    fileIO = FileIO::create(path, FileMode::Read, fileRead);
                    const size_t size = fileIO->getSize();
                    FEATHER_TK_ASSERT(11 == size);
                    if (FileRead::MemoryMapped == fileRead)
                    {
                        FEATHER_TK_ASSERT(fileIO->getMemoryStart());
                        FEATHER_TK_ASSERT(fileIO->getMemoryEnd());
                        FEATHER_TK_ASSERT(fileIO->getMemoryP());
                    }
                    std::string contents;
                    while (!fileIO->isEOF())
                    {
                        char c = 0;
                        fileIO->read(&c, 1);
                        contents.push_back(c);
                    }
                    FEATHER_TK_ASSERT(contents == "Hello world");
                    fileIO->setPos(0);
                    FEATHER_TK_ASSERT(0 == fileIO->getPos());
                    fileIO->seek(1);
                    fileIO->seek(1);
                    FEATHER_TK_ASSERT(2 == fileIO->getPos());
                    FEATHER_TK_ASSERT(!fileIO->isEOF());
                    fileIO->setPos(fileIO->getSize());                    
                    FEATHER_TK_ASSERT(fileIO->isEOF());
                    fileIO.reset();

                    InMemoryFile memoryRead((uint8_t*)contents.data(), contents.size());
                    fileIO = FileIO::create(path, memoryRead);
                    std::string contents2;
                    while (!fileIO->isEOF())
                    {
                        char c = 0;
                        fileIO->read(&c, 1);
                        contents2.push_back(c);
                    }
                    FEATHER_TK_ASSERT(contents2 == "Hello world");
                }
                {
                    const std::filesystem::path path = "FileIOTest2";
                    auto fileIO = FileIO::create(path, FileMode::Write);
                    int8_t i8 = 1;
                    uint8_t u8 = 2;
                    int16_t i16 = 3;
                    uint16_t u16 = 4;
                    int32_t i32 = 5;
                    uint32_t u32 = 6;
                    float f = 7.F;
                    fileIO->write8(i8);
                    fileIO->writeU8(u8);
                    fileIO->write16(i16);
                    fileIO->writeU16(u16);
                    fileIO->write32(i32);
                    fileIO->writeU32(u32);
                    fileIO->writeF32(f);
                    fileIO.reset();

                    fileIO = FileIO::create(path, FileMode::Read, fileRead);
                    int8_t i8b = 1;
                    uint8_t u8b = 2;
                    int16_t i16b = 3;
                    uint16_t u16b = 4;
                    int32_t i32b = 5;
                    uint32_t u32b = 6;
                    float fb = 7.F;
                    fileIO->read8(&i8b, 1);
                    fileIO->readU8(&u8b, 1);
                    fileIO->read16(&i16b, 1);
                    fileIO->readU16(&u16b, 1);
                    fileIO->read32(&i32b, 1);
                    fileIO->readU32(&u32b, 1);
                    fileIO->readF32(&fb, 1);
                    FEATHER_TK_ASSERT(i8 == i8b);
                    FEATHER_TK_ASSERT(u8 == u8b);
                    FEATHER_TK_ASSERT(i16 == i16b);
                    FEATHER_TK_ASSERT(u16 == u16b);
                    FEATHER_TK_ASSERT(i32 == i32b);
                    FEATHER_TK_ASSERT(u32 == u32b);
                    FEATHER_TK_ASSERT(f == fb);
                }
                {
                    const std::filesystem::path path = "FileIOTest3";
                    auto fileIO = FileIO::create(path, FileMode::Write);
                    uint32_t u32 = 1;
                    FEATHER_TK_ASSERT(!fileIO->hasEndianConversion());
                    fileIO->setEndianConversion(true);
                    FEATHER_TK_ASSERT(fileIO->hasEndianConversion());
                    fileIO->writeU32(u32);
                    fileIO.reset();

                    fileIO = FileIO::create(path, FileMode::Read, fileRead);
                    uint32_t u32b = 0;
                    fileIO->readU32(&u32b, 1);
                    FEATHER_TK_ASSERT(u32 != u32b);
                    fileIO.reset();

                    fileIO = FileIO::create(path, FileMode::Read, fileRead);
                    fileIO->setEndianConversion(true);
                    u32b = 0;
                    fileIO->readU32(&u32b, 1);
                    FEATHER_TK_ASSERT(u32 == u32b);
                    fileIO.reset();

                    fileIO = FileIO::create(path, FileMode::ReadWrite, fileRead);
                    fileIO->setEndianConversion(true);
                    u32b = 0;
                    fileIO->readU32(&u32b, 1);
                    FEATHER_TK_ASSERT(u32 == u32b);
                }
                try
                {
                    const std::filesystem::path path = "FileIOTest4";
                    auto fileIO = FileIO::create(path, FileMode::Read, fileRead);
                    FEATHER_TK_ASSERT(false);
                }
                catch (const std::exception&)
                {}
                //! \bug Why doesn't the read fail with an empty file on Windows?
#if !defined(_WINDOWS)
                try
                {
                    const std::filesystem::path path = "FileIOTest5";
                    auto fileIO = FileIO::create(path, FileMode::Write);
                    fileIO.reset();

                    fileIO = FileIO::create(path, FileMode::Read, fileRead);
                    uint8_t u8 = 0;
                    fileIO->readU8(&u8, 1);
                    FEATHER_TK_ASSERT(false);
                }
                catch (const std::exception&)
                {}
                try
                {
                    const std::filesystem::path path = "FileIOTest6";
                    auto fileIO = FileIO::create(path, FileMode::Write);
                    fileIO.reset();

                    fileIO = FileIO::create(path, FileMode::ReadWrite, fileRead);
                    uint8_t u8 = 0;
                    fileIO->readU8(&u8, 1);
                    FEATHER_TK_ASSERT(false);
                }
                catch (const std::exception&)
                {}
#endif
                try
                {
                    const std::filesystem::path path = "FileIOTest7";
                    auto fileIO = FileIO::create(path, FileMode::Read, fileRead);
                    fileIO->writeU8(1);
                    FEATHER_TK_ASSERT(false);
                }
                catch (const std::exception&)
                {}
                {
                    const std::filesystem::path path = std::filesystem::u8path("大平原");
                    auto fileIO = FileIO::create(path, FileMode::Write);
                    fileIO->writeU8(1);
                    fileIO.reset();

                    fileIO = FileIO::create(path, FileMode::Read, fileRead);
                    uint8_t c = 0;
                    fileIO->readU8(&c);
                    FEATHER_TK_ASSERT(1 == c);
                }
            }
        }
        
        void FileIOTest::_functions()
        {
            {
                const std::filesystem::path path = "FileIOTest8";
                auto fileIO = FileIO::create(path, FileMode::Write);
                fileIO->write("Hello world");
                fileIO.reset();

                fileIO = FileIO::create(path, FileMode::Read);
                std::string contents = read(fileIO);
                FEATHER_TK_ASSERT(contents == "Hello world");
            }
            {
                const std::filesystem::path path = "FileIOTest9";
                writeLines(
                    path,
                    {
                        "# This is a comment",
                        "Hello world"
                    });
                for (auto readType : getFileReadEnums())
                {
                    auto io = FileIO::create(path, FileMode::Read, readType);
                    char buf[cStringSize];
                    readWord(io, buf);
                    FEATHER_TK_ASSERT(std::string("Hello") == std::string(buf));
                    readWord(io, buf);
                    FEATHER_TK_ASSERT(std::string("world") == std::string(buf));
                }
            }
            {
                const std::filesystem::path path = "FileIOTest10";
                auto fileIO = FileIO::create(path, FileMode::Write);
                fileIO->write("Hello world");
                fileIO.reset();

                fileIO = FileIO::create(path, FileMode::Read);
                std::string line = readLine(fileIO);
                FEATHER_TK_ASSERT(line == "Hello world");
            }
            {
                const std::filesystem::path path = "FileIOTest11";
                std::vector<std::string> contents;
                contents.push_back("Hello");
                contents.push_back("World");
                writeLines(path, contents);
                FEATHER_TK_ASSERT(contents == readLines(path));
            }
            {
                const std::filesystem::path path = "FileIOTest12";
                auto fileIO = FileIO::create(path, FileMode::Write);
                fileIO->write("Hello world");
                fileIO.reset();

                truncateFile(path, 5);
                fileIO = FileIO::create(path, FileMode::ReadWrite);
                std::string contents = read(fileIO);
                FEATHER_TK_ASSERT(contents == "Hello");
            }
        }
        
        void FileIOTest::_operators()
        {
            {
                std::string contents = "Hello world";
                InMemoryFile a((uint8_t*)contents.data(), contents.size());
                InMemoryFile b((uint8_t*)contents.data(), contents.size());
                FEATHER_TK_ASSERT(a == b);
                b = InMemoryFile();
                FEATHER_TK_ASSERT(a != b);
            }
        }
    }
}

