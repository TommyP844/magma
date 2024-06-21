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

#define MAGMA_NULL (VkDeviceAddress)0ull

namespace magma
{
#ifdef VK_KHR_acceleration_structure
template<class Buffer>
inline VkDeviceOrHostAddressConstKHR address(const Buffer& buffer, VkDeviceAddress offset = 0ull) noexcept
{
    VkDeviceOrHostAddressConstKHR addr;
    addr.deviceAddress = buffer ? buffer->getDeviceAddress() + offset : NULL;
    return addr;
}

inline VkDeviceOrHostAddressConstKHR address(const void *buffer, uintptr_t offset = 0ull) noexcept
{
    VkDeviceOrHostAddressConstKHR addr;
    addr.hostAddress = (const uint8_t *)buffer + offset;
    return addr;
}
#endif // VK_KHR_acceleration_structure
} // namespace magma
