#ifndef MOVEF_H
#define MOVEF_H

#include "monster.h"

/* movef.c functions */

void m_movefunction( struct monster*, int );
void p_movefunction( int );
void sign_print( int, int, int ); /* this function in site1.c if MSDOS defined */

#endif
