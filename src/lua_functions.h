#ifndef LUA_FUNCTIONS_H
#define LUA_FUNCTIONS_H

#include <lua.hpp>

extern lua_State* lua_state;

lua_State* get_luastate();

void debug(const char* message);
void bail(lua_State* L, char* error_message);

int LUA_max(lua_State* state, const int first, const int second);
int LUA_min(lua_State* state, const int first, const int second);

#endif
