/* omega copyright (c) 1987,1988,1989 by Laurence Raphael Brothers */
/* This file is the header file for all omega modules */
/* defs.h */

/* omega will NOT function unless the implementor sets the appropriate
definitions in the following section. */

/* Transferred typedefs */
#include "symbol.h"
#include "environment.h"
#include "game_progress.h"
#include "attack.h"
#include "talk.h"
#include "functions.h"

#include "bank_account.h"
#include "room.h"
#include "spell.h"
#include "monster.h"
#include "object.h"
#include "terrain.h"
#include "location.h"
#include "level.h"
#include "player.h"

/*--------------------------USER DEFINITIONS--------------------------*/

/* Some minor quote changes...  This #define should be removed after some
 * public review, and the acceptable changes made permanent. */
#define NEW_QUOTES
/* A few parody quotes...  These have to be checked to make sure that they
 * make sense even if you don't know what they're parodying. */
#define TRADEMARK_VIOLATION

/* Update the display every turn to center on the player.  Rather heavy
 * on the bandwidth. */
/* #define CENTER_ON_PLAYER */

#define NEW_BANK

/* Implementor should uncomment the following if his system uses
string.h instead of strings.h (try man string) */

#define STRING

/* Implementor should define int32 as the type of integer which uses
 * 32 bits. */
typedef int int32;

/* Implementor should uncomment the following if getopt is not 
   available */

/* #define NOGETOPT */

/* Implementor should uncomment the following if omega appears to
redraw the screen excessively. */

#define EXCESSIVE_REDRAW

/* The following definition is recommended. Remove it only if you have
huge amounts of disk space and are annoyed at waiting a few more seconds
on save and restore. */

/*#define COMPRESS_SAVE_FILES*/

/* If your system has gzip, I recommend using it instead of compress */
/* (try just typing 'gzip' at the shell prompt) */

#define USE_GZIP

/* If your system doesn't have the usleep call, uncomment this line */
/* (try man usleep) */

/* #define NO_USLEEP */

/* Define the maximum length of a filename on your system.  If you don't */
/* define, will try to make an educated guess.  If you have one,  */
/* /usr/include/limits.h  is a good place to look for this value. */
/* DOS needn't worry; I'm forcing its FNAME_MAX_LENGTH to 8 elsewhere
 * in this file (we'll wait for LFN support). */
#define FNAME_MAX_LEN 48

/* OMEGALIB is where all the data files reside. 
   Note the final / is necessary.
   msdos note: \ is the C string escape character, so you need \\ in the
   path given in OMEGALIB
   This might usually be "/usr/games/lib/omegalib/", for unix,
   or something like "c:\\games\\omega\\omegalib\\" for msdos */

#define OMEGALIB "./lib/"
#define OMEGAVAR "./lib/"

/* TILEFILE is the name of the file you want to use for graphics tiles. You */
/* aren't really free to use any file you want here. It should be the Omega */
/* distribution graphics files provided for your computer. Of course a file */
/* of the same format and size as the "correct" file will also work if you */
/* want to change things around. This file should be located in OMEGALIB */

#define TILEFILE "omegatiles.xpm"

/* Comment the following line out if you want users to be able to override */
/* the OMEGALIB define, above, by setting the environment variable OMEGALIB */
/* (I recommend leaving this line uncommented, unless you're compiling */
/* for someone else and don't know where they'll be putting the omegalib */
/* directory, as is the case with compiling executables for home computers. */
/* It would be downright insecure to comment this line out in a multi-user */
/* environment, especially if you're going to run omega setuid.) */

#define FIXED_OMEGALIB

/* set WIZARD to maintainers's username */

#define WIZARD "root"

/* If CATCH_SIGNALS is set to 1, will not dump core, nicer for players. */
/* dbx still intercepts the signals first, so it's ok for debugging */

#define CATCH_SIGNALS 1


/*---------------------------SYSTEM DEFINITIONS---------------------------*/

/* Don't change anything from here on (unless you know what you're doing) */
#define VERSION 9002
#define VERSIONSTRING "omega version 0.90"

#ifndef AMIGA
#ifndef MSDOS
#ifndef BSD
#ifndef SYSV
    ERROR! - One of these should be set - edit the makefile appropriately
#endif
#endif
#endif
#endif

/*
 * WDT: according to my man page, getopt should be defined in unistd.h,
 * but my compiler seems to disagree unless this is set.  I hope that
 * this doesn't break too many things. */
/*#define __USE_POSIX2*/

#if defined(MSDOS_SUPPORTED_ANTIQUE)
#define SAVE_LEVELS
#endif

