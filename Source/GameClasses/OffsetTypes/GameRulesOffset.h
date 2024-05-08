#pragma once

#include <CS2/Classes/C_CSGameRules.h>
#include <Utils/FieldOffset.h>

/**
 * A type alias for a field offset in the CSGameRules class.
 * This allows for easier access to the field's value using the offset.
 */
template <typename FieldType, typename OffsetType = std::int32_t>
using GameRulesOffset = FieldOffset<cs2::C_CSGameRules, FieldType, OffsetType>;

/**
 * A type alias for the offset of the m_fRoundStartTime field in the CSGameRules class.
 */
constexpr GameRulesOffset<float, std::int32_t> RoundStartTimeOffset{
    offsetof(cs2::C_CSGameRules, m_fRoundStartTime)
};
