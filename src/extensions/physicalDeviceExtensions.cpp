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
#include "pch.h"
#pragma hdrstop
#include "physicalDeviceExtensions.h"
#include "../objects/physicalDevice.h"

namespace magma
{
PhysicalDeviceExtensions::PhysicalDeviceExtensions(std::shared_ptr<const PhysicalDevice> device):
    Extensions(device->enumerateExtensions()),

    MAGMA_CHECK_EXTENSION(AMD_buffer_marker),
    MAGMA_CHECK_EXTENSION(AMD_calibrated_timestamps),
    MAGMA_CHECK_EXTENSION(AMD_device_coherent_memory),
    MAGMA_CHECK_EXTENSION(AMD_display_native_hdr),
    MAGMA_CHECK_EXTENSION(AMD_draw_indirect_count),
    MAGMA_CHECK_EXTENSION(AMD_gcn_shader),
    MAGMA_CHECK_EXTENSION(AMD_gpa_interface),
    MAGMA_CHECK_EXTENSION(AMD_gpu_shader_half_float),
    MAGMA_CHECK_EXTENSION(AMD_gpu_shader_int16),
    MAGMA_CHECK_EXTENSION(AMD_memory_overallocation_behavior),
    MAGMA_CHECK_EXTENSION(AMD_mixed_attachment_samples),
    MAGMA_CHECK_EXTENSION(AMD_negative_viewport_height),
    MAGMA_CHECK_EXTENSION(AMD_pipeline_compiler_control),
    MAGMA_CHECK_EXTENSION(AMD_programmable_sample_locations),
    MAGMA_CHECK_EXTENSION(AMD_rasterization_order),
    MAGMA_CHECK_EXTENSION(AMD_shader_ballot),
    MAGMA_CHECK_EXTENSION(AMD_shader_core_properties),
    MAGMA_CHECK_EXTENSION(AMD_shader_core_properties2),
    MAGMA_CHECK_EXTENSION(AMD_shader_early_and_late_fragment_tests),
    MAGMA_CHECK_EXTENSION(AMD_shader_explicit_vertex_parameter),
    MAGMA_CHECK_EXTENSION(AMD_shader_fragment_mask),
    MAGMA_CHECK_EXTENSION(AMD_shader_image_load_store_lod),
    MAGMA_CHECK_EXTENSION(AMD_shader_info),
    MAGMA_CHECK_EXTENSION(AMD_shader_trinary_minmax),
    MAGMA_CHECK_EXTENSION(AMD_texture_gather_bias_lod),
    MAGMA_CHECK_EXTENSION(AMD_wave_limits),

    MAGMA_CHECK_EXTENSION(AMDX_shader_enqueue),

    MAGMA_CHECK_EXTENSION(ANDROID_external_memory_android_hardware_buffer),

    MAGMA_CHECK_EXTENSION(ARM_rasterization_order_attachment_access),
    MAGMA_CHECK_EXTENSION(ARM_shader_core_builtins),

