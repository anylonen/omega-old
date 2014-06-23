#ifndef MAP_H
#define MAP_H

/* I don't ever define map_type (except in the C file where it's used); this
 * means that you _must_ declare only pointers to it.  I've defined, of
 * course, all of the needed accessor and mutator functions; see externs.h,
 * in the map.c section. */
struct map_type;
typedef struct map_type map;

/* map.c functions */
map* map_open(enum map_identifier);
void map_setLevel(map*, int);
int map_getWidth(map*);
int map_getLength(map*);
int map_getDepth(map*);
char map_getSiteChar(map*, int, int);
void map_close(map*);

#endif
