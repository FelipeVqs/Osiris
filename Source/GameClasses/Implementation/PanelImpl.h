#pragma once

#include <MemoryPatterns/PanelPatterns.h>
#include <cs2/CPanel2D.h>

class PanelImpl {
public:
    static PanelImpl& instance() noexcept {
        static PanelImpl instance{PanelPatterns::instance().create()};
        return instance;
    }

private:
    explicit PanelImpl(cs2::CPanel2D::Create* create) noexcept
        : create{create} {}

    cs2::CPanel2D::Create* create;
};
