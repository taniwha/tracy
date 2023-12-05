#ifdef TRACY_ENABLE

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ___tracy_vkctx ___tracy_vkctx;
typedef struct ___tracy_vkctx_scope ___tracy_vkctx_scope;

___tracy_vkctx_scope *___tracy_vkctx_scope_new (___tracy_vkctx *c_ctx, const struct ___tracy_source_location_data *c_srcloc, VkCommandBuffer cmdbuf, int is_active);

___tracy_vkctx_scope *___tracy_vkctx_scope_new_depth (___tracy_vkctx *c_ctx, const struct ___tracy_source_location_data *c_srcloc, VkCommandBuffer cmdbuf, int depth, int is_active);

___tracy_vkctx_scope *___tracy_vkctx_scope_new_src (___tracy_vkctx *c_ctx, uint32_t line, const char *source, size_t sourceSz, const char *function, size_t functionSz, const char *name, size_t nameSz, VkCommandBuffer cmdbuf, int is_active);

___tracy_vkctx_scope *___tracy_vkctx_scope_new_src_depth (___tracy_vkctx *c_ctx, uint32_t line, const char *source, size_t sourceSz, const char *function, size_t functionSz, const char *name, size_t nameSz, VkCommandBuffer cmdbuf, int depth, int is_active);

void ___tracy_vkctx_scope_delete (___tracy_vkctx_scope *c_scope);

#ifdef TRACY_VK_USE_SYMBOL_TABLE
___tracy_vkctx * ___tracy_vkctx_new (VkInstance instance, VkPhysicalDevice physdev, VkDevice device, VkQueue queue, VkCommandBuffer cmdbuf, PFN_vkGetInstanceProcAddr instanceProcAddr, PFN_vkGetDeviceProcAddr deviceProcAddr, bool calibrated);
#  ifdef VK_EXT_host_query_reset
___tracy_vkctx * ___tracy_vkctx_new_host (VkInstance instance, VkPhysicalDevice physdev, VkDevice device, PFN_vkGetInstanceProcAddr instanceProcAddr, PFN_vkGetDeviceProcAddr deviceProcAddr);
#  endif
#else
___tracy_vkctx * ___tracy_vkctx_new (VkPhysicalDevice physdev, VkDevice device, VkQueue queue, VkCommandBuffer cmdbuf, PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT vkGetPhysicalDeviceCalibrateableTimeDomainsEXT, PFN_vkGetCalibratedTimestampsEXT vkGetCalibratedTimestampsEXT);
#  ifdef VK_EXT_host_query_reset
___tracy_vkctx * ___tracy_vkctx_new_host (VkPhysicalDevice physdev, VkDevice device, PFN_vkResetQueryPoolEXT vkResetQueryPool, PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT vkGetPhysicalDeviceCalibrateableTimeDomainsEXT, PFN_vkGetCalibratedTimestampsEXT vkGetCalibratedTimestampsEXT);
#  endif
#endif

void ___tracy_vkctx_delete (___tracy_vkctx *c_ctx);
void ___tracy_vkctx_name (___tracy_vkctx *c_ctx, const char *name, uint16_t len);
void ___tracy_vkctx_collect (___tracy_vkctx *c_ctx, VkCommandBuffer cmdbuf);

#ifdef __cplusplus
}
#endif