#ifdef COMPRESS_SAVE_FILES
# ifdef USE_GZIP
# define COMPRESSOR "gzip"
# define UNCOMPRESSOR "gunzip"
# define COMPRESS_EXT "gz"
# define EXT_LENGTH 2
# else
# define COMPRESSOR "compress"
# define UNCOMPRESSOR "uncompress"
# define COMPRESS_EXT "Z"
# define EXT_LENGTH 1
# endif
#else
# define EXT_LENGTH 0
#endif

#if !defined(FNAME_MAX_LEN) || defined(MSDOS)
# ifdef MSDOS
#  undef FNAME_MAX_LEN
#  define FNAME_MAX_LEN 7
# else
#  define FNAME_MAX_LEN 14
# endif
#endif


#define VACANT 0
#define ABORT -1
#define CASHVALUE -2

/* moderately arbitrary but probably cannot be easily changed */
#define SMALLSCREEN_LENGTH 16
#define SMALLSCREEN_WIDTH 64

#define STANDARD_LENGTH 64
#define STANDARD_WIDTH 64



#define ARENA_WIDTH SMALLSCREEN_WIDTH
#define ARENA_LENGTH SMALLSCREEN_LENGTH

#define ABYSS_WIDTH STANDARD_WIDTH
#define ABYSS_LENGTH SMALLSCREEN_LENGTH

#define ASTRAL_WIDTH STANDARD_WIDTH
#define ASTRAL_LENGTH STANDARD_LENGTH

#define CASTLE_WIDTH STANDARD_WIDTH
#define CASTLE_LENGTH STANDARD_LENGTH

#define CAVES_WIDTH STANDARD_WIDTH
#define CAVES_LENGTH STANDARD_LENGTH

#define CIRCLE_WIDTH SMALLSCREEN_WIDTH
#define CIRCLE_LENGTH SMALLSCREEN_LENGTH

#define COUNTRY_WIDTH STANDARD_WIDTH
#define COUNTRY_LENGTH STANDARD_LENGTH

#define COURT_WIDTH SMALLSCREEN_WIDTH
#define COURT_LENGTH 24

#define DLAIR_WIDTH SMALLSCREEN_WIDTH
#define DLAIR_LENGTH SMALLSCREEN_LENGTH

#define HOUSE_WIDTH SMALLSCREEN_WIDTH
#define HOUSE_LENGTH SMALLSCREEN_LENGTH

#define HOVEL_WIDTH SMALLSCREEN_WIDTH
#define HOVEL_LENGTH SMALLSCREEN_LENGTH

#define MANSION_WIDTH SMALLSCREEN_WIDTH
#define MANSION_LENGTH SMALLSCREEN_LENGTH

#define MISLE_WIDTH SMALLSCREEN_WIDTH
#define MISLE_LENGTH SMALLSCREEN_LENGTH

#define PALACE_WIDTH STANDARD_WIDTH
#define PALACE_LENGTH STANDARD_LENGTH

#define RAMPART_WIDTH 128
#define RAMPART_LENGTH STANDARD_LENGTH

#define SEWERS_WIDTH STANDARD_WIDTH
#define SEWERS_LENGTH STANDARD_LENGTH

#define SPEAK_WIDTH SMALLSCREEN_WIDTH
#define SPEAK_LENGTH SMALLSCREEN_LENGTH

#define TACTICAL_WIDTH SMALLSCREEN_WIDTH
#define TACTICAL_LENGTH SMALLSCREEN_LENGTH

#define TEMPLE_WIDTH SMALLSCREEN_WIDTH
#define TEMPLE_LENGTH SMALLSCREEN_LENGTH

#define VILLAGE_WIDTH SMALLSCREEN_WIDTH
#define VILLAGE_LENGTH SMALLSCREEN_LENGTH

#define VOLCANO_WIDTH STANDARD_WIDTH
#define VOLCANO_LENGTH STANDARD_LENGTH

/* number of items in pawn shop. Should be <= 26 */
#define PAWNITEMS 20 /* DG -- the more the merrier.  WDT -- I agree. */

/* number of lines back strings are recalled */
#define STRING_BUFFER_SIZE 25

/* number of rerolls allowed +1 */  /* added by dagibbs (DG) */
#define REROLLS -1

/* Verbosity levels */
#define TERSE 0
#define MEDIUM 1
#define VERBOSE 2 

/* Arbitrary. Max of the levels in the dungeons */
#define MAXLEVELS 21

/* levels in each dungeon */
#define ASTRALLEVELS 5
#define SEWERLEVELS 18
#define CASTLELEVELS 16
#define CAVELEVELS 10
#define VOLCANOLEVELS 20
#define PALACELEVELS 14

