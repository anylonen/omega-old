#ifndef ROOM_H
#define ROOM_H

/* room string id */
/* for use in roomname() */
/* number of rooms above ROOMBASE */
#define NUMROOMNAMES 30  

#define RS_WALLSPACE 1
#define RS_CORRIDOR 2
#define RS_CAVERN 3
#define RS_GOBLINKING 4
#define RS_DRAGONLORD 5
#define RS_PONDS 6
#define RS_OCEAN 7 
#define RS_WYRM 8
#define RS_ADEPT 9
#define RS_DESTINY 10
#define RS_ODIN 11
#define RS_SET 12
#define RS_ATHENA 13
#define RS_HECATE 14
#define RS_DRUID 15
#define RS_COUNTRYSIDE 16
#define RS_ARENA 17
#define RS_SEWER_DUCT 18
#define RS_DRAINED_SEWER 19
#define RS_DROWNED_SEWER 20
#define RS_KITCHEN 21
#define RS_BEDROOM 22
#define RS_BATHROOM 23
#define RS_DININGROOM 24
#define RS_SECRETPASSAGE 25
#define RS_CLOSET 26
#define RS_LOWERASTRAL 27
#define RS_EARTHPLANE 28
#define RS_WATERPLANE 29
#define RS_AIRPLANE 30
#define RS_FIREPLANE 31
#define RS_HIGHASTRAL 32
#define RS_VOLCANO 33
#define RS_STARPEAK 34
#define RS_MAGIC_ISLE 35
#define RS_CIRCLE 36
#define RS_ZORCH 37
#define RS_COURT 38
/* normal room name indices start after the RS_ constants */
#define ROOMBASE 39
#define RS_GARDEROBE ROOMBASE+0
#define RS_CELL ROOMBASE+1
#define RS_TILED ROOMBASE+2
#define RS_CRYSTAL_CAVE ROOMBASE+3
#define RS_BEDROOM2 ROOMBASE+4
#define RS_STOREROOM ROOMBASE+5
#define RS_CHARRED ROOMBASE+6
#define RS_MARBLE_HALL ROOMBASE+7
#define RS_EERIE_CAVE ROOMBASE+8
#define RS_TREASURE ROOMBASE+9
#define RS_SMOKEY ROOMBASE+10
#define RS_APARTMENT ROOMBASE+11
#define RS_ANTECHAMBER ROOMBASE+12
#define RS_HAREM ROOMBASE+13
#define RS_MULTIPURPOSE ROOMBASE+14
#define RS_STALACTITES ROOMBASE+15
#define RS_GREENHOUSE ROOMBASE+16
#define RS_WATERCLOSET ROOMBASE+17
#define RS_STUDY ROOMBASE+18
#define RS_LIVING_ROOM ROOMBASE+19
#define RS_DEN ROOMBASE+20
#define RS_ABATOIR ROOMBASE+21
#define RS_BOUDOIR ROOMBASE+22
#define RS_STAR_CHAMBER ROOMBASE+23
#define RS_MANMADE_CAVE ROOMBASE+24
#define RS_SEWER_CONTROL ROOMBASE+25
#define RS_SHRINE ROOMBASE+26
#define RS_MAGIC_LAB ROOMBASE+27
#define RS_PENTAGRAM ROOMBASE+28
#define RS_OMEGA_DAIS ROOMBASE+29

struct room
{
    int lighted;
    int left, right, top, bottom;
    int rsi; /* index into roomname switch */
};

#endif // ROOM_H
