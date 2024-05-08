//  GameSceneNodeOffset.h: Helper macros and types for accessing offsets in CGameSceneNode

#pragma once

#include <cs2/CGameSceneNode.h>
#include <Utils/FieldOffset.h>

#include <cstdint>

using FieldType = std::uint32_t;
using OffsetType = std::int32_t;
using CGameSceneNode = cs2::CGameSceneNode;
using CGameSceneNodePtr = CGameSceneNode*;

template <typename FieldType, typename OffsetType>
using GameSceneNodeOffset = FieldOffset<CGameSceneNode, FieldType, OffsetType>;

using OffsetToAbsOrigin = GameSceneNodeOffset<CGameSceneNode::m_vecAbsOrigin, OffsetType>;