    MAGMA_CHECK_EXTENSION(EXT_4444_formats),
    MAGMA_CHECK_EXTENSION(EXT_astc_decode_mode),
    MAGMA_CHECK_EXTENSION(EXT_attachment_feedback_loop_layout),
    MAGMA_CHECK_EXTENSION(EXT_blend_operation_advanced),
    MAGMA_CHECK_EXTENSION(EXT_buffer_device_address),
    MAGMA_CHECK_EXTENSION(EXT_border_color_swizzle),
    MAGMA_CHECK_EXTENSION(EXT_calibrated_timestamps),
    MAGMA_CHECK_EXTENSION(EXT_color_write_enable),
    MAGMA_CHECK_EXTENSION(EXT_conditional_rendering),
    MAGMA_CHECK_EXTENSION(EXT_conservative_rasterization),
    MAGMA_CHECK_EXTENSION(EXT_custom_border_color),
    MAGMA_CHECK_EXTENSION(EXT_debug_marker),
    MAGMA_CHECK_EXTENSION(EXT_depth_bias_control),
    MAGMA_CHECK_EXTENSION(EXT_depth_clamp_zero_one),
    MAGMA_CHECK_EXTENSION(EXT_depth_clip_control),
    MAGMA_CHECK_EXTENSION(EXT_depth_clip_enable),
    MAGMA_CHECK_EXTENSION(EXT_depth_range_unrestricted),
    MAGMA_CHECK_EXTENSION(EXT_descriptor_indexing),
    MAGMA_CHECK_EXTENSION(EXT_device_address_binding_report),
    MAGMA_CHECK_EXTENSION(EXT_device_fault),
    MAGMA_CHECK_EXTENSION(EXT_device_memory_report),
    MAGMA_CHECK_EXTENSION(EXT_discard_rectangles),
    MAGMA_CHECK_EXTENSION(EXT_display_control),
    MAGMA_CHECK_EXTENSION(EXT_display_surface_counter),
    MAGMA_CHECK_EXTENSION(EXT_dynamic_rendering_unused_attachments),
    MAGMA_CHECK_EXTENSION(EXT_extended_dynamic_state),
    MAGMA_CHECK_EXTENSION(EXT_extended_dynamic_state2),
    MAGMA_CHECK_EXTENSION(EXT_extended_dynamic_state3),
    MAGMA_CHECK_EXTENSION(EXT_external_memory_acquire_unmodified),
    MAGMA_CHECK_EXTENSION(EXT_external_memory_dma_buf),
    MAGMA_CHECK_EXTENSION(EXT_external_memory_host),
    MAGMA_CHECK_EXTENSION(EXT_filter_cubic),
    MAGMA_CHECK_EXTENSION(EXT_fragment_density_map),
    MAGMA_CHECK_EXTENSION(EXT_fragment_density_map2),
    MAGMA_CHECK_EXTENSION(EXT_fragment_shader_interlock),
    MAGMA_CHECK_EXTENSION(EXT_full_screen_exclusive),
    MAGMA_CHECK_EXTENSION(EXT_global_priority),
    MAGMA_CHECK_EXTENSION(EXT_global_priority_query),
    MAGMA_CHECK_EXTENSION(EXT_graphics_pipeline_library),
    MAGMA_CHECK_EXTENSION(EXT_hdr_metadata),
    MAGMA_CHECK_EXTENSION(EXT_headless_surface),
    MAGMA_CHECK_EXTENSION(EXT_host_image_copy),
    MAGMA_CHECK_EXTENSION(EXT_host_query_reset),
    MAGMA_CHECK_EXTENSION(EXT_image_2d_view_of_3d),
    MAGMA_CHECK_EXTENSION(EXT_image_compression_control),
    MAGMA_CHECK_EXTENSION(EXT_image_compression_control_swapchain),
    MAGMA_CHECK_EXTENSION(EXT_image_drm_format_modifier),
    MAGMA_CHECK_EXTENSION(EXT_image_robustness),
    MAGMA_CHECK_EXTENSION(EXT_image_view_min_lod),
    MAGMA_CHECK_EXTENSION(EXT_index_type_uint8),
    MAGMA_CHECK_EXTENSION(EXT_inline_uniform_block),
    MAGMA_CHECK_EXTENSION(EXT_legacy_dithering),
    MAGMA_CHECK_EXTENSION(EXT_line_rasterization),
    MAGMA_CHECK_EXTENSION(EXT_load_store_op_none),
    MAGMA_CHECK_EXTENSION(EXT_memory_budget),
    MAGMA_CHECK_EXTENSION(EXT_memory_priority),
    MAGMA_CHECK_EXTENSION(EXT_mesh_shader),
    MAGMA_CHECK_EXTENSION(EXT_metal_objects),
    MAGMA_CHECK_EXTENSION(EXT_multi_draw),
    MAGMA_CHECK_EXTENSION(EXT_multisampled_render_to_single_sampled),
    MAGMA_CHECK_EXTENSION(EXT_mutable_descriptor_type),
    MAGMA_CHECK_EXTENSION(EXT_non_seamless_cube_map),
    MAGMA_CHECK_EXTENSION(EXT_opacity_micromap),
    MAGMA_CHECK_EXTENSION(EXT_pageable_device_local_memory),
    MAGMA_CHECK_EXTENSION(EXT_pci_bus_info),
    MAGMA_CHECK_EXTENSION(EXT_physical_device_drm),
    MAGMA_CHECK_EXTENSION(EXT_pipeline_creation_cache_control),
    MAGMA_CHECK_EXTENSION(EXT_pipeline_creation_feedback),
    MAGMA_CHECK_EXTENSION(EXT_pipeline_properties),
    MAGMA_CHECK_EXTENSION(EXT_pipeline_protected_access),
    MAGMA_CHECK_EXTENSION(EXT_pipeline_robustness),
    MAGMA_CHECK_EXTENSION(EXT_post_depth_coverage),
    MAGMA_CHECK_EXTENSION(EXT_primitive_topology_list_restart),
    MAGMA_CHECK_EXTENSION(EXT_primitives_generated_query),
    MAGMA_CHECK_EXTENSION(EXT_private_data),
    MAGMA_CHECK_EXTENSION(EXT_provoking_vertex),
    MAGMA_CHECK_EXTENSION(EXT_queue_family_foreign),
    MAGMA_CHECK_EXTENSION(EXT_rasterization_order_attachment_access),
    MAGMA_CHECK_EXTENSION(EXT_rgba10x6_formats),
    MAGMA_CHECK_EXTENSION(EXT_robustness2),
    MAGMA_CHECK_EXTENSION(EXT_sample_locations),
    MAGMA_CHECK_EXTENSION(EXT_sampler_filter_minmax),
    MAGMA_CHECK_EXTENSION(EXT_scalar_block_layout),
    MAGMA_CHECK_EXTENSION(EXT_separate_stencil_usage),
    MAGMA_CHECK_EXTENSION(EXT_shader_atomic_float),
    MAGMA_CHECK_EXTENSION(EXT_shader_atomic_float2),
    MAGMA_CHECK_EXTENSION(EXT_shader_demote_to_helper_invocation),
    MAGMA_CHECK_EXTENSION(EXT_shader_image_atomic_int64),
    MAGMA_CHECK_EXTENSION(EXT_shader_module_identifier),
    MAGMA_CHECK_EXTENSION(EXT_shader_object),
    MAGMA_CHECK_EXTENSION(EXT_shader_stencil_export),
    MAGMA_CHECK_EXTENSION(EXT_shader_subgroup_ballot),
    MAGMA_CHECK_EXTENSION(EXT_shader_subgroup_vote),
    MAGMA_CHECK_EXTENSION(EXT_shader_tile_image),
    MAGMA_CHECK_EXTENSION(EXT_shader_viewport_index_layer),
    MAGMA_CHECK_EXTENSION(EXT_subgroup_size_control),
    MAGMA_CHECK_EXTENSION(EXT_subpass_merge_feedback),
    MAGMA_CHECK_EXTENSION(EXT_swapchain_maintenance1),
    MAGMA_CHECK_EXTENSION(EXT_texel_buffer_alignment),
    MAGMA_CHECK_EXTENSION(EXT_texture_compression_astc_hdr),
    MAGMA_CHECK_EXTENSION(EXT_tooling_info),
    MAGMA_CHECK_EXTENSION(EXT_transform_feedback),
    MAGMA_CHECK_EXTENSION(EXT_validation_cache),
    MAGMA_CHECK_EXTENSION(EXT_validation_features),
    MAGMA_CHECK_EXTENSION(EXT_validation_flags),
    MAGMA_CHECK_EXTENSION(EXT_vertex_attribute_divisor),
    MAGMA_CHECK_EXTENSION(EXT_vertex_input_dynamic_state),
    MAGMA_CHECK_EXTENSION(EXT_video_decode_h264),
    MAGMA_CHECK_EXTENSION(EXT_video_decode_h265),
    MAGMA_CHECK_EXTENSION(EXT_video_encode_h264),
    MAGMA_CHECK_EXTENSION(EXT_video_encode_h265),
    MAGMA_CHECK_EXTENSION(EXT_ycbcr_2plane_444_formats),
    MAGMA_CHECK_EXTENSION(EXT_ycbcr_image_arrays),