/* player game status */
#define DEAD 1
#define QUIT 2
#define WIN 3
#define BIGWIN 4

/* kind of arbitrary */
#define MAXROOMS 48
#define MAXCONNECTIONS 4 
#define STRING_LEN 100

/* some random characters */
#define ESCAPE 27
#define RETURN '\n' /* Aren't these backwards? WSS */
#define LINEFEED '\r' /* Aren't these backwards? WSS */
#define BACKSPACE '\b'
#define DELETE 127


/* random aux constants */
/* aux field for private residences in city */
#define BURGLED 2
#define LOCKED 3
#define UNLOCKED 0

/* cannot use M command on site with this aux value */
#define NOCITYMOVE 666

/* bow and crossbow object aux fields */
#define LOADED 1
#define UNLOADED 0

/* alignment used randomly throughout*/
#define LAWFUL 1
#define CHAOTIC 2
#define NEUTRAL 3

/* MONSTER STATUS/ABILITY BITS */
#include "monster_ability.h"
    
/* location lstatus bits */
#define SEEN 1
#define LIT 2
#define SECRET 4
#define STOPS 8
#define CHANGED 16


/* Colors */
#include "colors.h"
    
/* objects, locations, and terrain; characters to draw */
#define NULL_ITEM '\0'
#define SPACE (' ' | CLR(WHITE))
#define WALL ('#' | CLR(GREY))
#define PORTCULLIS ('7' | CLR(WHITE))
#define OPEN_DOOR ('|' | CLR(BROWN))
#define CLOSED_DOOR ('-' | CLR(BROWN))
#define WHIRLWIND ('6' | CLR(LIGHT_BLUE))
#define ABYSS ('0' | CLRS(BLACK,BROWN))
#define VOID_CHAR (' ' | CLR(WHITE))
#define LAVA ('`' | CLR(RED))
#define HEDGE ('\"' | CLR(GREEN))
#define WATER ('~' | CLR(BLUE))
#define FIRE (';' | CLR(LIGHT_RED))
#define TRAP ('^' | CLR(RED))
#define LIFT ('_' | CLR(BRIGHT_WHITE))
#define STAIRS_UP ('<' | CLR(WHITE))
#define STAIRS_DOWN ('>' | CLR(WHITE))
#define FLOOR ('.' | CLR(BROWN))
#define PLAYER ('@' | CLR(WHITE))
#define CORPSE ('+' | CLR(RED))
#define STATUE ('1' | CLR(GREY))
#define RUBBLE ('4' | CLR(GREY))
#define ALTAR ('8' | CLR(LIGHT_BLUE))
#define CASH ('$' | CLR(YELLOW))	/* various kinds of money */
#define PILE ('*' | CLR(BRIGHT_WHITE))	/* several objects in one place */
#define FOOD ('%' | CLR(BROWN))
#define WEAPON (')' | CLR(GREY))
#define MISSILEWEAPON ('(' | CLR(BROWN))
#define SCROLL ('?' | CLR(YELLOW))
#define POTION ('!' | CLR(LIGHT_GREEN))
#define ARMOR (']' | CLR(GREY))
#define SHIELD ('[' | CLR(BROWN))
#define CLOAK ('}' | CLR(CYAN))
#define BOOTS ('{' | CLR(BROWN))
#define STICK ('/' | CLR(BROWN))

#define RING ('=' | CLR(YELLOW))
#define THING ('\\' | CLR(WHITE))
#define ARTIFACT ('&' | CLR(YELLOW))

/* TERRAIN TYPES */
#include "terrain_types.h"

/* total number of editable stats */
#define NUMSTATS 11

/* total number of player options */
#define NUMOPTIONS 11

/* number of options with TRUE/FALSE values */
#define NUMTFOPTIONS 9

/* The slot number of the two options not in Player.options */
#define VERBOSITY_LEVEL 10
#define SEARCH_DURATION 11

/* Player.options bits */
#include "player_options.h"

/* This has to be changed whenever an item is added */
#define NUMSCROLLS 24
#define NUMPOTIONS 18
#define NUMFOODS 16
#define NUMTHINGS 31 /* DAG for mirror of self-knowledge */ /* WSS cards */
#define NUMCARDS 4
#define NUMWEAPONS 41
#define NUMARMOR 17
#define NUMSHIELDS 8
#define NUMCLOAKS 7
#define NUMBOOTS 7
#define NUMRINGS 9  /* DAG loss of ring of self-knowledge */
#define NUMSTICKS 17
#define NUMARTIFACTS 26

