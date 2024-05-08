#pragma once

#include <MemoryPatterns/PlayerPawnPatterns.h>

struct PlayerPawnImpl {
public:
    explicit PlayerPawnImpl(const PlayerPawnPatterns& playerPawnPatterns) noexcept
        : offsetToPlayerPawnImmunity{ playerPawnPatterns.getOffsetToPlayerPawnImmunity() }
        , offsetToWeaponServices{ playerPawnPatterns.getOffsetToWeaponServices() }
        , offsetToPlayerController{ playerPawnPatterns.getOffsetToPlayerController() }
        , offsetToIsDefusing{ playerPawnPatterns.getOffsetToIsDefusing() }
        , offsetToIsPickingUpHostage{ playerPawnPatterns.getOffsetToIsPickingUpHostage() }
    {}

    OffsetToPlayerPawnImmunity getOffsetToPlayerPawnImmunity() const noexcept {
        return offsetToPlayerPawnImmunity;
    }

    OffsetToWeaponServices getOffsetToWeaponServices() const noexcept {
        return offsetToWeaponServices;

