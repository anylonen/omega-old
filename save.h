#ifndef SAVE_H
#define SAVE_H

#include "level.h"
#include "monster.h"
#include "object.h"

/* save.c functions */

int ok_outdated( int );
int restore_game( char* );
void restore_hiscore_npc( pmt, int );
pob restore_item( FILE*, int );
pol restore_itemlist( FILE*, int );
void restore_country( FILE*, int );
void restore_level( FILE*, int );
void restore_monsters( FILE*, plv, int );
void restore_player( FILE*, int );
int save_game( int, char* );
int save_country( FILE* );
int save_item( FILE*, pob );
int save_itemlist( FILE*, pol );
int save_level( FILE*, plv );
int save_monsters( FILE*, pml );
int save_player( FILE* );

#endif
