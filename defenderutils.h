#ifndef DEFENDERUTILS
#define DEFENDERUTILS

#include "vector.h"

template<typename T>
inline void __unused(T t)
{
    (void)t;
}

template<typename T, typename... Args>
inline void __unused(T t, Args... args)
{
    __unused(t);
    __unused(args...);
}

namespace Defender
{
Vector2D getSmallestVectorTo(const Vector2D& from, const Vector2D& to);
}

#endif // DEFENDERUTILS

