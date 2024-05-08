#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include <GameClasses/OffsetTypes/PanoramaUiPanelOffset.h>
#include <Helpers/PatternNotFoundLogger.h>
#include <MemorySearch/PatternFinder.h>

/// Represents a set of patterns for finding members of a Panorama UI panel.
struct PanoramaUiPanelPatterns {
public:
    /// Constructs a PanoramaUiPanelPatterns object with the given pattern finders.
    /// @param clientPatternFinder The pattern finder for the client.
    /// @param panoramaPatternFinder The pattern finder for the Panorama UI.
    PanoramaUiPanelPatterns(
        const PatternFinder<PatternNotFoundLogger>& clientPatternFinder,
        const PatternFinder<PatternNotFoundLogger>& panoramaPatternFinder);

    /// Returns a pointer to the setParent pattern, or nullopt if not found.
    [[nodiscard]] std::optional<std::int32_t*> setParent() const;

    /// Returns a pointer to the setVisible pattern, or nullopt if not found.
    [[nodiscard]] std::optional<std::int32_t*> setVisible() const;

    /// Returns a pointer to the findChildInLayoutFile pattern, or nullopt if not found.
    [[nodiscard]] std::optional<std::int32_t*> findChildInLayoutFile() const;

    /// Returns a pointer to the getAttributeString pattern, or nullopt if not found.
    [[nodiscard]] std::optional<std::int32_t*> getAttributeString() const;

    /// Returns a pointer to the setAttributeString pattern, or nullopt if not found.
    [[nodiscard]] std::optional<std::int32_t*> setAttributeString() const;

    /// Returns the ChildPanelsVectorOffset, or nullopt if not found.
    [[nodiscard]] std::optional<ChildPanelsVectorOffset> childPanelsVectorOffset() const;

    /// Returns the PanelClassesVectorOffset, or nullopt if not found.
    [[nodiscard]] std::optional<PanelClassesVectorOffset> classesVectorOffset() const;

    /// Returns the PanelStyleOffset, or nullopt if not found.
    [[nodiscard]] std::optional<PanelStyleOffset> panelStyleOffset() const;

    /// Returns the ParentWindowOffset, or nullopt if not found.
    [[nodiscard]] std::optional<ParentWindowOffset> parentWindowOffset() const;

private:
    const PatternFinder<PatternNotFoundLogger>& clientPatternFinder;
    const PatternFinder<PatternNotFoundLogger>& panoramaPatternFinder;

    /// The type for integer pointers.
    using IntPtr = std::int32_t*;
};

/// Constructs a PanoramaUiPanelPatterns object with the given pattern finders.
inline PanoramaUiPanelPatterns::PanoramaUiPanelPatterns(
    const PatternFinder<PatternNotFoundLogger>& clientPatternFinder,
    const PatternFinder<PatternNotFoundLogger>& panoramaPatternFinder)
    : clientPatternFinder(clientPatternFinder),
      panoramaPatternFinder(panoramaPatternFinder) {}

/// Returns a pointer to the setParent pattern, or nullopt if not found.
inline std::optional<std::int32_t*> PanoramaUiPanelPatterns::setParent() const {
    return clientPatternFinder.findPattern<IntPtr>(
        "55 48 89 E5 57 48 83 EC 20 48 8B 05 ? ? ? ? 48 8D 0D ? ? ? ? 48 89 02");
}

/// Returns a pointer to the setVisible pattern, or nullopt if not found.
inline std::optional<std::int32_t*> PanoramaUiPanelPatterns::setVisible() const {
    return clientPatternFinder.findPattern<IntPtr>(
        "55 48 89 E5 57 48 83 EC 20 8B 45 08 8B 55 0C 53 56 57 41 B8 ? ? ? ? 48 8B 5
