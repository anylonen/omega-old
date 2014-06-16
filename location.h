#ifndef LOCATION_H
#define LOCATION_H

#include "symbol.h"
#include "object.h"
#include "monster.h"
#include "monk.h"

/* location functions */
#define L_NO_OP 0

/* random sites, used many places */
#define L_LIFT 1
#define L_FIRE 2
#define L_ALTAR 3
#define L_TRIFID 4
#define L_RAISE_PORTCULLIS 5
/* spare entry: 6 */

/* city level shop and guild functions */
/* following are those in CitySiteList */
#define NUMCITYSITES 30
#define CITYSITEBASE 7
#define L_CHARITY 7
#define L_ARMORER 8
#define L_CLUB 9
#define L_GYM 10
#define L_THIEVES_GUILD 11
#define L_COLLEGE 12
#define L_HEALER 13
#define L_CASINO 14
#define L_TAVERN 15
#define L_MERC_GUILD 16
#define L_ALCHEMIST 17
#define L_SORCERORS 18
#define L_CASTLE 19
#define L_ARENA 20
#define L_DPW 21
#define L_LIBRARY 22
#define L_PAWN_SHOP 23
#define L_BANK 24
#define L_CONDO 25
#define L_ORACLE 26
#define L_ORDER 27
#define L_DINER 28
#define L_COMMANDANT 29
#define L_CRAP 30
#define L_TEMPLE 31
#define L_COUNTRYSIDE 32
#define L_BROTHEL 33
#define L_SEWER 34
#define L_TOURIST 35
#ifdef INCLUDE_MONKS
#define L_MONASTERY 36 /* first available PGM */
#endif
/* end of city sites */

/* gap for a few more city sites, could be either list: 37, 38, 39, 40 */

/* other city sites, not in move list */
#define L_GARDEN 41
#define L_JAIL 42
#define L_MAZE 43      /* city */
#define L_CEMETARY 44  /* city */
#define L_VAULT 45     /* city */
#define L_MANSION 46   /* city */

/* sites in villages */
#define L_CARTOGRAPHER 47    /* villages */
#define L_STABLES 48         /* villages */
#define L_COMMONS 49         /* villages */
#define L_GRANARY 50         /* villages */
#define L_LAWSTONE 51
#define L_CHAOSTONE 52       /* shouldn't this be CHAOSSTONE ?? :) DAG */ 
#define L_SACRIFICESTONE 53
#define L_VOIDSTONE 54
#define L_BALANCESTONE 55
#define L_MINDSTONE 56

/* gap for a few more village or combined city/village sites: 57, 58, 59, 60 */
/* sites in city & villages */
#define L_HOVEL 61 
#define L_HOUSE 62 

/* sites in the countryside */
#define L_TEMPLE_WARNING 63  /* country */
#define L_ADEPT 64           /* country */
#define L_TACTICAL_EXIT 65   /* country, sort of */

/* allow a couple more country sites: 66, 67, 68 */

/* final abyss sites; ignore levitation */
#define L_EARTH_STATION 69
#define L_FIRE_STATION 70
#define L_WATER_STATION 71
#define L_AIR_STATION 72
#define L_VOID_STATION 73
#define L_VOID 74
#define L_VOICE1 75
#define L_VOICE2 76
#define L_VOICE3 77

/* circle hq sites */
#define L_TOME1 78
#define L_TOME2 79
#define L_ENTER_CIRCLE 80
#define L_CIRCLE_LIBRARY 81

/* other site functions, particular dungeons or special levels */

#define L_ARENA_EXIT 82    /* arena */
#define L_ENTER_COURT 83  /* castle */
#define L_THRONE 84       /* court of the archmage */
#define L_ESCALATOR 85    /* court of the archmage */
#define L_WHIRLWIND 86     /* astral */
#define L_HOUSE_EXIT 87    /* house */
#define L_SAFE 88          /* house */

/* unused site functions, these were defined, so I left them defined -- DAG */

#define L_OMEGA 89 /* not currently used */
#define L_DRUID 90  /* not currently used */
#define L_WARNING 91  /* not currently used */
#define L_OCCUPIED_HOUSE 92 /* not currently used */
#define L_FINAL_ABYSS 93 /* not currently used */

/* dungeon locations */
struct location
{
    unsigned char p_locf; /* function executed when moved on */
    unsigned char lstatus; /* seen,stopsrun,lit,secret, */
    unsigned char roomnumber; /* so room can be named */
    Symbol locchar; /* terrain type */
    Symbol showchar; /*char instantaneously drawn for site */
    int aux; /* signifies various things */
    unsigned char buildaux; /* used in constructing level */
    struct objectlist* things;
    struct monster* creature;
};

typedef struct location loctype;
typedef loctype *plc;

#endif
