#pragma once

#include <CS2/Classes/Panorama.h>
#include <Utils/FieldOffset.h>
#include <MemoryPatterns/PanoramaUiPanelPatterns.h>

/// A struct that contains offsets to various member functions of cs2::CUIPanel.
struct PanoramaUiPanelImpl {
    /// Constructs a PanoramaUiPanelImpl object with the given PanoramaUiPanelPatterns.
    explicit PanoramaUiPanelImpl(const PanoramaUiPanelPatterns& panoramaUiPanelPatterns) noexcept
        : setParent{panoramaUiPanelPatterns.setParent()}
        , setVisible{panoramaUiPanelPatterns.setVisible()}
        , findChildInLayoutFile{panoramaUiPanelPatterns.findChildInLayoutFile()}
        , getAttributeString{panoramaUiPanelPatterns.getAttributeString()}
        , setAttributeString{panoramaUiPanelPatterns.setAttributeString()}
        , childPanels{panoramaUiPanelPatterns.childPanelsVectorOffset()}
        , classes{panoramaUiPanelPatterns.classesVectorOffset()}
        , panelStyle{panoramaUiPanelPatterns.panelStyleOffset()}
        , parentWindowOffset{panoramaUiPanelPatterns.parentWindowOffset()} {}

    /// Gets a const reference to the singleton instance of PanoramaUiPanelImpl.
    [[nodiscard]] static const PanoramaUiPanelImpl& instance() noexcept;

    /// A type alias for a FieldOffset of a member function pointer of cs2::CUIPanel.
    template <typename T>
    using Offset = FieldOffset<const void, T, std::uint32_t>;

    Offset<void(cs2::CUIPanel::*)(cs2::CBasePanel*)> setParent;
    Offset<void(cs2::CUIPanel::*)(bool)> setVisible;
    Offset<cs2::CBasePanel*(cs2::CUIPanel::*)(const char*)> findChildInLayoutFile;
    Offset<const char*(cs2::CUIPanel::*)()> getAttributeString;
    Offset<void(cs2::CUIPanel::*)(const char*, const char*)> setAttributeString;

    /// An offset to the childPanels vector of cs2::CUIPanel.
    struct ChildPanelsVectorOffset {
        std::uint32_t offset;
        std::uint32_t size;
    } childPanels;

    /// An offset to the classes vector of cs2::CUIPanel.
    struct PanelClassesVectorOffset {
        std::uint32_t offset;
        std::uint32_t size;
    } classes;

    /// An offset to the panelStyle of cs2::CUIPanel.
    struct PanelStyleOffset {
        std::uint32_t offset;
        std::uint32_t size;
    } panelStyle;

    /// An offset to the parentWindow of cs2::CUIPanel.
    struct ParentWindowOffset {
        std::uint32_t offset;
        std::uint32_t size;
    } parentWindowOffset;
};

/// Ensures that the size of PanoramaUiPanelImpl is not too large.
static_assert(sizeof(PanoramaUiPanelImpl) <= 0x100, "PanoramaUiPanelImpl is too large");

/// Gets the address of the specified offset of cs2::CUIPanel.
template <typename T>
constexpr T* getAddress(const void* obj, PanoramaUiPanelImpl::Offset<T> offset) noexcept {
    return reinterpret_cast<T*>(
        reinterpret_cast<std::uintptr_t>(obj) + offset.fieldOffset);
}

/// Gets the address of the childPanels vector of cs2::CUIPanel.
constexpr auto getChildPanels(const void* obj) noexcept {
    return getAddress<std::vector<cs2::CBasePanel*>>(obj,
