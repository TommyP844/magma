/*
Magma - Abstraction layer over Khronos Vulkan API.
Copyright (C) 2018-2023 Victor Coda.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once
#include "object.h"
#include "ideviceMemory.h"
#include "resourcePool.h"

namespace magma
{
    /* Non-dispatchable handle types are a 64-bit integer type
       whose meaning is implementation-dependent, and may encode
       object information directly in the handle rather than acting
       as a reference to an underlying object. */

    template<class Type>
    class NonDispatchable : public TObject<Type>,
        /* private */ DeviceResourcePool
    {
        static_assert(
        #if (VK_USE_64_BIT_PTR_DEFINES==1)
            sizeof(Type) == sizeof(intptr_t),
        #else
            sizeof(Type) == sizeof(uint64_t),
        #endif
            "invalid size of non-dispatchable handle type");

    public:
        bool nonDispatchable() const noexcept override { return true; }
        uint64_t getHandle() const noexcept override
        {
        #ifdef MAGMA_X64
            // VK_EXT_debug_utils/VK_EXT_debug_marker requires uint64_t type
            return reinterpret_cast<uint64_t>(TObject<Type>::handle);
        #else
            return TObject<Type>::handle;
        #endif // MAGMA_X64
        }

    protected:
        explicit NonDispatchable(VkObjectType objectType,
            std::shared_ptr<IAllocator> hostAllocator) noexcept:
            TObject<Type>(objectType, std::move(hostAllocator)) {}

        explicit NonDispatchable(VkObjectType objectType,
            std::shared_ptr<Device> device,
            std::shared_ptr<IAllocator> hostAllocator) noexcept:
            TObject<Type>(objectType, std::move(device), std::move(hostAllocator))
        {
        #ifdef MAGMA_X64
            std::shared_ptr<ResourcePool> pool = DeviceResourcePool::getPool(this->device);
            if (pool) // Put resource in pool
                pool->getPool<NonDispatchable<Type>>().insert(this);
        #endif // MAGMA_X64
        }

        ~NonDispatchable()
        {
        #ifdef MAGMA_X64
            std::shared_ptr<ResourcePool> pool = DeviceResourcePool::getPool(this->device);
            if (pool) // Remove resource from pool
                pool->getPool<NonDispatchable<Type>>().erase(this);
        #endif // MAGMA_X64
        }
    };
} // namespace magma
