#pragma once

#include <cstdint>
#include <CS2/CGameEntitySystem.h> // Include the full entity system header

// Alias the entity system class to a shorter name for brevity
using EntitySystem = cs2::CGameEntitySystem;

// Offset of the highest entity index in the entity system
using HighestEntityIndexOffset = std::uint32_t;

// Offset of the concrete entity list in the entity system
using EntityListOffset = std::int8_t;

// Helper template for getting the offset of a field in the entity system
template <typename FieldType, typename OffsetType>
using EntitySystemOffset = OffsetType;
