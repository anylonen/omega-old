#ifndef SPELL_H
#define SPELL_H

/* spells */
#define NUMSPELLS 42

#define S_MON_DET 0
#define S_OBJ_DET 1
#define S_MISSILE 2
#define S_FIREBOLT 3
#define S_TELEPORT 4
#define S_LBALL 5
#define S_SLEEP 6
#define S_DISRUPT 7
#define S_DISINTEGRATE 8
#define S_POLYMORPH 9
#define S_HEAL 10
#define S_DISPEL 11
#define S_IDENTIFY 12
#define S_BREATHE 13
#define S_INVISIBLE 14
#define S_WARP 15
#define S_ENCHANT 16
#define S_BLESS 17
#define S_RESTORE 18
#define S_CURE 19
#define S_TRUESIGHT 20
#define S_HELLFIRE 21
#define S_KNOWLEDGE 22
#define S_HERO 23
#define S_RETURN 24
#define S_DESECRATE 25
#define S_HASTE 26
#define S_SUMMON 27
#define S_SANCTUARY 28
#define S_ACCURACY 29
#define S_RITUAL 30
#define S_FEAR 31
#define S_APPORT 32
#define S_SHADOWFORM 33
#define S_ALERT 34
#define S_REGENERATE 35
#define S_SANCTIFY 36
#define S_CLAIRVOYANCE 37
#define S_DRAIN 38
#define S_LEVITATE 39
#define S_WISH 40
#define S_NUTRITION 41

struct spell
{
    char known;
    char id;
    char powerdrain;
} ;

#endif // SPELL_H
