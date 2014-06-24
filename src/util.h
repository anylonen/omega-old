#ifndef UTIL_H
#define UTIL_H

#include "level.h"
#include "monster.h"

/* util.c functions */

void setPlayerXY( int, int );
long calc_points( void );
char* getarticle( char* );
char* month( void );
char* ordinal( int );
char* salloc( char* );
char inversedir( int );
void init_perms( void );
int confirmation( void );
char cryptkey( char* );
int day( void );
int distance( int, int, int, int );
int hitp( int, int );
int hour( void );
int inbounds( int, int );
int los_p( int, int, int, int );
int m_unblocked( struct monster*, int, int );
int nighttime( void );
int offscreen( int, int );
int ok_to_free( plv );
void free_level( plv );
void free_mons_and_objs( pml );
void free_obj( pob, int );
pob copy_obj( pob );
void free_objlist( pol );
void* checkmalloc( unsigned int );
unsigned random_range( unsigned int );
int screenmody( int );
int screenmodx( int );
int showhour( void );
int showminute( void );
int strmem( char, char* );
char* strjoin(char*, char*);

#endif
