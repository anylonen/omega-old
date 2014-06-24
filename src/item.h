#ifndef ITEM_H
#define ITEM_H

#include "monster.h"
#include "object.h"

/* item.c functions */

void shuffle( int [], int );
char* bootname( int );
char* cloakname( int );
char* grotname( void );
char* potionname( int );
char* ringname( int );
char* scrollname( int );
char* stickname( int );
int itemblessing( void );
int itemcharge( void );
int itemplus( void );
int twohandedp( int );
pob create_object( int );
void item_use( struct object* );
void make_armor( pob, int );
void make_artifact( pob, int );
void make_boots( pob, int );
void make_cash( pob, int );
void make_cloak( pob, int );
void make_corpse( pob, struct monster* );
void make_food( pob, int );
void make_potion( pob, int );
void make_ring( pob, int );
void make_scroll( pob, int );
void make_shield( pob, int );
void make_stick( pob, int );
void make_thing( pob, int );
void make_weapon( pob, int );

#endif
