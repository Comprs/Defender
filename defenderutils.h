#ifndef DEFENDERUTILS
#define DEFENDERUTILS

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

#endif // DEFENDERUTILS

