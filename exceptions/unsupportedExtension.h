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
#pragma once
#ifndef MAGMA_NO_EXCEPTIONS
#include "exception.h"

namespace magma
{
    namespace exception
    {
        /* Vulkan instance doesn't support requested extension. */

        class UnsupportedExtension : public Exception
        {
        public:
            explicit UnsupportedExtension(const char *extension,
                const source_location& location) noexcept:
                Exception(extension, location) {}
        };
    } // namespace exception
} // namespace magma

#define MAGMA_THROW_UNSUPPORTED(extensionName) throw magma::exception::UnsupportedExtension(extensionName, MAGMA_SOURCE_LOCATION)

#else

#define MAGMA_THROW_UNSUPPORTED(extensionName) abort()

#endif // !MAGMA_NO_EXCEPTIONS
