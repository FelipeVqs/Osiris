#pragma once

#include <cstddef> // for std::size_t
#include <new> // for std::nothrow
#include <cstring> // for std::strcpy

namespace cs2 {

struct CUtlString {
    char* m_pString;

    // Constructor: allocate memory and copy the input string
    CUtlString(const char* pInputString) {
        std::size_t length = std::strlen(pInputString) + 1;
        m_pString = new (std::nothrow) char[length];
        if (m_pString) {
            std::strcpy(m_pString, pInputString);
        }
    }

    // Destructor: deallocate memory
    ~CUtlString() {
        delete[] m_pString;
    }

    // Copy constructor: copy the input string and allocate new memory
    CUtlString(const CUtlString& other) {
        std::size_t length = std::strlen(other.m_pString) + 1;
        m_pString = new (std::nothrow) char[length];
        if (m_pString) {
            std::strcpy(m_pString, other.m_pString);
        }
    }

    // Copy assignment operator: deallocate memory, copy the input string and allocate new memory
    CUtlString& operator=(const CUtlString& other) {
        if (this != &other) {
            delete[] m_pString;

            std::size_t length = std::strlen(other.m_pString) + 1;
            m_pString = new (std::nothrow) char[length];
            if (m_pString) {
                std::strcpy(m_pString, other.m_pString);
            }
        }
        return *this;
    }

    // Move constructor: steal the input string's memory
    CUtlString(CUtlString&& other) noexcept {
        m_pString = other.m_pString;
        other.m_pString = nullptr;
    }

    // Move assignment operator: steal the input string's memory
    CUtlString& operator=(CUtlString&& other) noexcept {
        if (this != &other) {
            delete[] m_pString;

            m_pString = other.m_pString;
            other.m_pString = nullptr;
        }
        return *this;
    }
};

} // namespace cs2
