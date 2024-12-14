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
    class Image;
    class CommandBuffer;

    namespace aux
    {
        /* Generates mip levels from base texture level using a
           series of image blit operations. This is an analogue of
           glGenerateMipmap() function in OpenGL. */

        bool generateMipmap(lent_ptr<Image> image,
            uint32_t baseLevel,
            VkFilter filter,
            lent_ptr<CommandBuffer> cmdBuffer) noexcept;
    } // namespace aux
} // namespace magma
