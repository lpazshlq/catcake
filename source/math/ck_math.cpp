/*
    Copyright (c) 2007-2009 Takashi Kitao
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
    `  notice, this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
    `  notice, this list of conditions and the following disclaimer in the
    `  documentation and/or other materials provided with the distribution.

    3. The name of the author may not be used to endorse or promote products
    `  derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
    IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
    IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
    NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "pg_math_all.h"

#include "pg_low_level_api.h"


static const r32 s_sin_tbl[180] =
{
    0.000000f, 0.017452f, 0.034899f, 0.052336f, 0.069756f, 0.087156f, //
    0.104528f, 0.121869f, 0.139173f, 0.156434f, 0.173648f, 0.190809f, //
    0.207912f, 0.224951f, 0.241922f, 0.258819f, 0.275637f, 0.292372f, //
    0.309017f, 0.325568f, 0.342020f, 0.358368f, 0.374607f, 0.390731f, //
    0.406737f, 0.422618f, 0.438371f, 0.453991f, 0.469472f, 0.484810f, //
    0.500000f, 0.515038f, 0.529919f, 0.544639f, 0.559193f, 0.573576f, //
    0.587785f, 0.601815f, 0.615662f, 0.629320f, 0.642788f, 0.656059f, //
    0.669131f, 0.681998f, 0.694658f, 0.707107f, 0.719340f, 0.731354f, //
    0.743145f, 0.754710f, 0.766044f, 0.777146f, 0.788011f, 0.798636f, //
    0.809017f, 0.819152f, 0.829038f, 0.838671f, 0.848048f, 0.857167f, //
    0.866025f, 0.874620f, 0.882948f, 0.891007f, 0.898794f, 0.906308f, //
    0.913545f, 0.920505f, 0.927184f, 0.933580f, 0.939693f, 0.945519f, //
    0.951057f, 0.956305f, 0.961262f, 0.965926f, 0.970296f, 0.974370f, //
    0.978148f, 0.981627f, 0.984808f, 0.987688f, 0.990268f, 0.992546f, //
    0.994522f, 0.996195f, 0.997564f, 0.998630f, 0.999391f, 0.999848f, //
    1.000000f, 0.999848f, 0.999391f, 0.998630f, 0.997564f, 0.996195f, //
    0.994522f, 0.992546f, 0.990268f, 0.987688f, 0.984808f, 0.981627f, //
    0.978148f, 0.974370f, 0.970296f, 0.965926f, 0.961262f, 0.956305f, //
    0.951056f, 0.945519f, 0.939693f, 0.933580f, 0.927184f, 0.920505f, //
    0.913545f, 0.906308f, 0.898794f, 0.891006f, 0.882948f, 0.874620f, //
    0.866025f, 0.857167f, 0.848048f, 0.838671f, 0.829037f, 0.819152f, //
    0.809017f, 0.798635f, 0.788011f, 0.777146f, 0.766044f, 0.754709f, //
    0.743145f, 0.731354f, 0.719340f, 0.707107f, 0.694658f, 0.681998f, //
    0.669130f, 0.656059f, 0.642788f, 0.629320f, 0.615661f, 0.601815f, //
    0.587785f, 0.573576f, 0.559193f, 0.544639f, 0.529919f, 0.515038f, //
    0.500000f, 0.484810f, 0.469472f, 0.453990f, 0.438371f, 0.422618f, //
    0.406737f, 0.390731f, 0.374606f, 0.358368f, 0.342020f, 0.325568f, //
    0.309017f, 0.292372f, 0.275637f, 0.258819f, 0.241922f, 0.224951f, //
    0.207912f, 0.190809f, 0.173648f, 0.156434f, 0.139173f, 0.121869f, //
    0.104528f, 0.087156f, 0.069756f, 0.052336f, 0.034899f, 0.017452f
};


const r32 pgMath::EPSILON = 0.0001f;
const r32 pgMath::PI = 3.14159265358979323846f;
const r32 pgMath::DEG_TO_RAD = pgMath::PI / 180.0f;
const r32 pgMath::RAD_TO_DEG = 180.0f / pgMath::PI;


r32 pgMath::sqrt(r32 x)
{
    return pgLowLevelAPI::sqrt(x);
}


r32 pgMath::sin_r32(r32 deg)
{
    return pgLowLevelAPI::sin(deg * DEG_TO_RAD);
}


r32 pgMath::cos_r32(r32 deg)
{
    return pgLowLevelAPI::cos(deg * DEG_TO_RAD);
}


r32 pgMath::sin_s32(s32 deg)
{
    if (deg < 0)
    {
        deg -= (deg / 360 - 1) * 360;
    }

    deg %= 360;

    return (deg < 180) ? s_sin_tbl[deg] : -s_sin_tbl[deg - 180];
}


r32 pgMath::cos_s32(s32 deg)
{
    return sin_s32(deg + 90);
}


r32 pgMath::asin(r32 x)
{
    return pgLowLevelAPI::asin(x) * RAD_TO_DEG;
}


r32 pgMath::acos(r32 x)
{
    return pgLowLevelAPI::acos(x) * RAD_TO_DEG;
}


r32 pgMath::atan2(r32 y, r32 x)
{
    return pgLowLevelAPI::atan2(y, x) * RAD_TO_DEG;
}


void pgMath::srand(u32 seed)
{
    pgLowLevelAPI::srand(seed);
}


s32 pgMath::rand(s32 from, s32 to)
{
    if (to >= from)
    {
        s32 range = to - from + 1;

        return from + (pgLowLevelAPI::rand() % range);
    }
    else
    {
        s32 range = from - to + 1;

        return from - (pgLowLevelAPI::rand() % range);
    }
}


r32 pgMath::rand(r32 from, r32 to, r32 interval)
{
    interval = abs(interval);

    if (to >= from)
    {
        s32 range = static_cast<s32>((to - from) / interval + 1.0f);

        return from + (pgLowLevelAPI::rand() % range) * interval;
    }
    else
    {
        s32 range = static_cast<s32>((from - to) / interval + 1.0f);

        return from - (pgLowLevelAPI::rand() % range) * interval;
    }
}


r32 pgMath::interp(r32 from, r32 to, r32 ratio)
{
    if (ratio < pgMath::EPSILON)
    {
        return from;
    }
    else if (ratio > 1.0f - pgMath::EPSILON)
    {
        return to;
    }
    else
    {
        return from * (1.0f - ratio) + to * ratio;
    }
}