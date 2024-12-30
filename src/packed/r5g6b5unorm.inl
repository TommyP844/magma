namespace magma::packed
{
inline R5g6b5Unorm::R5g6b5Unorm(float r, float g, float b) noexcept
{
#ifdef MAGMA_SSE
    __m128 v = _mm_set_ps(0.f, r, g, b);
    v = _mm_max_ps(v, _mm_setzero_ps());
    v = _mm_min_ps(v, _mm_set_ps(0.f, 1.f, 1.f, 1.f));
    v = _mm_mul_ps(v, _mm_set_ps(0.f, 31.f, 63.f, 31.f));
    v = _mm_round_ps(v, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
    __m128 bitshift = _mm_set_ps(0.f, 2048.f, 32.f, 1.f); // -, 11, 5, 0
    v = _mm_mul_ps(v, bitshift);
    __m128i iv = _mm_cvtps_epi32(v);
    iv = _mm_horizontal_or(iv);
    this->v = (uint16_t)_mm_extract_epi16(iv, 0);
#elif defined(MAGMA_NEON)
    #error NEON codepath not implemented
#else // FPU
    r = std::min(std::max(0.f, r), 1.f);
    g = std::min(std::max(0.f, g), 1.f);
    b = std::min(std::max(0.f, b), 1.f);
    r = std::roundf(r * 31.f);
    g = std::roundf(g * 63.f);
    b = std::roundf(b * 31.f);
    this->b = uint16_t(b) & 0x1F;
    this->g = uint16_t(g) & 0x3F;
    this->r = uint16_t(r) & 0x1F;
#endif // FPU
}

inline R5g6b5Unorm::R5g6b5Unorm(uint8_t r, uint8_t g, uint8_t b) noexcept:
    R5g6b5Unorm(r/255.f, g/255.f, b/255.f)
{}

inline R5g6b5Unorm::R5g6b5Unorm(const float v[3]) noexcept:
    R5g6b5Unorm(v[0], v[1], v[2])
{}

inline R5g6b5Unorm::R5g6b5Unorm(const uint8_t v[3]) noexcept:
    R5g6b5Unorm(v[0]/255.f, v[1]/255.f, v[2]/255.f)
{}
} // namespace magma::packed
