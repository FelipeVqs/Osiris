#pragma once

#include <cstdint>
#include <CS2/Classes/CCSWeaponBaseVData.h>
#include <Utils/FieldOffset.h>

// A template for defining a type that represents the offset of a field in a CCSWeaponBaseVData object.
template <typename FieldType, typename OffsetType>
using WeaponVDataOffset = FieldOffset<CS2::CCSWeaponBaseVData, FieldType, OffsetType>;

// The offset of the m_szName field in a CCSWeaponBaseVData object.
using OffsetToWeaponName = WeaponVDataOffset<CS2::CCSWeaponBaseVData::m_szName, std::int32_t>;
