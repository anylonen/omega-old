/* omega copyright (c) 1987,1988,1989 by Laurence Raphael Brothers */
/* gen1.c */
/* level generator functions */

#include "gen1.h"
#include "glob.h"

#include <time.h>

/* Deallocate current dungeon */
void free_dungeon(void)
{
#ifndef SAVE_LEVELS
    plv tlv;

    while (Dungeon != NULL)
    {
        tlv = Dungeon;
        Dungeon = Dungeon->next;
        free_level(tlv);
    }

#else

    if (Dungeon != NULL)
    {
        sprintf(Str2, "om%d*.lev", Dungeon->environment);
        kill_levels(Str2);
    }

#endif
}

/* erase the level w/o deallocating it*/
void clear_level(struct level* dungeon_level)
{
    int i, j;

    if (dungeon_level != NULL)
    {
        dungeon_level->generated = FALSE;
        dungeon_level->numrooms = 0;
        dungeon_level->level_length = 0;
        dungeon_level->level_width = 0;
        dungeon_level->tunnelled = 0;
        dungeon_level->depth = 0;
        dungeon_level->mlist = NULL;
        dungeon_level->next = NULL;
        dungeon_level->last_visited = time(NULL);

        for (i = 0; i < MAXWIDTH; i++)
            for (j = 0; j < MAXLENGTH; j++)
            {
                dungeon_level->site[i][j].locchar = WALL;
                dungeon_level->site[i][j].showchar = SPACE;
                dungeon_level->site[i][j].creature = NULL;
                dungeon_level->site[i][j].things = NULL;
                /* PGM: clear_level is called from restore_level, before it knows anything about the current environment, which is where difficulty() gets its information! */
                dungeon_level->site[i][j].aux = difficulty() * 20;
                dungeon_level->site[i][j].buildaux = 0;
                dungeon_level->site[i][j].p_locf = L_NO_OP;
                dungeon_level->site[i][j].lstatus = 0;
                dungeon_level->site[i][j].roomnumber = RS_WALLSPACE;
            }
    }
}

/* Looks for level tolevel in current dungeon which is named by
Dungeon, which may be NULL. If the level is found, and rewrite_level
is FALSE, and the level has already been generated, nothing happens
beyond Level being set correctly. Otherwise the level is recreated
from scratch */

void change_level (char fromlevel, char tolevel, char rewrite_level)
{
    struct level* thislevel = NULL;
    Player.sx = -1;
    Player.sy = -1; /* sanctuary effect dispelled */
#ifndef SAVE_LEVELS
    thislevel = findlevel(Dungeon, tolevel);
    deepest[Current_Environment] = max(deepest[Current_Environment], tolevel);

    if (!thislevel)
    {
        thislevel = (level*)checkmalloc(sizeof(levtype));
        clear_level(thislevel);
        Level = thislevel;
        Level->next = Dungeon;
        Dungeon = Level;
    }

#else
    thislevel = msdos_changelevel(Level, Current_Environment, tolevel);
    deepest[Current_Environment] = max(deepest[Current_Environment], tolevel);

    if (!thislevel)
    {
        thislevel = &TheLevel;
        clear_level(thislevel);
        Level = thislevel;
        Level->next = Dungeon;
        Dungeon = Level;
    }

#endif
    Level = thislevel;

    if ((!Level->generated) || rewrite_level)
    {
        initrand(Current_Environment, tolevel);
        Level->environment = Current_Environment;
        Level->depth = tolevel;
        Level->generated = TRUE;

        switch (Current_Environment)
        {
            case E_CAVES:
                Level->level_width = CAVES_WIDTH;
                Level->level_length = CAVES_LENGTH;

                if ((0 == random_range(4)) && (tolevel < MaxDungeonLevels))
                {
                    room_level();
                }
                else
                {
                    cavern_level();
                }

                break;

            case E_SEWERS:
                Level->level_width = SEWERS_WIDTH;
                Level->level_length = SEWERS_LENGTH;

                if ((0 == random_range(4)) && (tolevel < MaxDungeonLevels))
                {
                    room_level();
                }
                else
                {
                    sewer_level();
                }

                break;

            case E_CASTLE:
                Level->level_width = CASTLE_WIDTH;
                Level->level_length = CASTLE_LENGTH;
                room_level();
                break;

            case E_PALACE: /* PGM TODO */
                Level->level_width = PALACE_WIDTH;
                Level->level_length = PALACE_LENGTH;
                room_level();
                break;

            case E_ASTRAL:
                Level->level_width = ASTRAL_WIDTH;
                Level->level_length = ASTRAL_LENGTH;
                maze_level();
                break;

            case E_VOLCANO:
                Level->level_width = VOLCANO_WIDTH;
                Level->level_length = VOLCANO_LENGTH;

                switch (random_range(3))
                {
                    case 0:
                        cavern_level();
                        break;

                    case 1:
                        room_level();
                        break;

                    case 2:
                        maze_level();
                        break;
                }

                break;

            default:
                print3("This dungeon not implemented!");
                assert(FALSE);
                break;
        }

        install_traps();
        install_specials();
        make_stairs(fromlevel);
        make_stairs(fromlevel);
        initrand(E_RESTORE, 0);
        populate_level(Current_Environment);
        stock_level();
    }

    find_stairs(fromlevel, tolevel);
    ScreenOffset = Player.y - (ScreenLength / 2);
    show_screen();
    screencheck(Player.x, Player.y);
    drawvision(Player.x, Player.y);
    /* synchronize with player on level change */
    Player.click = (Tick + 1) % 60;
    roomcheck();
}

