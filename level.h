#ifndef LEVEL_H
#define LEVEL_H

#include "location.h"
#include "monster.h"

#define MAXWIDTH 128
#define MAXLENGTH 64

struct level
{
    char depth; /* which level is this */
    struct level* next; /* pointer to next level in dungeon */
#ifndef SAVE_LEVELS
    struct location site[MAXWIDTH][MAXLENGTH]; /* dungeon data */
#else
    /* Over 64K worth of data! */
    struct location* site[MAXWIDTH]; /* dungeon data */
#endif
    char generated; /* has the level been made (visited) yet? */
    char numrooms; /* number of rooms on level */
    char tunnelled; /* amount of tunnelling done on this level */
    struct monsterlist* mlist; /* List of monsters on level */
    int environment; /* where kind of level is this? */
    int last_visited; /* time player was last on this level */
    int level_width; /* width of current level */
    int level_length; /* length of current level */
};
 
typedef struct level levtype;
typedef levtype *plv;

#endif