    MAGMA_CHECK_EXTENSION(FUCHSIA_buffer_collection),
    MAGMA_CHECK_EXTENSION(FUCHSIA_external_memory),
    MAGMA_CHECK_EXTENSION(FUCHSIA_external_semaphore),

    MAGMA_CHECK_EXTENSION(GGP_frame_token),

    MAGMA_CHECK_EXTENSION(GOOGLE_decorate_string),
    MAGMA_CHECK_EXTENSION(GOOGLE_display_timing),
    MAGMA_CHECK_EXTENSION(GOOGLE_hlsl_functionality1),
    MAGMA_CHECK_EXTENSION(GOOGLE_user_type),

    MAGMA_CHECK_EXTENSION(HUAWEI_cluster_culling_shader),
    MAGMA_CHECK_EXTENSION(HUAWEI_subpass_shading),
    MAGMA_CHECK_EXTENSION(HUAWEI_invocation_mask),

    MAGMA_CHECK_EXTENSION(IMG_filter_cubic),
    MAGMA_CHECK_EXTENSION(IMG_format_pvrtc),

    MAGMA_CHECK_EXTENSION(INTEL_performance_query),
    MAGMA_CHECK_EXTENSION(INTEL_shader_integer_functions2),

    MAGMA_CHECK_EXTENSION(KHR_16bit_storage),
    MAGMA_CHECK_EXTENSION(KHR_8bit_storage),
    MAGMA_CHECK_EXTENSION(KHR_acceleration_structure),
    MAGMA_CHECK_EXTENSION(KHR_bind_memory2),
    MAGMA_CHECK_EXTENSION(KHR_buffer_device_address),
    MAGMA_CHECK_EXTENSION(KHR_cooperative_matrix),
    MAGMA_CHECK_EXTENSION(KHR_copy_commands2),
    MAGMA_CHECK_EXTENSION(KHR_create_renderpass2),
    MAGMA_CHECK_EXTENSION(KHR_dedicated_allocation),
    MAGMA_CHECK_EXTENSION(KHR_deferred_host_operations),
    MAGMA_CHECK_EXTENSION(KHR_depth_stencil_resolve),
    MAGMA_CHECK_EXTENSION(KHR_descriptor_update_template),
    MAGMA_CHECK_EXTENSION(KHR_device_group),
    MAGMA_CHECK_EXTENSION(KHR_display_swapchain),
    MAGMA_CHECK_EXTENSION(KHR_draw_indirect_count),
    MAGMA_CHECK_EXTENSION(KHR_driver_properties),
    MAGMA_CHECK_EXTENSION(KHR_dynamic_rendering),
    MAGMA_CHECK_EXTENSION(KHR_external_fence),
    MAGMA_CHECK_EXTENSION(KHR_external_fence_fd),
    MAGMA_CHECK_EXTENSION(KHR_external_fence_win32),
    MAGMA_CHECK_EXTENSION(KHR_external_memory),
    MAGMA_CHECK_EXTENSION(KHR_external_memory_fd),
    MAGMA_CHECK_EXTENSION(KHR_external_memory_win32),
    MAGMA_CHECK_EXTENSION(KHR_external_semaphore),
    MAGMA_CHECK_EXTENSION(KHR_external_semaphore_fd),
    MAGMA_CHECK_EXTENSION(KHR_external_semaphore_win32),
    MAGMA_CHECK_EXTENSION(KHR_format_feature_flags2),
    MAGMA_CHECK_EXTENSION(KHR_fragment_shader_barycentric),
    MAGMA_CHECK_EXTENSION(KHR_fragment_shading_rate),
    MAGMA_CHECK_EXTENSION(KHR_get_memory_requirements2),
    MAGMA_CHECK_EXTENSION(KHR_global_priority),
    MAGMA_CHECK_EXTENSION(KHR_image_format_list),
    MAGMA_CHECK_EXTENSION(KHR_imageless_framebuffer),
    MAGMA_CHECK_EXTENSION(KHR_incremental_present),
    MAGMA_CHECK_EXTENSION(KHR_maintenance1),
    MAGMA_CHECK_EXTENSION(KHR_maintenance2),
    MAGMA_CHECK_EXTENSION(KHR_maintenance3),
    MAGMA_CHECK_EXTENSION(KHR_maintenance4),
    MAGMA_CHECK_EXTENSION(KHR_maintenance5),
    MAGMA_CHECK_EXTENSION(KHR_map_memory2),
    MAGMA_CHECK_EXTENSION(KHR_multiview),
    MAGMA_CHECK_EXTENSION(KHR_performance_query),
    MAGMA_CHECK_EXTENSION(KHR_pipeline_executable_properties),
    MAGMA_CHECK_EXTENSION(KHR_pipeline_library),
    MAGMA_CHECK_EXTENSION(KHR_portability_enumeration),
    MAGMA_CHECK_EXTENSION(KHR_portability_subset),
    MAGMA_CHECK_EXTENSION(KHR_present_id),
    MAGMA_CHECK_EXTENSION(KHR_present_wait),
    MAGMA_CHECK_EXTENSION(KHR_push_descriptor),
    MAGMA_CHECK_EXTENSION(KHR_ray_query),
    MAGMA_CHECK_EXTENSION(KHR_ray_tracing_maintenance1),
    MAGMA_CHECK_EXTENSION(KHR_ray_tracing_pipeline),
    MAGMA_CHECK_EXTENSION(KHR_ray_tracing_position_fetch),
    MAGMA_CHECK_EXTENSION(KHR_relaxed_block_layout),
    MAGMA_CHECK_EXTENSION(KHR_sampler_mirror_clamp_to_edge),
    MAGMA_CHECK_EXTENSION(KHR_sampler_ycbcr_conversion),
    MAGMA_CHECK_EXTENSION(KHR_separate_depth_stencil_layouts),
    MAGMA_CHECK_EXTENSION(KHR_shader_atomic_int64),
    MAGMA_CHECK_EXTENSION(KHR_shader_clock),
    MAGMA_CHECK_EXTENSION(KHR_shader_draw_parameters),
    MAGMA_CHECK_EXTENSION(KHR_shader_float16_int8),
    MAGMA_CHECK_EXTENSION(KHR_shader_float_controls),
    MAGMA_CHECK_EXTENSION(KHR_shader_integer_dot_product),
    MAGMA_CHECK_EXTENSION(KHR_shader_non_semantic_info),
    MAGMA_CHECK_EXTENSION(KHR_shader_subgroup_extended_types),
    MAGMA_CHECK_EXTENSION(KHR_shader_subgroup_uniform_control_flow),
    MAGMA_CHECK_EXTENSION(KHR_shader_terminate_invocation),
    MAGMA_CHECK_EXTENSION(KHR_shared_presentable_image),
    MAGMA_CHECK_EXTENSION(KHR_spirv_1_4),
    MAGMA_CHECK_EXTENSION(KHR_storage_buffer_storage_class),
    MAGMA_CHECK_EXTENSION(KHR_swapchain),
    MAGMA_CHECK_EXTENSION(KHR_swapchain_mutable_format),
    MAGMA_CHECK_EXTENSION(KHR_synchronization2),
    MAGMA_CHECK_EXTENSION(KHR_timeline_semaphore),
    MAGMA_CHECK_EXTENSION(KHR_uniform_buffer_standard_layout),
    MAGMA_CHECK_EXTENSION(KHR_variable_pointers),
    MAGMA_CHECK_EXTENSION(KHR_video_decode_h264),
    MAGMA_CHECK_EXTENSION(KHR_video_decode_h265),
    MAGMA_CHECK_EXTENSION(KHR_video_decode_queue),
    MAGMA_CHECK_EXTENSION(KHR_video_encode_queue),
    MAGMA_CHECK_EXTENSION(KHR_video_queue),
    MAGMA_CHECK_EXTENSION(KHR_vulkan_memory_model),
    MAGMA_CHECK_EXTENSION(KHR_win32_keyed_mutex),
    MAGMA_CHECK_EXTENSION(KHR_workgroup_memory_explicit_layout),
    MAGMA_CHECK_EXTENSION(KHR_zero_initialize_workgroup_memory),

