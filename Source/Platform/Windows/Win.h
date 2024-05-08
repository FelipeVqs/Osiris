#ifndef WIN_PEB_H
#define WIN_PEB_H

#include <Platform/Macros/IsPlatform.h>
#include <Utils/CharUtils.h>
#include <Utils/Pad.h>
#include <cstddef> // for std::size_t
#include <new> // for noexcept

namespace win
{

struct ListEntry
{
    ListEntry* fLink;
    ListEntry* bLink;
};

inline ListEntry* getListEntry(LdrDataTableEntry* entry) noexcept
{
    return &entry->inLoadOrderLinks;
}

struct PebLdrData
{
    PAD(0x10);
    ListEntry inLoadOrderModuleList;
};

inline PebLdrData* getPebLdrData(Peb* peb) noexcept
{
    return peb->ldr;
}

struct Peb
{
    PAD(0x18);
    PebLdrData* ldr;
};

struct UnicodeString
{
    unsigned short length;
    unsigned short maximumLength;
    wchar_t* buffer;

    UnicodeString(unsigned short length, unsigned short maximumLength, wchar_t* buffer) noexcept
        : length(length), maximumLength(maximumLength), buffer(buffer) {}

    [[nodiscard]] unsigned short lengthInChars() const noexcept
    {
        return length / sizeof(wchar_t);
    }

    [[nodiscard]] bool equalsCaseInsensitive(const char* otherString) const noexcept
    {
        for (std::size_t i = 0; i < lengthInChars(); ++i) {
            if (utils::toUpper(buffer[i]) != utils::toUpper(otherString[i]) || otherString[i] == '\0')
                return false;
        }
        return true;
    }
};

struct LdrDataTableEntry
{
    ListEntry inLoadOrderLinks;
    ListEntry inMemoryOrderLinks;
    ListEntry inInitializationOrderLinks;
    void* dllBase;
    void* entryPoint;
    unsigned long sizeOfImage;
    UnicodeString fullDllName;
    UnicodeString baseDllName;
};

inline UnicodeString* getUnicodeString(LdrDataTableEntry* entry, int index) noexcept
{
    switch (index) {
    case 0: return &(entry->fullDllName);
    case 1: return &(entry->baseDllName);
    default: return nullptr;
    }
}

inline bool equalsCaseInsensitive(UnicodeString* str1, UnicodeString* str2) noexcept
{
    if (str1->length != str2->length)
        return false;

    for (std::size_t i = 0; i < str1->lengthInChars(); ++i) {
        if (utils::toUpper(str1->buffer[i]) != utils::toUpper(str2->buffer[i]))
            return false;
    }

    return true;
}

inline const wchar_t* getModulePath(LdrDataTableEntry* entry) noexcept
{
    return entry->fullDllName.buffer;
}

inline const wchar_t* getModuleBaseName(LdrDataTableEntry* entry) noexcept
{
    return entry->baseDllName.buffer;
}

} // namespace win

#endif // WIN_PEB_H