/* running sum of itemtypes, for indexing into Objects array */
#define THINGID 0 
#define CARDID (THINGID+NUMTHINGS-NUMCARDS)
#define FOODID NUMTHINGS    /* 26 */
#define SCROLLID (FOODID + NUMFOODS)  /* 42 */
#define POTIONID (SCROLLID + NUMSCROLLS) /* 66 */
#define WEAPONID (POTIONID + NUMPOTIONS)  /* 84 */
#define ARMORID (WEAPONID + NUMWEAPONS) /* 125 */
#define SHIELDID (ARMORID + NUMARMOR)  /* 142 */
#define CLOAKID (SHIELDID + NUMSHIELDS)  /* 150 */
#define BOOTID (CLOAKID + NUMCLOAKS)  /* 157 */
#define RINGID (BOOTID + NUMBOOTS)  /* 164 */
#define STICKID (RINGID + NUMRINGS) /* 174 */
#define ARTIFACTID (STICKID + NUMSTICKS)  /* 191 */
#define CASHID (ARTIFACTID+NUMARTIFACTS)  /* 216 */
/* Corpse's aux field is monster id */
#define CORPSEID (CASHID+1)

#define TOTALITEMS (CORPSEID+1)

/* descriptive constants for various object ids */
#define OB_GARAGE_OPENER (THINGID+0)
#define OB_LOCK_PICK (THINGID+2)
#define OB_SALT_WATER (THINGID+6)
#define OB_KEY (THINGID+7)
#define OB_TORCH (THINGID+8)
#define OB_JUSTICIAR_BADGE (THINGID+16)
#define OB_TRAP_DART (THINGID+17)
#define OB_TRAP_ACID (THINGID+18)
#define OB_TRAP_SNARE (THINGID+19)
#define OB_TRAP_FIRE (THINGID+20)
#define OB_TRAP_TELEPORT (THINGID+21)
#define OB_TRAP_SLEEP (THINGID+22)
#define OB_TRAP_DISINTEGRATE (THINGID+23)
#define OB_TRAP_ABYSS (THINGID+24)
#define OB_TRAP_MANADRAIN (THINGID+25)
#define OB_DEBIT_CARD (CARDID+0)
#define OB_CREDIT_CARD (CARDID+1)
#define OB_PREPAID_CARD (CARDID+2)
#define OB_SMART_CARD (CARDID+3)
#define OB_RATION (FOODID+0)
#define OB_LEMBAS (FOODID+1)
#define OB_GRAIN (FOODID+15)
#define OB_BLANK_SCROLL (SCROLLID+0)
#define OB_SPELLS_SCROLL (SCROLLID+1)
#define OB_SCROLL_LAW (SCROLLID+17)
#define OB_POTION_CHAOS (POTIONID+14)
#define OB_SHORT_SWORD (WEAPONID+1)
#define OB_GREAT_SWORD  (WEAPONID+5)
#define OB_GREAT_AXE  (WEAPONID+12)
#define OB_CLUB  (WEAPONID+17)
#define OB_QUARTERSTAFF  (WEAPONID+18)
#define OB_SPEAR  (WEAPONID+19)
#define OB_HALBERD  (WEAPONID+20)
#define OB_MACE_DISRUPT  (WEAPONID+25)
#define OB_LONGBOW  (WEAPONID+26)
#define OB_CROSSBOW  (WEAPONID+27)
#define OB_ARROW  (WEAPONID+28)
#define OB_BOLT  (WEAPONID+29)
#define OB_DESECRATOR  (WEAPONID+32)
#define OB_DEFENDER  (WEAPONID+34)
#define OB_VICTRIX  (WEAPONID+35)
#define OB_HEWER  (WEAPONID+36)
#define OB_GIANT_CLUB  (WEAPONID+38)
#define OB_SCYTHE_DEATH  (WEAPONID+39)
#define OB_LEATHER (ARMORID+1)
#define OB_MITHRIL_PLATE (ARMORID+11)
#define OB_DRAGONSCALE (ARMORID+12)
#define OB_LRG_RND_SHIELD (SHIELDID+2)
#define OB_DEFLECT (SHIELDID+7)
#define OB_CLOAK_PROTECT (CLOAKID+4)
#define OB_ORB_MASTERY (ARTIFACTID+0)
#define OB_ORB_FIRE (ARTIFACTID+1)
#define OB_ORB_WATER (ARTIFACTID+2)
#define OB_ORB_EARTH (ARTIFACTID+3)
#define OB_ORB_AIR (ARTIFACTID+4)
#define OB_DEAD_ORB (ARTIFACTID+5)
#define OB_ANTIOCH (ARTIFACTID+7)
#define OB_YENDOR (ARTIFACTID+8)
#define OB_KOLWYNIA (ARTIFACTID+9)
#define OB_POTION_DEATH (ARTIFACTID+10)
#define OB_POTION_LIFE (ARTIFACTID+13)
#define OB_SYMBOL_ODIN (ARTIFACTID+14)
#define OB_SYMBOL_SET (ARTIFACTID+15)
#define OB_SYMBOL_ATHENA (ARTIFACTID+16)
#define OB_SYMBOL_HECATE (ARTIFACTID+17)
#define OB_SYMBOL_DRUID (ARTIFACTID+18)
#define OB_SYMBOL_DESTINY (ARTIFACTID+19)
#define OB_KARNAK (ARTIFACTID+20)
#define OB_STARGEM (ARTIFACTID+21)
#define OB_SCEPTRE (ARTIFACTID+22)
#define OB_HOLDING (ARTIFACTID+24)

