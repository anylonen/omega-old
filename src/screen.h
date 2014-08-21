#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include "monster.h"
#include "symbol.h"

/* scr.c functions */

using namespace std;

void omega_title( void );
int mcigetc( void );
long parsenum(string message );
char* msgscanstring( void );
Symbol getspot( int, int, int );
char lgetc( void );
char menugetc( void );
char mgetc( void );
void cinema_hide (void);
void cinema_blank (void);
void cinema_print_line (int line, string message);
int cinema_interact_line (int line, string choices, string text);
int cinema_ynq_line (int line, string prompt);
int cinema_getnum_line (int line, string prompt);
int cinema_confirm(string action_description);
int cinema_ynq(string action_description);
int cinema_interact(string choices, string line1, string line2, string line3);
void cinema_scene(string line1, string line2, string line3);
void cinema_display(string line1, string line2, string line3);
int ynq( void );
int ynq1( void );
int ynq2( void );
int getnumber( int );
int litroom( int, int );
int move_slot( int, int, int );
int stillonblock( void );
void blankoutspot( int, int );
void blotspot( int, int );
void buffercycle(const char* s);
int bufferappend(const char* s);
void bufferprint( void );
void checkclear( void );
void clear_if_necessary( void );
void clear_screen( void );
void clearmsg( void );
void clearmsg1( void );
void clearmsg3( void );
void colour_on( void );
void colour_off( void );
void commanderror( void );
void comwinprint( void );
void dataprint( void );
void deathprint( void );
void display_bigwin( void );
void display_death(string message);
void display_inventory_slot( int, int );
void display_option_slot( int );
void display_options( void );
void display_pack( void );
void display_possessions( void );
void display_quit( void );
void display_win( void );
void dobackspace( void );
void dodrawspot( int, int );
void draw_explosion( Symbol, int, int );
void drawmonsters( int );
void drawomega( void );
void drawplayer( void );
void drawscreen( void );
void drawspot( int, int );
void drawvision( int, int );
void endgraf( void );
void erase_level( void );
void erase_monster( struct monster* );
void hide_line( int );
void initgraf( void );
void levelrefresh( void );
void lightspot( int, int );
void locprint( char* );
void maddch( char );
void menuaddch( char );
void menuclear( void );
void menulongprint( long );
void menunumprint( int );
void menuprint(string message);
void menuspellprint( int );
void showmenu( void );
void mlongprint( long );
void mnumprint( int );
void morewait( void );
void mprint(string message);
void nprint1(string message);
void nprint2(string message);
void nprint3(string message);
void phaseprint( void );
void bank_init( void );
void plotchar( Symbol, int, int );
void plotmon( struct monster* );
void plotspot( int, int, int );
void print1(string message);
void print2(string message);
void print3(string message);
void putspot( int, int, Symbol );
void redraw( void );
void screencheck( int, int );
void setlastxy( int, int );
void show_screen( void );
void omshowcursor( int, int );
void showflags( void );
void spreadroomdark( int, int, int );
void spreadroomlight( int, int, int );
void timeprint( void );
void xredraw( void );

#endif
