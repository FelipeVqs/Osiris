#pragma once

#include <GameClasses/PanoramaUiEngine.h>
#include <Helpers/PanoramaPanelPointer.h>
#include <memory>

struct BombTimerState {
    /// Whether the bomb timer is enabled or not.
    bool enabled{false};

    /// The score, time, and bomb panel.
    PanoramaPanelPointer scoreAndTimeAndBombPanel;

    /// The bomb status panel.
    PanoramaPanelPointer bombStatusPanel;

    /// The invisible panel used for hiding the bomb timer.
    std::unique_ptr<PanoramaPanelPointer> invisiblePanel;

    /// The container panel for the bomb timer.
    std::unique_ptr<PanoramaPanelPointer> bombTimerContainerPanel;

    /// The icon panel for the bomb site.
    std::unique_ptr<PanoramaPanelPointer> bombSiteIconPanel;

    /// The panel for the bomb timer.
    std::unique_ptr<PanoramaPanelPointer> bombTimerPanel;

    ~BombTimerState() noexcept {
        restoreBombStatusPanel();
        deletePanoramaPanel(invisiblePanel->getHandle());
        deletePanoramaPanel(bombTimerPanel->getHandle());
        deletePanoramaPanel(bombTimerContainerPanel->getHandle());
    }

    void restoreBombStatusPanel() const noexcept {
        if (const auto bombStatus = bombStatusPanel.get()) {
            if (const auto scoreAndTimeAndBomb = scoreAndTimeAndBombPanel.get()) {
                bombStatus->setParent(scoreAndTimeAndBomb);
            }
        }
    }

    /// Helper function to delete a panel using the PanoramaUiEngine.
    static void deletePanoramaPanel(const PanoramaPanelHandle& handle) noexcept {
        if (handle.isValid()) {
            PanoramaUiEngine::onDeletePanel(handle);
        }
    }
};
