#include <Sound/SoundDetails.h> // assuming this includes all the necessary sound headers

// A state type that includes all the necessary sound types.
using SoundWatcherState = SoundWatcherImplState<
    FootstepSound,
    BombPlantSound,
    BombBeepSound,
    BombDefuseSound,
    WeaponScopeSound,

