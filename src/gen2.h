#ifndef GEN2_H
#define GEN2_H

#include "symbol.h"

/* gen2.c functions */

void make_country_screen( Symbol );
void make_general_map( char* );
void make_forest( void );
void make_jungle( void );
void make_mountains( void );
void make_plains( void );
void make_river( void );
void make_road( void );
void make_stairs( int );
void make_swamp( void );
void maze_corridor( int, int, int, int, char, char );
void maze_level( void );
void room_corridor( int, int, int, int, int );
void room_level( void );

#endif
