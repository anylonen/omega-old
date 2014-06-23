/* omega copyright (c) 1987,1988,1989 by Laurence Raphael Brothers */
/* extern.h -- function declarations */

#include "newrand.h"
#include "stats.h"
#include "omega.h"
#include "abyss.h"
#include "aux1.h"
#include "aux2.h"
#include "aux3.h"
#include "bank.h"
#include "character.h"
#include "city.h"
#include "command1.h"
#include "command2.h"
#include "command3.h"
#include "country.h"
#include "effect1.h"
#include "effect2.h"
#include "effect3.h"
#include "env.h"
#include "etc.h"
#include "file.h"
#include "gen1.h"
#include "gen2.h"
#include "guild1.h"
#include "guild2.h"
#include "house.h"
#include "inventory.h"
#include "item.h"
#include "itemf1.h"
#include "itemf2.h"
#include "itemf3.h"
#include "level.h"
#include "map.h"
#include "mmelee.h"
#include "mmove.h"
#include "monster.h"
#include "move.h"
#include "movef.h"
#include "mspec.h"
#include "mstrike.h"
#include "mtalk.h"
#include "priest.h"
#include "save.h"
#include "screen.h"
#include "site1.h"
#include "site2.h"
#include "spell.h"
#include "time.h"
#include "trap.h"
#include "util.h"

/* pdump.c functions */

void player_dump( void );
int strprefix( char*, char* );
int unblocked( int, int );
int view_los_p( int, int, int, int );
int view_unblocked( int, int );
void calc_weight( void );
void change_to_game_perms( void );
void change_to_user_perms( void );
void do_los( Symbol, int*, int*, int, int );
void do_object_los (Symbol, int*, int*, int, int);
void findspace( int*, int*, int );
int try_findspace( int*, int*, int );
void initdirs( void );
#ifdef NO_USLEEP
void usleep( int );
#endif

/* village.c functions */

void assign_village_function( int, int, int );
void load_village( int, int );
void make_food_bin( int, int );
void make_guard( int, int );
void make_horse( int, int );
void make_merchant( int, int );
void make_sheep( int, int );
void special_village_site( int, int, int );