#ifndef SAVE_LEVELS
/* tries to find the level of depth levelnum in dungeon; if can't find
   it returns NULL */
plv findlevel(struct level* dungeon, char levelnum)
{
    if (dungeon == NULL)
    {
        return (NULL);
    }
    else
    {
        while ((dungeon->next != NULL) && (dungeon->depth != levelnum))
        {
            dungeon = dungeon->next;
        }

        if (dungeon->depth == levelnum)
        {
            dungeon->last_visited = time(NULL);
            return (dungeon);
        }
        else
        {
            return (NULL);
        }
    }
}
#endif

/* keep going in one orthogonal direction or another until we hit our */
/* destination */

void straggle_corridor(int fx, int fy, int tx, int ty, Symbol loc, char rsi)
{
    int dx, dy;

    while ((fx != tx) || (fy != ty))
    {
        dx = tx - fx;
        dy = ty - fy;

        if (random_range(abs(dx) + abs(dy)) < abs(dx))
        {
            corridor_crawl(&fx, &fy, sign(dx), 0, random_range(abs(dx)) + 1, loc, rsi);
        }
        else
        {
            corridor_crawl(&fx, &fy, 0, sign(dy), random_range(abs(dy)) + 1, loc, rsi);
        }
    }
}

void makedoor(int x, int y)
{
    if (random_range(20) <= Level->depth / 10)
    {
        Level->site[x][y].locchar = FLOOR;
        lset(x, y, SECRET);
    }
    else if (random_range(20) <= Level->depth / 2)
    {
        Level->site[x][y].locchar = CLOSED_DOOR;

        if (random_range(20) <= Level->depth / 10)
        {
            lset(x, y, SECRET);
        }

        if (random_range(40) <= Level->depth)
        {
            Level->site[x][y].aux = LOCKED;
        }
        else
        {
            Level->site[x][y].aux = UNLOCKED;
        }
    }
    else
    {
        Level->site[x][y].locchar = OPEN_DOOR;
        Level->site[x][y].aux = UNLOCKED;
    }

    if (! loc_statusp(x, y, SECRET))
    {
        lset(x, y + 1, STOPS);
        lset(x + 1, y, STOPS);
        lset(x - 1, y, STOPS);
        lset(x, y - 1, STOPS);
        lset(x, y, STOPS);
    }

    Level->site[x][y].p_locf = L_NO_OP;
    /* prevents water corridors from being instant death in sewers */
}

void corridor_crawl(int* fx, int* fy, int sx, int sy, int n,
                    Symbol loc, char rsi)
{
    int i;

    for (i = 0; i < n; i++)
    {
        *fx += sx;
        *fy += sy;

        if ((*fx < Level->level_width) &&
                (*fx > -1) &&
                (*fy > -1) &&
                (*fy < Level->level_length))
        {
            Level->site[*fx][*fy].locchar = loc;

            if (Level->site[*fx][*fy].roomnumber == RS_WALLSPACE)
            {
                Level->site[*fx][*fy].roomnumber = rsi;
            }

            if (loc == WATER)
            {
                Level->site[*fx][*fy].p_locf = L_WATER;
            }
            else if (loc == FLOOR)
            {
                Level->site[*fx][*fy].p_locf = L_NO_OP;
            }
            else if (loc == RUBBLE)
            {
                Level->site[*fx][*fy].p_locf = L_RUBBLE;
            }
        }
    }
}

