#ifndef LOCATION_H
#define LOCATION_H

#include "symbol.h"
#include "object.h"
#include "monster.h"

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
