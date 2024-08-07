#ifndef GODOTJS_V8_HELPER_H
#define GODOTJS_V8_HELPER_H
#include "jsb_pch.h"
#include "jsb_object_handle.h"

namespace jsb
{
    struct V8Helper
    {
        static String stringify(v8::Isolate* isolate, const v8::Local<v8::Context>& context, const v8::Local<v8::Value>& p_val);

        // convert int64 to int32 anyway
        jsb_force_inline static v8::Local<v8::Integer> to_int32(v8::Isolate* isolate, int64_t p_val)
        {
            return v8::Int32::New(isolate, (int32_t) p_val);
        }

        static int32_t to_int32(const v8::Local<v8::Context>& context, v8::MaybeLocal<v8::Value> obj, const int32_t p_default_value)
        {
            int32_t value;
            v8::Local<v8::Value> local;
            if (obj.ToLocal(&local) && local->Int32Value(context).To(&value)) return value;
            return p_default_value;
        }

        template<typename TEnum>
        static TEnum to_enum(const v8::Local<v8::Context>& context, v8::MaybeLocal<v8::Value> obj, const TEnum p_default_value)
        {
            int32_t value;
            v8::Local<v8::Value> local;
            if (obj.ToLocal(&local) && local->Int32Value(context).To(&value)) return (TEnum) value;
            return p_default_value;
        }

        jsb_force_inline static v8::Local<v8::Boolean> to_boolean(v8::Isolate* isolate, bool p_val)
        {
            return v8::Boolean::New(isolate, p_val);
        }

        jsb_force_inline static v8::Local<v8::Number> to_number(v8::Isolate* isolate, double p_val)
        {
            return v8::Number::New(isolate, p_val);
        }

        /**
         * Convert a v8 utf-16 string to a godot String
         * @note crash if failed
        */
        jsb_force_inline static String to_string(const v8::String::Value& p_val)
        {
            String str_gd;
            const Error err = str_gd.parse_utf16((const char16_t*) *p_val, p_val.length());
            jsb_check(err == OK);
            return str_gd;
        }

        jsb_force_inline static String to_string_opt(v8::Isolate* isolate, const v8::MaybeLocal<v8::Value>& p_val)
        {
            v8::Local<v8::Value> local;
            return p_val.ToLocal(&local) ? to_string(isolate, local) : String();
        }

        /**
         * Convert a javascript 'String/Symbol' value to a godot String
        */
        static String to_string(v8::Isolate* isolate, const v8::Local<v8::Value>& p_val)
        {
            String str_gd;
            if (!p_val.IsEmpty() && (p_val->IsString() || p_val->IsSymbol()))
            {
                if (const v8::String::Utf8Value exchange(isolate, p_val); *exchange)
                {
                    const Error err = str_gd.parse_utf8(*exchange, exchange.length());
                    jsb_check(err == OK);
                }
            }
            return str_gd;
        }

        static String to_string_without_side_effect(v8::Isolate* isolate, const v8::Local<v8::Value>& p_val)
        {
            String str_gd;
            if (!p_val.IsEmpty() && (p_val->IsString() || p_val->IsSymbol()))
            {
                v8::Local<v8::String> detail_string;
                if (p_val->ToDetailString(isolate->GetCurrentContext()).ToLocal(&detail_string))
                {
                    if (const v8::String::Utf8Value exchange(isolate, detail_string); *exchange)
                    {
                        const Error err = str_gd.parse_utf8(*exchange, exchange.length());
                        jsb_check(err == OK);
                    }
                }
            }
            return str_gd;
        }

        template<size_t N>
        jsb_force_inline static v8::Local<v8::String> to_string(v8::Isolate* isolate, const char (&literal)[N])
        {
            return v8::String::NewFromUtf8Literal(isolate, literal, v8::NewStringType::kNormal);
        }

        jsb_force_inline static v8::Local<v8::String> to_string(v8::Isolate* isolate, const String& p_str)
        {
            const CharString cstr = p_str.utf8();
            return v8::String::NewFromUtf8(isolate, cstr.ptr(), v8::NewStringType::kNormal, cstr.length()).ToLocalChecked();
        }