char* roomname(int index)
{
    switch (index)
    {
        case RS_ZORCH:
            strcpy(Str4, "A place zorched by powerful magic.");
            break;

        case RS_COURT:
            strcpy(Str4, "The Court of the ArchMage.");
            break;

        case RS_CIRCLE:
            strcpy(Str4, "The Astral Demesne of the Circle of Sorcerors");
            break;

        case RS_MAGIC_ISLE:
            strcpy(Str4, "An island positively reeking of magic");
            break;

        case RS_STARPEAK:
            strcpy(Str4, "Near the oddly glowing peak of a mountain");
            break;

        case RS_VOLCANO:
            strcpy(Str4, "Deep within the bowels of the earth");
            break;

        case RS_HIGHASTRAL:
            strcpy(Str4, "The High Astral Plane");
            break;

        case RS_EARTHPLANE:
            strcpy(Str4, "The Plane of Earth");
            break;

        case RS_WATERPLANE:
            strcpy(Str4, "The Plane of Water");
            break;

        case RS_FIREPLANE:
            strcpy(Str4, "The Plane of Fire");
            break;

        case RS_AIRPLANE:
            strcpy(Str4, "The Plane of Air");
            break;

        case RS_KITCHEN:
            strcpy(Str4, "A kitchen");
            break;

        case RS_BATHROOM:
            strcpy(Str4, "A bathroom");
            break;

        case RS_BEDROOM:
            strcpy(Str4, "A bedroom");
            break;

        case RS_DININGROOM:
            strcpy(Str4, "A dining room");
            break;

        case RS_SECRETPASSAGE:
            strcpy(Str4, "A secret passage");
            break;

        case RS_CLOSET:
            strcpy(Str4, "A stuffy closet");
            break;

        case RS_ARENA:
            strcpy(Str4, "The Rampart Arena");
            break;

        case RS_DROWNED_SEWER:
            strcpy(Str4, "A water-filled sewer node");
            break;

        case RS_DRAINED_SEWER:
            strcpy(Str4, "An unused sewer node");
            break;

        case RS_SEWER_DUCT:
            strcpy(Str4, "A winding sewer duct");
            break;

        case RS_DESTINY:
            strcpy(Str4, "The Halls of Fate");
            break;

        case RS_DRUID:
            strcpy(Str4, "The Great Henge");
            break;

        case RS_HECATE:
            strcpy(Str4, "The Church of the Far Side");
            break;

        case RS_SET:
            strcpy(Str4, "The Temple of the Black Hand");
            break;

        case RS_ATHENA:
            strcpy(Str4, "The Parthenon");
            break;

        case RS_ODIN:
            strcpy(Str4, "The Shrine of the Noose");
            break;

        case RS_ADEPT:
            strcpy(Str4, "The Adept's Challenge");
            break;

        case RS_WYRM:
            strcpy(Str4, "The Sunken Cavern of the Great Wyrm.");
            break;

        case RS_OCEAN:
            strcpy(Str4, "The Underground Ocean.");
            break;

        case RS_PONDS:
            strcpy(Str4, "A series of subterranean pools and streams.");
            break;

        case RS_DRAGONLORD:
            strcpy(Str4, "The Lair of the DragonLord.");
            break;

        case RS_GOBLINKING:
            strcpy(Str4, "The Caves of the Goblins.");
            break;

        case RS_CAVERN:
            strcpy(Str4, "A vast natural cavern.");
            break;

        case RS_CORRIDOR:
            strcpy(Str4, "A dimly lit corridor.");
            break;

        case RS_WALLSPACE:
            strcpy(Str4, "A niche hollowed out of the wall.");
            break;

            /* following are above ROOMBASE */
        case RS_GARDEROBE:
            strcpy(Str4, "An abandoned garderobe.");
            break;

        case RS_CELL:
            strcpy(Str4, "A dungeon cell.");
            break;

        case RS_TILED:
            strcpy(Str4, "A tiled chamber.");
            break;

        case RS_CRYSTAL_CAVE:
            strcpy(Str4, "A crystal cavern.");
            break;

        case RS_BEDROOM2:
            strcpy(Str4, "Someone's bedroom.");
            break;

        case RS_STOREROOM:
            strcpy(Str4, "An old storeroom.");
            break;

        case RS_CHARRED:
            strcpy(Str4, "A room with charred walls.");
            break;

        case RS_MARBLE_HALL:
            strcpy(Str4, "A marble hall.");
            break;

        case RS_EERIE_CAVE:
            strcpy(Str4, "An eerie cave.");
            break;

        case RS_TREASURE:
            strcpy(Str4, "A ransacked treasure-chamber.");
            break;

        case RS_SMOKEY:
            strcpy(Str4, "A smoke-filled room.");
            break;

        case RS_APARTMENT:
            strcpy(Str4, "A well-appointed apartment.");
            break;

        case RS_ANTECHAMBER:
            strcpy(Str4, "An antechamber.");
            break;

        case RS_HAREM:
            strcpy(Str4, "An unoccupied harem.");
            break;

        case RS_MULTIPURPOSE:
            strcpy(Str4, "A multi-purpose room.");
            break;

        case RS_STALACTITES:
            strcpy(Str4, "A room filled with stalactites.");
            break;

        case RS_GREENHOUSE:
            strcpy(Str4, "An underground greenhouse.");
            break;

        case RS_WATERCLOSET:
            strcpy(Str4, "A water closet.");
            break;

        case RS_STUDY:
            strcpy(Str4, "A study.");
            break;

        case RS_LIVING_ROOM:
            strcpy(Str4, "A living room.");
            break;

        case RS_DEN:
            strcpy(Str4, "A comfortable den.");
            break;

        case RS_ABATOIR:
            strcpy(Str4, "An abatoir.");
            break;

        case RS_BOUDOIR:
            strcpy(Str4, "A boudoir.");
            break;

        case RS_STAR_CHAMBER:
            strcpy(Str4, "A star chamber.");
            break;

        case RS_MANMADE_CAVE:
            strcpy(Str4, "A manmade cavern.");
            break;

        case RS_SEWER_CONTROL:
            strcpy(Str4, "A sewer control room");
            break;

        case RS_SHRINE:
            strcpy(Str4, "A shrine to High Magic");
            break;

        case RS_MAGIC_LAB:
            strcpy(Str4, "A magic laboratory");
            break;

        case RS_PENTAGRAM:
            strcpy(Str4, "A room with inscribed pentagram");
            break;

        case RS_OMEGA_DAIS:
            strcpy(Str4, "A chamber with a blue crystal omega dais");
            break;

            /* WDT: removed period from description. */
        default:
            strcpy(Str4, "A room of mystery and allure");
            break;
    }

    return (Str4);
}

