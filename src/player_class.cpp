#include "player_class.h"
#include "glob.h"

PlayerClass::PlayerClass()
{
    _player = &Player;
}

PlayerClass::~PlayerClass()
{
    if(_player != NULL)
    {
        delete _player;
        _player = NULL;
    }
}

const long PlayerClass::get_mana()
{
    return _player->mana;
}

const long PlayerClass::get_mana_maximum()
{
    return _player->maxmana;
}
