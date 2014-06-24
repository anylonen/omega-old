#ifndef LUA_FUNCTIONS_H
#define LUA_FUNCTIONS_H

#include "vendor/luajit/src/luajit.h"
#include "vendor/luajit/src/lua.h"
#include "vendor/luajit/src/lualib.h"
#include "vendor/luajit/src/lauxlib.h"

extern lua_State* lua_state;

lua_State* get_luastate();

void bail(lua_State* L, char* error_message);

int LUA_max(lua_State* state, const int first, const int second);

#endif
