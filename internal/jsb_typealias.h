﻿#ifndef GODOTJS_TYPE_ALIAS_H
#define GODOTJS_TYPE_ALIAS_H

#include "jsb_sindex.h"

namespace jsb
{
    typedef internal::Index32 StringNameID;
    typedef internal::Index32 NativeClassID;
    typedef internal::Index32 ScriptClassID;
    typedef void* EnvironmentID;
    typedef internal::Index64 NativeObjectID;

    typedef internal::Index32 ObjectCacheID;

}
#endif
