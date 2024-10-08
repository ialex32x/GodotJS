#include "jsb_web_primitive_data.h"
#include "jsb_web_isolate.h"

namespace v8
{
    bool Data::IsInt32() const
    {
        return jsapi_sv_is_int32(isolate_->id_, stack_, index_);
    }

    bool Data::IsExternal() const
    {
        return jsapi_sv_is_external(isolate_->id_, stack_, index_);
    }

    bool Data::IsPromise() const
    {
        return jsapi_sv_is_promise(isolate_->id_, stack_, index_);
    }

    bool Data::IsArrayBuffer() const
    {
        return jsapi_sv_is_array_buffer(isolate_->id_, stack_, index_);
    }

    bool Data::IsUint32() const
    {
        return jsapi_sv_is_int32(isolate_->id_, stack_, index_);
    }

    bool Data::IsMap() const
    {
        return jsapi_sv_is_map(isolate_->id_, stack_, index_);
    }

    bool Data::IsNumber() const
    {
        return jsapi_sv_is_number(isolate_->id_, stack_, index_);
    }

    bool Data::IsSymbol() const
    {
        return jsapi_sv_is_symbol(isolate_->id_, stack_, index_);
    }

    bool Data::IsString() const
    {
        return jsapi_sv_is_string(isolate_->id_, stack_, index_);
    }

    bool Data::IsBigInt() const
    {
        return jsapi_sv_is_bigint(isolate_->id_, stack_, index_);
    }

    bool Data::IsBoolean() const
    {
        return jsapi_sv_is_boolean(isolate_->id_, stack_, index_);
    }

    bool Data::IsArray() const
    {
        return jsapi_sv_is_array(isolate_->id_, stack_, index_);
    }

    bool Data::IsUndefined() const
    {
        return jsapi_sv_is_undefined(isolate_->id_, stack_, index_);
    }

    bool Data::IsNullOrUndefined() const
    {
        return IsNull() || IsUndefined();
    }

    bool Data::IsNull() const
    {
        return jsapi_sv_is_null(isolate_->id_, stack_, index_);
    }

    bool Data::IsFunction() const
    {
        return jsapi_sv_is_function(isolate_->id_, stack_, index_);
    }

    bool Data::IsObject() const
    {
        return jsapi_sv_is_object(isolate_->id_, stack_, index_);
    }

    bool Data::equals_to(const Data& other) const
    {
        return jsapi_sv_equals(isolate_->id_,
                stack_, index_,
                other.stack_, other.index_);
    }

}
