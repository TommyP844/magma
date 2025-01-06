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
#include "pch.h"
#pragma hdrstop
#if defined(__Fuchsia__)
    #include <zircon/syscalls.h>
#endif
#include "externalSemaphore.h"
#include "../objects/device.h"
#include "../allocator/allocator.h"
#include "../misc/extension.h"
#include "../exceptions/errorResult.h"

namespace magma
{
#ifdef VK_KHR_external_semaphore
ExternalSemaphore::ExternalSemaphore(std::shared_ptr<Device> device,
    std::shared_ptr<IAllocator> allocator /* nullptr */,
    VkSemaphoreCreateFlags flags /* 0 */,
    const StructureChain& extendedInfo /* default */):
    Semaphore(std::move(allocator), std::move(device)),
#ifdef VK_KHR_external_semaphore_win32
    Win32ExternalSemaphore(this, VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT_KHR)
#elif defined(__Fuchsia__)
    zirconHandle(0)
#else
    fd(0)
#endif
{
    VkSemaphoreCreateInfo semaphoreInfo;
    VkExportSemaphoreCreateInfoKHR exportSemaphoreInfo;
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreInfo.pNext = &exportSemaphoreInfo;
    semaphoreInfo.flags = flags;
    exportSemaphoreInfo.sType = VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO_KHR;
    exportSemaphoreInfo.pNext = extendedInfo.headNode();
    exportSemaphoreInfo.handleTypes =
    #ifdef VK_KHR_external_semaphore_win32
        handleType;
    #elif defined(VK_FUCHSIA_external_semaphore)
        VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_ZIRCON_EVENT_BIT_FUCHSIA;
    #elif defined(VK_KHR_external_semaphore_fd)
        #ifdef VK_USE_PLATFORM_ANDROID_KHR
        // https://registry.khronos.org/EGL/extensions/ANDROID/EGL_ANDROID_native_fence_sync.txt
        VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT_KHR;
        #else
        VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT_KHR;
        #endif
    #else
        0;
    #endif // VK_KHR_external_semaphore_fd
    const VkResult result = vkCreateSemaphore(getNativeDevice(), &semaphoreInfo,
        MAGMA_OPTIONAL(hostAllocator), &handle);
    MAGMA_HANDLE_RESULT(result, "failed to create external semaphore");
}

ExternalSemaphore::ExternalSemaphore(std::shared_ptr<Device> device,
#if defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__)
    HANDLE hSemaphore,
    LPCWSTR name /* nullptr */,
#elif defined(__Fuchsia__)
    zx_handle_t zirconHandle,
#else
    int fd,
#endif
    std::shared_ptr<IAllocator> allocator /* nullptr */,
    VkSemaphoreCreateFlags flags /* 0 */,
    VkSemaphoreImportFlagsKHR importFlags /* 0 */,
    const StructureChain& extendedInfo /* default */):
    Semaphore(std::move(device), std::move(allocator), flags, extendedInfo),
#ifdef VK_KHR_external_semaphore_win32
    Win32ExternalSemaphore(this, VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT_KHR)
#elif defined(__Fuchsia__)
    zirconHandle(0)
#else
    fd(0)
#endif
{
#ifdef VK_KHR_external_semaphore_win32
    #if defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__)
    Win32ExternalSemaphore::importNtHandle(hSemaphore, name, importFlags);
    #endif
#elif defined(VK_FUCHSIA_external_semaphore)
    VkImportSemaphoreZirconHandleInfoFUCHSIA importZirconHandleInfo;
    importZirconHandleInfo.sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_ZIRCON_HANDLE_INFO_FUCHSIA;
    importZirconHandleInfo.pNext = nullptr;
    importZirconHandleInfo.semaphore = handle;
    importZirconHandleInfo.flags = importFlags;
    importZirconHandleInfo.handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_ZIRCON_EVENT_BIT_FUCHSIA;
    #if defined(__Fuchsia__)
    importZirconHandleInfo.zirconHandle = zirconHandle;
    #endif
    MAGMA_REQUIRED_DEVICE_EXTENSION(vkImportSemaphoreZirconHandleFUCHSIA, VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME);
    const VkResult result = vkImportSemaphoreZirconHandleFUCHSIA(getNativeDevice(), &importZirconHandleInfo);
    MAGMA_HANDLE_RESULT(result, "failed to import Zircon handle");
#elif defined(VK_KHR_external_semaphore_fd)
    VkImportSemaphoreFdInfoKHR importFdInfo;
    importFdInfo.sType = VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR;
    importFdInfo.pNext = nullptr;
    importFdInfo.semaphore = handle;
    importFdInfo.flags = importFlags;
    importFdInfo.handleType =
    #ifdef VK_USE_PLATFORM_ANDROID_KHR
        VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT_KHR;
    #else
        VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT_KHR;
    #endif
    importFdInfo.fd = fd;
    MAGMA_REQUIRED_DEVICE_EXTENSION(vkImportSemaphoreFdKHR, VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME);
    const VkResult result = vkImportSemaphoreFdKHR(getNativeDevice(), &importFdInfo);
    #ifdef VK_USE_PLATFORM_ANDROID_KHR
    MAGMA_HANDLE_RESULT(result, "failed to import Android fence descriptor");
    #else
    MAGMA_HANDLE_RESULT(result, "failed to import POSIX file descriptor");
    #endif
#endif // VK_KHR_external_semaphore_fd
}

ExternalSemaphore::~ExternalSemaphore()
{
#if defined(__Fuchsia__)
    zx_handle_close(zirconHandle);
#elif defined(__unix__) || defined(__unix)
    close(fd);
#endif
}

#if defined(__Fuchsia__)
zx_handle_t ExternalSemaphore::getEvent() const
{
#if defined(VK_FUCHSIA_external_semaphore)
    VkSemaphoreGetZirconHandleInfoFUCHSIA zirconHandleInfo;
    zirconHandleInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_ZIRCON_HANDLE_INFO_FUCHSIA;
    zirconHandleInfo.pNext = nullptr;
    zirconHandleInfo.semaphore = handle;
    zirconHandleInfo.handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_ZIRCON_EVENT_BIT_FUCHSIA;
    MAGMA_REQUIRED_DEVICE_EXTENSION(vkGetSemaphoreWin32HandleKHR, VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME);
    const VkResult result = vkGetSemaphoreZirconHandleFUCHSIA(getNativeDevice(), &zirconHandleInfo, &zirconHandle);
    MAGMA_HANDLE_RESULT(result, "failed to get Zircon handle");
#endif // VK_FUCHSIA_external_semaphore
    return zirconHandle;
}

#elif defined(__unix__) || defined(__unix)
int ExternalSemaphore::getFd() const
{
#if defined(VK_KHR_external_semaphore_fd)
    VkSemaphoreGetFdInfoKHR fdInfo;
    fdInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR;
    fdInfo.pNext = nullptr;
    fdInfo.semaphore = handle;
    fdInfo.handleType =
    #ifdef VK_USE_PLATFORM_ANDROID_KHR
        VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT_KHR;
    #else
        VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT_KHR;
    #endif
    MAGMA_REQUIRED_DEVICE_EXTENSION(vkGetSemaphoreFdKHR, VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME);
    const VkResult result = vkGetSemaphoreFdKHR(getNativeDevice(), &fdInfo, &fd);
#ifdef VK_USE_PLATFORM_ANDROID_KHR
    MAGMA_HANDLE_RESULT(result, "failed to get Android fence descriptor");
#else
    MAGMA_HANDLE_RESULT(result, "failed to get POSIX file descriptor");
#endif
#endif // VK_KHR_external_semaphore_fd
    return fd;
}
#endif // __unix__ || __unix
#endif // VK_KHR_external_semaphore
} // namespace magma
