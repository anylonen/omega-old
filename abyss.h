#ifndef ABYSS_H
#define ABYSS_H

/* abyss.c functions */

#ifdef MSDOS_SUPPORTED_ANTIQUE
void check_memory( void );
void kill_all_levels( void );
void kill_levels( char* );
void msdos_init( void );
plv msdos_changelevel( plv, int, int );
#endif
void load_abyss( void );

#endif
