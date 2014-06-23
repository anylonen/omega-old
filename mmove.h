#ifndef MMOVE_H
#define MMOVE_H

#include "monster.h"

/* mmove.c functions */

void m_confused_move( struct monster* );
void m_flutter_move( struct monster* );
void m_follow_move( struct monster* );
void m_move_animal( struct monster* );
void m_normal_move( struct monster* );
void m_random_move( struct monster* );
void m_scaredy_move( struct monster* );
void m_simple_move( struct monster* );
void m_smart_move( struct monster* );
void m_spirit_move( struct monster* );
void m_teleport( struct monster* );
void m_vanish( struct monster* );
void m_move_leash( struct monster* );

#endif
