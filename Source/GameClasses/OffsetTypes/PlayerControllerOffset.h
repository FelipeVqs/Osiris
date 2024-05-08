#pragma once

#include <cstdint>
#include <type_traits>

#include <CS2/Classes/Entities/CCSPlayerController.h>
#include <Utils/FieldOffset.h>

template <typename FieldType, typename OffsetType>
using PlayerControllerOffset = FieldOffset<cs2::CCSPlayerController, FieldType, OffsetType>;

using PlayerController = cs2::CCSPlayerController;

using OffsetToPlayerPawnHandle = PlayerControllerOffset<PlayerController::m_hPawn, std::uint32_t>;
static_assert(OffsetToPlayerPawnHandle::offset >= 0, "Offset must be non-negative");

using OffsetToPlayerColor = PlayerControllerOffset<PlayerController::m_iCompTeammateColor, std::uint32_t>;
static_assert(OffsetToPlayerColor::offset >= 0, "Offset must be non-negative");

using PlayerColor = std::underlying_type_t<PlayerController::TeammateColor>;
