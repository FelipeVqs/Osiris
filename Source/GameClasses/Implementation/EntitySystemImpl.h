#pragma once

#include <CS2/Classes/EntitySystem/CGameEntitySystem.h>
#include <MemoryPatterns/EntitySystemPatterns.h>
#include <memory> // for std::unique_ptr

// A wrapper class for the CS2 Entity System.
struct EntitySystemImpl {
    // Constructs an EntitySystemImpl object with the given entity system patterns.
    explicit EntitySystemImpl(const EntitySystemPatterns& entitySystemPatterns) noexcept
        : entity_system{std::unique_ptr<cs2::CGameEntitySystem>(new cs2::CGameEntitySystem(entitySystemPatterns.entitySystem()))}
        , highest_entity_index_offset{entitySystemPatterns.highestEntityIndexOffset()}
        , entity_list_offset{entitySystemPatterns.entityListOffset()}
    {
    }

    // The CS2 Entity System, managed by a unique_ptr to ensure proper deletion.
    std::unique_ptr<cs2::CGameEntitySystem> entity_system;

    // The highest entity index offset.
    cs2::HighestEntityIndexOffset highest_entity_index_offset;

    // The entity list offset.
    cs2::EntityListOffset entity_list_offset;
};
