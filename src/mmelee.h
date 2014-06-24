#ifndef MMELEE_H
#define MMELEE_H

#include "monster.h"

/* mmelee.c functions */

char random_loc( void );
int monster_hit( struct monster*, char, int );
void m_hit( struct monster*, int );
void monster_melee( struct monster*, char, int );
void tacmonster( struct monster* );
void transcribe_monster_actions( struct monster* );

#endif
