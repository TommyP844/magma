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
#include "model/nondispatchable.h"

namespace magma
{
    /* A descriptor set layout object is defined by an array
       of zero or more descriptor bindings. Each individual
       descriptor binding is specified by a descriptor type,
       a count (array size) of the number of descriptors
       in the binding, a set of shader stages that can access
       the binding, and (if using immutable samplers) an array
       of sampler descriptors. */

    class DescriptorSetLayout : public NonDispatchable<VkDescriptorSetLayout>
    {
    public:
        explicit DescriptorSetLayout(std::shared_ptr<Device> device,
            const std::vector<VkDescriptorSetLayoutBinding>& bindings,
            std::shared_ptr<IAllocator> allocator = nullptr,
            VkDescriptorSetLayoutCreateFlags flags = 0,
            const StructureChain& extendedInfo = StructureChain());
        ~DescriptorSetLayout();
        const std::vector<VkDescriptorSetLayoutBinding>& getBindings() const noexcept { return bindings; }
        VkDescriptorSetLayoutCreateFlags getFlags() const noexcept { return flags; }
        hash_t getHash() const noexcept { return hash; }

    private:
        const std::vector<VkDescriptorSetLayoutBinding> bindings;
        const VkDescriptorSetLayoutCreateFlags flags;
        hash_t hash;
    };
} // namespace magma
