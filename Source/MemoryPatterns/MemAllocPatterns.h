#pragma once

#include <cstdint>
#include <memory>

#include <CS2/Classes/IMemAlloc.h>
#include <Helpers/PatternNotFoundLogger.h>
#include <MemorySearch/PatternFinder.h>

class MemAllocPatterns {
public:
    MemAllocPatterns(const std::shared_ptr<IMemAlloc>& memAlloc,
                     const PatternFinder<PatternNotFoundLogger>& clientPatternFinder)
        : memAlloc_(memAlloc), clientPatternFinder_(clientPatternFinder) {}

    [[nodiscard]] std::int8_t* allocOffset() const noexcept;

private:
    std::shared_ptr<IMemAlloc> memAlloc_;
    const PatternFinder<PatternNotFoundLogger>& clientPatternFinder_;
};

std::int8_t* MemAllocPatterns::allocOffset() const noexcept {
    // Implement the functionality here
}
