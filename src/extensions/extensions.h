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

namespace magma
{
    /* For each extensions name we calculate its hash
       in compile-time. When instance or device extensions
       are enumerated, their hashes are added to the hash
       map, which allows a fast lookup of an extensions. */

    class Extensions
    {
    public:
        bool hasExtension(const char *name) const noexcept;
        void forEach(std::function<void(const std::string&, uint32_t)> fn) const noexcept;

    protected:
        Extensions(const std::vector<VkExtensionProperties>&);
        bool hasExtension(hash_t hash) const noexcept;

    private:
        std::map<std::string, uint32_t> extensions;
        std::unordered_set<hash_t> hashes;
    };

    MAGMA_TYPEDEF_MANAGED_PTR(Extensions)
} // namespace magma

#define MAGMA_CHECK_EXTENSION(name)\
    name(hasExtension(core::hashString(MAGMA_EXTENSION_PREFIX #name)))
