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
#include "vertexType.h"
#include "vertexInputState.h"
#include "vertexLayout.h"

namespace magma
{
    /* Template vertex input structure. */

    template<class Vertex>
    class VertexInputStructure : public VertexInputState
    {
    public:
        VertexInputStructure() = default;
        explicit VertexInputStructure(uint32_t binding,
            const VertexInputAttribute& attribute,
            VkVertexInputRate inputRate = VK_VERTEX_INPUT_RATE_VERTEX);
        explicit VertexInputStructure(uint32_t binding,
            const std::initializer_list<VertexInputAttribute>& attributes,
            VkVertexInputRate inputRate = VK_VERTEX_INPUT_RATE_VERTEX);
        template<uint32_t vertexAttributeCount>
        explicit VertexInputStructure(uint32_t binding,
            const VertexInputAttribute(&attributes)[vertexAttributeCount],
            VkVertexInputRate inputRate = VK_VERTEX_INPUT_RATE_VERTEX);
        VertexInputStructure(const VertexInputStructure& other) noexcept;
        VertexInputStructure& operator=(const VertexInputStructure& other) noexcept;
        virtual uint32_t stride(uint32_t binding) const noexcept override;
    };

    namespace specialization
    {
        /* User have to specialize this template for concrete type.
           <Unsigned> and <Normalized> parameters are used to distinguish
           Vulkan formats with UNORM, SNORM, UINT and SINT modificators. */

        template<VkFormat Format, bool Unsigned, bool Normalized>
        struct VertexAttributeTraits
        {
            constexpr static VkFormat format() noexcept { return Format; }
            constexpr static bool unsigned_() noexcept { return Unsigned; }
            constexpr static bool normalized() noexcept { return Normalized; }
        };

        template<class Type>
        struct VertexAttribute : VertexAttributeTraits<VK_FORMAT_UNDEFINED, false, false>
        {
            constexpr VertexAttribute() noexcept;
            constexpr static std::size_t size() noexcept { return sizeof(Type); }
        };

        #define MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Type, format) template<> struct VertexAttribute<Type> :\
            VertexAttributeTraits<format, Type::unsigned_(), Type::normalized()> {}