        jsb_force_inline static v8::Local<v8::String> to_string_ascii(v8::Isolate* isolate, const String& p_str)
        {
            const CharString cstr = p_str.ascii();
            return v8::String::NewFromOneByte(isolate, (const uint8_t*) cstr.ptr(), v8::NewStringType::kNormal, cstr.length()).ToLocalChecked();
        }

        static PackedByteArray to_packed_byte_array(v8::Isolate* isolate, const v8::Local<v8::ArrayBuffer>& array_buffer)
        {
            const size_t size = array_buffer->ByteLength();
            PackedByteArray packed;
            Error err = packed.resize((int) size);
            jsb_check(err == OK);
            const void* data = array_buffer->Data();
            memcpy(packed.ptrw(), data, size);
            return packed;
        }

        static v8::Local<v8::ArrayBuffer> to_array_buffer(v8::Isolate* isolate, const Vector<uint8_t>& packed)
        {
            v8::Local<v8::ArrayBuffer> buffer = v8::ArrayBuffer::New(isolate, packed.size());
            void* data = buffer->Data();
            memcpy(data, packed.ptr(), packed.size());
            return buffer;
        }

        static v8::Local<v8::Object> to_global_enum(v8::Isolate* isolate, const v8::Local<v8::Context>& context, const StringName& name)
        {
            HashMap<StringName, int64_t> enum_values;
            CoreConstants::get_enum_values(name, &enum_values);
            return to_global_enum(isolate, context, enum_values);
        }

        static v8::Local<v8::Object> to_global_enum(v8::Isolate* isolate, const v8::Local<v8::Context>& context, const HashMap<StringName, int64_t>& enum_values)
        {
            v8::Local<v8::Object> enumeration = v8::Object::New(isolate);
            for (const KeyValue<StringName, int64_t>& kv : enum_values)
            {
                jsb_verify_int64(kv.value, "%s %s", kv.key, uitos(kv.value));
                v8::Local<v8::String> name = V8Helper::to_string(isolate, kv.key);
                v8::Local<v8::Integer> value = V8Helper::to_int32(isolate, kv.value);
                enumeration->Set(context, name, value).Check();
                // represents the value back to string for convenient uses, such as MyColor[MyColor.White] => 'White'
                enumeration->DefineOwnProperty(context, value->ToString(context).ToLocalChecked(), name, v8::DontEnum).Check();
            }
            return enumeration;
        }

        static v8::Local<v8::ObjectTemplate> to_template_enum(v8::Isolate* isolate, const v8::Local<v8::Context>& context,
            const ClassDB::ClassInfo::EnumInfo& p_info, const HashMap<StringName, int64_t>& p_constants,
            HashSet<StringName>* o_names)
        {
            v8::Local<v8::ObjectTemplate> enumeration = v8::ObjectTemplate::New(isolate);
            for (const StringName& enum_name : p_info.constants)
            {
                const String& enum_name_str = (String) enum_name;
                jsb_not_implemented(enum_name_str.contains("."), "hierarchically nested definition is currently not supported");
                const auto& const_it = p_constants.find(enum_name);
                jsb_check(const_it);
                jsb_verify_int64(const_it->value, "%s %s", enum_name, const_it->value);
                v8::Local<v8::String> name = to_string(isolate, enum_name_str);
                v8::Local<v8::Integer> value = to_int32(isolate, const_it->value);
                enumeration->Set(name, value);
                // represents the value back to string for convenient uses, such as MyColor[MyColor.White] => 'White'
                enumeration->Set(value->ToString(context).ToLocalChecked(), name, v8::DontEnum);
                if (o_names) o_names->insert(enum_name);
            }
            return enumeration;
        }

        static v8::MaybeLocal<v8::Script> compile(v8::Local<v8::Context> context, v8::Local<v8::String> source, const String& p_filename)
        {
            v8::Isolate* isolate = context->GetIsolate();
            if (p_filename.is_empty())
            {
                return v8::Script::Compile(context, source);
            }

#if WINDOWS_ENABLED
            const CharString filename = p_filename.replace("/", "\\").utf8();
#else
            const CharString filename = p_filename.utf8();
#endif
            v8::ScriptOrigin origin(isolate, v8::String::NewFromUtf8(isolate, filename, v8::NewStringType::kNormal, filename.length()).ToLocalChecked());
            return v8::Script::Compile(context, source, &origin);
        }
    };
}
#endif