/* describing unique items and monsters */
#define COMMON 0
#define UNIQUE_UNMADE 1
#define UNIQUE_MADE 2
#define UNIQUE_TAKEN 3

/* general item function id's */
#define I_NO_OP 0
#define I_NOTHING 1

  /* note some of these functions are for other types of items too */

    /* scroll functions */
#define I_BLESS 101
#define I_ACQUIRE 102
#define I_ENCHANT 103
#define I_TELEPORT 104
#define I_WISH 105
#define I_CLAIRVOYANCE 106
#define I_DISPLACE 107
#define I_ID 108
#define I_FIREFLASH 109
#define I_SPELLS 110
#define I_JANE_T 111
#define I_ALERT 112
#define I_FLUX 113
#define I_CHARGE 114
#define I_WARP 115
#define I_KNOWLEDGE 116
#define I_LAW 117
#define I_HINT 118
#define I_HERO 119
#define I_TRUESIGHT 120
#define I_ILLUMINATE 121
#define I_DEFLECT 122

    /* potion functions */
#define I_HEAL 201
#define I_OBJDET 202
#define I_MONDET 203
#define I_SLEEP_SELF 204
#define I_RESTORE 205
#define I_NEUTRALIZE_POISON 206
#define I_SPEED 207
#define I_AZOTH 208
#define I_REGENERATE 210
#define I_INVISIBLE 211
#define I_BREATHING 212
#define I_FEAR_RESIST 213
#define I_AUGMENT 214
#define I_CHAOS 215
#define I_ACCURACY 216
#define I_LEVITATION 217
#define I_CURE 218

    /* stick functions */
#define I_FIREBOLT 301
#define I_LBOLT 302
#define I_MISSILE 303
#define I_SLEEP_OTHER 304
#define I_FIREBALL 305
#define I_LBALL 306
#define I_SUMMON 307
#define I_HIDE 308
#define I_DISRUPT 309
#define I_DISINTEGRATE 310
#define I_SNOWBALL 311
#define I_APPORT 312
#define I_DISPEL 313
#define I_POLYMORPH 314
#define I_FEAR 315

    /* food functions */
#define I_FOOD 401
#define I_LEMBAS 402
#define I_STIM 403
#define I_POW 404
#define I_IMMUNE 405
#define I_POISON_FOOD 406
#define I_CORPSE 407
#define I_PEPPER_FOOD 408
#define I_CANNIBAL 409
#define I_INEDIBLE 410

    /* boots functions */
#define I_PERM_SPEED 501
#define I_PERM_HERO 502
#define I_PERM_LEVITATE 503
#define I_PERM_AGILITY 504
#define I_BOOTS_JUMPING 505
#define I_BOOTS_7LEAGUE 506

    /* cloak functions */
#define I_PERM_DISPLACE 601
#define I_PERM_NEGIMMUNE 602
#define I_PERM_INVISIBLE 603
#define I_PERM_ACCURACY 604
#define I_PERM_PROTECTION 605
#define I_PERM_TRUESIGHT 606

    /* ring functions */
#define I_PERM_VISION 701
#define I_PERM_BURDEN 702
#define I_PERM_STRENGTH 703
#define I_PERM_GAZE_IMMUNE 704
#define I_PERM_FIRE_RESIST 705
#define I_PERM_POISON_RESIST 706
#define I_PERM_REGENERATE 707
#define I_PERM_KNOWLEDGE 708

    /* armor functions */
#define I_PERM_ENERGY_RESIST 801
#define I_PERM_BREATHING 802
#define I_PERM_FEAR_RESIST 803
#define I_NORMAL_ARMOR 804

