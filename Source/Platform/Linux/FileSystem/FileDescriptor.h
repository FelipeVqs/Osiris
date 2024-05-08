#ifndef FILE_DESCRIPTOR_H
#define FILE_DESCRIPTOR_H

#include <cassert>
#include <Platform/Linux/LinuxPlatformApi.h>

class noncopyable {
protected:
    constexpr noncopyable() noexcept = default;
    ~noncopyable() noexcept = default;

    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;
};

struct FileDescriptor : private noncopyable {
public:
    explicit FileDescriptor(int fileDescriptor) noexcept
        : fileDescriptor_{fileDescriptor}
    {
    }

    FileDescriptor(FileDescriptor&& other) noexcept
        : fileDescriptor_{other.fileDescriptor_}
    {
        other.fileDescriptor_ = -1;
    }

    FileDescriptor& operator=(FileDescriptor&& other) noexcept
    {
        if (this != &other) {
            close();
            fileDescriptor_ = other.fileDescriptor_;
            other.fileDescriptor_ = -1;
        }
        return *this;
    }

    [[nodiscard]] int get() const noexcept
    {
        return fileDescriptor_;
    }

    [[nodiscard]] bool isValid() const noexcept
    {
        return fileDescriptor_ >= 0;
    }

    void close() noexcept
    {
        if (isValid()) {
            LinuxPlatformApi::close(fileDescriptor_);
            fileDescriptor_ = -1;
        }
    }

    ~FileDescriptor() noexcept
    {
        close();
    }

private:
    int fileDescriptor_ = -1;
};

#endif // FILE_DESCRIPTOR_H
