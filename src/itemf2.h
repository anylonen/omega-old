#ifndef ITEMF2_H
#define ITEMF2_H

#include "monster.h"
#include "object.h"

/* itemf2.c functions */

void i_defend( pob );
void i_demonblade( pob );
void i_desecrate( pob );
void i_lightsabre( pob );
void i_mace_disrupt( pob );
void i_normal_armor( pob );
void i_normal_shield( pob );
void i_normal_weapon( pob );
void i_perm_breathing( pob );
void i_perm_burden( pob );
void i_perm_deflect( pob );
void i_perm_energy_resist( pob );
void i_perm_fear_resist( pob );
void i_perm_fire_resist( pob );
void i_perm_gaze_immune( pob );
void i_perm_knowledge( pob );
void i_perm_poison_resist( pob );
void i_perm_regenerate( pob );
void i_perm_strength( pob );
void i_victrix( pob );
void weapon_acidwhip( int, pob, struct monster* );
void weapon_arrow( int, pob, struct monster* );
void weapon_bare_hands( int, struct monster* );
void weapon_bolt( int, pob, struct monster* );
void weapon_defend( int, pob, struct monster* );
void weapon_demonblade( int, pob, struct monster* );
void weapon_desecrate( int, pob, struct monster* );
void weapon_firestar( int, pob, struct monster* );
void weapon_lightsabre( int, pob, struct monster* );
void weapon_mace_disrupt( int, pob, struct monster* );
void weapon_normal_hit( int, pob, struct monster* );
void weapon_scythe( int, pob, struct monster* );
void weapon_tangle( int, pob, struct monster* );
void weapon_victrix( int, pob, struct monster* );
void weapon_vorpal( int, pob, struct monster* );

#endif
