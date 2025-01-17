/*
Magma - Abstraction layer over Khronos Vulkan API.
Copyright (C) 2018-2024 Victor Coda.

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

namespace magma
{
#ifdef VK_KHR_acceleration_structure
    VkDeviceOrHostAddressConstKHR address(VkDeviceAddress deviceAddress) noexcept;
    VkDeviceOrHostAddressConstKHR address(const void *hostAddress) noexcept;
    VkDeviceOrHostAddressConstKHR address(const Buffer *buffer) noexcept;
    VkDeviceAddress align(std::size_t alignment, VkDeviceSize sizeOfBufferToBeAligned,
        VkDeviceAddress address, VkDeviceSize& sizeOfBufferLeftToOperate) noexcept;
#endif // VK_KHR_acceleration_structure
} // namespace magma

#include "address.inl"
