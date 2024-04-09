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
#include "extensions.h"

namespace magma
{
Extensions::Extensions(const std::vector<VkExtensionProperties>& properties)
{
    for (auto const& property: properties)
    {
        extensions.emplace(property.extensionName, property.specVersion);
        hashes.emplace(core::hashString(property.extensionName));
    }
}

bool Extensions::hasExtension(const char *name) const noexcept
{
    static const std::string prefix(MAGMA_EXTENSION_PREFIX);
    const hash_t hash = core::hashString(prefix + name);
    return hasExtension(hash);
}

void Extensions::forEach(std::function<void(const std::string&, uint32_t)> fn) const noexcept
{
    for (auto const& ext: extensions)
        fn(ext.first, ext.second);
}

bool Extensions::hasExtension(hash_t hash) const noexcept
{
    return hashes.find(hash) != hashes.end();
}
} // namespace magma
