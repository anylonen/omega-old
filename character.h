#ifndef CHARACTER_H
#define CHARACTER_H

/* character.c functions */

long calcmana( void );
FILE* omegarc_check( void );
int competence_check( int );
int fixnpc( int );
int initplayer( void );
int initstats( void );
void omegan_character_stats( void );
void save_omegarc( void );
void user_character_stats( void );

#endif
