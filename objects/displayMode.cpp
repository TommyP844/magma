/*
Magma - abstraction layer to facilitate usage of Khronos Vulkan API.
Copyright (C) 2018-2022 Victor Coda.

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
#include "displayMode.h"
#include "display.h"
#include "physicalDevice.h"
#include "device.h"
#include "../allocator/allocator.h"
#include "../misc/extProcAddress.h"
#include "../exceptions/errorResult.h"

namespace magma
{
#ifdef VK_KHR_display
DisplayMode::DisplayMode(std::shared_ptr<const Display> display, const VkExtent2D& visibleRegion, uint32_t refreshRate,
    std::shared_ptr<IAllocator> allocator /* nullptr */):
    NonDispatchable(VK_OBJECT_TYPE_DISPLAY_MODE_KHR, std::move(display->getDevice()), std::move(allocator)),
    instance(std::move(display->getPhysicalDevice()->getInstance())),
    physicalDevice(std::move(display->getPhysicalDevice())),
    visibleRegion(visibleRegion),
    refreshRate(refreshRate)
{
    VkDisplayModeCreateInfoKHR displayModeInfo;
    displayModeInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR;
    displayModeInfo.pNext = nullptr;
    displayModeInfo.flags = 0;
    displayModeInfo.parameters.visibleRegion = visibleRegion;
    displayModeInfo.parameters.refreshRate = refreshRate;
    MAGMA_REQUIRED_INSTANCE_EXTENSION(vkCreateDisplayModeKHR, VK_KHR_DISPLAY_EXTENSION_NAME);
    const VkResult result = vkCreateDisplayModeKHR(MAGMA_HANDLE(physicalDevice), *display, &displayModeInfo, MAGMA_OPTIONAL_INSTANCE(hostAllocator), &handle);
    MAGMA_THROW_FAILURE(result, "failed to create display mode");
}

const VkDisplayPlaneCapabilitiesKHR& DisplayMode::getPlaneCapabilities(uint32_t planeIndex) const
{
    const auto it = capabilities.find(planeIndex);
    if (it == capabilities.end())
    {
        VkDisplayPlaneCapabilitiesKHR planeCaps;
        MAGMA_INSTANCE_EXTENSION(vkGetDisplayPlaneCapabilitiesKHR);
        const VkResult result = vkGetDisplayPlaneCapabilitiesKHR(MAGMA_HANDLE(physicalDevice), handle, planeIndex, &planeCaps);
        MAGMA_THROW_FAILURE(result, "failed to get display plane capabilities");
        capabilities[planeIndex] = planeCaps;
    }
    return capabilities[planeIndex];
}
#endif // VK_KHR_display
} // namespace magma
