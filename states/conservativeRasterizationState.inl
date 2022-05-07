constexpr ConservativeRasterizationState::ConservativeRasterizationState(const RasterizationState& state,
    const VkConservativeRasterizationModeEXT conservativeRasterizationMode,
    const float extraPrimitiveOverestimationSize /* 0 */) noexcept:
    RasterizationState(state),
    conservative{
        VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT,
        state.pNext,
        0, // flags
        conservativeRasterizationMode,
        extraPrimitiveOverestimationSize
    }
{
    pNext = &conservative;
}

inline std::size_t ConservativeRasterizationState::hash() const noexcept
{
    std::size_t hash = RasterizationState::hash();
    core::hashCombine(hash, core::hashArgs(
        conservative.sType,
        conservative.flags,
        conservative.conservativeRasterizationMode,
        conservative.extraPrimitiveOverestimationSize));
    return hash;
}

constexpr bool ConservativeRasterizationState::operator==(const ConservativeRasterizationState& other) const noexcept
{
    return RasterizationState::operator==(other) &&
        (conservative.flags == other.conservative.flags) &&
        (conservative.conservativeRasterizationMode == other.conservative.conservativeRasterizationMode) &&
        (conservative.extraPrimitiveOverestimationSize == other.conservative.extraPrimitiveOverestimationSize);
}