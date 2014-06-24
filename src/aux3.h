#ifndef AUX3_H
#define AUX3_H

#include "symbol.h"

/* aux3.c functions */

char* citysiteid( int );
char* countryid( Symbol );
char getlocation( void );
int hostilemonstersnear( void );
int magic_resist( int );
int maneuvers( void );
int parsecitysite( void );
int stonecheck( int );
void alert_guards( void );
void countrysearch( void );
void default_maneuvers( void );
void destroy_order( void );
void hourly_check( void );
void indoors_random_event( void );
void outdoors_random_event( void );
void showknownsites( int, int );
void tenminute_check( void );
void terrain_check( int );

#endif
