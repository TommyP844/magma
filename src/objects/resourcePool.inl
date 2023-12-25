namespace magma
{
#ifdef MAGMA_X64
#define MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(Type, pool)\
template<>\
inline core::ThreadSafeUnorderedSet<NonDispatchable<Type>>& ResourcePool::getPool<NonDispatchable<Type>>()\
{\
    return pool;\
}

MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkSemaphore, semaphores)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkFence, fences)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkDeviceMemory, deviceMemories)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkBuffer, buffers)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkImage, images)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkEvent, events)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkQueryPool, queryPools)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkBufferView, bufferViews)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkImageView, imageViews)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkShaderModule, shaderModules)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkPipelineCache, pipelineCaches)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkPipelineLayout, pipelineLayouts)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkRenderPass, renderPasses)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkPipeline, pipelines)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkDescriptorSetLayout, descriptorSetLayouts)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkSampler, samplers)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkDescriptorPool, descriptorPools)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkDescriptorSet, descriptorSets)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkFramebuffer, framebuffers)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkCommandPool, commandPools)
#ifdef VK_KHR_deferred_host_operations
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkDeferredOperationKHR, deferredOperations)
#endif
#ifdef VK_KHR_sampler_ycbcr_conversion
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkSamplerYcbcrConversionKHR, ycbcrSamplers)
#endif
#ifdef VK_KHR_surface
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkSurfaceKHR, surfaces)
#endif
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkSwapchainKHR, swapchains)
#ifdef VK_KHR_display
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkDisplayKHR, displays)
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkDisplayModeKHR, displayModes)
#endif
#ifdef VK_EXT_debug_report
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkDebugReportCallbackEXT, debugReportCallbacks)
#endif
#ifdef VK_EXT_debug_utils
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkDebugUtilsMessengerEXT, debugUtilsMessengers)
#endif
#ifdef VK_EXT_private_data
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkPrivateDataSlotEXT, privateDataSlots)
#endif
#ifdef VK_NV_ray_tracing
MAGMA_RESOURCE_POOL_IMPLEMENT_ACCESSOR(VkAccelerationStructureNV, accelerationStructures)
#endif
#endif // MAGMA_X64
} // namespace magma