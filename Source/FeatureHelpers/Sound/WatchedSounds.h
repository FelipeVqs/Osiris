#pragma once

#include <algorithm>
#include <ranges>
#include <vector>

#include "PlayedSound.h"
#include <Utils/DynamicArray.h>

class WatchedSounds {
public:
    void addSound(int guid, const PlayedSound& sound) {
        if (!guids.pushBack(guid))
            return;

        auto it = std::ranges::find_if(sounds, [&](const auto& s) { return s.origin == sound.origin; });
        if (it != sounds.end()) {
            it->spawnTime = sound.spawnTime;
        } else if (sounds.emplaceBack(sound)) {
            std::swap(guids.back(), guids[sounds.getSize() - 1]);
        }
    }

    bool hasSound(int soundGuid) const {
        return std::ranges::any_of(guids, [&](const auto guid) { return guid == soundGuid; });
    }

    template <typename Predicate>
    void removeExpiredSounds(Predicate&& predicate) {
        guids.remove_if([&](const auto guid) {
            if (const auto soundIt = std::ranges::find_if(sounds, [&](const auto& s) { return s.guid == guid; });
                soundIt != sounds.end() && predicate(*soundIt)) {
                removeSoundAndGuid(std::ranges::distance(sounds.begin(), soundIt));
                return true;
            }
            return false;
        });
    }

    template <typename F>
    void forEach(F&& f) const {
        std::ranges::for_each(sounds, std::forward<F>(f));
    }

    auto begin() { return sounds.begin(); }
    auto end() { return sounds.end(); }

private:
    void removeSoundAndGuid(std::size_t index) {
        sounds.fastRemoveAt(index);
        guids[index] = guids[sounds.getSize()];
        guids.fastRemoveAt(sounds.getSize());
    }

    DynamicArray<int> guids;
    DynamicArray<PlayedSound> sounds;
};
