/*
Magma - abstraction layer to facilitate usage of Khronos Vulkan API.
Copyright (C) 2018-2020 Victor Coda.

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
#include "pch.h"
#pragma hdrstop
#include "descriptorSetReflection.h"
#include "descriptorSetBinding.h"
#include "shaderReflectionFactory.h"
#include "../objects/descriptorPool.h"
#include "../objects/descriptorSetLayout.h"
#include "../shaders/shaderReflection.h"
#include "../helpers/spirvReflectionTypeCast.h"
#include "../helpers/stringize.h"
#include "../exceptions/errorResult.h"

namespace magma
{
namespace reflection
{
std::shared_ptr<magma::DescriptorSetLayout> DescriptorSetLayout::createLayout(std::shared_ptr<magma::Device> device, uint32_t stageFlags,
    std::shared_ptr<IAllocator> allocator /* nullptr */)
{
    std::vector<VkDescriptorSetLayoutBinding> bindings;
    for (auto binding : getBindings())
    {
        binding->stageFlags = stageFlags; 
        bindings.push_back(*binding);
    }
    layout = std::make_shared<magma::DescriptorSetLayout>(
        std::move(device), bindings, std::move(allocator), 0);
    return layout;
}

DescriptorSet::DescriptorSet(std::shared_ptr<magma::DescriptorPool> pool, DescriptorSetLayout& setLayout, uint32_t setIndex, uint32_t stageFlags,
    std::shared_ptr<IAllocator> allocator /* nullptr */,
    std::shared_ptr<IShaderReflectionFactory> shaderReflectionFactory /* nullptr */,
    const std::string& shaderFileName /* default */):
    NonDispatchable(VK_OBJECT_TYPE_DESCRIPTOR_SET, pool->getDevice(), allocator),
    pool(std::move(pool)),
    layout(setLayout.createLayout(this->pool->getDevice(), stageFlags, std::move(allocator))),
    setIndex(setIndex),
    bindings(setLayout.getBindings())
{
    if (shaderReflectionFactory && !shaderFileName.empty())
        validateReflection(shaderReflectionFactory->getReflection(shaderFileName));
    const VkDescriptorSetLayout dereferencedSetLayouts[1] = {*setLayout.getLayout()};
    VkDescriptorSetAllocateInfo allocInfo;
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.pNext = nullptr;
    allocInfo.descriptorPool = *this->pool;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = dereferencedSetLayouts;
    const VkResult result = vkAllocateDescriptorSets(MAGMA_HANDLE(device), &allocInfo, &handle);
    MAGMA_THROW_FAILURE(result, "failed to allocate descriptor set");
    for (auto binding : this->bindings)
        binding->descriptorWrite.dstSet = handle; // Assign handle to write descriptor
}

DescriptorSet::~DescriptorSet()
{
    vkFreeDescriptorSets(MAGMA_HANDLE(device), *pool, 1, &handle);
}

bool DescriptorSet::dirty() const noexcept
{
    for (auto binding : bindings)
    {
        if (binding->dirty())
            return true;
    }
    return false;
}

void DescriptorSet::update()
{
    std::vector<VkWriteDescriptorSet> descriptorWrites;
    descriptorWrites.reserve(bindings.size());
    for (auto binding : bindings)
    {
        if (binding->dirty())
        {
            descriptorWrites.push_back(binding->getDescriptorWrite());
            binding->updated = false;
        }
    }
    device->updateDescriptorSets(descriptorWrites);
}

void DescriptorSet::validateReflection(std::shared_ptr<const ShaderReflection> shaderReflection) const
{
    std::vector<const SpvReflectDescriptorSet *> descriptorSets = shaderReflection->enumerateDescriptorSets();
    if (setIndex >= descriptorSets.size())
        MAGMA_THROW("set index exceeds number of reflected descriptor sets");
    const SpvReflectDescriptorSet *descriptorSet = descriptorSets[setIndex];
    for (const auto definedBinding : bindings)
    {
        const SpvReflectDescriptorBinding *reflectedBinding = nullptr;
        for (uint32_t i = 0; i < descriptorSet->binding_count; ++i)
        {
            if (definedBinding->binding == descriptorSet->bindings[i]->binding)
            {
                reflectedBinding = descriptorSet->bindings[i];
                break;
            }
        }
        if (!reflectedBinding)
        {
            std::ostringstream oss;
            oss << "binding #" << definedBinding->binding << " not found in the reflection";
            MAGMA_THROW(oss.str());
        }
        const VkDescriptorType reflectedDescriptorType = helpers::castToDescriptorType(reflectedBinding->descriptor_type);
        if (definedBinding->descriptorType != reflectedDescriptorType)
        {
            std::ostringstream oss;
            oss << "descriptor type mismatch:" << std::endl
                << "binding #" << definedBinding->binding << std::endl
                << "expected: " << helpers::stringize(reflectedDescriptorType) << std::endl
                << "defined: " << helpers::stringize(definedBinding->descriptorType);
            MAGMA_THROW(oss.str());
        }
    }
}
} // namespace reflection
} // namespace magma
