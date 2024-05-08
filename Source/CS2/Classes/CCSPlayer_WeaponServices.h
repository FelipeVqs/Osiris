#ifndef CS2_CCS_PLAYER_WEAPON_SERVICES_H
#define CS2_CCS_PLAYER_WEAPON_SERVICES_H

#include <EntitySystem/IEntityHandle.h> // use the interface instead of the concrete implementation

namespace cs2
{

struct CCSPlayerWeaponServices {
    using ActiveWeaponHandle = const IEntityHandle<class CWeaponEntity>;

    ActiveWeaponHandle m_activeWeapon;
};

} // namespace cs2

#endif // CS2_CCS_PLAYER_WEAPON_SERVICES_H
