#pragma once

#include <array>
#include <cstddef>
#include <initializer_list>

#include <CS2/Classes/CUtlVector.h>
#include <CS2/Classes/Panorama.h>
#include <CS2/Classes/Transform3D.h>

namespace cs2 {
class CTransform3D;
}  // namespace cs2

using namespace std;
using cs2::CTransform3D;
using cs2::CUtlVector;

template <size_t N>
struct PanoramaTransformations {
    void applyTo(const PanelStyleSetter& style) const noexcept;

    array<CTransform3D*, N> transformations;

    template <typename... Args>
    constexpr PanoramaTransformations(Args&&... args) noexcept
        : transformations{forward<Args>(args)...} {}

    constexpr PanoramaTransformations(initializer_list<CTransform3D*> il) noexcept
        : transformations{il} {}
};

template <size_t N>
void PanoramaTransformations<N>::applyTo(const PanelStyleSetter& style) const noexcept {
    CUtlVector<CTransform3D*> dummyVector;
    dummyVector.allocationCount = N;
    dummyVector.memory = transformations.data();
    dummyVector.growSize = 0;
    dummyVector.size = N;

    style.setTransform3D(dummyVector);
}

template <typename... Args>
PanoramaTransformations(Args...) -> PanoramaTransformations<sizeof...(Args)>;
