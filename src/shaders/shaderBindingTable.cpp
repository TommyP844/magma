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
#include "shaderBindingTable.h"
#include "../objects/device.h"
#include "../objects/physicalDevice.h"
#include "../objects/deviceMemory.h"
#include "../objects/rayTracingPipeline.h"

namespace magma
{
#ifdef VK_NV_ray_tracing
ShaderBindingTable::ShaderBindingTable(std::shared_ptr<Device> device, const void *shaderGroupHandles, uint32_t groupCount,
    std::shared_ptr<Allocator> allocator /* nullptr */,
    const Initializer& optional /* default */,
    const Sharing& sharing /* default */):
    Buffer(device,
        device->getPhysicalDevice()->getRayTracingProperties().shaderGroupBaseAlignment * groupCount,
        0, // flags
        // Note that VK_BUFFER_USAGE_RAY_TRACING_BIT_NV = VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR in newer SDK revision
        VK_BUFFER_USAGE_RAY_TRACING_BIT_NV | VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        optional, sharing, std::move(allocator))
{
    uint8_t *shaderBindingData = (uint8_t *)getMemory()->map();
    if (shaderBindingData)
    {
        const VkPhysicalDeviceRayTracingPropertiesNV& rayTracingProperties = device->getPhysicalDevice()->getRayTracingProperties();
        const uint32_t handleSize = rayTracingProperties.shaderGroupHandleSize;
        const uint32_t baseAlignment = rayTracingProperties.shaderGroupBaseAlignment;
        for (uint32_t groupIndex = 0; groupIndex < groupCount; ++groupIndex)
        {
            memcpy(shaderBindingData, (const uint8_t *)shaderGroupHandles + groupIndex * handleSize, handleSize);
            shaderBindingData += baseAlignment;
        }
        getMemory()->unmap();
    }
}

ShaderBindingTable::ShaderBindingTable(std::shared_ptr<Device> device, const std::vector<uint8_t>& shaderGroupHandles, uint32_t groupCount,
    std::shared_ptr<Allocator> allocator /* nullptr */,
    const Initializer& optional /* default */,
    const Sharing& sharing /* default */):
    ShaderBindingTable(std::move(device), shaderGroupHandles.data(), groupCount,
        std::move(allocator), optional, sharing)
{}

ShaderBindingTable::ShaderBindingTable(std::shared_ptr<const RayTracingPipeline> pipeline,
    std::shared_ptr<Allocator> allocator /* nullptr */,
    const Initializer& optional /* default */,
    const Sharing& sharing /* default */):
    ShaderBindingTable(pipeline->getDevice(), pipeline->getShaderGroupHandles(), pipeline->getShaderGroupCount(),
        std::move(allocator), optional, sharing)
{}
#endif // VK_NV_ray_tracing
} // namespace magma
