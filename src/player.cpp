#include "player.h"
#include "glob.h"

void player_regenerate_hp()
{
    if ((Player.status[DISEASED] == 0) && (Player.hp < Player.maxhp))
    {
        int increment = Player.level + 1;
        Player.hp = min(Player.maxhp, Player.hp + increment);
    }
}

void player_regenerate_mana()
{
    /* At this point there is no condition which prevents mana regeneration */
    if ( Player.mana < Player.maxmana)
    {
        int increment = (Player.pow * Player.maxmana) / 1000 + Player.level;
        Player.mana = min(Player.maxmana, Player.mana + increment);
    }
}

void player_regenerate_all()
{
    player_regenerate_hp();
    player_regenerate_mana();
}
