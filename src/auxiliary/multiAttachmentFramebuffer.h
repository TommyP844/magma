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
#include "baseFramebuffer.h"

namespace magma
{
    class Device;
    class Image2D;
    class ImageView;
    class Allocator;

    namespace aux
    {
        /* Auxiliary frame buffer that is responsible for management
           of multiple color attachments and depth/stencil buffer.
           This allows the rendering pipeline to draw to multiple
           render targets at once. */

        class MultiAttachmentFramebuffer : public Framebuffer
        {
        public:
            explicit MultiAttachmentFramebuffer(std::shared_ptr<Device> device,
                const std::initializer_list<VkFormat>& colorAttachmentFormats,
                const VkFormat depthStencilFormat,
                const VkExtent2D& extent,
                bool depthSampled,
                std::shared_ptr<Allocator> allocator = nullptr,
                bool colorClearOp = true,
                bool depthStencilClearOp = true, // Set to false in case of separate depth pass
                const std::vector<VkComponentMapping>& swizzles = {});
            const std::shared_ptr<ImageView>& getAttachmentView(uint32_t index) const noexcept { return attachmentViews[index]; }
            const std::shared_ptr<ImageView>& getDepthStencilView() const noexcept { return attachmentViews.back(); }
            const std::shared_ptr<RenderPass>& getDepthRenderPass() const { return lazyDepthRenderPass(); }
            const std::shared_ptr<magma::Framebuffer>& getDepthFramebuffer();
            bool hasColorClear() const noexcept { return colorClearOp; }
            bool hasDepthStencilClear() const noexcept { return depthStencilClearOp; }

        private:
            const std::shared_ptr<RenderPass>& lazyDepthRenderPass() const;

            const bool colorClearOp;
            const bool depthStencilClearOp;
            std::vector<std::shared_ptr<ImageView>> attachmentViews;
            mutable std::shared_ptr<RenderPass> depthRenderPass;
            mutable std::shared_ptr<magma::Framebuffer> depthFramebuffer;
        };
    } // namespace aux
} // namespace magma
