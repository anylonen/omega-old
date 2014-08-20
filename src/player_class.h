#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include "player.h"

class PlayerClass
{
public:
    PlayerClass();
    ~PlayerClass();

    const long get_mana();
    const long get_mana_maximum();

private:

    struct player* _player;

    long _mana;
    long _maximum_mana;
};

#endif // PLAYER_CLASS_H
