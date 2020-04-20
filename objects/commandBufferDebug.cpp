/*
Magma - abstraction layer to facilitate usage of Khronos Vulkan API.
Copyright (C) 2018-2019 Victor Coda.

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
#include "commandBuffer.h"
#include "device.h"
#include "../misc/deviceExtension.h"

namespace magma
{
void CommandBuffer::beginDebugMarker(const char *name, uint32_t color) noexcept
{
    MAGMA_ASSERT(name);
    MAGMA_ASSERT(strlen(name) > 0);
    MAGMA_ASSERT(color);
#ifdef MAGMA_DEBUG
    MAGMA_OPTIONAL_DEVICE_EXTENSION(vkCmdDebugMarkerBeginEXT);
    if (vkCmdDebugMarkerBeginEXT)
    {
        VkDebugMarkerMarkerInfoEXT info;
        info.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
        info.pNext = nullptr;
        info.pMarkerName = name;
        info.color[0] = ((color >> 24) & 0xFF) / 255.f; // R
        info.color[1] = ((color >> 16) & 0xFF) / 255.f; // G
        info.color[2] = ((color >> 8) & 0xFF) / 255.f; // B
        info.color[3] = (color & 0xFF) / 255.f; // A
        vkCmdDebugMarkerBeginEXT(handle, &info);
    }
#elif defined(_MSC_VER)
    name;
    color;
#endif // MAGMA_DEBUG
}

void CommandBuffer::endDebugMarker() noexcept
{
#ifdef MAGMA_DEBUG
    MAGMA_OPTIONAL_DEVICE_EXTENSION(vkCmdDebugMarkerEndEXT);
    if (vkCmdDebugMarkerEndEXT)
        vkCmdDebugMarkerEndEXT(handle);
#endif // MAGMA_DEBUG
}

void CommandBuffer::insertDebugMarker(const char *name, uint32_t color) noexcept
{
    MAGMA_ASSERT(name);
    MAGMA_ASSERT(strlen(name) > 0);
    MAGMA_ASSERT(color);
#ifdef MAGMA_DEBUG
    MAGMA_OPTIONAL_DEVICE_EXTENSION(vkCmdDebugMarkerInsertEXT);
    if (vkCmdDebugMarkerInsertEXT)
    {
        VkDebugMarkerMarkerInfoEXT info;
        info.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
        info.pNext = nullptr;
        info.pMarkerName = name;
        info.color[0] = ((color >> 24) & 0xFF) / 255.f; // R
        info.color[1] = ((color >> 16) & 0xFF) / 255.f; // G
        info.color[2] = ((color >> 8) & 0xFF) / 255.f; // B
        info.color[3] = (color & 0xFF) / 255.f; // A
        vkCmdDebugMarkerInsertEXT(handle, &info);
    }
#elif defined(_MSC_VER)
    name;
    color;
#endif // MAGMA_DEBUG
}

void CommandBuffer::beginDebugLabel(const char *name, uint32_t color) noexcept
{
    MAGMA_ASSERT(name);
    MAGMA_ASSERT(strlen(name) > 0);
    MAGMA_ASSERT(color);
#ifdef MAGMA_DEBUG
    MAGMA_OPTIONAL_DEVICE_EXTENSION(vkCmdBeginDebugUtilsLabelEXT);
    if (vkCmdBeginDebugUtilsLabelEXT)
    {
        VkDebugUtilsLabelEXT info;
        info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
        info.pNext = nullptr;
        info.pLabelName = name;
        info.color[0] = ((color >> 24) & 0xFF) / 255.f; // R
        info.color[1] = ((color >> 16) & 0xFF) / 255.f; // G
        info.color[2] = ((color >> 8) & 0xFF) / 255.f; // B
        info.color[3] = (color & 0xFF) / 255.f; // A
        vkCmdBeginDebugUtilsLabelEXT(handle, &info);
    }
#elif defined(_MSC_VER)
    name;
    color;
#endif // MAGMA_DEBUG
}

void CommandBuffer::endDebugLabel() noexcept
{
    MAGMA_OPTIONAL_DEVICE_EXTENSION(vkCmdEndDebugUtilsLabelEXT);
    if (vkCmdEndDebugUtilsLabelEXT)
        vkCmdEndDebugUtilsLabelEXT(handle);
}

void CommandBuffer::insertDebugLabel(const char *name, uint32_t color) noexcept
{
    MAGMA_ASSERT(name);
    MAGMA_ASSERT(strlen(name) > 0);
    MAGMA_ASSERT(color);
#ifdef MAGMA_DEBUG
    MAGMA_OPTIONAL_DEVICE_EXTENSION(vkCmdInsertDebugUtilsLabelEXT);
    if (vkCmdInsertDebugUtilsLabelEXT)
    {
        VkDebugUtilsLabelEXT info;
        info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
        info.pNext = nullptr;
        info.pLabelName = name;
        info.color[0] = ((color >> 24) & 0xFF) / 255.f; // R
        info.color[1] = ((color >> 16) & 0xFF) / 255.f; // G
        info.color[2] = ((color >> 8) & 0xFF) / 255.f; // B
        info.color[3] = (color & 0xFF) / 255.f; // A
        vkCmdInsertDebugUtilsLabelEXT(handle, &info);
    }
#elif defined(_MSC_VER)
    name;
    color;
#endif // MAGMA_DEBUG
}

bool CommandBuffer::begin(const char *blockName, uint32_t blockColor,
    VkCommandBufferUsageFlags flags /* 0 */) noexcept
{
    const bool beginResult = begin(flags);
#ifdef MAGMA_DEBUG
    beginDebugLabel(blockName, blockColor);
    beginMarked = VK_TRUE;
#elif defined(_MSC_VER)
    blockName;
    blockColor;
#endif // MAGMA_DEBUG
    return beginResult;
}

