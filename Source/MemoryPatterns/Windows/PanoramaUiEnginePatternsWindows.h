#pragma once

#include <MemoryPatterns/PanoramaUiEnginePatterns.h>
#include <MemorySearch/BytePatternLiteral.h>

class PanoramaUiEnginePatterns {
public:
    PanoramaUiEnginePatterns() = delete;
    PanoramaUiEnginePatterns(const PanoramaUiEnginePatterns&) = delete;
    PanoramaUiEnginePatterns& operator=(const PanoramaUiEnginePatterns&) = delete;

    PanoramaUiEnginePatterns(PanoramaUiEnginePatterns&&) = delete;
    PanoramaUiEnginePatterns& operator=(PanoramaUiEnginePatterns&&) = delete;

    static cs2::CUIEngine::getPanelHandle getPanelHandle() {
        return patternFinder("8B 81 ? ? ? ? 4C 8B D9 83 F8 FF 74 41"_pat).as<cs2::CUIEngine::getPanelHandle>();
    }

    static cs2::CUIEngine::getPanelPointer getPanelPointer() {
        return patternFinder("4C 63 02 4D 8B C8"_pat).as<cs2::CUIEngine::getPanelPointer>();
    }

    static cs2::CUIEngine::runScript runScript() {
        return patternFinder("48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 54 41 56 41 57 48 81 EC ? ? ? ? 4C 8B"_pat).as<cs2::CUIEngine::runScript>();
    }

    static cs2::CUIEngine::makeSymbol makeSymbol() {
        return patternFinder("8B CA 49 8B D0"_pat).as<cs2::CUIEngine::makeSymbol>();
    }

    static cs2::CUIEngine::onDeletePanel onDeletePanel() {
        return patternFinder("48 89 5C 24 ? 56 48 83 EC 20 8B 05"_pat).as<cs2::CUIEngine::onDeletePanel>();
    }

private:
    static BytePatternFinder& patternFinder(const char* pattern) {
        static std::unordered_map<std::string, BytePatternFinder> patternMap;
        if (patternMap.find(pattern) == patternMap.end()) {
            patternMap[pattern] = BytePatternFinder(pattern);
        }
        return patternMap[pattern];
    }

    static BytePatternFinder& panoramaPatternFinder(const char* pattern) {
        static BytePatternFinder panoramaPattern(pattern);
        return panoramaPattern;
    }

    static BytePatternFinder panoramaPattern;
};

BytePatternFinder PanoramaUiEnginePatterns::panoramaPattern = BytePatternFinder("8B 81 ? ? ? ? 4C 8B D9 83 F8 FF 74 41"_pat);

cs2::CUIEngine::getPanelHandle PanoramaUiEnginePatterns::patternNotFound(const char* pattern) {
    // Handle the case when the pattern is not found
    // ...
}
