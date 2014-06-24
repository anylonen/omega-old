#ifndef OMEGA_H
#define OMEGA_H

/* omega.c functions */

int main( int, char *[] );
int game_restore( char* );
void init_world( void );
void inititem( int );
void initrand( int, int );
void signalexit(int);
void signalsave(int);

#endif
