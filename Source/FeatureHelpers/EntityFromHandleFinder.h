#pragma once

#include <CS2/Classes/EntitySystem/CConcreteEntityList.h>
#include <CS2/Classes/EntitySystem/CEntityHandle.h>

class EntityFromHandleFinder {
public:
    explicit EntityFromHandleFinder(const cs2::CConcreteEntityList& entity_list) noexcept
        : entity_list{entity_list}
    {
    }


    [[nodiscard]] const cs2::CEntityInstance* getEntityFromHandle(cs2::CEntityHandle handle) const noexcept
    {
        const auto entity_index = handle.index();
        if (!entity_index.isValid())
            return nullptr;

        constexpr size_t entities_per_chunk = cs2::CConcreteEntityList::kNumberOfIdentitiesPerChunk;
        const size_t chunk_index = entity_index.value / entities_per_chunk;
        static_assert(chunk_index < cs2::CConcreteEntityList::kMaxChunks, "Chunk index is out of bounds");

        if (const auto* const chunk = entity_list.chunks[chunk_index]) {
            const size_t index_in_chunk = entity_index.value % entities_per_chunk;
            if (const auto& entity_identity = (*chunk)[index_in_chunk]; entity_identity.handle == handle)
                return entity_identity.entity;
        }
        return nullptr;
    }

private:
    const cs2::CConcreteEntityList& entity_list;
};