    MAGMA_CHECK_EXTENSION(SEC_amigo_profiling),

    MAGMA_CHECK_EXTENSION(NV_acquire_winrt_display),
    MAGMA_CHECK_EXTENSION(NV_clip_space_w_scaling),
    MAGMA_CHECK_EXTENSION(NV_compute_shader_derivatives),
    MAGMA_CHECK_EXTENSION(NV_cooperative_matrix),
    MAGMA_CHECK_EXTENSION(NV_copy_memory_indirect),
    MAGMA_CHECK_EXTENSION(NV_corner_sampled_image),
    MAGMA_CHECK_EXTENSION(NV_coverage_reduction_mode),
    MAGMA_CHECK_EXTENSION(NV_cuda_kernel_launch),
    MAGMA_CHECK_EXTENSION(NV_dedicated_allocation),
    MAGMA_CHECK_EXTENSION(NV_dedicated_allocation_image_aliasing),
    MAGMA_CHECK_EXTENSION(NV_device_diagnostic_checkpoints),
    MAGMA_CHECK_EXTENSION(NV_device_diagnostics_config),
    MAGMA_CHECK_EXTENSION(NV_device_generated_commands),
    MAGMA_CHECK_EXTENSION(NV_external_memory),
    MAGMA_CHECK_EXTENSION(NV_external_memory_capabilities),
    MAGMA_CHECK_EXTENSION(NV_external_memory_rdma),
    MAGMA_CHECK_EXTENSION(NV_external_memory_win32),
    MAGMA_CHECK_EXTENSION(NV_fill_rectangle),
    MAGMA_CHECK_EXTENSION(NV_fragment_coverage_to_color),
    MAGMA_CHECK_EXTENSION(NV_fragment_shader_barycentric),
    MAGMA_CHECK_EXTENSION(NV_fragment_shading_rate_enums),
    MAGMA_CHECK_EXTENSION(NV_framebuffer_mixed_samples),
    MAGMA_CHECK_EXTENSION(NV_geometry_shader_passthrough),
    MAGMA_CHECK_EXTENSION(NV_glsl_shader),
    MAGMA_CHECK_EXTENSION(NV_inherited_viewport_scissor),
    MAGMA_CHECK_EXTENSION(NV_linear_color_attachment),
    MAGMA_CHECK_EXTENSION(NV_memory_decompression),
    MAGMA_CHECK_EXTENSION(NV_mesh_shader),
    MAGMA_CHECK_EXTENSION(NV_optical_flow),
    MAGMA_CHECK_EXTENSION(NV_present_barrier),
    MAGMA_CHECK_EXTENSION(NV_ray_tracing),
    MAGMA_CHECK_EXTENSION(NV_ray_tracing_invocation_reorder),
    MAGMA_CHECK_EXTENSION(NV_ray_tracing_motion_blur),
    MAGMA_CHECK_EXTENSION(NV_representative_fragment_test),
    MAGMA_CHECK_EXTENSION(NV_sample_mask_override_coverage),
    MAGMA_CHECK_EXTENSION(NV_scissor_exclusive),
    MAGMA_CHECK_EXTENSION(NV_shader_image_footprint),
    MAGMA_CHECK_EXTENSION(NV_shader_sm_builtins),
    MAGMA_CHECK_EXTENSION(NV_shader_subgroup_partitioned),
    MAGMA_CHECK_EXTENSION(NV_shading_rate_image),
    MAGMA_CHECK_EXTENSION(NV_viewport_array2),
    MAGMA_CHECK_EXTENSION(NV_viewport_swizzle),
    MAGMA_CHECK_EXTENSION(NV_win32_keyed_mutex),

