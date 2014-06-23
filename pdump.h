#ifndef PDUMP_H
#define PDUMP_H

#include "symbol.h"

/* pdump.c functions */

void player_dump( void );
int strprefix( char*, char* );
int unblocked( int, int );
int view_los_p( int, int, int, int );
int view_unblocked( int, int );
void calc_weight( void );
void change_to_game_perms( void );
void change_to_user_perms( void );
void do_los( Symbol, int*, int*, int, int );
void do_object_los (Symbol, int*, int*, int, int);
void findspace( int*, int*, int );
int try_findspace( int*, int*, int );
void initdirs( void );
#ifdef NO_USLEEP
void usleep( int );
#endif

#endif
