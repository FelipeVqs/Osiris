#pragma once

#include <cstdint>
#include <cs2/Classes/Panorama.h>
#include <Utils/FieldOffset.h>

// Template for getting the offset of a field in a class
template <typename FieldType, typename OffsetType>
using PanoramaUiPanelOffset = FieldOffset<cs2::CUIPanel, FieldType, OffsetType>;

// Offset of the `childrenVector` field in `cs2::CUIPanel`
using ChildPanelsVectorOffset = PanoramaUiPanelOffset<cs2::CUIPanel::childrenVector, std::uintptr_t>;

// Offset of the `classesVector` field in `cs2::CUIPanel`
using PanelClassesVectorOffset = PanoramaUiPanelOffset<cs2::CUIPanel::classesVector, std::uintptr_t>;

// Offset of the `panelStyle` field in `cs2::CUIPanel`
using PanelStyleOffset = PanoramaUiPanelOffset<cs2::CPanelStyle*, std::uintptr_t>;

// Offset of the `parentWindow` field in `cs2::CTopLevelWindow`
using ParentWindowOffset = PanoramaUiPanelOffset<cs2::CTopLevelWindow*, std::uintptr_t>;

// Check that `FieldType` is a pointer type
template <typename T>
constexpr bool is_pointer() {
    return std::is_pointer<T>::value;
}

template <typename FieldType, typename OffsetType>
using ImprovedPanoramaUiPanelOffset = PanoramaUiPanelOffset<FieldType, OffsetType>;

template <typename FieldType>
using ImprovedChildPanelsVectorOffset = std::enable_if_t<is_pointer<FieldType>::value, PanoramaUiPanelOffset<cs2::CUIPanel::childrenVector, std::uintptr_t>>;

template <typename FieldType>
using ImprovedPanelClassesVectorOffset = std::enable_if_t<is_pointer<FieldType>::value, PanoramaUiPanelOffset<cs2::CUIPanel::classesVector, std::uintptr_t>>;

template <typename FieldType>
using ImprovedPanelStyleOffset = std::enable_if_t<is_pointer<FieldType>::value, PanoramaUiPanelOffset<cs2::CPanelStyle, std::uintptr_t>>;

template <typename FieldType>
using ImprovedParentWindowOffset = std::enable_if_t<is_pointer<FieldType>::value, PanoramaUiPanelOffset<cs2::CTopLevelWindow, std::uintptr_t>>;
