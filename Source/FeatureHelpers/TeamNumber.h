#pragma once

#include <CS2/Classes/Entities/C_BaseEntity.h>
#include <CS2/Constants/TeamNumberConstants.h>

/// <summary>
/// Represents the team number for a CS:GO player.
/// </summary>
enum class TeamNumber : cs2::TeamNum {
    /// <summary>
    /// The terrorist team number.
    /// </summary>
    TT = cs2::TeamNum::TEAM_TERRORIST,

    /// <summary>
    /// The counter-terrorist team number.
    /// </summary>
    CT = cs2::TeamNum::TEAM_CT
};

