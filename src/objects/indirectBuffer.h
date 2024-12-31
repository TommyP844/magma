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
#include "buffer.h"
#include "deviceMemory.h"

namespace magma
{
    /* Indirect buffer allows to source the draw command's
       parameters indirectly from memory. */

    class IndirectBuffer : public Buffer
    {
    public:
        ~IndirectBuffer();
        uint32_t getMaxDrawCount() const noexcept { return maxDrawCount; }
        uint32_t getDrawCount() const noexcept { return drawCount; }
        uint32_t getStride() const noexcept { return stride; }
        bool persistentlyMapped() const noexcept { return persistent; }
        void reset() noexcept { drawCount = 0; }

    protected:
        IndirectBuffer(std::shared_ptr<Device> device,
            uint32_t maxDrawCount,
            std::size_t stride,
            bool persistentlyMapped,
            const Initializer& optional,
            const Sharing& sharing,
            std::shared_ptr<Allocator> allocator);

        const uint32_t maxDrawCount;
        const uint32_t stride;
        const bool persistent;
        uint32_t drawCount;
    };

    /* An array of VkDrawIndirectCommand structures. */

    class DrawIndirectBuffer : public IndirectBuffer
    {
    public:
        explicit DrawIndirectBuffer(std::shared_ptr<Device> device,
            uint32_t maxDrawCommands,
            std::shared_ptr<Allocator> allocator = nullptr,
            bool persistentlyMapped = false,
            const Initializer& optional = Initializer(),
            const Sharing& sharing = Sharing());
        uint32_t writeDrawCommand(uint32_t vertexCount,
            uint32_t firstVertex = 0) noexcept;
        uint32_t writeDrawInstancedCommand(uint32_t vertexCount,
            uint32_t instanceCount,
            uint32_t firstVertex = 0,
            uint32_t firstInstance = 0) noexcept;
        uint32_t writeDrawCommand(const VkDrawIndirectCommand& drawCmd) noexcept;

    private:
        VkDrawIndirectCommand *const mappedData;
    };

    /* An array of VkDrawIndexedIndirectCommand structures. */

    class DrawIndexedIndirectBuffer : public IndirectBuffer
    {
    public:
        explicit DrawIndexedIndirectBuffer(std::shared_ptr<Device> device,
            uint32_t maxDrawIndexedCommands,
            std::shared_ptr<Allocator> allocator = nullptr,
            bool persistentlyMapped = false,
            const Initializer& optional = Initializer(),
            const Sharing& sharing = Sharing());
        uint32_t writeDrawIndexedCommand(uint32_t indexCount,
            uint32_t firstIndex = 0,
            uint32_t vertexOffset = 0) noexcept;
        uint32_t writeDrawIndexedInstancedCommand(uint32_t indexCount,
            uint32_t instanceCount,
            uint32_t firstIndex = 0,
            uint32_t vertexOffset = 0,
            uint32_t firstInstance = 0) noexcept;
        uint32_t writeDrawIndexedCommand(const VkDrawIndexedIndirectCommand& drawIndexedCmd) noexcept;

    private:
        VkDrawIndexedIndirectCommand *const mappedData;
    };

    /* An array of VkDispatchIndirectCommand structures. */

    class DispatchIndirectBuffer : public IndirectBuffer
    {
    public:
        explicit DispatchIndirectBuffer(std::shared_ptr<Device> device,
            uint32_t maxDispatchCommands,
            std::shared_ptr<Allocator> allocator = nullptr,
            bool persistentlyMapped = false,
            const Initializer& optional = Initializer(),
            const Sharing& sharing = Sharing());
        uint32_t writeDispatchCommand(uint32_t x, uint32_t y, uint32_t z) noexcept;

    private:
        VkDispatchIndirectCommand *const mappedData;
    };

    /* An array of VkDrawMeshTasksIndirectCommand structures. */

#if defined(VK_EXT_mesh_shader) || defined(VK_NV_mesh_shader)
    class DrawMeshTasksIndirectBuffer : public IndirectBuffer
    {
    public:
        explicit DrawMeshTasksIndirectBuffer(std::shared_ptr<Device> device,
            uint32_t maxDrawMeshTasksCommands,
            std::shared_ptr<Allocator> allocator = nullptr,
            bool persistentlyMapped = false,
            const Initializer& optional = Initializer(),
            const Sharing& sharing = Sharing());
        uint32_t writeDrawMeshTaskCommand(uint32_t groupCountX,
            uint32_t groupCountY = 1,
            uint32_t groupCountZ = 1);

    private:
        static std::size_t indirectCommandStride(std::shared_ptr<Device> device) noexcept;

        void *const mappedData;
        const bool extMeshShader;
    };
#endif // VK_EXT_mesh_shader || VK_NV_mesh_shader
} // namespace magma

#include "indirectBuffer.inl"
