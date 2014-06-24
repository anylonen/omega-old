#ifndef GEN1_H
#define GEN1_H

#include "level.h"
#include "symbol.h"

/* gen1.c functions */

char* roomname( int );
plv findlevel( struct level*, char );
void build_room( int, int, int, char, int );
void build_square_room( int, int, int, char, int );
void cavern_level( void );
void change_level( char, char, char );
void clear_level( struct level* );
void corridor_crawl( int*, int*, int, int, int, Symbol, char );
void find_stairs( char, char );
void free_dungeon( void );
void install_specials( void );
void install_traps( void );
void makedoor( int, int );
void sewer_corridor( int, int, int, int, Symbol );
void sewer_level( void );
void straggle_corridor( int, int, int, int, Symbol, char );

#endif