bool CommandBuffer::beginInherited(const std::shared_ptr<RenderPass>& renderPass, uint32_t subpass, const std::shared_ptr<Framebuffer>& framebuffer,
    const char *blockName, uint32_t blockColor,
    VkCommandBufferUsageFlags flags /* 0 */) noexcept
{
    const bool beginResult = beginInherited(renderPass, subpass, framebuffer, flags);
#ifdef MAGMA_DEBUG
    beginDebugLabel(blockName, blockColor);
    beginMarked = VK_TRUE;
#elif defined(_MSC_VER)
    blockName;
    blockColor;
#endif // MAGMA_DEBUG
    return beginResult;
}

void CommandBuffer::beginRenderPass(const std::shared_ptr<RenderPass>& renderPass, const std::shared_ptr<Framebuffer>& framebuffer,
    const std::vector<ClearValue>& clearValues, const char *renderPassName, uint32_t renderPassColor,
    VkSubpassContents contents /* VK_SUBPASS_CONTENTS_INLINE */) noexcept
{
    beginRenderPass(renderPass, framebuffer, clearValues, contents);
#ifdef MAGMA_DEBUG
    beginDebugLabel(renderPassName, renderPassColor);
    beginRenderPassMarked = VK_TRUE;
#elif defined(_MSC_VER)
    renderPassName;
    renderPassColor;
#endif // MAGMA_DEBUG
}

#ifdef VK_KHR_device_group
bool CommandBuffer::beginDeviceGroup(uint32_t deviceMask, const char *blockName, uint32_t blockColor,
    VkCommandBufferUsageFlags flags /* 0 */) noexcept
{
    const bool beginResult = beginDeviceGroup(deviceMask, flags);
#ifdef MAGMA_DEBUG
    beginDebugLabel(blockName, blockColor);
    beginMarked = VK_TRUE;
#elif defined(_MSC_VER)
    blockName;
    blockColor;
#endif // MAGMA_DEBUG
    return beginResult;
}

void CommandBuffer::beginRenderPassDeviceGroup(const std::shared_ptr<RenderPass>& renderPass, const std::shared_ptr<Framebuffer>& framebuffer,
    uint32_t deviceMask, const std::vector<ClearValue>& clearValues, const char *renderPassName, uint32_t renderPassColor,
    VkSubpassContents contents /* VK_SUBPASS_CONTENTS_INLINE */) noexcept
{
    beginRenderPassDeviceGroup(renderPass, framebuffer, deviceMask, clearValues, contents);
#ifdef MAGMA_DEBUG
    beginDebugLabel(renderPassName, renderPassColor);
    beginRenderPassMarked = VK_TRUE;
#elif defined(_MSC_VER)
    renderPassName;
    renderPassColor;
#endif // MAGMA_DEBUG
}
#endif // VK_KHR_device_group
} // namespace magma