    MAGMA_CHECK_EXTENSION(NVX_binary_import),
    MAGMA_CHECK_EXTENSION(NVX_device_generated_commands),
    MAGMA_CHECK_EXTENSION(NVX_display_timing),
    MAGMA_CHECK_EXTENSION(NVX_image_clear_padding),
    MAGMA_CHECK_EXTENSION(NVX_image_view_handle),
    MAGMA_CHECK_EXTENSION(NVX_multiview_per_view_attributes),
    MAGMA_CHECK_EXTENSION(NVX_raytracing),

    MAGMA_CHECK_EXTENSION(QCOM_fragment_density_map_offset),
    MAGMA_CHECK_EXTENSION(QCOM_image_processing),
    MAGMA_CHECK_EXTENSION(QCOM_multiview_per_view_render_areas),
    MAGMA_CHECK_EXTENSION(QCOM_multiview_per_view_viewports),
    MAGMA_CHECK_EXTENSION(QCOM_render_pass_shader_resolve),
    MAGMA_CHECK_EXTENSION(QCOM_render_pass_store_ops),
    MAGMA_CHECK_EXTENSION(QCOM_render_pass_transform),
    MAGMA_CHECK_EXTENSION(QCOM_rotated_copy_commands),
    MAGMA_CHECK_EXTENSION(QCOM_tile_properties),

    MAGMA_CHECK_EXTENSION(QNX_external_memory_screen_buffer),

    MAGMA_CHECK_EXTENSION(VALVE_descriptor_set_host_mapping),
    MAGMA_CHECK_EXTENSION(VALVE_mutable_descriptor_type)
{}
} // namespace magma
