#ifndef GODOTJS_WEB_INTEROP_H
#define GODOTJS_WEB_INTEROP_H

#include "jsb_web_stub_types.h"

#ifdef WEB_ENABLED
#include <emscripten/emscripten.h>
#endif

#ifdef __cplusplus
#define JSAPI_EXTERN extern "C"
#else
#define JSAPI_EXTERN
#endif

JSAPI_EXTERN void jsapi_init(void);
JSAPI_EXTERN int jsapi_create_engine(v8::Isolate* isolate);
JSAPI_EXTERN void jsapi_drop_engine(int engine_id);

// stack calls

JSAPI_EXTERN int jsapi_stack_enter(int engine_id);
JSAPI_EXTERN void jsapi_stack_exit(int engine_id);

// eval the code, return the stack position
JSAPI_EXTERN int jsapi_stack_push_global(int engine_id);
JSAPI_EXTERN int jsapi_stack_push_null(int engine_id);
JSAPI_EXTERN int jsapi_stack_push_symbol(int engine_id);
JSAPI_EXTERN int jsapi_stack_push_object(int engine_id);

JSAPI_EXTERN int jsapi_stack_push_pv(int engine_id, int pid);
JSAPI_EXTERN int jsapi_stack_push_boolean(int engine_id, bool value);
JSAPI_EXTERN int jsapi_stack_push_int(int engine_id, int32_t value);
JSAPI_EXTERN int jsapi_stack_push_number(int engine_id, double value);
JSAPI_EXTERN int jsapi_stack_push_string(int engine_id, const char* value);

// stack-based calls

JSAPI_EXTERN bool jsapi_sv_is_int32(int engine_id, int stack, int index);
JSAPI_EXTERN bool jsapi_sv_is_number(int engine_id, int stack, int index);
JSAPI_EXTERN bool jsapi_sv_is_boolean(int engine_id, int stack, int index);
JSAPI_EXTERN bool jsapi_sv_is_symbol(int engine_id, int stack, int index);
JSAPI_EXTERN bool jsapi_sv_is_array(int engine_id, int stack, int index);
JSAPI_EXTERN bool jsapi_sv_is_string(int engine_id, int stack, int index);
JSAPI_EXTERN bool jsapi_sv_is_bigint(int engine_id, int stack, int index);
JSAPI_EXTERN bool jsapi_sv_is_map(int engine_id, int stack, int index);
JSAPI_EXTERN bool jsapi_sv_is_undefined(int engine_id, int stack, int index);
JSAPI_EXTERN bool jsapi_sv_is_null(int engine_id, int stack, int index);
JSAPI_EXTERN bool jsapi_sv_is_function(int engine_id, int stack, int index);
JSAPI_EXTERN bool jsapi_sv_is_object(int engine_id, int stack, int index);
JSAPI_EXTERN bool jsapi_sv_is_promise(int engine_id, int stack, int index);
JSAPI_EXTERN bool jsapi_sv_is_array_buffer(int engine_id, int stack, int index);
JSAPI_EXTERN bool jsapi_sv_is_external(int engine_id, int stack, int index);

JSAPI_EXTERN int64_t jsapi_sv_to_integer(int engine_id, int stack, int index);
JSAPI_EXTERN const char* jsapi_sv_to_string(int engine_id, int stack, int index);

JSAPI_EXTERN void jsapi_sv_internal_set(int engine_id, int stack, int index, int slot, void* value);
JSAPI_EXTERN void* jsapi_sv_internal_get(int engine_id, int stack, int index, int slot);
JSAPI_EXTERN int jsapi_sv_internal_num(int engine_id, int stack, int index);

JSAPI_EXTERN int jsapi_sv_eval(int engine_id, int stack, int index);
JSAPI_EXTERN bool jsapi_sv_equals(int engine_id, int from_depth, int from_index, int to_depth, int to_index);
JSAPI_EXTERN void jsapi_sv_copy(int engine_id, int from_depth, int from_index, int to_depth, int to_index);

// persistent-based value calls

JSAPI_EXTERN int jsapi_pv_add(int engine_id, int stack, int index);
JSAPI_EXTERN void jsapi_pv_remove(int engine_id, int pid);
JSAPI_EXTERN void jsapi_pv_set_weak(int engine_id, int pid, void* cb, void* parameter);
JSAPI_EXTERN void jsapi_pv_clear_weak(int engine_id, int pid);
JSAPI_EXTERN void jsapi_pv_equals(int engine_id, int from_pid, int to_pid);

// exception calls

JSAPI_EXTERN bool jsapi_exception_check(int engine_id);
JSAPI_EXTERN void jsapi_exception_clear(int engine_id);

#endif
