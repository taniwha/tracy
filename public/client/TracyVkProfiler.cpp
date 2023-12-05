#ifdef TRACY_ENABLE

#ifdef _WIN32
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif
#  include <winsock2.h>
#  include <windows.h>
#  include <tlhelp32.h>
#  include <inttypes.h>
#  include <intrin.h>
#  include "../common/TracyUwp.hpp"
#else
#  include <sys/time.h>
#  include <sys/param.h>
#endif

#ifdef _GNU_SOURCE
#  include <errno.h>
#endif

#ifdef __linux__
#  include <dirent.h>
#  include <pthread.h>
#  include <sys/types.h>
#  include <sys/syscall.h>
#endif

#if defined __APPLE__ || defined BSD
#  include <sys/types.h>
#  include <sys/sysctl.h>
#endif

#if defined __APPLE__
#  include "TargetConditionals.h"
#  include <mach-o/dyld.h>
#endif

#ifdef __ANDROID__
#  include <sys/mman.h>
#  include <sys/system_properties.h>
#  include <stdio.h>
#  include <stdint.h>
#  include <algorithm>
#  include <vector>
#endif

#ifdef __QNX__
#  include <stdint.h>
#  include <stdio.h>
#  include <string.h>
#  include <sys/syspage.h>
#  include <sys/stat.h>
#endif

#include <algorithm>
#include <assert.h>
#include <atomic>
#include <chrono>
#include <limits>
#include <new>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <thread>


#ifdef TRACY_VK_USE_SYMBOL_TABLE
#ifndef VK_NO_PROTOTYPES
#define VK_NO_PROTOTYPES
#endif
#endif
#include "vulkan/vulkan.h"

#include "../tracy/TracyVulkan.hpp"
#include "../tracy/TracyCVulkan.h"
#include "../tracy/TracyC.h"

namespace tracy
{
}

#ifdef __cplusplus
extern "C" {
#endif

___tracy_vkctx_scope *___tracy_vkctx_scope_new (___tracy_vkctx *c_ctx, const ___tracy_source_location_data *c_srcloc, VkCommandBuffer cmdbuf, int is_active)
{
	auto ctx = (tracy::VkCtx *) c_ctx;
	const auto srcloc = (const tracy::SourceLocationData *) c_srcloc;
	auto scope = new tracy::VkCtxScope (ctx, srcloc, cmdbuf, is_active);
	return (___tracy_vkctx_scope *) scope;
}

___tracy_vkctx_scope *___tracy_vkctx_scope_new_depth (___tracy_vkctx *c_ctx, const ___tracy_source_location_data *c_srcloc, VkCommandBuffer cmdbuf, int depth, int is_active)
{
	auto ctx = (tracy::VkCtx *) c_ctx;
	const auto srcloc = (const tracy::SourceLocationData *) c_srcloc;
	auto scope = new tracy::VkCtxScope (ctx, srcloc, cmdbuf, depth, is_active);
	return (___tracy_vkctx_scope *) scope;
}

___tracy_vkctx_scope *___tracy_vkctx_scope_new_src (___tracy_vkctx *c_ctx, uint32_t line, const char *source, size_t sourceSz, const char *function, size_t functionSz, const char *name, size_t nameSz, VkCommandBuffer cmdbuf, int is_active)
{
	auto ctx = (tracy::VkCtx *) c_ctx;
	auto scope = new tracy::VkCtxScope (ctx, line, source, sourceSz, function, functionSz, name, nameSz, cmdbuf, is_active);
	return (___tracy_vkctx_scope *) scope;
}

___tracy_vkctx_scope *___tracy_vkctx_scope_new_src_depth (___tracy_vkctx *c_ctx, uint32_t line, const char *source, size_t sourceSz, const char *function, size_t functionSz, const char *name, size_t nameSz, VkCommandBuffer cmdbuf, int depth, int is_active)
{
	auto ctx = (tracy::VkCtx *) c_ctx;
	auto scope = new tracy::VkCtxScope (ctx, line, source, sourceSz, function, functionSz, name, nameSz, cmdbuf, depth, is_active);
	return (___tracy_vkctx_scope *) scope;
}

void ___tracy_vkctx_scope_delete (___tracy_vkctx_scope *c_scope)
{
	auto scope = (tracy::VkCtxScope *) c_scope;
	delete scope;
}

#ifdef TRACY_VK_USE_SYMBOL_TABLE
___tracy_vkctx * ___tracy_vkctx_new (VkInstance instance, VkPhysicalDevice physdev, VkDevice device, VkQueue queue, VkCommandBuffer cmdbuf, PFN_vkGetInstanceProcAddr instanceProcAddr, PFN_vkGetDeviceProcAddr deviceProcAddr, bool calibrated)
{
	auto ctx = new tracy::VkCtx (instance, physdev, device, queue, cmdbuf, instanceProcAddr, deviceProcAddr, calibrated);
	return (___tracy_vkctx *) ctx;
}

#ifdef VK_EXT_host_query_reset
___tracy_vkctx * ___tracy_vkctx_new_host (VkInstance instance, VkPhysicalDevice physdev, VkDevice device, PFN_vkGetInstanceProcAddr instanceProcAddr, PFN_vkGetDeviceProcAddr deviceProcAddr)
{
	auto ctx = new tracy::VkCtx (instance, physdev, device, instanceProcAddr, deviceProcAddr);
	return (___tracy_vkctx *) ctx;
}
#endif
#else
___tracy_vkctx * ___tracy_vkctx_new (VkPhysicalDevice physdev, VkDevice device, VkQueue queue, VkCommandBuffer cmdbuf, PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT vkGetPhysicalDeviceCalibrateableTimeDomainsEXT, PFN_vkGetCalibratedTimestampsEXT vkGetCalibratedTimestampsEXT)
{
	auto ctx = new tracy::VkCtx (physdev, device, queue, cmdbuf, vkGetPhysicalDeviceCalibrateableTimeDomainsEXT, vkGetCalibratedTimestampsEXT);
	return (___tracy_vkctx *) ctx;
}

#ifdef VK_EXT_host_query_reset
___tracy_vkctx * ___tracy_vkctx_new_host (VkPhysicalDevice physdev, VkDevice device, PFN_vkResetQueryPoolEXT vkResetQueryPool, PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT vkGetPhysicalDeviceCalibrateableTimeDomainsEXT, PFN_vkGetCalibratedTimestampsEXT vkGetCalibratedTimestampsEXT)
{
	auto ctx = new tracy::VkCtx (physdev, device, vkResetQueryPool, vkGetPhysicalDeviceCalibrateableTimeDomainsEXT, vkGetCalibratedTimestampsEXT);
	return (___tracy_vkctx *) ctx;
}
#endif
#endif

void ___tracy_vkctx_delete (___tracy_vkctx *c_ctx)
{
	auto ctx = (tracy::VkCtx *) c_ctx;
	delete ctx;
}

void ___tracy_vkctx_name (___tracy_vkctx *c_ctx, const char *name, uint16_t len)
{
	auto ctx = (tracy::VkCtx *) c_ctx;
	ctx->Name (name, len);
}

void ___tracy_vkctx_collect (___tracy_vkctx *c_ctx, VkCommandBuffer cmdbuf)
{
	auto ctx = (tracy::VkCtx *) c_ctx;
	ctx->Collect (cmdbuf);
}

#ifdef __cplusplus
}
#endif

#endif
