#pragma once

#include <cstddef>

struct StringView {
    const char* string;

    bool skip_prefix(const char* prefix) noexcept {
        if (!string || !prefix) {
            return false;
        }

        const char* current = string;
        while (*current && *prefix && *current == *prefix) {
            ++current;
            ++prefix;
        }

        return *prefix == '\0' || *current == '\0';
    }
};
