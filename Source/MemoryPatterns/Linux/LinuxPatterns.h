#pragma once

#if defined(LINUX) || defined(__LINUX__) || defined(__linux__)
#include "ClientPatternsLinux.h"
#include "ConVarPatternsLinux.h"
#include "CvarPatternsLinux.h"
#include "EntityPatternsLinux.h"
#include "EntitySystemPatternsLinux.h"
#include "FileSystemPatternsLinux.h"
#include "GameRulesPatternsLinux.h"
#include "GameSceneNodePatternsLinux.h"
#include "MemAllocPatternsLinux.h"
#include "PanelPatternsLinux.h"
#include "PanelStylePatternsLinux.h"
#include "PanoramaImagePanelPatternsLinux.h"
#include "PanoramaLabelPatternsLinux.h"
#include "PanoramaUiEnginePatternsLinux.h"
#include "PanoramaUiPanelPatternsLinux.h"
#include "PlantedC4PatternsLinux.h"
#include "PlayerControllerPatternsLinux.h"
#include "PlayerPawnPatternsLinux.h"
#include "SdlPatternsLinux.h"
#include "SoundSystemPatternsLinux.h"
#include "TopLevelWindowPatternsLinux.h"
#include "WeaponServicesPatternsLinux.h"
#include "WeaponVDataPatternsLinux.h"
#elif defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
// Include Windows-specific headers here
#endif


#include "PlatformHeaders.h"
