#pragma once

#include <cstdint>

#include <CS2/Classes/Entities/C_CSPlayerPawn.h>
#include <Utils/FieldOffset.h>

template <typename FieldType, typename OffsetType>
using PlayerPawnOffset = FieldOffset<cs2::C_CSPlayerPawn, FieldType, OffsetType>;

using ImmunityOffset = PlayerPawnOffset<cs2::C_CSPlayerPawn::m_bGunGameImmunity, std::uint32_t>;
using WeaponServicesOffset = PlayerPawnOffset<cs2::C_CSPlayerPawn::m_pWeaponServices, std::uint32_t>;
using PlayerControllerOffset = PlayerPawnOffset<cs2::C_CSPlayerPawn::m_hController, std::uint32_t>;
using IsDefusingOffset = PlayerPawnOffset<cs2::C_CSPlayerPawn::m_bIsDefusing, std::uint32_t>;
using IsPickingUpHostageOffset = PlayerPawnOffset<cs2::C_CSPlayerPawn::m_bIsGrabbingHostage, std::uint32_t>;
