#pragma once

#include <MemoryPatterns/GameSceneNodePatterns.h>

// Represents an implementation of a GameSceneNode.
struct GameSceneNodeImpl {
    // Constructs a GameSceneNodeImpl with the given patterns.
    explicit GameSceneNodeImpl(const GameSceneNodePatterns& gameSceneNodePatterns) noexcept
        : offsetToAbsOrigin{gameSceneNodePatterns.offsetToAbsOrigin()} {}

    // Constructs a default GameSceneNodeImpl.
    GameSceneNodeImpl() noexcept = default;

    // The offset to the absolute origin of the GameSceneNode.
    const OffsetToAbsOrigin offsetToAbsOrigin;
};