/* artifact functions */
#define I_ORBFIRE 901
#define I_ORBWATER 902
#define I_ORBEARTH 903
#define I_ORBAIR 904
#define I_ORBMASTERY 905
#define I_ORBDEAD 906
#define I_CRYSTAL 907
#define I_ANTIOCH 908
#define I_KOLWYNIA 909
#define I_DEATH 910
#define I_ENCHANTMENT 911
#define I_HELM 912
#define I_LIFE 913
#define I_JUGGERNAUT 914
#define I_SYMBOL 915
#define I_STARGEM 916
#define I_SCEPTRE 917
#define I_PLANES 918
#define I_HOLDING 919
#define I_SERENITY 920

/* weapons functions */
#define I_NORMAL_WEAPON 1001
#define I_LIGHTSABRE 1002
#define I_DEMONBLADE 1003
#define I_MACE_DISRUPT 1004
#define I_TANGLE 1005
#define I_ARROW 1006
#define I_BOLT 1007
#define I_VORPAL 1008
#define I_DESECRATE 1009
#define I_FIRESTAR 1010
#define I_DEFEND 1011
#define I_VICTRIX 1012
#define I_EMPIRE 1013
#define I_SCYTHE 1014
#define I_ACIDWHIP 1015

/* thing functions */
#define I_PICK 1101
#define I_KEY 1102
#define I_SHOVEL 1103 /* unused */
#define I_EXCAVATOR 1104 /* unused */
#define I_PERM_ILLUMINATE 1105
#define I_TRAP 1106
#define I_RAISE_PORTCULLIS 1107

/* shield functions */
#define I_PERM_DEFLECT 1201
#define I_NORMAL_SHIELD 1202

/* monster function ids */
/* Its conceivable for a function of one type to be called when another
would usually occur. A monster's special function may be an extra move,
for example. */

#define M_NO_OP -1

/* ability functions */
#define M_SP_SURPRISE 201
#define M_SP_MP 202
#define M_SP_THIEF 203
#define M_SP_AGGRAVATE 204
#define M_SP_POISON_CLOUD 205
#define M_SP_HUGE 206
#define M_SP_SUMMON 207
#define M_SP_ILLUSION 208
#define M_SP_FLUTTER 209
#define M_SP_ESCAPE 210
#define M_SP_SPELL 211
#define M_SP_EXPLODE 212
#define M_SP_DEMON 213
#define M_SP_ACID_CLOUD 214
#define M_SP_WHIRL 215
#define M_SP_GHOST 216
#define M_SP_WHISTLEBLOWER 217
#define M_SP_EATER 218
#define M_SP_LAWBRINGER 219
#define M_SP_DRAGONLORD 220
#define M_SP_DE 221
#define M_SP_DEMONLOVER 222
#define M_SP_SEDUCTOR 223
#define M_SP_MASTER 224
#define M_SP_WYRM 225
#define M_SP_BLACKOUT 226
#define M_SP_BOG 227
#define M_SP_MERCHANT 228
#define M_SP_WERE 229
#define M_SP_SERVANT 231
#define M_SP_AV 232
#define M_SP_LW 233
#define M_SP_SWARM 234
#define M_SP_ANGEL 235
#define M_SP_MB 236
#define M_SP_MIRROR 237
#define M_SP_RAISE 238
#define M_SP_DEATH 239
#define M_SP_COURT 240
#define M_SP_LAIR 241
#define M_SP_PRIME 242

/* rangestrike functions */
#define M_STRIKE_MISSILE 301
#define M_STRIKE_FBOLT 302
#define M_STRIKE_LBALL 303
#define M_STRIKE_FBALL 304
#define M_STRIKE_BLIND 305
#define M_STRIKE_SNOWBALL 306
#define M_STRIKE_MASTER 307
#define M_STRIKE_SONIC 308

/* combat functions */
#define M_MELEE_NORMAL 401
#define M_MELEE_FIRE 402
#define M_MELEE_DRAGON 403
#define M_MELEE_MP 404
#define M_MELEE_ELEC 405
#define M_MELEE_POISON 406
#define M_MELEE_NG 407
#define M_MELEE_SUCCUBUS 408
#define M_MELEE_SPIRIT 409
#define M_MELEE_DISEASE 410
#define M_MELEE_SLEEP 411
#define M_MELEE_COLD 412
#define M_MELEE_MASTER 413
#define M_MELEE_GRAPPLE 414
#define M_MELEE_DEATH 415

/* movement functions */
#include "movement.h"
    
/* MLx -> index to Monsters starting for level x */
/* MLx -> number of monsters of level x or less */
/* NML_x -> number of monsters of level x */
/* NML-X must be changed whenever a monster is added */
/* This whole thing MUST be repaired.  Monster levels must
 * be represented elsewhere. */
