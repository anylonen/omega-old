#ifndef PRIEST_H
#define PRIEST_H

#include "object.h"

/* priest.c functions */

int check_sacrilege( int );
void answer_prayer( void );
void hp_req_print( void );
void hp_req_test( void );
int increase_priest_rank( int );
void l_altar( void );
void make_hp( pob );
void player_join_patron(const int patron);
void can_player_join_odin(void);
void can_player_join_set(void);
void can_player_join_athena(void);
void can_player_join_hecate(void);
void can_player_join_druid(void);
void can_player_join_destiny(void);
void player_has_no_priesthood_rank(const int deity);
const int player_has_priesthood_rank(const int deity);
#endif
