#ifndef INVENTORY_H
#define INVENTORY_H

#include "monster.h"
#include "object.h"
#include "symbol.h"

/* inv.c functions */

void do_inventory_control( void );
int  key_to_index( signed char );
signed char index_to_key( int );
long get_money( long );
char* cashstr( void );
char* itemid( pob );
int baditem( int );
int badobject( char );
int cursed( pob );
int find_and_remove_item( int, int );
int find_item( pob*, int, int );
int get_inventory_slot( void );
int get_item_number( pob );
int get_to_pack( pob );
int getitem( Symbol );
int getitem_prompt (char*, Symbol);
int item_useable( pob, int );
int objequal( struct object*, struct object* );
int slottable( pob, int );
int take_from_pack( int, int );
pob detach_money( long );
pob split_item( int, pob );
void add_to_pack( pob );
void conform_lost_object( pob );
void conform_lost_objects( int, pob );
void conform_unused_object( pob );
void dispose_lost_objects( int, pob );
void drop_at( int, int, pob );
void drop_from_slot( int );
void drop_money( void );
void fixpack( void );
void gain_item( pob );
void give_money( struct monster* );
void givemonster( struct monster*, struct object* );
void inventory_control( void );
void item_inventory( int );
void lose_all_items( void );
void merge_item( int );
void p_drop_at( int, int, int, pob );
void pack_extra_items( pob );
void pickup_at( int, int );
void put_to_pack( int );
void setchargestr( pob, char* );
void setnumstr( pob, char* );
void setplustr( pob, char* );
void show_inventory_slot( int, int );
void switch_to_slot( int );
void top_inventory_control( void );

#endif
