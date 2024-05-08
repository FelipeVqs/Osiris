#pragma once

#include <cassert>
#include <cs2/Classes/Panorama.h>
#include <GameClasses/PanoramaUiEngine.h>
#include <GameClasses/PanoramaUiPanel.h>

struct PanoramaPanelPointer {
    explicit PanoramaPanelPointer(cs2::CUIPanel* panel, bool success = true) noexcept
        : handle{ success ? PanoramaUiEngine::getPanelHandle(panel) : cs2::PanelHandle() }
    {
        assert(!panel || handle.isValid());
    }

    explicit PanoramaPanelPointer(PanoramaUiPanel panel) noexcept
        : PanoramaPanelPointer{ static_cast<cs2::CUIPanel*>(panel) }
    {
    }

    PanoramaPanelPointer(const PanoramaPanelPointer& other) noexcept
        : handle{ other.handle }
    {
    }

    PanoramaPanelPointer& operator=(const PanoramaPanelPointer& other) noexcept
    {
        handle = other.handle;
        return *this;
    }

    PanoramaPanelPointer(PanoramaPanelPointer&& other) noexcept
        : handle{ std::move(other.handle) }
    {
    }

    PanoramaPanelPointer& operator=(PanoramaPanelPointer&& other) noexcept
    {
        handle = std::move(other.handle);
        return *this;
    }

    ~PanoramaPanelPointer() noexcept
    {
    }

    void swap(PanoramaPanelPointer& other) noexcept
    {
        handle.swap(other.handle);
    }

    [[nodiscard]] cs2::PanelHandle getHandle() const noexcept
    {
        return handle;
    }

    [[nodiscard]] PanoramaUiPanel get() const noexcept
    {
        return PanoramaUiPanel{ PanoramaUiEngine::getPanelPointer(handle) };
    }

    [[nodiscard]] explicit operator bool() const noexcept
    {
        return handle.isValid();
    }

    friend bool operator==(const PanoramaPanelPointer& lhs, const PanoramaPanelPointer& rhs) noexcept
    {
        return lhs.handle == rhs.handle;
    }

    friend bool operator!=(const PanoramaPanelPointer& lhs, const PanoramaPanelPointer& rhs) noexcept
    {
        return lhs.handle != rhs.handle;
    }

    void reset() noexcept
    {
        handle = cs2::PanelHandle();
    }

private:
    cs2::PanelHandle handle;
};