#if defined TRACY_VK_USE_SYMBOL_TABLE
#define TracyCVkContext( instance, physdev, device, queue, cmdbuf, instanceProcAddr, deviceProcAddr ) ___tracy_vkctx_new( instance, physdev, device, queue, cmdbuf, instanceProcAddr, deviceProcAddr );
#else
#define TracyCVkContext( physdev, device, queue, cmdbuf ) ___tracy_vkctx_new( physdev, device, queue, cmdbuf, nullptr, nullptr );
#endif
#if defined TRACY_VK_USE_SYMBOL_TABLE
#define TracyCVkContextCalibrated( instance, physdev, device, queue, cmdbuf, instanceProcAddr, deviceProcAddr ) ___tracy_vkctx_new( instance, physdev, device, queue, cmdbuf, instanceProcAddr, deviceProcAddr, true );
#else
#define TracyCVkContextCalibrated( physdev, device, queue, cmdbuf, gpdctd, gct ) ___tracy_vkctx_new( physdev, device, queue, cmdbuf, gpdctd, gct );
#endif
#if defined VK_EXT_host_query_reset
#if defined TRACY_VK_USE_SYMBOL_TABLE
#define TracyCVkContextHostCalibrated( instance, physdev, device, instanceProcAddr, deviceProcAddr ) ___tracy_vkctx_new_host( instance, physdev, device, instanceProcAddr, deviceProcAddr );
#else
#define TracyCVkContextHostCalibrated( physdev, device, qpreset, gpdctd, gct ) ___tracy_vkctx_new_host( physdev, device, qpreset, gpdctd, gct );
#endif
#endif
#define TracyCVkDestroy( ctx ) ___tracy_vkctx_delete( ctx );
#define TracyCVkContextName( ctx, name, size ) ___tracy_vkctx_name( ctx, name, size );
#if defined TRACY_HAS_CALLSTACK && defined TRACY_CALLSTACK
#  define TracyCVkNamedZone( ctx, varname, cmdbuf, name, active ) static const struct ___tracy_source_location_data TracyConcat(___tracy_gpu_source_location,TracyLine) = { name, TracyFunction,  TracyFile, (uint32_t)TracyLine, 0 }; ___tracy_vkctx_scope *varname = ___tracy_vkctx_scope_new( ctx, &TracyConcat(___tracy_gpu_source_location,TracyLine), cmdbuf, TRACY_CALLSTACK, active );
#  define TracyCVkNamedZoneC( ctx, varname, cmdbuf, name, color, active ) static const struct ___tracy_source_location_data TracyConcat(___tracy_gpu_source_location,TracyLine) = { name, TracyFunction,  TracyFile, (uint32_t)TracyLine, color }; ___tracy_vkctx_scope *varname = ___tracy_vkctx_scope_new( ctx, &TracyConcat(___tracy_gpu_source_location,TracyLine), cmdbuf, TRACY_CALLSTACK, active );
#  define TracyCVkZone( ctx, cmdbuf, name ) TracyCVkNamedZoneS( ctx, ___tracy_gpu_zone, cmdbuf, name, TRACY_CALLSTACK, true )
#  define TracyCVkZoneC( ctx, cmdbuf, name, color ) TracyCVkNamedZoneCS( ctx, ___tracy_gpu_zone, cmdbuf, name, color, TRACY_CALLSTACK, true )
#  define TracyCVkZoneTransient( ctx, varname, cmdbuf, name, active ) TracyCVkZoneTransientS( ctx, varname, cmdbuf, name, TRACY_CALLSTACK, active )
#else
#  define TracyCVkNamedZone( ctx, varname, cmdbuf, name, active ) static const struct ___tracy_source_location_data TracyConcat(___tracy_gpu_source_location,TracyLine) = { name, TracyFunction,  TracyFile, (uint32_t)TracyLine, 0 }; ___tracy_vkctx_scope *varname = ___tracy_vkctx_scope_new( ctx, &TracyConcat(___tracy_gpu_source_location,TracyLine), cmdbuf, active );
#  define TracyCVkNamedZoneC( ctx, varname, cmdbuf, name, color, active ) static const struct ___tracy_source_location_data TracyConcat(___tracy_gpu_source_location,TracyLine) = { name, TracyFunction,  TracyFile, (uint32_t)TracyLine, color }; ___tracy_vkctx_scope *varname = ___tracy_vkctx_scope_new( ctx, &TracyConcat(___tracy_gpu_source_location,TracyLine), cmdbuf, active );
#  define TracyCVkZone( ctx, cmdbuf, name ) TracyCVkNamedZone( ctx, ___tracy_gpu_zone, cmdbuf, name, true )
#  define TracyCVkZoneC( ctx, cmdbuf, name, color ) TracyCVkNamedZoneC( ctx, ___tracy_gpu_zone, cmdbuf, name, color, true )
#  define TracyCVkZoneTransient( ctx, varname, cmdbuf, name, active ) ___tracy_vkctx_scope *varname = ___tracy_vkctx_scope_new_src( ctx, TracyLine, TracyFile, strlen( TracyFile ), TracyFunction, strlen( TracyFunction ), name, strlen( name ), cmdbuf, active );
#endif
#define TracyCVkCollect( ctx, cmdbuf ) ___tracy_vkctx_collect( ctx, cmdbuf );

