#ifndef GODOTJS_CONFIG_H
#define GODOTJS_CONFIG_H

#ifndef JSB_DEBUG
#   if defined(DEBUG_ENABLED)
#       define JSB_DEBUG 1
#   else
#       define JSB_DEBUG 0
#   endif
#endif

// lower log levels are completely skipped (at compile-time)
// see `internal/jsb_log_severity.def.h`
#ifndef JSB_MIN_LOG_LEVEL
#   if JSB_DEBUG
#       define JSB_MIN_LOG_LEVEL Verbose
#   else
#       define JSB_MIN_LOG_LEVEL Warning
#   endif
#endif // JSB_MIN_LOG_LEVEL

// enable jsb_check
#ifndef JSB_WITH_CHECK
#define JSB_WITH_CHECK JSB_DEBUG
#endif

// print benchmark
#define JSB_BENCHMARK 1

// Check if the type of `p_pointer` is really NativeClassType::GodotObject.
#define JSB_VERIFY_GODOT_OBJECT 1

// enable `RequestGarbageCollectionForTesting`
#define JSB_EXPOSE_GC_FOR_TESTING 0

// only for debug, print gc time
#define JSB_PRINT_GC_TIME 1

#define JSB_SUPPORT_RELOAD 1

// translate the js source stacktrace with source map (currectly, the `.map` file must locate at the same filename & directory of the js source)
#define JSB_WITH_SOURCEMAP 1

// log with [source filename, line number, function name]
#define JSB_LOG_WITH_SOURCE 0

// use a pool allocator for creating variant instances
#define JSB_WITH_VARIANT_POOL 1

// construct a Variant with `Variant::construct` instead of `VariantUtilityFunctions::type_convert`
#define JSB_CONSTRUCT_DEFAULT_VARIANT_SLOW 0

// NOT IMPLEMENTED YET
#define JSB_WITH_STATIC_BINDINGS 0

// [EXPERIMENTAL] use optimized wrapper function calls if possible
#define JSB_FAST_REFLECTION 1

// implicitly convert a javascript array as godot Vector<T> which is convenient but less performant if massively used
#define JSB_IMPLICIT_PACKED_ARRAY_CONVERSION 1

// not to generate method declaration if already defined as get/set property
#define JSB_EXCLUDE_GETSET_METHODS 1

#define JSB_INITIAL_OBJECT_SLOTS (1024 * 64)
#define JSB_INITIAL_SCRIPT_SLOTS 1024
#define JSB_INITIAL_CLASS_EXTRA_SLOTS 0
#define JSB_VARIANT_DELETION_QUEUE_SIZE (1024 * 16)

#define JSB_TYPESCRIPT_EXT "ts"
#define JSB_JAVASCRIPT_EXT "js"

#define JSB_BUNDLE_VERSION 2

#endif
