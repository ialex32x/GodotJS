#ifndef GODOTJS_CONFIG_H
#define GODOTJS_CONFIG_H

#ifdef DEV_ENABLED
// jsb_check is only evaluated when `JSB_DEBUG` is true
#   define JSB_DEBUG 1
#else
#   define JSB_DEBUG 0
#endif

//TODO for unknown reason, gc scavenger doesn't work actively as expected
// enable `RequestGarbageCollectionForTesting`
#define JSB_EXPOSE_GC_FOR_TESTING 0

// only for debug, print gc time
#define JSB_PRINT_GC_TIME 1

#if DEV_ENABLED
// lower log levels are completely skipped (at compile-time)
#   define JSB_MIN_LOG_LEVEL Verbose
#else
#   define JSB_MIN_LOG_LEVEL Warning
#endif

// print benchmark
#define JSB_BENCHMARK 1

// enable to debug with Chrome devtools with the following link by default:
// devtools://devtools/bundled/inspector.html?experiments=true&v8only=true&ws=127.0.0.1:9229/1
#define JSB_WITH_DEBUGGER 1

// translate the js source stacktrace with source map (currectly, the `.map` file must locate at the same filename & directory of the js source)
#define JSB_WITH_SOURCEMAP 1

// enable this to let all methods in `console` print with js stacktrace
#define JSB_WITH_STACKTRACE_ALWAYS 0

// JSB_WITH_LWS must be enabled if JSB_WITH_DEBUGGER is used.
// currently use `libwebsockets` to handle v8 debugger connection since `modules/websocket` fail to handshake with `devtools`
// `devtools` do not response the upgrade request with a `sec-websocket-protocol` header which does not apply the handshake requirements of `WSLPeer`
// and the connection will break immediately by `devtools` if `selected_protocol` is assigned manually in `WSLPeer`
#define JSB_WITH_LWS 1

// log with [source filename, line number, function name]
#define JSB_LOG_WITH_SOURCE 0

// use a pool allocator for creating variant instances
#define JSB_WITH_VARIANT_POOL 1

// construct a Variant with `Variant::construct` instead of `VariantUtilityFunctions::type_convert`
#define JSB_CONSTRUCT_DEFAULT_VARIANT_SLOW 0

//TODO not implemented yet
#define JSB_WITH_STATIC_PRIMITIVE_TYPE_BINDINGS 0

// implicitly convert a javascript array as godot Vector<T> which is convenient but less performant if massively used
#define JSB_IMPLICIT_PACKED_ARRAY_CONVERSION 1

#endif