/* puts the player on the first set of stairs from the apt level */
/* if can't find them, just drops player anywhere.... */
void find_stairs(char fromlevel, char tolevel)
{
    int i, j, found = FALSE;
    Symbol sitechar;

    if (fromlevel > tolevel)
    {
        sitechar = STAIRS_DOWN;
    }
    else
    {
        sitechar = STAIRS_UP;
    }

    for (i = 0; i < Level->level_width; i++)
        for (j = 0; j < Level->level_length; j++)
            if ((Level->site[i][j].locchar == sitechar) && (! found))
            {
                found = TRUE;
                Player.x = i;
                Player.y = j;
                break;
            }

    if (! found)
    {
        findspace(&Player.x, &Player.y, -1);

        if (Level->environment != E_ASTRAL)
        {
            Level->site[Player.x][Player.y].locchar = sitechar;
            lset(Player.x, Player.y, CHANGED);
        }
    }
}

void install_traps(void)
{
    int i, j;

    for (i = 0; i < Level->level_width; i++)
        for (j = 0; j < Level->level_length; j++)
            if ((Level->site[i][j].locchar == FLOOR) &&
                    (Level->site[i][j].p_locf == L_NO_OP) &&
                    random_range(500) <= ((int)(Level->depth / 6)))
            {
                Level->site[i][j].p_locf = TRAP_BASE + random_range(NUMTRAPS);
            }
}

/* x, y, is top left corner, l is length of side, rsi is room string index */
/* baux is so all rooms will have a key field. */
void build_square_room(int x, int y, int l, char rsi, int baux)
{
    int i, j;

    for (i = x; i <= x + l; i++)
        for (j = y; j <= y + l; j++)
        {
            Level->site[i][j].roomnumber = rsi;
            Level->site[i][j].buildaux = baux;
        }

    for (i = x + 1; i < x + l; i++)
        for (j = y + 1; j < y + l; j++)
        {
            Level->site[i][j].locchar = FLOOR;
            Level->site[i][j].p_locf = L_NO_OP;
        }
}

