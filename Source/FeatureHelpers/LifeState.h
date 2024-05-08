#pragma once

#include <CS2/Classes/Entities/C_BaseEntity.h>
#include <CS2/Constants/LifeStateConstants.h>

// Use the enum class keyword to make LifeState a strongly-typed enumeration
// to prevent unintended implicit conversions and improve type safety.
enum class LifeState : std::underlying_type_t<cs2::C_BaseEntity::m_lifeState> {
    Alive = cs2::LIFE_ALIVE
};

// Optionally, you can provide a type alias for the underlying type of LifeState
using LifeStateUnderlyingType = std::underlying_type_t<LifeState>;

