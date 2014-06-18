#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/* random  function declarations from system libraries */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#undef sign
#undef max
#undef min

/* These must be made to work for both longs and ints */
#define sign(n) (((n) < 0) ? -1 : (((n) > 0) ? 1 : 0))
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

#define RANDFUNCTION genrand
#define SRANDFUNCTION sgenrand

/* WDT: This should be harmless under ANSI C, and will stop
 * some errors under bizarre platforms. */ 
#define pow2(n) (1L << (n))

/* these bit operations were functions, but are faster as macros... */

#define loc_statusp(x,y,stat) ((Level->site[x][y].lstatus&(stat))?1:0)
#define lset(x,y,stat) (Level->site[x][y].lstatus |= (stat))
#define lreset(x,y,stat) (Level->site[x][y].lstatus &= ~(stat))

#define c_statusp(x,y,stat) ((Country[x][y].status&(stat))?1:0)
#define c_set(x,y,stat) (Country[x][y].status |= (stat))
#define c_reset(x,y,stat) (Country[x][y].status &= ~(stat))

#define m_statusp(m,s) (((m)->status&(s))?1:0)
#define m_status_set(m,s) ((m)->status |= (s))
#define m_status_reset(m,s) ((m)->status &= ~(s))
#define m_immunityp(m,s) (((m)->immunity&pow2(s))?1:0)

#define gamestatusp(flag) ((GameStatus&(flag))?1:0)
#define setgamestatus(flag) (GameStatus |= (flag))
#define resetgamestatus(flag) (GameStatus &= ~(flag))

#define optionp(o) ((Player.options&(o))?1:0)
#define optionset(o) (Player.options |= (o))
#define optionreset(o) (Player.options &= ~(o))

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#endif
