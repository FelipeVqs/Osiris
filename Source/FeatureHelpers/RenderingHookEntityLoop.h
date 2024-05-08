#pragma once

#include <HookDependencies/HookDependenciesMask.h>
#include <CS2/Classes/Entities/CEntityInstance.h>
#include <Features/Visuals/PlayerInformationThroughWalls/PlayerInformationThroughWalls.h>
#include "EntityFromHandleFinder.h"
#include <vector>

class RenderingHookEntityLoop {
public:
    explicit RenderingHookEntityLoop(HookDependencies& dependencies, PlayerInformationThroughWalls& playerInformationThroughWalls) noexcept
        : dependencies{dependencies}
        , playerInformationThroughWalls{playerInformationThroughWalls}
    {
    }

    void run() const noexcept
    {
        if (!dependencies.requestDependencies(kCrucialDependencies))
            return;

        for (const auto& entity : dependencies.getDependency<EntityListWalker>().getEntities()) {
            handleEntity(entity);
        }
    }

private:
    static constexpr HookDependenciesMask kCrucialDependencies{
        HookDependenciesMask::Feature::EntitiesVMTs,
        HookDependenciesMask::Feature::EntityListWalker
    };

    void handleEntity(const cs2::CEntityInstance& entity) const noexcept
    {
        if (dependencies.getDependency<EntitiesVMTs>().isPlayerPawn(entity.vmt)) {
            const auto& playerPawn = static_cast<const cs2::C_CSPlayerPawn&>(entity);
            playerInformationThroughWalls.drawPlayerInformation(playerPawn);
        }
    }

    HookDependencies& dependencies;
    PlayerInformationThroughWalls& playerInformationThroughWalls;
};
