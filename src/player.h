#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "monk.h"

/* player immunity indices */
/* also monster immunity bits (2^n) */
/* also damage types */
#define NUMIMMUNITIES 14
#define UNSTOPPABLE 0 
#define NORMAL_DAMAGE 1
#define FLAME 2
#define COLD 3
#define ELECTRICITY 4
#define POISON 5
#define ACID 6
#define FEAR 7
#define SLEEP 8
#define NEGENERGY 9
#define OTHER_MAGIC 10
#define THEFT 11
#define GAZE 12
#define INFECTION 13
#define EVERYTHING -1

/* PLAYER STATUS INDICES */
#define NUMSTATI 25

#define ACCURACY 0
#define BLINDED 1
#define SLOWED 2
#define DISPLACED 3
#define SLEPT 4
#define DISEASED 5
#define POISONED 6
#define HASTED 7
#define BREATHING 8
#define INVISIBLE 9
#define REGENERATING 10
#define VULNERABLE 11
#define BERSERK 12
#define IMMOBILE 13
#define ALERT 14
#define AFRAID 15
#define HERO 16
#define LEVITATING 17
#define ACCURATE 18
#define TRUESIGHT 19
#define SHADOWFORM 20
#define ILLUMINATION 21
#define DEFLECTION 22
#define PROTECTION 23
/* PROTECTION is deviant -- indicates protective value, not duration */
#define RETURNING 24
/* RETURNING is somewhat deviant--how many turns 'til RETURN spell goes off */

/* ranks in guilds, etc */
#define NUMRANKS 10

#define LEGION 0
#define ARENA 1
#define COLLEGE 2
#define THIEVES 3
#define ORDER 4
#define CIRCLE 5
#define NOBILITY 6
#define PRIESTHOOD 7
#ifdef INCLUDE_MONKS
#define MONKS 8
#endif
#define ADEPT 9

#define LEGIONAIRE 1
#define CENTURION 2
#define FORCE_LEADER 3
#define COLONEL 4
#define COMMANDANT 5

#define TRAINEE 1
#define BESTIARIUS 2
#define RETIARIUS 3
#define GLADIATOR 4
#define CHAMPION 5

#define NOVICE 1
#define STUDENT 2
#define PRECEPTOR 3
#define MAGE 4
#define ARCHMAGE 5

#define TMEMBER 1
#define ATHIEF 2
#define THIEF 3
#define TMASTER 4
#define SHADOWLORD 5

#define GALLANT 1
#define GUARDIAN 2
#define CHEVALIER 3
#define PALADIN 4
#define JUSTICIAR 5

#define INITIATE 1
#define ENCHANTER 2
#define SORCEROR 3
#define HIGHSORCEROR 4
#define PRIME 5

#define COMMONER 1
#define ESQUIRE 2
#define KNIGHT 3
#define LORD 4
#define DUKE 5

#define LAY 1
#define ACOLYTE 2
#define PRIEST 3
#define SPRIEST 4
#define HIGHPRIEST 5

#ifdef INCLUDE_MONKS
#define MONK_TRAINEE 1
#define MONK_MONK 2
#define MONK_MASTER 3
#define MONK_MASTER_SIGHS 4
#define MONK_MASTER_PAINS 5
#define MONK_MASTER_TEARS 6
#define MONK_GRANDMASTER 7
#endif

/* different priesthoods */
#define ODIN 1
#define SET 2
#define ATHENA 3
#define HECATE 4
#define DRUID 5
#define DESTINY 6

struct player
{
    int str, con, dex, agi, iq, pow, maxstr, maxcon, maxdex, maxagi, maxiq, maxpow;
    long xp;
    int level, hp, maxhp, hit, dmg, absorption, speed, click;
    int defense, food, alignment;
    long mana, maxmana;
    long cash;
    int patron, birthday;
    char preference;
    int sx, sy; /* sanctuary coordinates */
    int x, y; /* current player coordinates */
    int itemweight, maxweight;
    int immunity[NUMIMMUNITIES];
    int status[NUMSTATI];
    long options;
    int rank[NUMRANKS];
    long guildxp[NUMRANKS];
    char name[64];
    char meleestr[64];
    struct object* possessions[MAXITEMS];
    struct object* pack[MAXPACK];
    int packptr;
};

void player_regenerate_hp();
void player_regenerate_mana();
void player_regenerate();

#endif
