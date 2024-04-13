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
#include "image.h"

namespace magma
{
    /* Mutable image can be used to create an image view with
       a different format from the image. For multi-planar formats,
       image view can be created of a plane of the image. */

    class MutableImage : public Image
    {
    public:
        bool blockTexelViewCompatible() const noexcept;

    protected:
        MutableImage(std::shared_ptr<Device> device,
            VkImageType imageType,
            VkFormat format,
            const VkExtent3D& extent,
            uint32_t mipLevels,
            uint32_t arrayLayers,
            uint32_t samples,
            VkImageCreateFlags flags,
            const Initializer& optional,
            const Sharing& sharing,
            std::shared_ptr<Allocator> allocator);
    };
} // namespace magma
