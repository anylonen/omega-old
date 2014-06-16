#ifndef MONSTER_H
#define MONSTER_H

#include "symbol.h"

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
