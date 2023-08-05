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
#include "pipelineBatch.h"
#include "../shaders/rayTracingShaderGroup.h"

namespace magma
{
    /* Exposes Vulkan's ability to create multiple ray tracing pipelines in a single call.
       As there may be thousands of ray tracing pipelines in the complicated rendering engine,
       it may be more efficient for graphics driver to create them at once. */

#ifdef VK_NV_ray_tracing
    class RayTracingPipeline;
    class PipelineCache;

    class RayTracingPipelineBatch : public PipelineBatch<RayTracingPipeline>
    {
    public:
        explicit RayTracingPipelineBatch(uint32_t capacity = 32);
        uint32_t batchPipeline(const std::vector<PipelineShaderStage>& shaderStages,
            const std::vector<RayTracingShaderGroup>& shaderGroups,
            uint32_t maxRecursionDepth,
            std::shared_ptr<PipelineLayout> layout,
            std::shared_ptr<RayTracingPipeline> basePipeline = nullptr,
            VkPipelineCreateFlags flags = 0);
        void buildPipelines(std::shared_ptr<Device> device,
            std::shared_ptr<PipelineCache> pipelineCache,
            std::shared_ptr<IAllocator> allocator = nullptr) override;

    private:
        std::shared_ptr<Device> device;
        std::list<std::vector<RayTracingShaderGroup>> groups;
        std::vector<VkRayTracingPipelineCreateInfoNV> pipelineInfos;
    };
#endif // VK_NV_ray_tracing
} // namespace magma
