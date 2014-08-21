#ifndef AUX1_H
#define AUX1_H

#include <string>
#include "monster.h"
#include "object.h"

/* aux1.c functions */

using namespace std;

char* levelname( int );
char* mstatus_string( struct monster* );
string trapid( int );
int getdir( void );
int goberserk( void );
int p_country_moveable( int, int );
int p_moveable( int, int );
int player_on_sanctuary( void );
void calc_melee( void );
int damage_item( pob );
void describe_player( void );
void fight_monster( struct monster* );
void foodcheck( void );
void gain_experience( int );
void p_damage( int, int, string message);
void p_death(string message);
void roomcheck( void );
void searchat( int, int );
void setspot( int*, int* );
void showroom( int );
void surrender( struct monster* );
void threaten( struct monster* );
void tunnelcheck( void );

#endif
