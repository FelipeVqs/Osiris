#pragma once

#include <MemoryPatterns/PanelStylePatterns.h>

namespace {

struct PanelStyleImpl {
    explicit PanelStyleImpl(const PanelStylePatterns& panelStylePatterns) noexcept
        : setProperty{panelStylePatterns.setProperty()}
    {
    }

    const cs2::CPanelStyle::SetProperty* setProperty;
};

const PanelStyleImpl& instance() noexcept {
    static PanelStyleImpl instance{PanelStylePatterns::getDefaults()};
    return instance;
}

} // namespace
