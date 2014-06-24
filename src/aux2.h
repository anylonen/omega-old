#ifndef AUX2_H
#define AUX2_H

#include "object.h"
#include "monster.h"
#include "symbol.h"

/* aux2.c functions */

long expval( int );
long item_value( pob );
long true_item_value( pob );
char* actionlocstr( char );
int p_immune( int );
int player_hit( int, char, struct monster* );
int statmod( int );
void break_weapon( void );
void change_environment( char );
void drop_weapon( void );
void enter_site( Symbol );
void gain_level( void );
void minute_status_check( void );
void moon_check( void );
void movecursor( int*, int*, int, int );
void p_drown( void );
void p_fumble( int );
void p_hit ( struct monster*, int, int );
void p_win( void );
void player_miss( struct monster*, int );
void tacplayer( struct monster* );
void tenminute_status_check( void );
void toggle_item_use( int );
void torch_check( void );
void weapon_use( int, pob, struct monster* );

#endif
