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
#include "baseUniformBuffer.h"
#include "../helpers/uniformArray.h"
#include "../exceptions/exception.h"

namespace magma
{
    /* An array of uniform values that are used in various
       shader stages. It is host visible so can be mapped
       by user to write uniform values. */

    template<class Type>
    class UniformBuffer : public BaseUniformBuffer
    {
    public:
        typedef Type UniformType;
        explicit UniformBuffer(std::shared_ptr<Device> device,
            bool stagedPool = false,
            bool mappedPersistently = false,
            uint32_t arraySize = 1,
            std::shared_ptr<Allocator> allocator = nullptr,
            const Initializer& optional = Initializer(),
            const Sharing& sharing = Sharing()):
            BaseUniformBuffer(std::move(device),
                sizeof(Type), arraySize,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, // Make it compatible with vkCmdUpdateBuffer
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT |
                    (stagedPool ? VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT : 0),
                optional, sharing, std::move(allocator),
                mappedPersistently)
        {
            static_assert(std::alignment_of<Type>() == 16, "uniform type should have 16-byte alignment");
        }

        VkDeviceSize getAlignment() const noexcept override { return std::alignment_of<Type>(); }
        bool dynamic() const noexcept override { return false; }

        helpers::UniformArray<Type> mapToArray(uint32_t firstIndex = 0,
            uint32_t arraySize = std::numeric_limits<uint32_t>::max())
        {
            void *data = mapRange(firstIndex, arraySize);
            if (!data)
                MAGMA_ERROR("failed to map range of uniform buffer");
            return helpers::UniformArray<Type>(data, arraySize);
        }
    };

    /* Host visible but non-coherent uniform buffer.
       Requires to flush mapped memory range after data upload.
       Mapping and unmapping uniform buffer have a CPU cost.
       Therefore, if updated frequently, user may define it
       as persistenly mapped. */

    template<class Type>
    class NonCoherentUniformBuffer : public BaseUniformBuffer
    {
    public:
        typedef Type UniformType;
        explicit NonCoherentUniformBuffer(std::shared_ptr<Device> device,
            bool mappedPersistently,
            std::shared_ptr<Allocator> allocator = nullptr,
            uint32_t arraySize = 1,
            const Initializer& optional = Initializer(),
            const Sharing& sharing = Sharing()):
            BaseUniformBuffer(std::move(device),
                sizeof(Type), arraySize,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                optional, sharing, std::move(allocator),
                false)
        {
            static_assert(std::alignment_of<Type>() == 16, "non-coherent uniform type should have 16-byte alignment");
        }

        VkDeviceSize getAlignment() const noexcept override { return std::alignment_of<Type>(); }
        bool dynamic() const noexcept override { return false; }

        helpers::UniformArray<Type> mapToArray(uint32_t firstIndex = 0,
            uint32_t arraySize = std::numeric_limits<uint32_t>::max())
        {
            void *data = mapRange(firstIndex, arraySize);
            if (!data)
                MAGMA_ERROR("failed to map range of non-coherent uniform buffer");
            return helpers::UniformArray<Type>(data, arraySize);
        }

        bool flushMappedRange(const helpers::UniformArray<Type>& array) noexcept
        {
            if (!memory->mapped())
                return false;
            VkDeviceSize offset = array.getFirstIndex() * getAlignment();
            const VkDeviceSize nonCoherentAtomSize = getNonCoherentAtomSize();
            if (offset % nonCoherentAtomSize)
                offset = offset / nonCoherentAtomSize * nonCoherentAtomSize;
            VkDeviceSize size = array.getUpdatedRange() * getAlignment();
            const VkDeviceSize minFlushSize = std::min(memory->getSize(), nonCoherentAtomSize);
            size = std::max(size, minFlushSize);
            return memory->flushMappedRange(offset + getMapOffset(), size);
        }
    };

    template<class Type> using UniformBufferPtr = std::shared_ptr<UniformBuffer<Type>>;
    template<class Type> using NonCoherentUniformBufferPtr = std::shared_ptr<NonCoherentUniformBuffer<Type>>;
} // namespace magma
