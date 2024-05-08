#pragma once

#include <memory> // for std::unique_ptr
#include <string> // for std::string

// Includes for GameClassImplementations
#include "ConVarImpl.h"
#include "CvarImpl.h"
#include "EntityImpl.h"
#include "EntitySystemImpl.h"
#include "GameRulesImpl.h"
#include "GameSceneNodeImpl.h"
#include "MemAllocImpl.h"
#include "PlayerControllerImpl.h"
#include "PlayerPawnImpl.h"
#include "WeaponServicesImpl.h"
#include "WeaponVDataImpl.h"

// Includes for PatternFinders
#include "Pattern/VmtFinder.h"
#include "Patterns/ConVarPatterns.h"
#include "Patterns/CvarPatterns.h"
#include "Patterns/EntityPatterns.h"
#include "Patterns/EntitySystemPatterns.h"
#include "Patterns/FileSystemPatterns.h"
#include "Patterns/GameRulesPatterns.h"
#include "Patterns/GameSceneNodePatterns.h"
#include "Patterns/MemAllocPatterns.h"
#include "Patterns/PanelPatterns.h"
#include "Patterns/PanelStylePatterns.h"
#include "Patterns/PanoramaImagePanelPatterns.h"
#include "Patterns/PanoramaLabelPatterns.h"
#include "Patterns/PanoramaUiEnginePatterns.h"
#include "Patterns/PanoramaUiPanelPatterns.h"
#include "Patterns/PlantedC4Patterns.h"
#include "Patterns/PlayerControllerPatterns.h"
#include "Patterns/PlayerPawnPatterns.h"
#include "Patterns/TopLevelWindowPatterns.h"
#include "Patterns/WeaponServicesPatterns.h"
#include "Patterns/WeaponVDataPatterns.h"

// Includes for Tier0
#include "Tier0/tier0.h"

// Includes for Panorama
#include "panorama_ui/panorama_ui.h"

// Includes for FileSystem
#include "filesystem_stdio.h"

struct GameClassImplementations {
    GameClassImplementations(const PatternFinder<PatternNotFoundLogger>& clientPatternFinder,
                             const PatternFinder<PatternNotFoundLogger>& panoramaPatternFinder,
                             const PatternFinder<PatternNotFoundLogger>& tier0PatternFinder,
                             const FileSystemPatterns& fileSystemPatterns,
                             Tier0Dll tier0Dll) noexcept
        : conVar(tier0PatternFinder)
        , cvar(clientPatternFinder, tier0PatternFinder)
        , entity(clientPatternFinder)
        , entitySystem(clientPatternFinder)
        , fileNameSymbolTable(std::move(tier0Dll))
        , fileSystem(fileSystemPatterns)
        , gameRules(clientPatternFinder)
        , gameSceneNode(clientPatternFinder)
        , memAlloc(std::move(tier0Dll), clientPatternFinder)
        , panel(clientPatternFinder)
        , panelStyle(panoramaPatternFinder)
        , imagePanel(clientPatternFinder)
        , panoramaLabel(clientPatternFinder)
        , uiEngine(clientPatternFinder, panoramaPatternFinder)
        , panoramaUiPanelOffsets(clientPatternFinder, panoramaPatternFinder)
        , plantedC4(clientPatternFinder)
        , playerController(clientPatternFinder)
        , playerPawn(clientPatternFinder)
        , topLevelWindow(panoramaPatternFinder)
        , weaponServices(clientPatternFinder)
        , weaponVData(clientPatternFinder)
    {
    }

    ConVarImpl conVar;
    CvarImpl cvar;
    EntityImpl entity;
    EntitySystemImpl entitySystem;
    FileNameSymbolTableImpl fileNameSymbolTable;
    FileSystemImpl fileSystem;
    GameRulesImpl gameRules;
    GameSceneNodeImpl gameSceneNode;
    MemAllocImpl memAlloc;
    PanelImpl panel;
    PanelStyleImpl panelStyle;
    PanoramaImagePanelImpl imagePanel;
    PanoramaLabelImpl panoramaLabel;
    PanoramaUiEngineImpl uiEngine;
    PanoramaUiPanelImpl panoramaUiPanelOffsets;
    PlantedC4Impl plantedC4;
    PlayerControllerImpl playerController;
    PlayerPawnImpl playerPawn;
    TopLevelWindowImpl topLevelWindow;
    WeaponServicesImpl weaponServices;
    WeaponVDataImpl weaponVData;
};
