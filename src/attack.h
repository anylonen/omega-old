#ifndef ATTACK_H
#define ATTACK_H

/* tac mode action definitions */
/* have to remember to find where these are used, mostly unused, now! */
#define DISENGAGE 10
#define BLOCK 20
#define CUT 30
#define THRUST 40
#define MAGIC 50
#define LUNGE 60
#define RIPOSTE 70
#define WIELD 80
#define PICK_UP 90

/* as in attack low, block high, etc. */
/* These values may be added to the ones above to get things like
   block high, cut low, etc. CLEVER is only used by some monsters
   to cheat with.... */
#define LOW 1
#define CENTER 2
#define HIGH 3
#define CLEVER 4


/* weapon types */
#define CUTTING 1
#define THRUSTING 2
#define STRIKING 3
#define MISSILE 4

#endif
