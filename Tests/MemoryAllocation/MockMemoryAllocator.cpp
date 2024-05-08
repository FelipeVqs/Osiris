#ifndef MOCKMEMORYALLOCATOR_H
#define MOCKMEMORYALLOCATOR_H

#include "MemoryAllocation/MemoryAllocatorBase.h"

namespace Testing {

class MockMemoryAllocator {
public:
    using MockType = MemoryAllocatorBase;

    static std::shared_ptr<MockType> create();

private:
    class MockTypeImpl;
    std::shared_ptr<MockTypeImpl> mock;
};

}  // namespace Testing

#endif  // MOCKMEMORYALLOCATOR_H


#include "MockMemoryAllocator.h"

namespace Testing {

class MockMemoryAllocator::MockTypeImpl : public MockType {
public:
    std::byte* allocate(std::size_t size) noexcept override {
        // Implementation for mock allocate
    }

    void deallocate(std::byte* memory, std::size_t size) noexcept override {
        // Implementation for mock deallocate
    }
};

std::shared_ptr<MockMemoryAllocator::MockType> MockMemoryAllocator::create() {
    if (const auto existingMock = mockMemoryAllocator.lock())
        return existingMock;

    auto mock = std::make_shared<MockTypeImpl>();
    mockMemoryAllocator = mock;
    return mock;
}

}  // namespace Testing


#ifndef MEMORYALLOCATORBASE_H
#define MEMORYALLOCATORBASE_H

#include <cstddef>

namespace Testing {

class MemoryAllocatorBase {
public:
    virtual std::byte* allocate(std::size_t size) noexcept = 0;
    virtual void deallocate(std::byte* memory, std::size_t size) noexcept = 0;
};

}  // namespace Testing

#endif  // MEMORYALLOCATORBASE_H
