namespace magma
{
constexpr ClearValue::ClearValue() noexcept
#ifndef _MSC_VER
    : value{}
#endif
{
    static_assert(sizeof(ClearValue) == sizeof(VkClearValue), "size of ClearValue must be equal to the size of VkClearValue");
}

constexpr ClearColor::ClearColor(const float r, const float g, const float b, const float a /* 1.f */) noexcept
{
    value.color.float32[0] = r;
    value.color.float32[1] = g;
    value.color.float32[2] = b;
    value.color.float32[3] = a;
}

constexpr ClearColor::ClearColor(const int32_t r, const int32_t g, const int32_t b, const int32_t a) noexcept
{
    value.color.int32[0] = r;
    value.color.int32[1] = g;
    value.color.int32[2] = b;
    value.color.int32[3] = a;
}

constexpr ClearColor::ClearColor(const uint32_t r, const uint32_t g, const uint32_t b, const uint32_t a) noexcept
{
    value.color.uint32[0] = r;
    value.color.uint32[1] = g;
    value.color.uint32[2] = b;
    value.color.uint32[3] = a;
}

constexpr ClearColor::ClearColor(const float color[4]) noexcept
{
    value.color.float32[0] = color[0];
    value.color.float32[1] = color[1];
    value.color.float32[2] = color[2];
    value.color.float32[3] = color[3];
}

constexpr ClearColor::ClearColor(const int32_t color[4]) noexcept
{
    value.color.int32[0] = color[0];
    value.color.int32[1] = color[1];
    value.color.int32[2] = color[2];
    value.color.int32[3] = color[3];
}

constexpr ClearColor::ClearColor(const uint32_t color[4]) noexcept
{
    value.color.uint32[0] = color[0];
    value.color.uint32[1] = color[1];
    value.color.uint32[2] = color[2];
    value.color.uint32[3] = color[3];
}

constexpr ClearColor::ClearColor(const uint32_t hexValue) noexcept
{
    value.color.float32[0] = ((hexValue >> 16) & 0xFF) / 255.f;
    value.color.float32[1] = ((hexValue >> 8) & 0xFF) / 255.f;
    value.color.float32[2] = (hexValue & 0xFF) / 255.f;
    value.color.float32[3] = 1.f;
}

constexpr ClearDepth::ClearDepth(const float depth) noexcept
{   // assignment to member 'depthStencil' of union with active member 'color' is not allowed in a constant expression
    value.color.float32[0] = depth;
    value.color.float32[1] = 0.f;
    value.color.float32[2] = 0.f;
    value.color.float32[3] = 0.f;
}

inline ClearDepthStencil::ClearDepthStencil(float depth, uint32_t stencil) noexcept
{
    value.depthStencil.depth = depth;
    value.depthStencil.stencil = stencil;
}
} // namespace magma
