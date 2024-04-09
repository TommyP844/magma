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
#include "pch.h"
#pragma hdrstop
#include "vertexInputState.h"
#include "../misc/format.h"

namespace magma
{
VertexInputState::VertexInputState(const VertexInputBinding& binding,
    const std::initializer_list<VertexInputAttribute>& attributes) noexcept:
    VkPipelineVertexInputStateCreateInfo{
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        nullptr, // pNext
        0, // flags
        1, // vertexBindingDescriptionCount
        core::copyArray<VkVertexInputBindingDescription>(&binding, 1), // pVertexBindingDescriptions
        MAGMA_COUNT(attributes), // vertexAttributeDescriptionCount
        core::copyInitializerList<VkVertexInputAttributeDescription>(attributes) // pVertexAttributeDescriptions
    }
{
#ifdef VK_EXT_vertex_attribute_divisor
    vertexInputDivisorInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT;
    vertexInputDivisorInfo.pNext = nullptr;
    vertexInputDivisorInfo.vertexBindingDivisorCount = 0;
    vertexInputDivisorInfo.pVertexBindingDivisors = nullptr;
#endif // VK_EXT_vertex_attribute_divisor
}

VertexInputState::VertexInputState(const std::initializer_list<VertexInputBinding>& bindings,
    const std::initializer_list<VertexInputAttribute>& attributes) noexcept:
    VkPipelineVertexInputStateCreateInfo{
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        nullptr, // pNext
        0, // flags
        MAGMA_COUNT(bindings), // vertexBindingDescriptionCount
        core::copyInitializerList<VkVertexInputBindingDescription>(bindings), // pVertexBindingDescriptions
        MAGMA_COUNT(attributes), // vertexAttributeDescriptionCount
        core::copyInitializerList<VkVertexInputAttributeDescription>(attributes) // pVertexAttributeDescriptions
    }
{
#ifdef VK_EXT_vertex_attribute_divisor
    vertexInputDivisorInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT;
    vertexInputDivisorInfo.pNext = nullptr;
    vertexInputDivisorInfo.vertexBindingDivisorCount = 0;
    vertexInputDivisorInfo.pVertexBindingDivisors = nullptr;
#endif // VK_EXT_vertex_attribute_divisor
}

#ifdef VK_EXT_vertex_attribute_divisor
VertexInputState::VertexInputState(const VertexInputBindingDivisor& binding,
    const std::initializer_list<VertexInputAttribute>& attributes) noexcept:
    VkPipelineVertexInputStateCreateInfo{
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        &vertexInputDivisorInfo, // pNext
        0, // flags
        1, // vertexBindingDescriptionCount
        core::copyArray<VkVertexInputBindingDescription>(&binding, 1), // pVertexBindingDescriptions
        MAGMA_COUNT(attributes), // vertexAttributeDescriptionCount
        core::copyInitializerList<VkVertexInputAttributeDescription>(attributes) // pVertexAttributeDescriptions
    }
{
    vertexInputDivisorInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT;
    vertexInputDivisorInfo.pNext = nullptr;
    vertexInputDivisorInfo.vertexBindingDivisorCount = 1;
    VkVertexInputBindingDivisorDescriptionEXT *vertexBindingDivisor = MAGMA_NEW VkVertexInputBindingDivisorDescriptionEXT[1];
    if (vertexBindingDivisor)
    {
        vertexBindingDivisor->binding = binding.binding;
        vertexBindingDivisor->divisor = binding.divisor;
    }
    vertexInputDivisorInfo.pVertexBindingDivisors = vertexBindingDivisor;
}

VertexInputState::VertexInputState(const std::initializer_list<VertexInputBindingDivisor>& bindings,
    const std::initializer_list<VertexInputAttribute>& attributes) noexcept
{
    sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    pNext = &vertexInputDivisorInfo;
    flags = 0;
    vertexBindingDescriptionCount = 0;
    VkVertexInputBindingDescription *vertexBindingDescriptions = MAGMA_NEW VkVertexInputBindingDescription[bindings.size()];
    if (vertexBindingDescriptions)
    {
        for (auto const& binding: bindings)
        {
            vertexBindingDescriptions[vertexBindingDescriptionCount].binding = binding.binding;
            vertexBindingDescriptions[vertexBindingDescriptionCount].stride = binding.stride;
            vertexBindingDescriptions[vertexBindingDescriptionCount++].inputRate = binding.inputRate;
        }
    }
    pVertexBindingDescriptions = vertexBindingDescriptions;
    vertexAttributeDescriptionCount = MAGMA_COUNT(attributes);
    pVertexAttributeDescriptions = core::copyInitializerList<VkVertexInputAttributeDescription>(attributes);
    vertexInputDivisorInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT;
    vertexInputDivisorInfo.pNext = nullptr;
    vertexInputDivisorInfo.vertexBindingDivisorCount = 0;
    VkVertexInputBindingDivisorDescriptionEXT *vertexBindingDivisors = MAGMA_NEW VkVertexInputBindingDivisorDescriptionEXT[vertexBindingDescriptionCount];
    if (vertexBindingDivisors)
    {
        for (auto const& binding: bindings)
        {
            vertexBindingDivisors[vertexInputDivisorInfo.vertexBindingDivisorCount].binding = binding.binding;
            vertexBindingDivisors[vertexInputDivisorInfo.vertexBindingDivisorCount++].divisor = binding.divisor;
        }
    }
    vertexInputDivisorInfo.pVertexBindingDivisors = vertexBindingDivisors;
}
#endif // VK_EXT_vertex_attribute_divisor

VertexInputState::VertexInputState(const VertexInputState& other) noexcept
{
    sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    pNext = nullptr;
    flags = other.flags;
    vertexBindingDescriptionCount = other.vertexBindingDescriptionCount;
    pVertexBindingDescriptions = core::copyArray(other.pVertexBindingDescriptions, vertexBindingDescriptionCount);
    vertexAttributeDescriptionCount = other.vertexAttributeDescriptionCount;
    pVertexAttributeDescriptions = core::copyArray(other.pVertexAttributeDescriptions, vertexAttributeDescriptionCount);
#ifdef VK_EXT_vertex_attribute_divisor
    if (other.pNext)
        pNext = &vertexInputDivisorInfo;
    vertexInputDivisorInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT;
    vertexInputDivisorInfo.pNext = nullptr;
    vertexInputDivisorInfo.vertexBindingDivisorCount = other.vertexInputDivisorInfo.vertexBindingDivisorCount;
    if (vertexInputDivisorInfo.vertexBindingDivisorCount)
        vertexInputDivisorInfo.pVertexBindingDivisors = core::copyArray(other.vertexInputDivisorInfo.pVertexBindingDivisors, other.vertexInputDivisorInfo.vertexBindingDivisorCount);
    else
        vertexInputDivisorInfo.pVertexBindingDivisors = nullptr;
#endif // VK_EXT_vertex_attribute_divisor
}

VertexInputState& VertexInputState::operator=(const VertexInputState& other) noexcept
{
    if (this != &other)
    {
        flags = other.flags;
        vertexBindingDescriptionCount = other.vertexBindingDescriptionCount;
        delete[] pVertexBindingDescriptions;
        pVertexBindingDescriptions = core::copyArray(other.pVertexBindingDescriptions, vertexBindingDescriptionCount);
        vertexAttributeDescriptionCount = other.vertexAttributeDescriptionCount;
        delete[] pVertexAttributeDescriptions;
        pVertexAttributeDescriptions = core::copyArray(other.pVertexAttributeDescriptions, vertexAttributeDescriptionCount);
#ifdef VK_EXT_vertex_attribute_divisor
        if (other.pNext)
            pNext = &vertexInputDivisorInfo;
        vertexInputDivisorInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT;
        vertexInputDivisorInfo.pNext = nullptr;
        vertexInputDivisorInfo.vertexBindingDivisorCount = other.vertexInputDivisorInfo.vertexBindingDivisorCount;
        delete[] vertexInputDivisorInfo.pVertexBindingDivisors;
        if (vertexInputDivisorInfo.vertexBindingDivisorCount)
            vertexInputDivisorInfo.pVertexBindingDivisors = core::copyArray(other.vertexInputDivisorInfo.pVertexBindingDivisors, other.vertexInputDivisorInfo.vertexBindingDivisorCount);
        else
            vertexInputDivisorInfo.pVertexBindingDivisors = nullptr;
#endif // VK_EXT_vertex_attribute_divisor
    }
    return *this;
}

VertexInputState::~VertexInputState()
{
    delete[] pVertexBindingDescriptions;
    delete[] pVertexAttributeDescriptions;
#ifdef VK_EXT_vertex_attribute_divisor
    delete[] vertexInputDivisorInfo.pVertexBindingDivisors;
#endif
}

uint32_t VertexInputState::stride(uint32_t binding) const noexcept
{
    std::size_t stride = 0;
    for (uint32_t i = 0; i < vertexAttributeDescriptionCount; ++i)
    {
        auto const& vertexAttibDescription = pVertexAttributeDescriptions[i];
        if (vertexAttibDescription.binding == binding)
        {   // TODO: alignment?
            const std::size_t vertexAttribSize = Format(vertexAttibDescription.format).size();
            stride += vertexAttribSize;
        }
    }
    return static_cast<uint32_t>(stride);
}

hash_t VertexInputState::hash() const noexcept
{
    hash_t hash = core::hashArgs(
        sType,
        flags,
        vertexBindingDescriptionCount,
        vertexAttributeDescriptionCount);
    for (uint32_t i = 0; i < vertexBindingDescriptionCount; ++i)
    {
        auto const& vertexBindingDescription = pVertexBindingDescriptions[i];
        hash = core::hashCombine(hash, core::hashArgs(
            vertexBindingDescription.binding,
            vertexBindingDescription.stride,
            vertexBindingDescription.inputRate));
    }
    for (uint32_t i = 0; i < vertexAttributeDescriptionCount; ++i)
    {
        auto const& vertexAttribDescription = pVertexAttributeDescriptions[i];
        hash = core::hashCombine(hash, core::hashArgs(
            vertexAttribDescription.location,
            vertexAttribDescription.binding,
            vertexAttribDescription.format,
            vertexAttribDescription.offset));
    }
#ifdef VK_EXT_vertex_attribute_divisor
    hash = core::hashCombine(hash, core::hashArgs(
        vertexInputDivisorInfo.sType,
        vertexInputDivisorInfo.vertexBindingDivisorCount));
    for (uint32_t i = 0; i < vertexInputDivisorInfo.vertexBindingDivisorCount; ++i)
    {
        auto const& vertexBindingDivisor = vertexInputDivisorInfo.pVertexBindingDivisors[i];
        hash = core::hashCombine(hash, core::hashArgs(
            vertexBindingDivisor.binding,
            vertexBindingDivisor.divisor));
    }
#endif // VK_EXT_vertex_attribute_divisor
    return hash;
}

bool VertexInputState::operator==(const VertexInputState& other) const noexcept
{
   return (flags == other.flags) &&
        (vertexBindingDescriptionCount == other.vertexBindingDescriptionCount) &&
        (vertexAttributeDescriptionCount == other.vertexAttributeDescriptionCount) &&
        core::compareArrays(pVertexBindingDescriptions, other.pVertexBindingDescriptions, vertexBindingDescriptionCount) &&
        core::compareArrays(pVertexAttributeDescriptions, other.pVertexAttributeDescriptions, vertexAttributeDescriptionCount) &&
    #ifdef VK_EXT_vertex_attribute_divisor
        (vertexInputDivisorInfo.vertexBindingDivisorCount == other.vertexInputDivisorInfo.vertexBindingDivisorCount) &&
        core::compareArrays(vertexInputDivisorInfo.pVertexBindingDivisors, other.vertexInputDivisorInfo.pVertexBindingDivisors, vertexInputDivisorInfo.vertexBindingDivisorCount);
    #else
        true;
    #endif
}
} // namespace magma
