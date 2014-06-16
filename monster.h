#ifndef MONSTER_H
#define MONSTER_H

#include "symbol.h"

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

struct monster
{
    struct objectlist* possessions;
    unsigned char attacked;
    int aux1, aux2, x, y, click;
    int id, hp, hit, ac, dmg, sense, wakeup, level, speed;
    unsigned char sleep, treasure;
    long xpv;
    int corpseweight, corpsevalue, transformid, startthing;
    unsigned char uniqueness;
    int talkf, movef, meleef, strikef, specialf;
    long status, immunity;
    Symbol monchar;
    char* monstring, *corpsestr, *meleestr;
};

struct monsterlist
{
    struct monster* m;
    struct monsterlist* next;
};

typedef struct monster montype;
typedef montype *pmt;

typedef struct monsterlist mltype;
typedef mltype *pml;

#endif
