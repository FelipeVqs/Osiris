#pragma once

#include <optional>

#include <CS2/Constants/BombSiteIndex.h>
#include <CS2/Constants/EntityHandle.h>
#include "Implementation/PlantedC4Impl.h"

struct PlantedC4 {
    explicit PlantedC4(cs2::CPlantedC4& thisptr, const PlantedC4Impl& impl) noexcept
        : thisptr{thisptr}
        , impl{impl}
    {
    }

    [[nodiscard]] float getTimeToExplosion(float curtime) const noexcept
    {
        if (ticking())
            return impl.blowTime.of(&thisptr).value_or(0.0f) - curtime;
        return -1.0f;
    }

    [[nodiscard]] bool isBeingDefused() const noexcept
    {
        return impl.defuser.of(&thisptr).value_or(cs2::INVALID_EHANDLE_INDEX) != cs2::INVALID_EHANDLE_INDEX;
    }

    [[nodiscard]] std::optional<bool> canBeDefused() const noexcept
    {
        const auto defuseEndTime = impl.defuseEndTime.of(&thisptr);
        const auto blowTime = impl.blowTime.of(&thisptr);
        if (defuseEndTime.has_value() && blowTime.has_value())
            return *defuseEndTime < *blowTime;
        return {};
    }

    [[nodiscard]] float getTimeToDefuseEnd(float curtime) const noexcept
    {
        return impl.defuseEndTime.of(&thisptr).value_or(0.0f) - curtime;
    }

    [[nodiscard]] const char* getBombSiteIconUrl() const noexcept
    {
        static constexpr auto INVALID_BOMBSITE_INDEX = -1;
        switch (impl.bombSite.of(&thisptr).value_or(INVALID_BOMBSITE_INDEX)) {
        case cs2::BOMBSITE_A_INDEX: return "s2r://panorama/images/icons/ui/map_bombzone_a.vsvg";
        case cs2::BOMBSITE_B_INDEX: return "s2r://panorama/images/icons/ui/map_bombzone_b.vsvg";
        default: return nullptr;
        }
    }

private:
    [[nodiscard]] bool ticking() const noexcept
    {
        return impl.ticking.of(&thisptr).value_or(false);
    }

    cs2::CPlantedC4& thisptr;
    const PlantedC4Impl& impl;
};

