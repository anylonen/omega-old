#ifndef OBJECT_H
#define OBJECT_H

#include "symbol.h"

/* number of slots in inventory. Cannot be changed without work */
#define MAXITEMS 16

/* number of slots in pack. Should be <= 26. */
#define MAXPACK 26

struct object
{
    int id, weight, plus, charge, dmg, hit, aux, number, fragility;
    long basevalue;
    unsigned char known, used;
    int blessing;
    unsigned char type, uniqueness;
    int usef;
    unsigned char level;
    Symbol objchar;
    char* objstr, *truename, *cursestr;
};

struct objectlist
{
    struct object* thing;
    struct objectlist* next;
};

#endif
