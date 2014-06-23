#ifndef VILLAGE_H
#define VILLAGE_H

#define VIL_STARVIEW  1
#define VIL_WOODMERE  2
#define VIL_STORMWAT  3
#define VIL_THAUMARI  4
#define VIL_SKORCH    5
#define VIL_WHORFEN   6

/* village.c functions */

void assign_village_function( int, int, int );
void load_village( int, int );
void make_food_bin( int, int );
void make_guard( int, int );
void make_horse( int, int );
void make_merchant( int, int );
void make_sheep( int, int );
void special_village_site( int, int, int );

#endif
