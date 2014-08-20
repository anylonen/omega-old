#include "player.h"
#include "glob.h"

void player_regenerate_hp()
{
    if ((Player.status[DISEASED] == 0) && (Player.hp < Player.maxhp))
    {
        int increment = player_get_level() + 1;
        Player.hp = min(Player.maxhp, Player.hp + increment);
    }
}

void player_regenerate_mana()
{
    lua_State* L = get_luastate();
    lua_getglobal(L, "player_regenerate_mana");
    lua_pcall(L, 0, 0, 0);
}

void player_regenerate_all()
{
    player_regenerate_hp();
    player_regenerate_mana();
}

const long player_get_mana()
{
    return Player.mana;
}

void player_set_mana(const long amount)
{
    Player.mana = amount;
}

const long player_get_max_mana()
{
    return Player.maxmana;
}

void player_set_max_mana(const long amount)
{
    Player.maxmana = amount;
}

const int player_get_level()
{
    return Player.level;
}

void player_set_level(const int amount)
{
    Player.level = amount;
}

const int player_get_power()
{
    return Player.pow;
}

void player_set_power(const int amount)
{
    Player.pow = amount;
}

const long player_get_max_power()
{
    return Player.maxpow;
}

void player_set_max_power(const long amount)
{
    Player.maxpow = amount;
}

int lua_player_get_mana(lua_State* L)
{
    lua_pushnumber(L, player_get_mana());
    return 1;
}

int lua_player_set_mana(lua_State* L)
{
    const int amount = lua_tonumber(L, -1);
    lua_pop(L, 1);
    player_set_mana(amount);
    return 0;
}

int lua_player_get_max_mana(lua_State* L)
{
    lua_pushnumber(L, player_get_max_mana());
    return 1;
}

int lua_player_set_max_mana(lua_State* L)
{
    const int amount = lua_tonumber(L, -1);
    lua_pop(L, 1);
    player_set_max_mana(amount);
    return 0;
}

int lua_player_get_power(lua_State* L)
{
    lua_pushnumber(L, player_get_power());
    return 1;
}

int lua_player_set_power(lua_State* L)
{
    const int amount = lua_tonumber(L, -1);
    lua_pop(L, 1);
    player_set_power(amount);
    return 0;
}

int lua_player_get_max_power(lua_State* L)
{
    lua_pushnumber(L, player_get_max_power());
    return 1;
}

int lua_player_set_max_power(lua_State* L)
{
    const int amount = lua_tonumber(L, -1);
    lua_pop(L, 1);
    player_set_max_power(amount);
    return 0;
}

int lua_player_get_level(lua_State* L)
{
    lua_pushnumber(L, player_get_level());
    return 1;
}

int lua_player_set_level(lua_State* L)
{
    const int amount = lua_tonumber(L, -1);
    lua_pop(L, 1);
    player_set_level(amount);
    return 0;
}


void register_lua_player_functions()
{
    lua_State* L = get_luastate();
    luaL_Reg module[] =
    {
        {"player_get_mana", &lua_player_get_mana},
        {"player_set_mana", &lua_player_set_mana},
        {"player_get_max_mana", &lua_player_get_max_mana},
        {"player_set_max_mana", &lua_player_set_max_mana},
        {"player_get_power", &lua_player_get_power},
        {"player_set_power", &lua_player_set_power},
        {"player_get_max_power", &lua_player_get_max_power},
        {"player_set_max_power", &lua_player_set_max_power},
        {"player_get_level", &lua_player_get_level},
        {"player_set_level", &lua_player_set_level},
        {NULL, NULL}
    };
    luaL_register(L, "_G", module);
}
