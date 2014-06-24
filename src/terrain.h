#ifndef TERRAIN_H
#define TERRAIN_H

#include "symbol.h"

/* terrain locations */
struct terrain
{
    Symbol base_terrain_type;
    Symbol current_terrain_type;
    char aux;
    char status;
};

#endif
