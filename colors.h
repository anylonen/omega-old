#ifndef COLORS_H
#define COLORS_H

#if defined(MSDOS_SUPPORTED_ANTIQUE) || defined(AMIGA)
#define CLR(fg)		COL_##fg
#define CLRS(fg,bg)	COL_##fg|COL_BG_##bg
#endif

#if defined(MSDOS_SUPPORTED_ANTIQUE)

#define COL_BLACK 0x0000
#define COL_BLUE 0x0100
#define COL_GREEN 0x0200
#define COL_CYAN 0x0300
#define COL_RED 0x0400
#define COL_PURPLE 0x0500
#define COL_BROWN 0x0600
#define COL_WHITE 0x0700
#define COL_GREY 0x0800
#define COL_LIGHT_BLUE 0x0900
#define COL_LIGHT_GREEN 0x0a00
#define COL_LIGHT_CYAN 0x0b00
#define COL_LIGHT_RED 0x0c00
#define COL_LIGHT_PURPLE 0x0d00
#define COL_YELLOW 0x0e00
#define COL_BRIGHT_WHITE 0x0f00
#define COL_BG_BLACK 0x0000
#define COL_BG_BLUE 0x1000
#define COL_BG_GREEN 0x2000
#define COL_BG_CYAN 0x3000
#define COL_BG_RED 0x4000
#define COL_BG_PURPLE 0x5000
#define COL_BG_BROWN 0x6000
#define COL_BG_WHITE 0x7000
#define COL_FG_BLINK 0x8000

#elif defined(AMIGA)

#include <curses210.h>

/* unfortunately, this curses package only implements 8 colours... */

#define COL_WHITE 0x0100
#define COL_BLACK COL_WHITE
/* this assumes that all things with black fg have white bg */
#define COL_BROWN 0x0200
#define COL_YELLOW 0x0300
#define COL_GREY 0x0400
#define COL_GREEN 0x0500
#define COL_BLUE 0x0600
#define COL_RED 0x0700
#define COL_CYAN 0x0500		/* = green */
#define COL_PURPLE 0x0700	/* = red */
#define COL_LIGHT_BLUE 0x0600	/* = blue */
#define COL_LIGHT_GREEN 0x0500	/* = green */
#define COL_LIGHT_CYAN 0x0500	/* = green */
#define COL_LIGHT_RED 0x0700	/* = red */
#define COL_LIGHT_PURPLE 0x0100	/* = white */
#define COL_BRIGHT_WHITE 0x0100	/* = white */
#define COL_BG_BLACK 0x0000
#define COL_BG_WHITE (A_REVERSE<<8)
#define COL_BG_GREEN (A_REVERSE<<8)
#define COL_BG_CYAN (A_REVERSE<<8)
#define COL_BG_RED (A_REVERSE<<8)
#define COL_BG_PURPLE (A_REVERSE<<8)
#define COL_BG_BROWN (A_REVERSE<<8)
#define COL_BG_BLUE (A_REVERSE<<8)
#define COL_FG_BLINK 0x0000	/* not implemented :( */
/* WDT: thank goodness for that lack of implementation. */

#else /* !MSDOS_ANTIQUE && !AMIGA */

# ifdef USE_OPCURSES
#  include "../opcurses/curses.h"
# else
#  include <curses.h>
# endif

# define COL_FG_BLINK A_BLINK

# ifdef COLOR_PAIR

#  ifdef OMEGA_CLRGEN
#   define CLR(fg)	OMEGA_CLRGEN1 fg
#   define CLRS(fg, bg)	OMEGA_CLRGEN2 fg bg
#  else
#   include "clrgen.h"
#   define CLR(fg)	CLR_##fg##_BLACK
#   define CLRS(fg, bg)	CLR_##fg##_##bg
#  endif

# else /* COLOR_PAIR */

#  define CLR(fg)		0
#  define CLRS(fg,bg)	0

# endif /* COLOR_PAIR */
#endif /* !MSDOS_ANTIQUE && !AMIGA */

#endif
