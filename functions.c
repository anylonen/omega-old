#include "functions.h"

int max(const int first, const int second)
{
    return LUA_max(get_luastate(),first, second);
};
