// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/String.h>
#include <feather-tk/core/Util.h>

#include <filesystem>
#include <memory>

namespace feather_tk
{
    //! \name File I/O
    ///@{
        
    //! File I/O modes.
    enum class FileMode
    {
        Read,
        Write,
        ReadWrite,
        Append,

        Count,
        First = Read
    };
    FEATHER_TK_ENUM(FileMode);

    //! File read type.
    enum class FileRead
    {
        Normal,
        MemoryMapped,

        Count,
        First = Normal
    };
    FEATHER_TK_ENUM(FileRead);

    //! In-memory file.
    struct InMemoryFile
    {
        InMemoryFile() = default;
        InMemoryFile(const uint8_t*, size_t size);

        const uint8_t* p = nullptr;
        size_t size = 0;

        bool operator == (const InMemoryFile&) const;
        bool operator != (const InMemoryFile&) const;
    };

    //! File I/O.
    class FileIO : public std::enable_shared_from_this<FileIO>
    {
        FEATHER_TK_NON_COPYABLE(FileIO);

    protected:
        FileIO();

    public:
        ~FileIO();

        //! Create a new file I/O object.
        static std::shared_ptr<FileIO> create(
            const std::filesystem::path&,
            FileMode,
            FileRead = FileRead::MemoryMapped);

        //! Create a new file I/O object.
        static std::shared_ptr<FileIO> create(
            const std::string&,
            FileMode,
            FileRead = FileRead::MemoryMapped);

        //! Create a read-only file I/O object from memory.
        static std::shared_ptr<FileIO> create(
            const std::filesystem::path&,
            const InMemoryFile&);

        //! Create a read-only file I/O object from memory.
        static std::shared_ptr<FileIO> create(
            const std::string&,
            const InMemoryFile&);

        //! Get whether the file is open.
        bool isOpen() const;

        //! \name Information
        ///@{

        //! Get the file path.
        const std::filesystem::path& getPath() const;

        //! Get the file size.
        size_t getSize() const;

        ///@}

        //! \name Position
        ///@{

        //! Get the current file position.
        size_t getPos() const;

        //! Set the current file position.
        void setPos(size_t);

        //! Advance the current file position.
        void seek(size_t);

        //! Get whether the file position is at the end of the file.
        bool isEOF() const;

        ///@}

        //! \name Read
        ///@{

        void read(void*, size_t, size_t wordSize = 1);

        void read8(int8_t*, size_t = 1);
        void readU8(uint8_t*, size_t = 1);
        void read16(int16_t*, size_t = 1);
        void readU16(uint16_t*, size_t = 1);
        void read32(int32_t*, size_t = 1);
        void readU32(uint32_t*, size_t = 1);
        void readF32(float*, size_t = 1);

        ///@}

        //! \name Write
        ///@{

        void write(const void*, size_t, size_t wordSize = 1);

        void write8(const int8_t*, size_t);
        void writeU8(const uint8_t*, size_t);
        void write16(const int16_t*, size_t);
        void writeU16(const uint16_t*, size_t);
        void write32(const int32_t*, size_t);
        void writeU32(const uint32_t*, size_t);
        void writeF32(const float*, size_t);

        void write8(int8_t);
        void writeU8(uint8_t);
        void write16(int16_t);
        void writeU16(uint16_t);
        void write32(int32_t);
        void writeU32(uint32_t);
        void writeF32(float);

        void write(const std::string&);

        ///@}

        //! \name Memory Mapping
        ///@{

        //! Get a pointer to the start of the memory-map.
        const uint8_t* getMemoryStart() const;

        //! Get a pointer to the end of the memory-map.
        const uint8_t* getMemoryEnd() const;

        //! Get the current memory-map position.
        const uint8_t* getMemoryP() const;

        ///@}

        //! \name Endian
        ///@{

        //! Get whether automatic endian conversion is performed.
        bool hasEndianConversion() const;

        //! Set whether automatic endian conversion is performed.
        void setEndianConversion(bool);

        ///@}

    private:
        void _open(const std::filesystem::path&, FileMode, FileRead);
        bool _close(std::string* error = nullptr);

        FEATHER_TK_PRIVATE();
    };

    //! Read the contents from a file.
    std::string read(const std::shared_ptr<FileIO>&);

    //! Read a word from a file.
    void readWord(const std::shared_ptr<FileIO>&, char*, size_t maxLen = cStringSize);

    //! Read a line from a file.
    std::string readLine(const std::shared_ptr<FileIO>&);

    //! Read all the lines from a file.
    std::vector<std::string> readLines(const std::filesystem::path&);

    //! Read all the lines from a file.
    std::vector<std::string> readLines(const std::string&);

    //! Write lines to a file.
    void writeLines(const std::filesystem::path&, const std::vector<std::string>&);

    //! Write lines to a file.
    void writeLines(const std::string&, const std::vector<std::string>&);

    //! Truncate a file.
    void truncateFile(const std::filesystem::path&, size_t);

    //! Truncate a file.
    void truncateFile(const std::string&, size_t);

    ///@}
}

#include <feather-tk/core/FileIOInline.h>