#define ML0 0
#define NML_0 9
#define ML1 (ML0 + NML_0) /* 9 */
#define NML_1 22
#define ML2 (ML1 + NML_1) /* 31 */
#define NML_2 14
#define ML3 (ML2 + NML_2) /* 45 */
#define NML_3 15
#define ML4 (ML3 + NML_3) /* 60 */
#define NML_4 18
#define ML5 (ML4 + NML_4) /* 78 */
#define NML_5 14
#define ML6 (ML5 + NML_5) /* 92 */
#define NML_6 13
#define ML7 (ML6 + NML_6) /* 105 */
#define NML_7 15
#define ML8 (ML7 + NML_7) /* 120 */
#define NML_8 12
#define ML9 (ML8 + NML_8) /* 132 */
#define NML_9 8
#define ML10 (ML9 + NML_9) /* 140 */
#define NML_10 11

#define NUMMONSTERS (ML10 + NML_10)  /* 151 */

/* Some monster ID's : (Those that are explicitly named in code) */
/* Actually, there are still many magic constants floating around. */
/* Eventually I'll get around to making each monster's id a constant.... */
/* done, thanks to David Gibbs. */
#define RANDOM -1
#define HORNET (ML0+0)
#define MEND_PRIEST (ML0+1)
#define ITIN_MERCH (ML0+2)
#define GUARD (ML0+3)
#define NPC (ML0+4)
#define SHEEP (ML0+5)
#define MERCHANT (ML0+6)
#define ZERO_NPC (ML0+7)
#define HISCORE_NPC (ML0+8)
#define GRUNT (ML1+0)
#define TSETSE (ML1+1)
#define FNORD (ML1+2)
#define SEWER_RAT (ML1+3)
#define AGGRAVATOR (ML1+4)
#define BLIPPER (ML1+5)
#define GOBLIN (ML1+6)
#define PHANTASTICON (ML1+7)
#define ROBOT (ML1+8)
#define GEEK (ML1+9)
#define BOROGROVE (ML1+10)
#define QUAIL (ML1+11)
#define BADGER (ML1+12)
#define HAWK (ML1+13)
#define DEER (ML1+14)
#define CAMEL (ML1+15)
#define ANTEATER (ML1+16)
#define BUNNY (ML1+17)
#define TROUT (ML1+18)
#define BASS (ML1+19)
#define PARROT (ML1+20)
#define HYENA (ML1+21)
#define APPR_NINJA (ML2+0)
#define NIGHT_GAUNT (ML2+1)
#define SNEAK_THIEF (ML2+2)
#define EYE (ML2+3)
#define TOVE (ML2+4)
#define NASTY (ML2+5)
#define GHOST (ML2+6)
#define ENCHANTOR (ML2+7)  /* use 'OR' to avoid conflict with circle rank */
#define MURK (ML2+8)
#define GOBLIN_CHIEF (ML2+9)
#define WOLF (ML2+10)
#define ANT (ML2+11)
#define ELEPHANT (ML2+12)
#define HORSE (ML2+13)
#define SALAMANDER (ML3+0)
#define CATOBLEPAS (ML3+1)
#define L_FDEMON (ML3+2)
#define ACID_CLOUD (ML3+3)
#define PHANTOM (ML3+4)
#define GOBLIN_KING (ML3+5)
#define PTERODACTYL (ML3+6)
#define GOBLIN_SHAMAN (ML3+7)
#define LION (ML3+8)
#define BRIGAND (ML3+9)
#define BEAR (ML3+10)
#define MAMBA (ML3+11)
#define MANOWAR (ML3+12)
#define WEREHUMAN (ML3+13)
#define THOUGHTFORM (ML3+14)
#define MANTICORE (ML4+0)
#define TASMANIAN (ML4+1)
#define AUTO_MINOR (ML4+2)
#define DENEBIAN (ML4+3)
#define JUBJUB (ML4+4)
#define HAUNT (ML4+5)
#define INCUBUS (ML4+6)
#define SATYR (ML4+7)
#define CROC (ML4+8)
#define TORPOR (ML4+9)
#define DOBERMAN (ML4+10)
#define FUZZY (ML4+11)
#define SERV_LAW (ML4+12)
#define SERV_CHAOS (ML4+13)
#define SWARM (ML4+14)
#define BAN_SIDHE (ML4+15)
#define GRUE (ML4+16)
#define GENIN (ML4+17)
#define DRAGONETTE (ML5+0)
#define TESLA (ML5+1)
#define WYVERN (ML5+2)
#define CATEAGLE (ML5+3)
#define FROST_DEMON (ML5+4)
#define SPECTRE (ML5+5)
#define NECROMANCER (ML5+6)
#define SHADOW (ML5+7)
#define BOGTHING (ML5+8)
#define ASTRAL_VAMP (ML5+9)
#define LAVA_WORM (ML5+10)
#define MANABURST (ML5+11)
#define OUTER_DEMON (ML5+12)
#define MIRRORSHADE (ML5+13)
#define FIRE_ELEM (ML6+0)
#define AIR_ELEM (ML6+1)
#define WATER_ELEM (ML6+2)
#define EARTH_ELEM (ML6+3)
#define BANDERSNATCH (ML6+4)
#define LICHE (ML6+5)
#define TRITON (ML6+6)
#define MAST_THIEF (ML6+7)
#define TRICER (ML6+8)
#define RAKSHASA (ML6+9)
#define DEMON_SERP (ML6+10)
#define ANGEL (ML6+11)
#define CHUNIN (ML6+12)
#define BEHEMOTH (ML7+0)
#define NAZGUL (ML7+1)
#define UNICORN (ML7+2)
#define ROUS (ML7+3)
#define ILL_FIEND (ML7+4)
#define GREAT_WYRM (ML7+5)
#define FLAME_DEV (ML7+6)
#define LURKER (ML7+7)
#define SANDMAN (ML7+8)
#define MIRRORMAST (ML7+9)
#define ELDER_GRUE (ML7+10)
#define LOATHLY (ML7+11)
#define ZOMBIE (ML7+12)
#define RICOCHET (ML7+13)
#define INNER_DEMON (ML7+14)
#define GOOD_FAIRY (ML8+0)
#define BAD_FAIRY (ML8+1)
#define AUTO_MAJOR (ML8+2)
#define DRAGON (ML8+3)
#define JABBERWOCK (ML8+4)
#define FDEMON_L (ML8+5)
#define TIGERSHARK (ML8+6)
#define JONIN (ML8+7)
#define SHADOW_SLAY (ML8+8)
#define MIL_PRIEST (ML8+9)
#define COMA (ML8+10)
#define HIGH_ANGEL (ML8+11)
#define JOTUN (ML9+0)
#define INVIS_SLAY (ML9+1)
#define KING_WYV (ML9+2)
#define DEATHSTAR (ML9+3)
#define THAUMATURGIST (ML9+4)
#define VAMP_LORD (ML9+5)
#define ARCHANGEL (ML9+6)
#define DEMON_PRINCE (ML9+7)
#define DEATH (ML10+0)
#define EATER (ML10+1)
#define LAWBRINGER (ML10+2)
#define DRAGON_LORD (ML10+3)
#define DEMON_EMP (ML10+4)
#define LORD_EARTH (ML10+5)
#define LORD_AIR (ML10+6)
#define LORD_WATER (ML10+7)
#define LORD_FIRE (ML10+8)
#define ELEM_MASTER (ML10+9)
#define MAHARAJA (ML10+10)

