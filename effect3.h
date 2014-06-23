#ifndef EFFECT3_H
#define EFFECT3_H

/* effect3.c functions */

int itemlist( int, int );
int monsterlist( void );
void acid_cloud( void );
void aggravate( void );
void amnesia( void );
void annihilate( int );
void apport( int );
void clairvoyance( int );
void cleanse( int );
void cure( int );
void deflection( int );
void disease( int );
void disintegrate( int, int );
void dispel( int );
void disrupt( int, int, int );
void drain( int );
void drain_life( int );
void hellfire( int, int, int );
void hero( int );
void hide( int, int );
void illuminate( int );
void inflict_fear( int, int );
void learnspell( int );
void level_drain( int, char* );
void level_return( void );
void levitate( int );
void p_poison( int );
void p_teleport( int );
void polymorph( int );
void sanctuary( void );
void shadowform( void );
void sleep_monster( int );
void sleep_player( int );
void strategic_teleport( int );
void summon( int, int );
void truesight( int );

#endif
