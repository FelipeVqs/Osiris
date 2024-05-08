#pragma once

#include <MemoryPatterns/EntityPatterns.h>

struct EntityImpl {
    EntityImpl(const EntityPatterns& entityPatterns) noexcept
        : EntityImpl{std::move(entityPatterns)}
    {}

    EntityImpl(EntityPatterns&& entityPatterns) noexcept
        : offsetToGameSceneNode{entityPatterns.offsetToGameSceneNode()}
        , offsetToHealth{entityPatterns.offsetToHealth()}
        , offsetToLifeState{entityPatterns.offsetToLifeState()}
        , offsetToTeamNumber{entityPatterns.offsetToTeamNumber()}
        , offsetToVData{entityPatterns.offsetToVData()}
    {}

    OffsetToGameSceneNode offsetToGameSceneNode;
    OffsetToHealth offsetToHealth;
    OffsetToLifeState offsetToLifeState;
    OffsetToTeamNumber offsetToTeamNumber;
    OffsetToVData offsetToVData;
};
