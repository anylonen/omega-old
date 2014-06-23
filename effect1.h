#ifndef EFFECT1_H
#define EFFECT1_H

/* effect1.c functions */

int random_item (void);
int stolen_item (void);
void acquire( int );
void ball( int, int, int, int, int, int );
void bless( int );
void bolt( int, int, int, int, int, int, int );
void enchant( int );
void fball( int, int, int, int, int );
void fbolt( int, int, int, int, int, int );
void heal( int );
void identify( int );
void lball( int, int, int, int, int );
void lbolt( int, int, int, int, int, int );
void manastorm( int, int, int );
void mondet( int );
void nbolt( int, int, int, int, int, int );
void icebolt( int, int, int, int, int, int );
void objdet( int );
void snowball( int, int, int, int, int );
void wish( int );

#endif