void build_room(int x, int y, int l, char rsi, int baux)
{
    build_square_room(x, y, l, rsi, baux);
}

void cavern_level(void)
{
    int i, fx, fy, tx, ty, t, l, e;
    char rsi;
    Level->numrooms = 1;

    if ((Current_Dungeon == E_CAVES) && (Level->depth == CAVELEVELS))
    {
        rsi = RS_GOBLINKING;
    }
    else
    {
        rsi = RS_CAVERN;
    }

    t = random_range((Level->level_length) / 2);
    l = random_range((Level->level_width) / 2);
    e = random_range((Level->level_width) / 8) + (Level->level_width) / 8;
    build_square_room(t, l, e, rsi, 0);

    for (i = 0; i < 16; i++)
    {
        findspace(&tx, &ty, -1);
        fx = random_range((Level->level_width) - 2) + 1;
        fy = random_range((Level->level_length) - 2) + 1;
        straggle_corridor(fx, fy, tx, ty, FLOOR, RS_CORRIDOR);
    }

    while (random_range(3) == 1)
    {
        findspace(&tx, &ty, -1);
        fx = random_range((Level->level_width) - 2) + 1;
        fy = random_range((Level->level_length) - 2) + 1;
        straggle_corridor(fx, fy, tx, ty, WATER, RS_PONDS);
    }

    if (Current_Dungeon == E_CAVES)
    {
        if ((Level->depth == CAVELEVELS) && (! gamestatusp(COMPLETED_CAVES)))
        {
            findspace(&tx, &ty, -1);
            Level->mlist = ((pml) checkmalloc(sizeof(mltype)));
            Level->mlist->next = NULL;
            Level->mlist->m =
                Level->site[tx][ty].creature =
                    ((pmt) make_creature(GOBLIN_KING)); /* goblin king */
            Level->mlist->m->x = tx;
            Level->mlist->m->y = ty;
        }
    }
    else if (Current_Environment == E_VOLCANO)
    {
        if (Level->depth == VOLCANOLEVELS)
        {
            findspace(&tx, &ty, -1);
            Level->mlist = ((pml) checkmalloc(sizeof(mltype)));
            Level->mlist->next = NULL;
            Level->mlist->m =
                Level->site[tx][ty].creature =
                    ((pmt) make_creature(DEMON_EMP)); /* The demon emp */
            Level->mlist->m->x = tx;
            Level->mlist->m->y = ty;
        }
    }
}

void sewer_level(void)
{
    int i, tx, ty, t, l, e;
    char rsi;
    Symbol lchar;
    Level->numrooms = random_range(3) + 3;
    rsi = RS_DRAINED_SEWER;

    for (i = 0; i < Level->numrooms; i++)
    {
        do
        {
            t = random_range((Level->level_length) - 10) + 1;
            l = random_range((Level->level_width) - 10) + 1;
            e = 4;
        }
        while ((Level->site[l][t].roomnumber == rsi) ||
                (Level->site[l + e][t].roomnumber == rsi) ||
                (Level->site[l][t + e].roomnumber == rsi) ||
                (Level->site[l + e][t + e].roomnumber == rsi));

        if (random_range(5))
        {
            lchar = FLOOR;
            rsi = RS_DRAINED_SEWER;
        }
        else
        {
            lchar = WATER;
            rsi = RS_DROWNED_SEWER;
        }

        build_room(l, t, e, rsi, i);
        sewer_corridor(l, t, -1, -1, lchar);
        sewer_corridor(l + e, t, 1, -1, lchar);
        sewer_corridor(l, t + e, -1, 1, lchar);
        sewer_corridor(l + e, t + e, 1, 1, lchar);
    }

    if (Current_Dungeon == E_SEWERS)
    {
        if ((Level->depth == SEWERLEVELS) && (! gamestatusp(COMPLETED_SEWERS)))
        {
            findspace(&tx, &ty, -1);
            Level->mlist = ((pml) checkmalloc(sizeof(mltype)));
            Level->mlist->next = NULL;
            Level->mlist->m =
                Level->site[tx][ty].creature =
                    ((pmt) make_creature(GREAT_WYRM)); /* The Great Wyrm */
            Level->mlist->m->x = tx;
            Level->mlist->m->y = ty;
        }
    }
}

