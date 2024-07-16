// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkCore/FileIO.h>

#include <dtkCore/Assert.h>
#include <dtkCore/Error.h>

#include <algorithm>
#include <array>
#include <iostream>

namespace dtk
{
    namespace core
    {
        DTK_ENUM_IMPL(
            FileMode,
            "Read",
            "Write",
            "ReadWrite",
            "Append");

        DTK_ENUM_IMPL(
            FileRead,
            "Normal",
            "MemoryMapped");

        std::shared_ptr<FileIO> FileIO::create(
            const std::filesystem::path& path,
            FileMode mode,
            FileRead readType)
        {
            auto out = std::shared_ptr<FileIO>(new FileIO);
            out->_open(path, mode, readType);
            return out;
        }

        void FileIO::read8(int8_t* value, size_t size)
        {
            return read(value, size, 1);
        }

        void FileIO::readU8(uint8_t* value, size_t size)
        {
            return read(value, size, 1);
        }

        void FileIO::read16(int16_t* value, size_t size)
        {
            return read(value, size, 2);
        }

        void FileIO::readU16(uint16_t* value, size_t size)
        {
            return read(value, size, 2);
        }

        void FileIO::read32(int32_t* value, size_t size)
        {
            return read(value, size, 4);
        }

        void FileIO::readU32(uint32_t* value, size_t size)
        {
            return read(value, size, 4);
        }

        void FileIO::readF32(float* value, size_t size)
        {
            return read(value, size, 4);
        }

        void FileIO::write8(const int8_t* value, size_t size)
        {
            write(value, size, 1);
        }

        void FileIO::writeU8(const uint8_t* value, size_t size)
        {
            write(value, size, 1);
        }

        void FileIO::write16(const int16_t* value, size_t size)
        {
            write(value, size, 2);
        }

        void FileIO::writeU16(const uint16_t* value, size_t size)
        {
            write(value, size, 2);
        }

        void FileIO::write32(const int32_t* value, size_t size)
        {
            return write(value, size, 4);
        }

        void FileIO::writeU32(const uint32_t* value, size_t size)
        {
            return write(value, size, 4);
        }

        void FileIO::writeF32(const float* value, size_t size)
        {
            write(value, size, 4);
        }

        void FileIO::write8(int8_t value)
        {
            write8(&value, 1);
        }

        void FileIO::writeU8(uint8_t value)
        {
            writeU8(&value, 1);
        }

        void FileIO::write16(int16_t value)
        {
            write16(&value, 1);
        }

        void FileIO::writeU16(uint16_t value)
        {
            writeU16(&value, 1);
        }

        void FileIO::write32(int32_t value)
        {
            write32(&value, 1);
        }

        void FileIO::writeU32(uint32_t value)
        {
            writeU32(&value, 1);
        }

        void FileIO::writeF32(float value)
        {
            writeF32(&value, 1);
        }

        void FileIO::write(const std::string& value)
        {
            write8(reinterpret_cast<const int8_t*>(value.c_str()), value.size());
        }

        std::string read(const std::shared_ptr<FileIO>& io)
        {
            std::string out;
            if (const uint8_t* p = io->getMemoryP())
            {
                const uint8_t* end = io->getMemoryEnd();
                out = std::string(reinterpret_cast<const char*>(p), end - p);
            }
            else
            {
                const size_t fileSize = io->getSize();
                out.resize(fileSize);
                io->read(reinterpret_cast<void*>(&out[0]), fileSize);
            }
            return out;
        }

        std::string readLine(const std::shared_ptr<FileIO>& io)
        {
            std::string out;
            if (!io->isEOF())
            {
                char c = 0;
                do
                {
                    io->read(&c, 1);
                    if (c != '\n' &&
                        c != '\r')
                    {
                        out.push_back(c);
                    }
                } while (
                    c != '\n' &&
                    c != '\r' &&
                    !io->isEOF());
            }
            return out;
        }

        std::vector<std::string> readLines(const std::filesystem::path& path)
        {
            std::vector<std::string> out;
            auto io = FileIO::create(path, FileMode::Read);
            while (!io->isEOF())
            {
                out.push_back(readLine(io));
            }
            return out;
        }

        void writeLines(const std::filesystem::path& path, const std::vector<std::string>& lines)
        {
            auto io = FileIO::create(path, FileMode::Write);
            for (const auto& line : lines)
            {
                io->write(line);
                io->write8('\n');
            }
        }
    }
}
