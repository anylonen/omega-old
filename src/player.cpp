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
    /* At this point there is no condition which prevents mana regeneration */
    if ( player_get_mana() < player_get_max_mana())
    {
        int increment = (player_get_power() * player_get_max_mana()) / 1000 + player_get_level();
        player_set_mana(min(player_get_max_mana(), player_get_mana() + increment));
    }
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
