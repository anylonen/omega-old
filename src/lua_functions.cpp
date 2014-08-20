#include "lua_functions.h"
#include <stdio.h>
#include <lua.hpp>

lua_State* lua_state = 0;

lua_State* get_luastate()
{
    if (lua_state == 0)
    {
        lua_state = luaL_newstate();
    }

    return lua_state;
}

void debug(const char* message)
{
    lua_State* L = get_luastate();
    lua_getglobal(L, "write_log");
    lua_pushstring(L, message);
    if(lua_pcall(L, 1, 0, 0) != 0)
    {
        bail(L, "Error while writing log");
    }
}

void bail(lua_State* L, char* error_message)
{
    fprintf(stderr, "\nFATAL ERROR:\n %s: %s\n\n", error_message, lua_tostring(L, -1));
}

int LUA_max(lua_State* state, const int first, const int second)
{
    lua_getglobal(state, "max");
    lua_pushnumber(state, first);
    lua_pushnumber(state, second);

    if (lua_pcall(state, 2, 1, 0) != 0)
    {
        bail(state, "Error running function max");
    }

    if (!lua_isnumber(state, -1))
    {
        bail(state, "Expected number, got something else");
    }

    int max = lua_tonumber(state, -1);
    lua_pop(state, 1);
    return max;
}

int LUA_min(lua_State* state, const int first, const int second)
{
    lua_getglobal(state, "min");
    lua_pushnumber(state, first);
    lua_pushnumber(state, second);

    if (lua_pcall(state, 2, 1, 0) != 0)
    {
        bail(state, "Error running function min");
    }

    if (!lua_isnumber(state, -1))
    {
        bail(state, "Expected number, got something else");
    }

    int max = lua_tonumber(state, -1);
    lua_pop(state, 1);
    return max;
}
