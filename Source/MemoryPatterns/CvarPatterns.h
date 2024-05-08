#pragma once

#include <CS2/Classes/CCvar.h>
#include <GameClasses/OffsetTypes/CvarOffset.h>
#include <Helpers/PatternNotFoundLogger.h>
#include <MemorySearch/PatternFinder.h>

// A struct that contains the necessary information to find the CVar and its list offset
struct CvarPatterns {
    // The pattern finder for the client module
    constexpr inline static const PatternFinder<PatternNotFoundLogger>& clientPatternFinder = GetClientPatternFinder();

    // The pattern finder for the tier0 module
    constexpr inline static const PatternFinder<PatternNotFoundLogger>& tier0PatternFinder = GetTier0PatternFinder();

    // The CVar object
    [[nodiscard]] const cs2::CCvar* cvar() const noexcept {
        return *reinterpret_cast<const cs2::CCvar**>(offsetToConVarList().get());
    }

    // The offset to the CVar list
    const OffsetToConVarList offsetToConVarList;

private:
    // Helper functions to get the pattern finders
    constexpr static const PatternFinder<PatternNotFoundLogger>& GetClientPatternFinder() {
        static const PatternFinder<PatternNotFoundLogger> finder("client.dll", "B9 ? ? ? ? E8 ? ? ? ? 8B 54 24 ? 51 56", "xx????xx????xxxx????xx???xx");
        return finder;
    }

    constexpr static const PatternFinder<PatternNotFoundLogger>& GetTier0PatternFinder() {
        static const PatternFinder<PatternNotFoundLogger> finder("tier0.dll", "8B 0D ? ? ? ? 85 C9 74 4A 8B 87 ? ? ? ? 75 12", "xx????x?x????xx????xxxx");
        return finder;
    }
};