/* hold for 94, 95, 96, 97, 98, 99 still in the affect player while
   levitating range */

/* greater than LEVITATION_AVOIDANCE, no effect if player is levitating */
#define LEVITATION_AVOIDANCE 100

/* traps */
#include "traps.h"

/* random sites */
#include "sites.h"

#define L_DROP_EVERY_PORTCULLIS 131 /* tested, but never set */

/* unused site functions, these were defined, so I left them defined -- DAG */
#define L_STATUE_RANDOM 132  /* not currently used */

/* player possession slots */
#include "possession.h"

/* How depressingly stupid that there weren't already defined.  WDT. */
#include "village.h"

/* Changing these would currently require changing the maps as well (although
 * there should be no other side effects).  I intend to remove the need for
 * this list later, by making the maps refer to each other (and thus removing
 * the need for the game to know about anything but map 0), but that comes
 * MUCH later. */
enum map_identifier {
    MAP_country=0,
    MAP_arena=1,
    MAP_circle=2,
    MAP_city=3,
    MAP_abyss=4,
    MAP_court=5,
    MAP_dlair=6,
    MAP_hedges=7,
    MAP_house=8,
    MAP_hovel=9,
    MAP_mansion=10,
    MAP_misle=11,
    MAP_skorch=12,
    MAP_speak=13,
    MAP_starview=14,
    MAP_stormwat=15,
    MAP_temple=16,
    MAP_thaumari=17,
    MAP_whorfen=18,
    MAP_woodmere=19,
};

/* typedefs needed by structs */

/* I don't ever define map_type (except in the C file where it's used); this
 * means that you _must_ declare only pointers to it.  I've defined, of
 * course, all of the needed accessor and mutator functions; see externs.h,
 * in the map.c section. */
struct map_type;
typedef struct map_type map;

#ifdef SAVE_LEVELS
plv msdos_changelevel();
#endif