        /* Built-in specializations for scalar vertex input types. */

        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UByteNorm, VK_FORMAT_R8_UNORM);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(ByteNorm, VK_FORMAT_R8_SNORM);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UByte, VK_FORMAT_R8_UINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Byte, VK_FORMAT_R8_SINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UShortNorm, VK_FORMAT_R16_UNORM);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(ShortNorm, VK_FORMAT_R16_SNORM);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UShort, VK_FORMAT_R16_UINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Short, VK_FORMAT_R16_SINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Half, VK_FORMAT_R16_SFLOAT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UInt, VK_FORMAT_R32_UINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Int, VK_FORMAT_R32_SINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Float, VK_FORMAT_R32_SFLOAT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(LargeUInt, VK_FORMAT_R64_UINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(LargeInt, VK_FORMAT_R64_SINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Double, VK_FORMAT_R64_SFLOAT);

        /* Built-in specializations for vectorized vertex input types. */

        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UByteNorm2, VK_FORMAT_R8G8_UNORM);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(ByteNorm2, VK_FORMAT_R8G8_SNORM);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UByte2, VK_FORMAT_R8G8_UINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Byte2, VK_FORMAT_R8G8_SINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UByteNorm4, VK_FORMAT_R8G8B8A8_UNORM);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(ByteNorm4, VK_FORMAT_R8G8B8A8_SNORM);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UByte4, VK_FORMAT_R8G8B8A8_UINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Byte4, VK_FORMAT_R8G8B8A8_SINT);

        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UShortNorm2, VK_FORMAT_R16G16_UNORM);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(ShortNorm2, VK_FORMAT_R16G16_SNORM);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UShort2, VK_FORMAT_R16G16_UINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Short2, VK_FORMAT_R16G16_SINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UShortNorm3, VK_FORMAT_R16G16B16_UNORM);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(ShortNorm3, VK_FORMAT_R16G16B16_SNORM);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UShort3, VK_FORMAT_R16G16B16_UINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Short3, VK_FORMAT_R16G16B16_SINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UShortNorm4, VK_FORMAT_R16G16B16A16_UNORM);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(ShortNorm4, VK_FORMAT_R16G16B16A16_SNORM);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UShort4, VK_FORMAT_R16G16B16A16_UINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Short4, VK_FORMAT_R16G16B16A16_SINT);

        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UInt2, VK_FORMAT_R32G32_UINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Int2, VK_FORMAT_R32G32_SINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UInt3, VK_FORMAT_R32G32B32_UINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Int3, VK_FORMAT_R32G32B32_SINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(UInt4, VK_FORMAT_R32G32B32A32_UINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Int4, VK_FORMAT_R32G32B32A32_SINT);

        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(LargeUInt2, VK_FORMAT_R64G64_UINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(LargeInt2, VK_FORMAT_R64G64_SINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(LargeUInt3, VK_FORMAT_R64G64B64_UINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(LargeInt3, VK_FORMAT_R64G64B64_SINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(LargeUInt4, VK_FORMAT_R64G64B64A64_UINT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(LargeInt4, VK_FORMAT_R64G64B64A64_SINT);

        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Half2, VK_FORMAT_R16G16_SFLOAT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Half3, VK_FORMAT_R16G16B16_SFLOAT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Half4, VK_FORMAT_R16G16B16A16_SFLOAT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Float2, VK_FORMAT_R32G32_SFLOAT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Float3, VK_FORMAT_R32G32B32_SFLOAT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Float4, VK_FORMAT_R32G32B32A32_SFLOAT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Double2, VK_FORMAT_R64G64_SFLOAT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Double3, VK_FORMAT_R64G64B64_SFLOAT);
        MAGMA_SPECIALIZE_VERTEX_ATTRIBUTE(Double4, VK_FORMAT_R64G64B64A64_SFLOAT);
    } // namespace specialization
} // namespace magma

namespace magma
{
    /* Pre-defined vertex input structures. */

    namespace renderstate
    {
        /* No input vertex data. */

        extern const VertexInputStructure<int> nullVertexInput;

        /* Vertex position only. */

        extern const VertexInputStructure<layout::Pos2h> pos2h;
        extern const VertexInputStructure<layout::Pos2f> pos2f;
        extern const VertexInputStructure<layout::Pos2d> pos2d;
        extern const VertexInputStructure<layout::Pos3h> pos3h;
        extern const VertexInputStructure<layout::Pos3f> pos3f;
        extern const VertexInputStructure<layout::Pos3d> pos3d;
        extern const VertexInputStructure<layout::Pos4h> pos4h;
        extern const VertexInputStructure<layout::Pos4f> pos4f;
        extern const VertexInputStructure<layout::Pos4d> pos4d;

        /* Vertex position and color. */

        extern const VertexInputStructure<layout::Pos2hColor4ub> pos2hColor4ub;
        extern const VertexInputStructure<layout::Pos2fColor4ub> pos2fColor4ub;
        extern const VertexInputStructure<layout::Pos2dColor4ub> pos2dColor4ub;
        extern const VertexInputStructure<layout::Pos3hColor4ub> pos3hColor4ub;
        extern const VertexInputStructure<layout::Pos3fColor4ub> pos3fColor4ub;
        extern const VertexInputStructure<layout::Pos3dColor4ub> pos3dColor4ub;
        extern const VertexInputStructure<layout::Pos4hColor4ub> pos4hColor4ub;
        extern const VertexInputStructure<layout::Pos4fColor4ub> pos4fColor4ub;
        extern const VertexInputStructure<layout::Pos4dColor4ub> pos4dColor4ub;

        /* Vertex position and texture coordinates. */

        extern const VertexInputStructure<layout::Pos2hTex2h> pos2hTex2h;
        extern const VertexInputStructure<layout::Pos2fTex2h> pos2fTex2h;
        extern const VertexInputStructure<layout::Pos2fTex2f> pos2fTex2f;
        extern const VertexInputStructure<layout::Pos2dTex2f> pos2dTex2f;
        extern const VertexInputStructure<layout::Pos3hTex2h> pos3hTex2h;
        extern const VertexInputStructure<layout::Pos3fTex2h> pos3fTex2h;
        extern const VertexInputStructure<layout::Pos3fTex2f> pos3fTex2f;
        extern const VertexInputStructure<layout::Pos3dTex2f> pos3dTex2f;
        extern const VertexInputStructure<layout::Pos4hTex2h> pos4hTex2h;
        extern const VertexInputStructure<layout::Pos4fTex2h> pos4fTex2h;
        extern const VertexInputStructure<layout::Pos4fTex2f> pos4fTex2f;
        extern const VertexInputStructure<layout::Pos4dTex2f> pos4dTex2f;

        /* Vertex position and normal. */

        extern const VertexInputStructure<layout::Pos3hNormal3h> pos3hNormal3h;
        extern const VertexInputStructure<layout::Pos3hNormal4ub> pos3hNormal4ub;
        extern const VertexInputStructure<layout::Pos3fNormal3h> pos3fNormal3h;
        extern const VertexInputStructure<layout::Pos3fNormal3f> pos3fNormal3f;
        extern const VertexInputStructure<layout::Pos3fNormal4ub> pos3fNormal4ub;
        extern const VertexInputStructure<layout::Pos3dNormal3h> pos3dNormal3h;
        extern const VertexInputStructure<layout::Pos3dNormal3f> pos3dNormal3f;
        extern const VertexInputStructure<layout::Pos3dNormal4ub> pos3dNormal4ub;
        extern const VertexInputStructure<layout::Pos4hNormal3h> pos4hNormal3h;
        extern const VertexInputStructure<layout::Pos4hNormal4ub> pos4hNormal4ub;
        extern const VertexInputStructure<layout::Pos4fNormal3h> pos4fNormal3h;
        extern const VertexInputStructure<layout::Pos4fNormal3f> pos4fNormal3f;
        extern const VertexInputStructure<layout::Pos4fNormal4ub> pos4fNormal4ub;
        extern const VertexInputStructure<layout::Pos4dNormal3h> pos4dNormal3h;
        extern const VertexInputStructure<layout::Pos4dNormal3f> pos4dNormal3f;
        extern const VertexInputStructure<layout::Pos4dNormal4ub> pos4dNormal4ub;

        /* Vertex position, TBN matrix and texture coordinates. */

        extern const VertexInputStructure<layout::Pos3hTBN4ubTex2h> pos3hTBN4ubTex2h;
        extern const VertexInputStructure<layout::Pos3fTBN4ubTex2h> pos3fTBN4ubTex2h;
        extern const VertexInputStructure<layout::Pos3fTBN4ubTex2f> pos3fTBN4ubTex2f;
        extern const VertexInputStructure<layout::Pos3dTBN4ubTex2h> pos3dTBN4ubTex2h;
        extern const VertexInputStructure<layout::Pos3dTBN4ubTex2f> pos3dTBN4ubTex2f;
        extern const VertexInputStructure<layout::Pos4hTBN4ubTex2h> pos4hTBN4ubTex2h;
        extern const VertexInputStructure<layout::Pos4fTBN4ubTex2h> pos4fTBN4ubTex2h;
        extern const VertexInputStructure<layout::Pos4fTBN4ubTex2f> pos4fTBN4ubTex2f;
        extern const VertexInputStructure<layout::Pos4dTBN4ubTex2h> pos4dTBN4ubTex2h;
        extern const VertexInputStructure<layout::Pos4dTBN4ubTex2f> pos4dTBN4ubTex2f;
    } // namespace renderstate
} // namespace magma

#include "vertexInputStructure.inl"
