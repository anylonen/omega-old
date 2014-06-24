#ifndef MONSTER_ABILITY_H
#define MONSTER_ABILITY_H

/* MONSTER STATUS/ABILITY BITS */
    /* currently a long */
#define AWAKE 1
#define MOBILE 2
#define HOSTILE 4
/* missing bit 3, 8 */
#define WANDERING 16
#define HUNGRY 32
#define GREEDY 64
#define NEEDY  128
#define ONLYSWIM 256
#define FLYING 512
#define INTANGIBLE 1024
#define M_INVISIBLE 2048
#define SWIMMING 4096
#define POISONOUS 8192
#define EDIBLE 16384
#define ALLOC 32768  /* allocated monstring & corpsestr */

#endif
