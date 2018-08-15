/*
Magma - C++1x interface over Khronos Vulkan API.
Copyright (C) 2018 Victor Coda.

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
#include "object.h"
#include "../allocator/objectAllocator.h"

namespace magma
{
std::shared_ptr<IObjectAllocator> Object::_allocator;

void *Object::operator new(std::size_t size)
{
    void *ptr;
    if (_allocator)
        ptr = _allocator->alloc(size);
    else
        ptr = malloc(size);
    if (!ptr)
        throw std::bad_alloc();
    return ptr;
}

void *Object::operator new(std::size_t size, const std::nothrow_t&) noexcept
{
    void *ptr;
    if (_allocator)
        ptr = _allocator->alloc(size);
    else
        ptr = malloc(size);
    return ptr;
}

void Object::operator delete(void *ptr)
{
    if (_allocator)
        _allocator->free(ptr);
    else
        free(ptr);
}

void Object::setAllocator(std::shared_ptr<IObjectAllocator> allocator)
{
    _allocator = std::move(allocator);
}

std::shared_ptr<IObjectAllocator> Object::getAllocator()
{
    return _allocator;
}
} // namespace magma
