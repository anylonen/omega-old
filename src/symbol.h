#ifndef SYMBOL_H
#define SYMBOL_H

#if defined(MSDOS_SUPPORTED_ANTIQUE) || defined(AMIGA)
typedef short Symbol;
#else
#include <curses.h>
typedef chtype Symbol;
#endif

#endif // SYMBOL_H
