#ifndef CENTITYIDENTITY_H
#define CENTITYIDENTITY_H

#include <Utils/Pad.h>
#include "CEntityHandle.h"

namespace cs2
{

struct CEntityInstance;

struct CEntityIdentity {
    CEntityInstance* entity{nullptr};
    PAD(8);
    CEntityHandle handle;
    PAD(100);

    CEntityIdentity() : entity(nullptr) {}

    ~CEntityIdentity() {}

    CEntityHandle getHandle() const {
        return handle;
    }
};

static_assert(sizeof(CEntityIdentity) == 120);

} // namespace cs2

#endif // CENTITYIDENTITY_H
