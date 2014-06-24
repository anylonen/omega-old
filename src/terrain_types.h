#ifndef TERRAIN_TYPES_H
#define TERRAIN_TYPES_H

#include "colors.h"

/* TERRAIN TYPES */
#define PLAINS ('-' | CLR(LIGHT_GREEN))
#define TUNDRA ('_' | CLR(GREY))
#define ROAD ('.' | CLR(BROWN))
#define MOUNTAINS ('^' | CLR(GREY))
#define PASS ('v' | CLR(BROWN))
#define RIVER ('~' | CLR(BLUE))
#define CITY ('O' | CLR(WHITE))
#define VILLAGE ('o' | CLR(WHITE))
#define FOREST ('(' | CLR(LIGHT_GREEN))
#define JUNGLE (')' | CLR(GREEN))
#define SWAMP ('=' | CLR(GREEN))
#define VOLCANO ('!' | CLR(RED))
#define CASTLE ('%' | CLR(GREY))
#define TEMPLE ('X' | CLR(BROWN))
#define CAVES ('*' | CLRS(BLACK,BROWN))
#define DESERT ('\"' | CLR(YELLOW))
#define CHAOS_SEA ('+' | CLR(LIGHT_PURPLE))
#define STARPEAK ('|' | CLR(LIGHT_BLUE))
#define DRAGONLAIR ('$' | CLR(BROWN))
#define MAGIC_ISLE ('&' | CLR(PURPLE))
#define PALACE ('K' | CLR(PURPLE))

#define CHAIR ('5' | CLR(BROWN))
#define SAFE ('3' | CLR(GREY))
#define FURNITURE ('2' | CLR(BROWN))
#define BED ('9' | CLR(CYAN))

/* wow, all characters used! */

#endif
