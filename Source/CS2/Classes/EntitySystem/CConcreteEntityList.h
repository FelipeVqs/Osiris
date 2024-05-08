#pragma once

#include <array>
#include "CEntityIdentity.h"
#include "CEntityIndex.h"

namespace cs2
{

struct CConcreteEntityList {
    static constexpr std::size_t kNumberOfChunks = 64;
    static constexpr std::size_t kNumberOfIdentitiesPerChunk = 512;

    using EntityChunk = CEntityIdentity[kNumberOfIdentitiesPerChunk];
    using ChunkArray = std::array<EntityChunk, kNumberOfChunks>;

    CConcreteEntityList() : chunks_() { }

    std::size_t size() const {
        std::size_t size = 0;
        for (const auto& chunk : chunks_) {
            size += chunk.size();
        }
        return size;
    }

    EntityChunk& getChunk(std::size_t index) {
        return chunks_[index];
    }

    ChunkArray chunks_;
};

}
