#pragma once

#include <cstdint>
#include <cs2/Classes/Entities/C_BaseEntity.h>
#include <Utils/FieldOffset.h>

namespace cs2
{
/// A type alias for an offset to a field of type FieldType in a C_BaseEntity.
/// The offset is represented as an integer value of type OffsetType.
template <typename FieldType, typename OffsetType>
using EntityOffset = FieldOffset<C_BaseEntity, FieldType, OffsetType>;
}  // namespace cs2

/// Offset to the game scene node of a C_BaseEntity.
using OffsetToGameSceneNode = EntityOffset<cs2::C_BaseEntity::m_pGameSceneNode, std::int32_t>;

/// Offset to the health of a C_BaseEntity.
using OffsetToHealth = EntityOffset<cs2::C_BaseEntity::m_iHealth, std::int32_t>;

/// Offset to the life state of a C_BaseEntity.
using OffsetToLifeState = EntityOffset<cs2::C_BaseEntity::m_lifeState, std::int32_t>;

/// Offset to the team number of a C_BaseEntity.
using OffsetToTeamNumber = EntityOffset<cs2::C_BaseEntity::m_iTeamNum, std::int32_t>;

/// Offset to the subclass VData of a C_BaseEntity.
using OffsetToVData = EntityOffset<cs2::C_BaseEntity::m_pSubclassVData, std::int32_t>;

/// Checks that FieldType is a pointer type.
template <typename FieldType>
constexpr bool is_pointer_v = std::is_pointer_v<FieldType>;

/// Statically asserts that FieldType is a pointer type.
static_assert(is_pointer_v<cs2::C_BaseEntity::m_pGameSceneNode>,
              "FieldType must be a pointer type");