#ifdef TRACY_HAS_CALLSTACK
#  define TracyCVkNamedZoneS( ctx, varname, cmdbuf, name, depth, active ) static const struct ___tracy_source_location_data TracyConcat(___tracy_gpu_source_location,TracyLine) = { name, TracyFunction,  TracyFile, (uint32_t)TracyLine, 0 }; ___tracy_vkctx_scope *varname = ___tracy_vkctx_scope_new_depth( ctx, &TracyConcat(___tracy_gpu_source_location,TracyLine), cmdbuf, depth, active );
#  define TracyCVkNamedZoneCS( ctx, varname, cmdbuf, name, color, depth, active ) static const struct ___tracy_source_location_data TracyConcat(___tracy_gpu_source_location,TracyLine) = { name, TracyFunction,  TracyFile, (uint32_t)TracyLine, color }; ___tracy_vkctx_scope *varname = ___tracy_vkctx_scope_new_depth( ctx, &TracyConcat(___tracy_gpu_source_location,TracyLine), cmdbuf, depth, active );
#  define TracyCVkZoneS( ctx, cmdbuf, name, depth ) TracyCVkNamedZoneS( ctx, ___tracy_gpu_zone, cmdbuf, name, depth, true )
#  define TracyCVkZoneCS( ctx, cmdbuf, name, color, depth ) TracyCVkNamedZoneCS( ctx, ___tracy_gpu_zone, cmdbuf, name, color, depth, true )
#  define TracyCVkZoneTransientS( ctx, varname, cmdbuf, name, depth, active ) ___tracy_vkctx_scope *varname = ___tracy_vkctx_scope_new_src_depth( ctx, TracyLine, TracyFile, strlen( TracyFile ), TracyFunction, strlen( TracyFunction ), name, strlen( name ), cmdbuf, depth, active );
#else
#  define TracyCVkNamedZoneS( ctx, varname, cmdbuf, name, depth, active ) TracyCVkNamedZone( ctx, varname, cmdbuf, name, active )
#  define TracyCVkNamedZoneCS( ctx, varname, cmdbuf, name, color, depth, active ) TracyCVkNamedZoneC( ctx, varname, cmdbuf, name, color, active )
#  define TracyCVkZoneS( ctx, cmdbuf, name, depth ) TracyCVkZone( ctx, cmdbuf, name )
#  define TracyCVkZoneCS( ctx, cmdbuf, name, color, depth ) TracyCVkZoneC( ctx, cmdbuf, name, color )
#  define TracyCVkZoneTransientS( ctx, varname, cmdbuf, name, depth, active ) TracyCVkZoneTransient( ctx, varname, cmdbuf, name, active )
#endif

#define TracyCVkZoneEnd( ctx ) ___tracy_vkctx_scope_delete( ctx );

#else

#if defined TRACY_VK_USE_SYMBOL_TABLE
#define TracyCVkContext( instance, physdev, device, queue, cmdbuf, instanceProcAddr, deviceProcAddr )
#else
#define TracyCVkContext( physdev, device, queue, cmdbuf )
#endif

#if defined TRACY_VK_USE_SYMBOL_TABLE
#define TracyCVkContextCalibrated( instance, physdev, device, queue, cmdbuf, instanceProcAddr, deviceProcAddr )
#else
#define TracyCVkContextCalibrated( physdev, device, queue, cmdbuf, gpdctd, gct )
#endif

#if defined VK_EXT_host_query_reset
#if defined TRACY_VK_USE_SYMBOL_TABLE
#define TracyCVkContextHostCalibrated( instance, physdev, device, instanceProcAddr, deviceProcAddr )
#else
#define TracyCVkContextHostCalibrated( physdev, device, qpreset, gpdctd, gct )
#endif
#endif
#define TracyCVkDestroy( ctx )
#define TracyCVkContextName( ctx, name, size )
#define TracyCVkNamedZone( ctx, varname, cmdbuf, name, active )
#define TracyCVkNamedZoneC( ctx, varname, cmdbuf, name, color, active )
#define TracyCVkZone( ctx, cmdbuf, name )
#define TracyCVkZoneC( ctx, cmdbuf, name, color )
#define TracyCVkZoneTransient( ctx, varname, cmdbuf, name, active )
#define TracyCVkCollect( ctx, cmdbuf )

#define TracyCVkNamedZoneS( ctx, varname, cmdbuf, name, depth, active )
#define TracyCVkNamedZoneCS( ctx, varname, cmdbuf, name, color, depth, active )
#define TracyCVkZoneS( ctx, cmdbuf, name, depth )
#define TracyCVkZoneCS( ctx, cmdbuf, name, color, depth )
#define TracyCVkZoneTransientS( ctx, varname, cmdbuf, name, depth, active )

#endif
