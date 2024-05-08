#pragma once

#include <Helpers/PatternNotFoundLogger.h>
#include <MemorySearch/PatternFinder.h>
#include <SoundChannels.h> // assuming this is where SoundChannels is defined

namespace cs2
{
    class SoundSystemPatterns
    {
    public:
        SoundSystemPatterns(const PatternFinder<PatternNotFoundLogger>& patternFinder)
            : soundSystemPatternFinder(patternFinder) {}

        [[nodiscard]] cs2::SoundChannels** soundChannels() const noexcept
        {
            // implementation here
        }

        const PatternFinder<PatternNotFoundLogger>& getPatternFinder() const noexcept
        {
            return soundSystemPatternFinder;
        }

    private:
        const PatternFinder<PatternNotFoundLogger>& soundSystemPatternFinder;
    };
}