void sewer_corridor(int x, int y, int dx, int dy, Symbol locchar)
{
    int continuing = TRUE;
    makedoor(x, y);
    x += dx;
    y += dy;

    while (continuing)
    {
        Level->site[x][y].locchar = locchar;

        if (locchar == WATER)
        {
            Level->site[x][y].p_locf = L_WATER;
        }
        else
        {
            Level->site[x][y].p_locf = L_NO_OP;
        }

        Level->site[x][y].roomnumber = RS_SEWER_DUCT;
        x += dx;
        y += dy;

        if (locchar == WATER)
            continuing = (inbounds(x, y) &&
                          ((Level->site[x][y].locchar == WALL) ||
                           (Level->site[x][y].locchar == WATER)));
        else
            continuing = (inbounds(x, y) &&
                          ((Level->site[x][y].roomnumber == RS_WALLSPACE) ||
                           (Level->site[x][y].roomnumber == RS_SEWER_DUCT)));
    }

    if (inbounds(x, y))
    {
        makedoor(x, y);
    }
}

void install_specials(void)
{
    int i, j, x, y;

    for (x = 0; x < Level->level_width; x++)
    {
        for (y = 0; y < Level->level_length; y++)
        {
            if ((Level->site[x][y].locchar == FLOOR) &&
                    (Level->site[x][y].p_locf == L_NO_OP) &&
                    (random_range(300) < difficulty()))
            {
                i = random_range(100);

                if (i < 10)
                {
                    Level->site[x][y].locchar = ALTAR;
                    Level->site[x][y].p_locf = L_ALTAR;
                    Level->site[x][y].aux = random_range(10);
                }
                else if (i < 20)
                {
                    Level->site[x][y].locchar = WATER;
                    Level->site[x][y].p_locf = L_MAGIC_POOL;
                }
                else if (i < 35)
                {
                    Level->site[x][y].locchar = RUBBLE;
                    Level->site[x][y].p_locf = L_RUBBLE;
                }
                else if (i < 40)
                {
                    Level->site[x][y].locchar = LAVA;
                    Level->site[x][y].p_locf = L_LAVA;
                }
                else if (i < 45)
                {
                    Level->site[x][y].locchar = FIRE;
                    Level->site[x][y].p_locf = L_FIRE;
                }
                else if ((i < 50) && (Current_Environment != E_ASTRAL))
                {
                    Level->site[x][y].locchar = LIFT;
                    Level->site[x][y].p_locf = L_LIFT;
                }
                else if ((i < 55) && (Current_Environment != E_VOLCANO))
                {
                    Level->site[x][y].locchar = HEDGE;
                    Level->site[x][y].p_locf = L_HEDGE;
                }
                else if (i < 57)
                {
                    Level->site[x][y].locchar = HEDGE;
                    Level->site[x][y].p_locf = L_TRIFID;
                }
                else if (i < 70)
                {
                    Level->site[x][y].locchar = STATUE;

                    if (random_range(100) < difficulty())
                        for (j = 0; j < 8; j++)
                        {
                            if (Level->site[x + Dirs[0][j]][y + Dirs[1][j]].p_locf != L_NO_OP)
                            {
                                Level->site[x + Dirs[0][j]][y + Dirs[1][j]].locchar = FLOOR;
                            }

                            Level->site[x + Dirs[0][j]][y + Dirs[1][j]].p_locf =
                                L_STATUE_WAKE;
                        }
                }
                else
                {
                    if (Current_Environment == E_VOLCANO)
                    {
                        Level->site[x][y].locchar = LAVA;
                        Level->site[x][y].p_locf = L_LAVA;
                    }
                    else if (Current_Environment == E_ASTRAL)
                    {
                        if (Level->depth == 1)
                        {
                            Level->site[x][y].locchar = RUBBLE;
                            Level->site[x][y].p_locf = L_RUBBLE;
                        }
                        else if (Level->depth == 2)
                        {
                            Level->site[x][y].locchar = FIRE;
                            Level->site[x][y].p_locf = L_FIRE;
                        }
                        else if (Level->depth == 3)
                        {
                            Level->site[x][y].locchar = WATER;
                            Level->site[x][y].p_locf = L_WATER;
                        }
                        else if (Level->depth == 4)
                        {
                            Level->site[x][y].locchar = ABYSS;
                            Level->site[x][y].p_locf = L_ABYSS;
                        }
                    }
                    else
                    {
                        Level->site[x][y].locchar = WATER;
                        Level->site[x][y].p_locf = L_WATER;
                    }
                }
            }
        }
    }
}
