/* omega copyright (C) by Laurence Raphael Brothers, 1987,1988,1989 */
/* inv.c */
/* functions having to do with player item inventory */

#ifdef MSDOS_SUPPORTED_ANTIQUE
# include "curses.h"
#else
# ifdef AMIGA
#  include <curses210.h>
# elif defined(USE_OPCURSES)
#  include "../opcurses/curses.h"
# else
#  include <curses.h>
# endif
#endif

#include "inventory.h"
#include "glob.h"

static void inv_display_munge(void);
static void inv_display_refresh(void);

/* drops money, heh heh */
void drop_money(void)
{
    pob money;
    money = detach_money(0);

    if (money != NULL)
    {
        if (Current_Environment == E_CITY)
        {
            print1("As soon as the money leaves your hand,");
            print2("a horde of scrofulous beggars snatch it up and are gone!");
            free( money );
        }
        else
        {
            drop_at(Player.x, Player.y, money);
        }
    }
    else
    {
        setgamestatus(SKIP_MONSTERS);
    }
}

/* returns some money from player back into "money" item.
   for giving and dropping money */
pob detach_money(long howmuch)
/* if howmuch == 0, ask the player. otherwise, just get howmuch. */
{
    long c;
    pob cash = NULL;

    if ( howmuch == 0 )
    {
        c = get_money(Player.cash);
    }
    else
    {
        c = howmuch;
    }

    if (c != ABORT)
    {
        Player.cash -= c;
        cash = ((pob) checkmalloc(sizeof(objtype)));
        make_cash(cash, difficulty());
        cash->basevalue = c;
    }

    return (cash);
}

/* gets a legal amount of money or ABORT */
long get_money(long limit)
{
    long c;
    c = parsenum("How much money? ");

    if (c > limit)
    {
        print3("Forget it, buddy.");
        return (ABORT);
    }
    else
    {
        return (c);
    }
}

/* pick up from some location x,y */
/* Lift entire itemlist off ground, pass it to inventory control, which
   may drop things back onto the now null ground */
void pickup_at (int x, int y)
{
    char response = 0;
    pol ol;
    pol temp;
    resetgamestatus(FAST_MOVE);
    ol = Level->site[x][y].things;
    Level->site[x][y].things = 0;

    while (ol != 0)
    {
        if (response != 'q')
        {
            clearmsg1();
            response = cinema_ynq(strjoin("Pick up: ", itemid(ol->thing)));
        }

        if (response == 'y')
        {
            gain_item(ol->thing);
        }
        else
        {
            drop_at(x, y, ol->thing);
        }

        temp = ol;
        ol = ol->next;
        temp->next = 0;
        temp->thing = 0;
        free(temp);
    }
}

/* WDT -- convert from a char (keypress) to an item index in
 * player inventory */
/* Item identifiers, in this case the letters of the alphabet minus
 * any letters already used for commands.  Yes, there are more here
 * than could be needed, but I don't want to short myself for later.
 */
signed char inventory_keymap[] = "-abcfghimnoqruvwyz";
int key_to_index(signed char key)
{
    int i;
    assert( MAXITEMS > 0 ); /* must have room for an item, or this loop will
                         * die! */

    for (i = 0; i < MAXITEMS; i++)
    {
        if (key == inventory_keymap[i])
        {
            return (signed char)i;
        }
    }

    return O_UP_IN_AIR;
}

signed char index_to_key(signed int index)
{
    if ( index < MAXITEMS )
    {
        return inventory_keymap[index];
    }
    else
    {
        return '-';
    }
}

/* criteria for being able to put some item in some slot */
/* WDT -- why on earth does the 'slottable' function print stuff???? */
int aux_slottable(pob o, int slot)
{
    int ok = TRUE;

    if (o == NULL)
    {
        ok = FALSE;
    }
    else if (slot == O_ARMOR)
    {
        if (o->objchar != ARMOR)
        {
            ok = FALSE;
        }
    }
    else if (slot == O_SHIELD)
    {
        if (o->objchar != SHIELD)
        {
            ok = FALSE;
        }
    }
    else if (slot == O_BOOTS)
    {
        if (o->objchar != BOOTS)
        {
            ok = FALSE;
        }
    }
    else if (slot == O_CLOAK)
    {
        if (o->objchar != CLOAK)
        {
            ok = FALSE;
        }
    }
    else if (slot >= O_RING1)
    {
        if (o->objchar != RING)
        {
            ok = FALSE;
        }
    }

    return (ok);
}

/* put all of o on objlist at x,y on Level->depth */
/* Not necessarily dropped by character; just dropped... */
void drop_at(int x, int y, pob o)
{
    pol tmp;
    pob cpy;

    if (Current_Environment != E_COUNTRYSIDE)
    {
        if ((Level->site[x][y].locchar != VOID_CHAR) &&
                (Level->site[x][y].locchar != ABYSS))
        {
            cpy = copy_obj( o );
            tmp = ((pol) checkmalloc(sizeof(oltype)));
            cpy->used = FALSE;
            tmp->thing = cpy;
            tmp->next = Level->site[x][y].things;
            Level->site[x][y].things = tmp;
        }
        else if (Level->site[x][y].p_locf == L_VOID_STATION)
        {
            setgamestatus(PREPARED_VOID);
        }
    }
}

/* put n of o on objlist at x,y on Level->depth */
void p_drop_at(int x, int y, int n, pob o)
{
    pol tmp;

    if (Current_Environment != E_COUNTRYSIDE)
    {
        if ((Level->site[x][y].locchar != VOID_CHAR) &&
                (Level->site[x][y].locchar != ABYSS))
        {
            tmp = ((pol) checkmalloc(sizeof(oltype)));
            tmp->thing = copy_obj( o );
            tmp->thing->used = FALSE;
            tmp->thing->number = n;
            print2("Dropped ");
            nprint2(itemid(tmp->thing));
            morewait();
            tmp->next = Level->site[x][y].things;
            Level->site[x][y].things = tmp;
        }
        else if (Level->site[x][y].p_locf == L_VOID_STATION)
        {
            setgamestatus(PREPARED_VOID);
        }
    }
}

/* returns a string for identified items */
char* itemid(pob obj)
{
    char tstr[80];

    if (obj->objchar == CASH)
    {
        strcpy(Str4, obj->truename);
        return (Str4);
    }
    else
    {
        if (Objects[obj->id].known > obj->known)
        {
            obj->known = Objects[obj->id].known;
        }

        setnumstr(obj, tstr);
        strcpy(Str4, tstr);

        if (obj->known == 0)
        {
            strcat(Str4, obj->objstr);
        }
        else if (obj->known == 1)
        {
            if (obj->id == OB_YENDOR || obj->id == OB_KARNAK ||
                    obj->id == OB_STARGEM )
            {
                strcat(Str4, "the ");
            }

            strcat(Str4, obj->truename);
        }
        else
        {
            if (obj->id == OB_YENDOR || obj->id == OB_KARNAK ||
                    obj->id == OB_STARGEM )
            {
                strcat(Str4, "the ");
            }

            if (obj->usef == I_NOTHING && Objects[obj->id].usef != I_NOTHING)
            {
                strcat(Str4, "disenchanted ");
            }

            if (obj->blessing < 0)
            {
                strcat(Str4, "cursed ");
                strcat(Str4, obj->cursestr);
            }
            else if (obj->blessing > 0)
            {
                strcat(Str4, "blessed ");
                strcat(Str4, obj->truename);
            }
            else
            {
                strcat(Str4, obj->truename);
            }

            if (obj->number > 1)
            {
                strcat(Str4, "s");
            }

            switch (obj->objchar)
            {
                case STICK:
                    setchargestr(obj, tstr);
                    strcat(Str4, tstr);
                    break;

                case MISSILEWEAPON:
                case ARMOR:
                case RING:
                case SHIELD:
                case WEAPON:
                    setplustr(obj, tstr);
                    strcat(Str4, tstr);
                    break;

                default:
                    strcat(Str4, "");
                    break;
            }
        }

        return (Str4);
    }
}

char* cashstr(void)
{
    if (difficulty() < 3)
    {
        return ("copper pieces");
    }
    else if (difficulty() < 5)
    {
        return ("silver pieces");
    }
    else if (difficulty() < 7)
    {
        return ("gold pieces");
    }
    else if (difficulty() < 8)
    {
        return ("semiprecious gems");
    }
    else if (difficulty() < 9)
    {
        return ("mithril pieces");
    }
    else if (difficulty() < 10)
    {
        return ("precious gems");
    }
    else
    {
        return ("orichalc pieces");
    }
}

/* return an object's plus as a string */
void setplustr(pob obj, char* pstr)
{
    pstr[0] = ' ';
    pstr[1] = (obj->plus < 0 ? '-' : '+' );

    if (abs(obj->plus) < 10)
    {
        pstr[2] = '0' + abs(obj->plus);
        pstr[3] = 0;
    }
    else
    {
        pstr[2] = '0' + abs(obj->plus / 10);
        pstr[3] = '0' + abs(obj->plus % 10);
        pstr[4] = 0;
    }
}

/* return an object's number as a string */
void setnumstr(pob obj, char* nstr)
{
    if (obj->number < 2)
    {
        nstr[0] = 0;
    }
    else if (obj->number < 10)
    {
        nstr[0] = '0' + obj->number;
        nstr[1] = 'x';
        nstr[2] = ' ';
        nstr[3] = 0;
    }
    else if (obj->number < 41)
    {
        nstr[0] = '0' + ((int)(obj->number / 10));
        nstr[1] = '0' + (obj->number % 10);
        nstr[2] = 'x';
        nstr[3] = ' ';
        nstr[4] = 0;
    }
    else
    {
        strcpy(nstr, "lots of ");
    }
}

/* return object with charges */
void setchargestr(pob obj, char* cstr)
{
    cstr[0] = ' ';
    cstr[1] = '[';

    if (obj->charge < 0)
    {
        cstr[2] = 'd';
        cstr[3] = 'e';
        cstr[4] = 'a';
        cstr[5] = 'd';
        cstr[6] = ']';
        cstr[7] = 0;
    }
    else if (obj->charge < 10)
    {
        cstr[2] = '0' + obj->charge;
        cstr[3] = ']';
        cstr[4] = 0;
    }
    else
    {
        cstr[2] = '0' + ((int)(obj->charge / 10));
        cstr[3] = '0' + (obj->charge % 10);
        cstr[4] = ']';
        cstr[5] = 0;
    }
}

void give_money(struct monster* m)
{
    pob cash;
    cash = detach_money(0);

    if (cash == NULL)
    {
        setgamestatus(SKIP_MONSTERS);
    }
    else
    {
        givemonster(m, cash);
    }
}

void lawbringer_gets_gem(pmt m, pob o)
{
    clearmsg();
    print1("The LawBringer accepts the gem reverently.");
    print2("He raises it above his head, where it bursts into lambent flame!");
    morewait();
    print1("You are bathed in a shimmering golden light.");
    print2("You feel embedded in an infinite matrix of ordered energy.");
    morewait();

    if (Imprisonment > 0)
    {
        Imprisonment = 0;
    }

    if (Player.rank[ORDER] == -1)
    {
        print2("You have been forgiven. You feel like a Paladin....");
        Player.rank[ORDER] = 1;
    }

    Player.alignment += 200;
    Player.pow = Player.maxpow = Player.pow * 2;
    gain_experience(2000);
    setgamestatus(GAVE_STARGEM);
    /* WDT HACK!!!  Where else would this ever get freed?? */
    free_obj(o, TRUE);
}

void givemonster(pmt m, pob o)
{
    /* special case -- give gem to LawBringer */
    if ((m->id == LAWBRINGER) && (o->id == OB_STARGEM))
    {
        lawbringer_gets_gem(m, o);
    }
    else
    {
        if (m->uniqueness == COMMON)
        {
            strcpy(Str3, "The ");
            strcat(Str3, m->monstring);
        }
        else
        {
            strcpy(Str3, m->monstring);
        }

        if (m_statusp(m, GREEDY) || m_statusp(m, NEEDY))
        {
            m_pickup(m, o);
            strcat(Str3, " takes your gift");
            print1(Str3);
            Player.alignment++;

            if (m_statusp(m, GREEDY) && (true_item_value(o) < (long) m->level * 100))
            {
                nprint1("...but does not appear satisfied.");
            }
            else if (m_statusp(m, NEEDY) &&
                     (true_item_value(o) < (long) Level->depth * Level->depth))
            {
                nprint1("...and looks chasteningly at you.");
            }
            else
            {
                nprint1("...and seems happy with it.");
                m_status_reset(m, HOSTILE);
                m_status_reset(m, GREEDY);
                m_status_reset(m, NEEDY);
            }
        }
        else if (m_statusp(m, HUNGRY))
        {
            if (((m->id == HORSE) && (o->id == OB_GRAIN)) || /* grain */
                    ((m->id != HORSE) &&
                     ((o->usef == I_FOOD) || (o->usef == I_POISON_FOOD))))
            {
                strcat(Str3, " wolfs down your food ... ");
                print1(Str3);
                m_status_reset(m, HUNGRY);
                m_status_reset(m, HOSTILE);

                if  (o->usef == I_POISON_FOOD)
                {
                    Player.alignment -= 2;
                    nprint1("...and chokes on the poisoned ration!");
                    morewait();
                    m_status_set(m, HOSTILE);
                    m_damage(m, 100, POISON);
                }
                else
                {
                    nprint1("...and now seems satiated.");
                }

                morewait();
                free_obj(o, TRUE);
            }
            else
            {
                strcat(Str3, " spurns your offering and leaves it on the ground.");
                print1(Str3);
                drop_at(m->x, m->y, o);
            }
        }
        else
        {
            strcat(Str3, " doesn't care for your offering and drops it.");
            print1(Str3);
            drop_at(m->x, m->y, o);
        }
    }
}

/* will clear all, not just one of an object. */
void conform_lost_object(pob obj)
{
    if (obj != NULL)
    {
        conform_lost_objects(obj->number, obj);
    }
}

/* removes n of object from inventory; frees object if appropriate. */
void dispose_lost_objects(int n, pob obj)
{
    int i, conformed = FALSE, subtracted = FALSE;

    if (obj == NULL)
    {
        return;
    }

    for (i = 0; i < MAXITEMS; i++)
        if (Player.possessions[i] == obj)
        {
            if (! subtracted)
            {
                obj->number -= n;
                subtracted = TRUE;
            }

            if (obj->number < 1)
            {
                if (!conformed)
                {
                    conform_unused_object(obj);
                    conformed = TRUE;
                }

                Player.possessions[i] = NULL;
            }
        }

    if (obj->number < 1)
    {
        free_obj( obj, TRUE );
    }
}

/* removes n of object from inventory without freeing object.
   Removes all instances of pointer (might be 2 handed weapon, etc) */
void conform_lost_objects(int n, pob obj)
{
    int i, conformed = FALSE, subtracted = FALSE;

    if (obj != NULL) for (i = 0; i < MAXITEMS; i++)
            if (Player.possessions[i] == obj)
            {
                if (! subtracted)
                {
                    obj->number -= n;
                    subtracted = TRUE;
                }

                if (obj->number < 1)
                {
                    if (!conformed)
                    {
                        conform_unused_object(obj);
                        conformed = TRUE;
                    }

                    Player.possessions[i] = NULL;
                }
            }
}

/* clears unused possession */
void conform_unused_object(pob obj)
{
    if (obj->used)
    {
        obj->used = FALSE;
        item_use(obj);
        inv_display_munge();
    }

    calc_melee();
}

/* select an item from inventory */
/* if itype is NULL_ITEM, any kind of item is acceptable.
   if itype is CASH, any kind of item or '$' (cash) is acceptable.
   if itype is FOOD, CORPSE or FOOD is acceptable, but only FOOD is
listed in the possibilities.
   if itype is any other object type (eg SCROLL, POTION, etc.), only
that type of item is acceptable or is listed */

int item_is_selectable (Symbol itype, struct object* item)
{
    if (!item)
    {
        return FALSE;
    }

    if (CASH == itype)
    {
        return TRUE;
    }

    if (NULL_ITEM == itype)
    {
        return TRUE;
    }

    if (item->objchar == itype)
    {
        return TRUE;
    }

    if (FOOD == itype && CORPSE == item->objchar)
    {
        return TRUE;
    }

    return FALSE;
}

int getitem (Symbol itype)
{
    return getitem_prompt(0, itype);
}

int getitem_prompt(string message, Symbol itype)
{
    int key;
    char* line3;
    char invstr[64];
    char selectstr[80];
    int i, k;
    int again;
    int found = FALSE;
    int drewmenu = FALSE;
    found = ((itype == NULL_ITEM) || ((itype == CASH) && (Player.cash > 0)));
    /* build invstr, which lists all valid selections that the user can make */
    invstr[0] = 0;
    k = 0;

    for (i = 1; i < MAXITEMS; ++i)
    {
        if (item_is_selectable(itype, Player.possessions[i]))
        {
            found = TRUE;
            invstr[k++] = index_to_key(i);
            invstr[k] = 0;
        }
    }

    if (!found)
    {
        print3("Nothing appropriate.");
        return ABORT;
    }

    if (itype == CASH)
    {
        invstr[k++] = CASH & 0xff;
        invstr[k] = 0;
    }

    /* gotta let the user see what everything means... */
    invstr[k++] = '?';
    invstr[k] = 0;
    line3 = NULL;
    /* build prompt... */
    selectstr[0] = 0;

    if (message.length() > 0)
    {
        strcpy(selectstr, message.c_str());
    }

    strcat(selectstr, "Select an item. (");
    i = 0;
    k = strlen(selectstr);

    while (TRUE)
    {
        if ('?' == invstr[i])
        {
            break;
        }

        selectstr[k++] = invstr[i++];
        selectstr[k++] = ',';

        if (k > 75)
        {
            break;
        }
    }

    selectstr[k - 1] = ')';
    selectstr[k] = 0;

    /* get input from the user */
    do
    {
        again = FALSE;
        key = cinema_interact(invstr, selectstr, "  ? to display items", line3);
        line3 = NULL;

        if ('?' == key)
        {
            again = TRUE;
            drewmenu = TRUE;

            for (i = 1; i < MAXITEMS; ++i)
            {
                if (item_is_selectable(itype, Player.possessions[i]))
                {
                    display_inventory_slot(i, FALSE);
                }
            }
        }
        else if ((CASH & 0xff) == key && (CASH != itype))
        {
            again = TRUE;
            line3 = "You cannot select cash now.";
        }
    }
    while (again);

    if (drewmenu)
    {
        xredraw();
    }

    if (-1 == key)
    {
        return ABORT;    /* cinema_interact() returns -1 for ESC */
    }

    if ((CASH & 0xff) == key)
    {
        return CASHVALUE;
    }

    return key_to_index(key);
}

/* true if the numerical index based on 'a' == 1 turns out to be either
out of the range of the possessions array or a null item */
int badobject(char slotchar)
{
    int slot = slotchar + 1 - 'a';

    if ((slot < 1) || (slot >= MAXITEMS))
    {
        return (TRUE);
    }
    else
    {
        return (Player.possessions[slot] == NULL);
    }
}

#ifndef MSDOS_SUPPORTED_ANTIQUE
/* this takes the numerical index directly for the same effect as badobject*/
int baditem(int slotnum)
{
    if ((slotnum < 1) || (slotnum >= MAXITEMS))
    {
        return (TRUE);
    }
    else
    {
        return (Player.possessions[slotnum] == NULL);
    }
}
#endif

/* formerly add_item_to_pack */
void gain_item(pob o)
{
    if (o->uniqueness == UNIQUE_MADE)
    {
        Objects[o->id].uniqueness = UNIQUE_TAKEN;
    }

    if (o->objchar == CASH)
    {
        print2("You gained some cash.");
        Player.cash += o->basevalue;
        free_obj(o, TRUE);
        dataprint();
    }
    else if (optionp(PACKADD))
    {
        if (! get_to_pack(o))
        {
            Player.possessions[O_UP_IN_AIR] = o;
            do_inventory_control();
        }
    }
    else
    {
        Player.possessions[O_UP_IN_AIR] = o;
        do_inventory_control();
    }
}

/*  tosses the item into the pack, making it the first reachable item */
void push_pack(pob o)
{
    int i;

    for (i = Player.packptr; i > 0; i--)
    {
        Player.pack[i] = Player.pack[i - 1];
    }

    Player.pack[0] = o;
    Player.packptr++;
}

/* Adds item to pack list */
void add_to_pack(pob o)
{
    if (Player.packptr >= MAXPACK)
    {
        print3("Your pack is full. The item drops to the ground.");
        drop_at(Player.x, Player.y, o);
    }
    else
    {
        push_pack(o);
        print3("Putting item in pack.");
    }
}

/* Adds item to pack list, maybe going into inventory mode if pack is full */
int get_to_pack(pob o)
{
    if (Player.packptr >= MAXPACK)
    {
        print3("Your pack is full.");
        morewait();
        return (FALSE);
    }
    else
    {
        push_pack(o);
        print3("Putting item in pack.");
        return (TRUE);
    }
}

int pack_item_cost(int index)
{
    int cost;

    if (index > 20)
    {
        cost = 17;
    }
    else if (index > 15)
    {
        cost = 7;
    }
    else
    {
        cost = 2;
    }

    return cost;
}

/* WDT -- 'response' must be an index into the pack. */
void use_pack_item(int response, int slot)
{
    pob item;
    int i;
    i = pack_item_cost(response);

    if (i > 10)
    {
        cinema_scene("You begin to rummage through your pack.", NULL, NULL);
    }

    if (i > 5)
    {
        cinema_scene("You search your pack for the item.", NULL, NULL);
    }

    print3("You take the item from your pack.");
    morewait();
    Command_Duration += i;
    item = Player.possessions[slot] = Player.pack[response];

    for (i = response; i < Player.packptr - 1; i++)
    {
        Player.pack[i] = Player.pack[i + 1];
    }

    Player.pack[--Player.packptr] = NULL;

    if ((slot == O_READY_HAND || slot == O_WEAPON_HAND) &&
            twohandedp(item->id))
    {
        if (Player.possessions[O_READY_HAND] == NULL)
        {
            Player.possessions[O_READY_HAND] = item;
        }

        if (Player.possessions[O_WEAPON_HAND] == NULL)
        {
            Player.possessions[O_WEAPON_HAND] = item;
        }
    }

    if (item_useable(item, slot))
    {
        item->used = TRUE;
        item_use(item);
        inv_display_munge();
        morewait();

        if (item->number > 1)
        {
            pack_extra_items(item);
        }
    }
}

/* WDT HACK!  This ought to be in scr.c, along with its companion.  However,
 * right now it's only used in the function directly below. */
int aux_display_pack(int start_item, int slot)
{
    int i = start_item, items;
    string depth_string;
    menuclear();
#if 0

    /* WDT: I decided to remove these lines, since the purpose of this routine
     * is to generate a pack menu, not update the message line.  This is
     * especially important now that I'm making the inventory system use the
     * new 'Cinema' message box (which will stop the message corruption
     * problems that were epidemic). */
    if (Player.packptr < 1)
    {
        print3("Pack is empty.");
    }
    else if (Player.packptr <= start_item)
    {
        print3("You see the leather at the bottom of the pack.");
    }

#else

    /* These cases are not terribly important, but they can happen. */
    if (Player.packptr < 1 || Player.packptr <= start_item)
    {
        return start_item;
    }

#endif
    else
    {
        items = 0;

        for (i = start_item; i < Player.packptr && items < ScreenLength - 5; i++)
        {
            if ( aux_slottable(Player.pack[i], slot) )
            {
                if (pack_item_cost(i) > 10)
                {
                    depth_string = "**";
                }
                else if (pack_item_cost(i) > 5)
                {
                    depth_string = "* ";
                }
                else
                {
                    depth_string = "  ";
                }

                sprintf(Str1, "  %c: %s %s\n", i + 'a', depth_string.c_str(),
                        itemid(Player.pack[i]));

                if (items == 0)
                {
                    menuprint("Items in Pack:\n");
                }

                menuprint(Str1);
                items++;
            }
        }

        if (items == 0)
        {
            menuprint("You see nothing useful for that slot in the pack.");
        }
        else
        {
            menuprint("\n*: Takes some time to reach; **: buried very deeply.");
        }

        showmenu();
    }

    return i;
}

/* takes something from pack, puts to slot,
 * or to 'up-in-air', one of which at least must be empty */
int aux_take_from_pack(int slot)
{
    char response, pack_item, last_item;
    int quit = FALSE, ok = TRUE;

    if (Player.possessions[slot] != NULL)
    {
        slot = O_UP_IN_AIR;
    }

    if (Player.possessions[slot] != NULL)
    {
        print3("slot is not empty!");
    }
    else if (Player.packptr < 1)
    {
        print3("Pack is empty!");
    }
    else
    {
        pack_item = 0;

        do
        {
            ok = TRUE;
            last_item = aux_display_pack(pack_item, slot);

            if (last_item == Player.packptr && pack_item == 0 )
            {
                print1("Enter pack slot letter or ESCAPE to quit.");
            }
            else if (last_item == Player.packptr)
            {
                print1("Enter pack slot letter, - to go back, or ESCAPE to quit.");
            }
            else if (pack_item == 0)
            {
                print1("Enter pack slot letter, + to see more, or ESCAPE to quit.");
            }
            else
            {
                print1("Enter pack slot letter, + or - to see more, or ESCAPE to quit.");
            }

            response = mcigetc();

            if (response == '?')
            {
                /* WDT HACK -- display some help instead. */
                print1("Help not implemented (sorry).");
                morewait();
                ok = FALSE;
            }
            else if (response == ESCAPE)
            {
                quit = TRUE;
            }
            else if (response == '+')
            {
                if (last_item < Player.packptr)
                {
                    pack_item = last_item;
                }

                ok = FALSE;
            }
            else if (response == '-')
            {
                /* WDT HACK: this _should_ make us page up.  Sadly,
                 * I have no way of calculating how much I'll be paging up.
                 * This is fixable, but I have no idea how much work... As
                 * a hack, I'm just returning to the first page of the listing.
                 */
                pack_item = 0;
                ok = FALSE;
            }
            else
            {
                ok = ((response >= 'a') && (response < 'a' + Player.packptr));

                if (ok)
                {
                    ok = slottable(Player.pack[response - 'a'], slot);
                }
            }
        }
        while (! ok);

        if (! quit)
        {
            use_pack_item(response - 'a', slot);
        }
    }

    inv_display_munge();
    return slot;
}

/* takes something from pack, puts to slot,
or to 'up-in-air', one of which at least must be empty */
int aux_top_take_from_pack(int slot, int display)
{
    char response;
    int quit = FALSE, ok = TRUE;

    if (Player.possessions[slot] != NULL)
    {
        slot = O_UP_IN_AIR;
    }

    if (Player.possessions[slot] != NULL)
    {
        print3("slot is not empty!");
    }
    else if (Player.packptr == 0)
    {
        print3("Pack is empty!");
    }
    else
    {
        do
        {
            ok = TRUE;
            print1("Enter pack slot letter, or ? to show pack, or ESCAPE to quit.");
            response = mcigetc();

            if (response == '?')
            {
                display_pack();
                inv_display_munge();
                ok = FALSE;
            }
            else if (response == ESCAPE)
            {
                quit = TRUE;
            }
            else
            {
                ok = ((response >= 'a') && (response < 'a' + Player.packptr));

                if (ok)
                {
                    ok = slottable(Player.pack[response - 'a'], slot);
                }
            }
        }
        while (! ok);

        if (! quit)
        {
            use_pack_item(response - 'a', slot);
        }
    }

    return slot;
}

int take_from_pack(int slot, int display)
{
    if (optionp(TOPINV))
    {
        return aux_top_take_from_pack(slot, display);
    }
    else
    {
        return aux_take_from_pack(slot);
    }
}

#ifndef MSDOS_SUPPORTED_ANTIQUE
/* General interface to inventory */
void item_inventory(int topline)
{
    if (topline)
    {
        display_possessions();
        inventory_control();
    }
    else
    {
        top_inventory_control();
    }
}
#endif

void do_inventory_control(void)
{
    if (optionp(TOPINV))
    {
        top_inventory_control();
    }
    else
    {
        menuclear();
        display_possessions();
        inventory_control();
    }
}

/* inventory_control assumes a few setup things have been done,
 * like loading the O_UP_IN_AIR item, etc.
 * Each action uses up a little time. If only inspection actions
 * are taken, no time is used up. */
void inventory_control(void)
{
    int slot = O_UP_IN_AIR, done = FALSE;
    int response;
    char letter;
#ifdef MSDOS_SUPPORTED_ANTIQUE
    int simple = 0;
#endif
    /* Start out assuming that we'll need to redraw. */
    inv_display_munge();
    clearmsg3();

    do
    {
        checkclear();
        print1("Action [d,e,l,p,s,t,x,>,<,?,ESCAPE]:");
        inv_display_refresh();
        show_inventory_slot(slot, FALSE);
        display_inventory_slot(O_UP_IN_AIR, FALSE);
        move_slot(slot, slot, MAXITEMS);
        response = mcigetc();

        switch (response)
        {
            case 12:
            case 18: /* ^l, ^r */
                display_possessions();
                break;

            case 'd':
                if (Player.possessions[O_UP_IN_AIR] != NULL)
                {
                    drop_from_slot(O_UP_IN_AIR);
                    display_inventory_slot(O_UP_IN_AIR, FALSE);
                }
                else if (Player.possessions[slot] != NULL)
                {
                    drop_from_slot(slot);
                    show_inventory_slot(slot, FALSE);
                }
                else
                {
                    print3("Nothing in selected slot!");
                }

                Command_Duration++;
                break;

            case 'l':
                Str1[0] = '\0';

                if (Player.possessions[slot] != NULL)
                {
                    if (!strcmp(itemid(Player.possessions[slot]),
                                Player.possessions[slot]->objstr))
                    {
                        print3("You notice nothing new about it.");
                    }
                    else
                    {
                        if (Player.possessions[slot]->uniqueness == COMMON)
                        {
                            strcat(Str1, "Your ");
                        }

                        strcat(Str1, itemid(Player.possessions[slot]));

                        if (Player.possessions[slot]->objchar == BOOTS)
                        {
                            strcat(Str1, " look like ");
                        }
                        else
                        {
                            strcat(Str1, " looks like a");
                            letter = Player.possessions[slot]->objstr[0];

                            if (letter == 'a' || letter == 'A' || letter == 'e' ||
                                    letter == 'E' || letter == 'i' || letter == 'I' ||
                                    letter == 'o' || letter == 'O' || letter == 'u' || letter == 'U')
                            {
                                strcat(Str1, "n ");
                            }
                            else
                            {
                                strcat(Str1, " ");
                            }
                        }

                        strcat(Str1, Player.possessions[slot]->objstr);
                        print3(Str1);
                    }
                }
                else
                {
                    print3("Nothing in selected slot!");
                }

                break;

            case 'p':
                if (Player.possessions[slot] != NULL)
                {
                    put_to_pack(slot);
                    show_inventory_slot(slot, FALSE);
                }

                Command_Duration += 5;
                break;

            case 's':
                display_pack();
                morewait();
                inv_display_munge();
                Command_Duration += 5;
                break;

            case 't':
                show_inventory_slot(take_from_pack(slot, TRUE), FALSE);
                Command_Duration += 5;
                break;

            case 'e':
                switch_to_slot(slot);
                show_inventory_slot(O_UP_IN_AIR, FALSE);
                show_inventory_slot(slot, FALSE);
                Command_Duration += 2;
                break;

            case '\n':
            case 'x':
                switch_to_slot(slot);
                show_inventory_slot(O_UP_IN_AIR, FALSE);
                show_inventory_slot(slot, FALSE);
                Command_Duration += 2;
                done = (Player.possessions[O_UP_IN_AIR] == NULL);
                break;

            case 'j':
            case '>':
            case '2':
#if defined(KEY_DOWN)
            case KEY_DOWN:
#endif
                slot = move_slot(slot, slot + 1, MAXITEMS);
                break;

            case 'k':
            case '<':
            case '8':
#if defined(KEY_UP)
            case KEY_UP:
#endif
                slot = move_slot(slot, slot - 1, MAXITEMS);
                break;
#ifdef KEY_HOME

            case KEY_HOME:
#endif
            case '-':
                slot = move_slot(slot, 0, MAXITEMS);
                break;
#ifdef KEY_LL

            case KEY_LL:
#endif
            case '+':
                slot = move_slot(slot, MAXITEMS - 1, MAXITEMS);
                break;

            case '?':
                menuclear();
                menuprint("d:\tDrop up-in-air or current item\n");
                menuprint("e:\tExchange current slot with up-in-air slot\n");
                menuprint("l:\tLook at current item\n");
                menuprint("p:\tPut up-in-air or current item in pack\n");
                menuprint("s:\tShow contents of pack\n");
                menuprint("t:\tTake something from pack into the\n\tcurrent or up-in-air slot\n");
                menuprint("x:\tAs 'e', but exit if up-in-air slot finishes empty\n");
                menuprint(">:\tMove down one slot/item\n");
                menuprint("<:\tMove up one slot/item\n");
                menuprint("?:\tDisplay help (this message + help file)\n");
                menuprint("ESCAPE:\texit\n");
                showmenu();
                clearmsg();
                print1("Display full help? (y/n)");

                if (ynq1() == 'y')
                {
                    inv_help();
                }

                inv_display_munge();
                break;

            case ESCAPE:
                if (Player.possessions[O_UP_IN_AIR] != NULL)
                {
                    drop_at(Player.x, Player.y, Player.possessions[O_UP_IN_AIR]);
                    Player.possessions[O_UP_IN_AIR] = NULL;
                    print3("Object 'up in air' dropped.");
                }

                done = TRUE;
                break;

            default:
                if (key_to_index(response) > 0)
                {
                    slot = move_slot(slot, key_to_index(response), MAXITEMS);

                    if (Player.possessions[slot] == NULL
                            &&
                            Player.possessions[O_UP_IN_AIR] == NULL)
                    {
                        show_inventory_slot(take_from_pack(slot, TRUE), FALSE);
                        Command_Duration += 5;
                    }
                    else
                    {
                        switch_to_slot(slot);
                        show_inventory_slot(slot, FALSE);
                        slot = O_UP_IN_AIR;
                        show_inventory_slot(slot, FALSE);
                        Command_Duration += 2;
                    }
                }
        }

        calc_melee();
    }
    while (! done);

    xredraw();
}

/* Make it clear that the inventory window mmust be redrawn. */
static int inv_must_redraw;
static void inv_display_munge(void)
{
    inv_must_redraw = TRUE;
}

static void inv_display_refresh(void)
{
    if ( inv_must_redraw )
    {
        display_possessions();
    }

    inv_must_redraw = FALSE;
}

/* same as inventory_control, but only uses msg window for i/o*/
void top_inventory_control(void)
{
    int slot = 0, done = FALSE, usedmenu = FALSE;
    char response, letter;
    clearmsg3();

    do
    {
        clearmsg1();
        print1("Action [d,e,l,p,s,t,x,~,?,ESCAPE]:");
        print2("'Up in air': ");

        if (Player.possessions[O_UP_IN_AIR] == NULL)
        {
            nprint2("NOTHING");
        }
        else
        {
            nprint2(itemid(Player.possessions[O_UP_IN_AIR]));
        }

        response = (char) mcigetc();

        switch (response)
        {
            case 'd':
                if (Player.possessions[O_UP_IN_AIR] != NULL)
                {
                    drop_from_slot(O_UP_IN_AIR);
                }
                else
                {
                    slot = get_inventory_slot();

                    if (Player.possessions[slot] != NULL)
                    {
                        drop_from_slot(slot);
                    }
                    else
                    {
                        print3("Nothing in selected slot!");
                    }
                }

                Command_Duration++;
                break;

            case 'l':
                Str1[0] = '\0';
                slot = get_inventory_slot();

                if (Player.possessions[slot] != NULL)
                {
                    if (!strcmp(itemid(Player.possessions[slot]),
                                Player.possessions[slot]->objstr))
                    {
                        print3("You notice nothing new about it.");
                    }
                    else
                    {
                        if (Player.possessions[slot]->uniqueness == COMMON)
                        {
                            strcat(Str1, "Your ");
                        }

                        strcat(Str1, itemid(Player.possessions[slot]));

                        if (Player.possessions[slot]->objchar == BOOTS)
                        {
                            strcat(Str1, " look like ");
                        }
                        else
                        {
                            strcat(Str1, " looks like a");
                            letter = Player.possessions[slot]->objstr[0];

                            if (letter == 'a' || letter == 'A' || letter == 'e' ||
                                    letter == 'E' || letter == 'i' || letter == 'I' ||
                                    letter == 'o' || letter == 'O' || letter == 'u' || letter == 'U')
                            {
                                strcat(Str1, "n ");
                            }
                            else
                            {
                                strcat(Str1, " ");
                            }
                        }

                        strcat(Str1, Player.possessions[slot]->objstr);
                        print3(Str1);
                    }
                }
                else
                {
                    print3("Nothing in selected slot!");
                }

                break;

            case 'p':
                if (Player.possessions[O_UP_IN_AIR] == NULL)
                {
                    slot = get_inventory_slot();
                }
                else
                {
                    slot = O_UP_IN_AIR;
                }

                put_to_pack(slot);
                Command_Duration += 5;
                break;

            case 's':
                display_pack();
                usedmenu = TRUE;
                Command_Duration += 5;
                break;

            case 't':
                slot = get_inventory_slot();
                (void) take_from_pack(slot, FALSE);
                Command_Duration += 5;
                break;

            case 'e':
                slot = get_inventory_slot();

                if ( slot == O_UP_IN_AIR )
                {
                    break;
                }

                switch_to_slot(slot);
                Command_Duration += 2;
                break;

            case 'x':
                slot = get_inventory_slot();

                if ( slot == O_UP_IN_AIR )
                {
                    break;
                }

                switch_to_slot(slot);
                Command_Duration += 2;
                done = (Player.possessions[O_UP_IN_AIR] == NULL);
                break;

            case '~':
                display_possessions();
                inventory_control();
                usedmenu = TRUE;
                done = TRUE;
                break;

            case '?':
                menuclear();
                menuprint("d:\tDrop an item\n");
                menuprint("e:\tExchange a slot with up-in-air slot\n");
                menuprint("l:\tLook at an item\n");
                menuprint("p:\tPut an item in pack\n");
                menuprint("s:\tShow contents of pack\n");
                menuprint("t:\tTake something from pack into a slot\n");
                menuprint("x:\tAs 'e', above, exit if up-in-air slot finishes empty\n");
                menuprint("~:\tEnter full-screen inventory mode\n");
                menuprint("?:\tDisplay help (this message + help file)\n");
                menuprint("ESCAPE:\texit\n");
                showmenu();
                clearmsg();
                print1("Display full help? (y/n)");

                if (ynq1() == 'y')
                {
                    inv_help();
                }

                usedmenu = TRUE;
                break;

            case ESCAPE:
                if (Player.possessions[O_UP_IN_AIR] != NULL)
                {
                    drop_at(Player.x, Player.y, Player.possessions[O_UP_IN_AIR]);
                    Player.possessions[O_UP_IN_AIR] = NULL;
                    print3("Object 'up in air' dropped.");
                }

                done = TRUE;
                break;
        }

        calc_melee();
    }
    while (! done);

    if (usedmenu)
    {
        xredraw();
    }
}

/* Let the user select a slot. */
int get_inventory_slot(void)
{
    signed char response;

    do
    {
        clearmsg1();
        print1("Which inventory slot ['-'='up-in-air' slot]?");
        response = (signed char)mcigetc();

        if ( response == ESCAPE || response == '-' )
        {
            return O_UP_IN_AIR;
        }
        else
        {
            response = key_to_index(response);
        }
    }
    while (response != O_UP_IN_AIR);

    return response;
}

/* returns some number between 0 and o->number */
int get_item_number(pob o)
{
    int n = 0;

    if (o->number == 1)
    {
        return 1;
    }

    do
    {
        clearmsg();
        print1("How many? -- max ");
        mnumprint(o->number);
        nprint1(" :");
        n = (int) parsenum("");

        if (n > o->number)
        {
            print3("Too many!");
        }
        else if (n < 1)
        {
            n = 0;
        }
    }
    while (n > o->number);

    if (n < 1)
    {
        n = 0;
    }

    return (n);
}

void drop_from_slot(int slot)
{
    int n, waitflag;

    if (Player.possessions[slot] != NULL)
    {
        if (cursed(Player.possessions[slot]) == TRUE + TRUE)
        {
            print3("It sticks to your fingers!");
        }
        else
        {
            n = get_item_number(Player.possessions[slot]);

            if (n > 0)
            {
                p_drop_at(Player.x, Player.y, n, Player.possessions[slot]);
                waitflag = (Player.possessions[slot]->used &&
                            (Player.possessions[slot]->number == n));
                conform_lost_objects(n, Player.possessions[slot]);

                if (waitflag)
                {
                    morewait();
                }
            }
            else
            {
                print3("Didn't drop anything.");
            }
        }
    }
    else
    {
        print3("Didn't drop anything.");
    }
}

void put_to_pack(int slot)
{
    int waitflag, num = 1;
    pob temp, oslot = Player.possessions[slot];

    if (oslot == NULL)
    {
        print3("Slot is empty!");
    }
    else if (cursed(oslot) == TRUE + TRUE)
    {
        print3("Item is cursed!");
    }
    else
    {
        num = get_item_number(oslot);

        if (num > 0)
        {
            temp = split_item(num, oslot);
            waitflag = (oslot->used && (oslot->number == num));
            conform_lost_objects(num, oslot);

            if (waitflag)
            {
                morewait();
            }

            add_to_pack(temp);
        }
    }
}

/* splits num off of item to make newitem which is returned */
/* something else (conform_lost_objects) has to reduce the actual
   number value of item and Player.itemweight */
pob split_item(int num, pob item)
{
    pob newitem = NULL;

    if (item != NULL)
    {
        newitem = copy_obj( item );

        if (num <= item->number)
        {
            newitem->number = num;
        }

        /* else num > item->number, so return newitem with number = item->number */
        newitem->used = FALSE;  /* whether the original item was used or not */
    }

    return (newitem);
}

/* Trades contents of "up in air" slot with selected slot. One or both
may be null. If both slots are 'objequal' merges two groups into one
in the selected slot. If one slot is null and the number of the other
is greater than one, requests how many to move. */
void switch_to_slot(int slot)
{
    pob oslot = Player.possessions[slot];
    pob oair = Player.possessions[O_UP_IN_AIR];
    pob otemp = NULL;
    int slotnull, airnull, num = 1, trade = FALSE, put = FALSE, take = FALSE, merge = FALSE;
    int s2h = FALSE, a2h = FALSE;

    /* ie, is cursed and in use */
    if (slot == O_UP_IN_AIR)
    {
        print3("This action makes no sense!");
    }
    else if (cursed(oslot) == TRUE + TRUE) /* WDT: this is SICK!!!!  TRUE doesn't
                      * add. */
    {
        print3("The object in that slot is cursed -- you can't get rid of it!");
    }
    else
    {
        slotnull = (oslot == NULL);
        airnull = (oair == NULL);

        if  (!slotnull)
            s2h = (Player.possessions[O_READY_HAND] ==
                   Player.possessions[O_WEAPON_HAND]);

        if (! airnull)
            a2h = (twohandedp(oair->id) &&
                   ((slot == O_READY_HAND) || (slot == O_WEAPON_HAND)));

        /* figure out which action to take */
        /* merge if both are same kind of object */
        merge = objequal(oslot, oair);
        take = ((!merge) && (!slotnull) && airnull);
        put = ((!merge) && slotnull && (!airnull) && slottable(oair, slot));
        trade = ((!merge) && (!slotnull) && (!airnull) && slottable(oair, slot));

        if (merge)
        {
            merge_item(slot);
        }
        else if (put)
        {
            /* deal with a 2-handed weapon */
            if (a2h)
            {
                if (Player.possessions[O_READY_HAND] == NULL)
                {
                    Player.possessions[O_READY_HAND] = oair;
                }

                if (Player.possessions[O_WEAPON_HAND] == NULL)
                {
                    Player.possessions[O_WEAPON_HAND] = oair;
                }
            }
            else
            {
                Player.possessions[slot] = oair;
            }

            Player.possessions[O_UP_IN_AIR] = NULL;

            if (item_useable(oair, slot))
            {
                oair->used = TRUE;
                item_use(oair);
                inv_display_munge();
                morewait();

                if (oair->number > 1)
                {
                    pack_extra_items(oair);
                }
            }

            Player.possessions[O_UP_IN_AIR] = NULL;
        }
        else if (take)
        {
            num = get_item_number(oslot);

            if (num > 0)
            {
                otemp = split_item(num, oslot);
                dispose_lost_objects(num, oslot);
                Player.possessions[O_UP_IN_AIR] = otemp;
            }

            if (s2h)
            {
                if (Player.possessions[O_READY_HAND] == oslot)
                {
                    Player.possessions[O_READY_HAND] = NULL;
                }

                if (Player.possessions[O_WEAPON_HAND] == oslot)
                {
                    Player.possessions[O_WEAPON_HAND] = NULL;
                }
            }
        }
        else if (trade)
        {
            /* first remove item from slot */
            num = oslot->number;
            conform_lost_objects(oslot->number, oslot);
            oslot->number = num;
            Player.possessions[O_UP_IN_AIR] = oslot;
            Player.possessions[slot] = oair;

            if (s2h)
            {
                if (Player.possessions[O_READY_HAND] == oslot)
                {
                    Player.possessions[O_READY_HAND] = NULL;
                }

                if (Player.possessions[O_WEAPON_HAND] == oslot)
                {
                    Player.possessions[O_WEAPON_HAND] = NULL;
                }
            }

            if (a2h)
            {
                if (Player.possessions[O_READY_HAND] == NULL)
                {
                    Player.possessions[O_READY_HAND] = oair;
                }

                if (Player.possessions[O_WEAPON_HAND] == NULL)
                {
                    Player.possessions[O_WEAPON_HAND] = oair;
                }
            }

            if (item_useable(oair, slot))
            {
                oair->used = TRUE;
                item_use(oair);
                inv_display_munge();
                morewait();

                if (oair->number > 1)
                {
                    pack_extra_items(oair);
                }
            }
        }
    }
}

/* merges the up-in-air items into the selected items */
void merge_item(int slot)
{
    Player.possessions[slot]->number +=
        Player.possessions[O_UP_IN_AIR]->number;
    Player.possessions[O_UP_IN_AIR] = NULL;
}

/* are two objects equal except for their number field? */
/* returns false if either object is null */
int objequal(pob o, pob p)
{
    if ((o == NULL) || (p == NULL))
    {
        return (FALSE);
    }
    else return (
                        (o->id == p->id) &&
                        /* DAG won't match corpses because they use charge for monster id, */
                        /* except for hornets which have mid == 0, so will stack.  Prevent this. */
                        (o->id != CORPSEID) &&
                        (o->plus == p->plus) &&
                        (o->charge == 0) &&
                        (p->charge == 0) &&
                        (o->dmg == p->dmg) &&
                        (o->hit == p->hit) &&
                        (o->aux == p->aux) &&
                        (o->known == p->known) &&
                        (o->blessing == p->blessing) &&
                        (o->usef == p->usef) &&
                        (o->objstr == p->objstr )
                    );
}

/* criteria for being able to put some item in some slot */
int slottable(pob o, int slot)
{
    int ok = TRUE;

    if (o == NULL)
    {
        ok = FALSE;
    }
    else if (slot == O_ARMOR)
    {
        if (o->objchar != ARMOR)
        {
            print3("Only armor can go in the armor slot!");
            ok = FALSE;
        }
    }
    else if (slot == O_SHIELD)
    {
        if (o->objchar != SHIELD)
        {
            print3("Only a shield can go in the shield slot!");
            ok = FALSE;
        }
    }
    else if (slot == O_BOOTS)
    {
        if (o->objchar != BOOTS)
        {
            print3("Only boots can go in the boots slot!");
            ok = FALSE;
        }
    }
    else if (slot == O_CLOAK)
    {
        if (o->objchar != CLOAK)
        {
            print3("Only a cloak can go in the cloak slot!");
            ok = FALSE;
        }
    }
    else if (slot >= O_RING1)
    {
        if (o->objchar != RING)
        {
            print3("Only a ring can go in a ring slot!");
            ok = FALSE;
        }
    }

    return (ok);
}

/* whether or not an item o can be used in a slot. Assumes o can in
   fact be placed in the slot. */
int item_useable(pob o, int slot)
{
    /* don't have to check the object in the first if since only armor
    can go in armor slot, cloak in cloak slot, etc */
    if ((slot == O_ARMOR) ||
            (slot == O_CLOAK) ||
            (slot == O_SHIELD) ||
            (slot == O_BOOTS) ||
            (slot >= O_RING1))
    {
        return (TRUE);
    }
    /* weapon is useable if it is put in weapon hand or if it is two-handed
       and put in either hand when the other also holds the weapon */
    else if ((o->objchar == WEAPON) ||
             (o->objchar == MISSILEWEAPON))
    {
        if (twohandedp(o->id) &&
                ((slot == O_READY_HAND) || (slot == O_WEAPON_HAND)))
        {
            if (Player.possessions[O_READY_HAND] ==
                    Player.possessions[O_WEAPON_HAND])
            {
                print1("You heft the weapon and find you must use both hands.");
                morewait();
                return (TRUE);
            }
            else
            {
                print1("This weapon is two-handed, so at the moment, ");
                print2("you are just lugging it around....");
                morewait();
                return (FALSE);
            }
        }
        else
        {
            return (slot == O_WEAPON_HAND);
        }
    }
    else
    {
        return (FALSE);
    }
}

/* returns FALSE if not cursed, TRUE if cursed but not used,
   TRUE + TRUE if cursed and used */
int cursed(pob obj)
{
    return ((obj == NULL) ?
            FALSE :
            ((obj->blessing < 0) ?
             (obj->used == TRUE) + TRUE :
             FALSE));
}

/* returns true if item with id and charge is found in pack or in
   inventory slot. charge is used to differentiate
   corpses instead of aux, which is their food value. */
int find_item(pob* o, int id, int chargeval)
{
    int i, found = FALSE;
    *o = NULL;

    for (i = 1; ((i < MAXITEMS) && (! found)); i++)
        if (Player.possessions[i] != NULL)
            if ((Player.possessions[i]->id == id) &&
                    ((chargeval == -1) ||
                     (Player.possessions[i]->charge == chargeval)))
            {
                *o = Player.possessions[i];
                found = TRUE;
            }

    if (! found)
        for (i = 0; ((i < Player.packptr) && (! found)); i++)
            if (Player.pack[i] != NULL)
                if ((Player.pack[i]->id == id) &&
                        ((chargeval == -1) ||
                         (Player.pack[i]->charge == chargeval)))
                {
                    *o = Player.pack[i];
                    found = TRUE;
                }

    return (found);
}

/* returns true if item with id and charge is found in pack or in
   inventory slot. Destroys item. charge is used to differentiate
   corpses instead of aux, which is their food value. */
int find_and_remove_item(int id, int chargeval)
{
    int i, found = FALSE;
    pob o = NULL;

    for (i = 1; ((i < MAXITEMS) && (! found)); i++)
        if (Player.possessions[i] != NULL)
            if ((Player.possessions[i]->id == id) &&
                    ((chargeval == -1) ||
                     (Player.possessions[i]->charge == chargeval)))
            {
                o = Player.possessions[i];
                conform_lost_objects(1, o);
                found = TRUE;
            }

    if (! found) for (i = 0; ((i < Player.packptr) && (! found)); i++)
            if (Player.pack[i] != NULL)
                if ((Player.pack[i]->id == id) &&
                        ((chargeval == -1) ||
                         (Player.pack[i]->charge == chargeval)))
                {
                    Player.pack[i]->number--;

                    if (Player.pack[i]->number == 0)
                    {
                        free_obj( Player.pack[i], TRUE );
                        Player.pack[i] = NULL;
                    }

                    found = TRUE;
                }

    fixpack();
    return (found);
}

void lose_all_items(void)
{
    int i;
    print1("You notice that you are completely devoid of all possessions.");
    morewait();

    for (i = 0; i < MAXITEMS; i++)
        if (Player.possessions[i] != NULL)
        {
            dispose_lost_objects(Player.possessions[i]->number,
                                 Player.possessions[i]);
            Player.possessions[i] = NULL;
        }

    for (i = 0; i < MAXPACK; i++)
    {
        if (Player.pack[i] != NULL)
        {
            free_obj( Player.pack[i], TRUE );
        }

        Player.pack[i] = NULL;
    }

    Player.packptr = 0;
    calc_melee();
    morewait();
}

/* prevents people from wielding 3 short swords, etc. */
void pack_extra_items(pob item)
{
    pob extra = copy_obj( item );
    extra->number = item->number - 1;
    extra->used = FALSE;
    item->number = 1;

    if (Player.packptr < MAXPACK)
    {
        print3("Putting extra items back in pack.");
        morewait();
        push_pack(extra);
    }
    else if (Player.possessions[O_UP_IN_AIR] == NULL)
    {
        print3("Extra copies of item are 'up in the air'");
        Player.possessions[O_UP_IN_AIR] = extra;
    }
    else
    {
        print3("No room for extra copies of item -- dropping them.");
        drop_at(Player.x, Player.y, extra);
    }

    calc_melee();
}

/* makes sure Player.pack is OK, (used after sale from pack) */
void fixpack(void)
{
    pob tpack[MAXPACK];
    int i, tctr = 0;

    for (i = 0; i < MAXPACK; i++)
    {
        tpack[i] = NULL;
    }

    for (i = 0; i < MAXPACK; i++)
        if (Player.pack[i] != NULL)
        {
            tpack[tctr++] = Player.pack[i];
        }

    for (i = 0; i < MAXPACK; i++)
    {
        Player.pack[i] = tpack[i];
    }

    Player.packptr = tctr;
}

/* show slots, with appropriate additional displays if two-handed weapons */
/* are involved */
void show_inventory_slot(int slotnum, int topline)
{
    if (!topline)
        if (Player.possessions[O_READY_HAND] == Player.possessions[O_WEAPON_HAND] &&
                (slotnum == O_READY_HAND || slotnum == O_WEAPON_HAND))
        {
            display_inventory_slot(O_READY_HAND, topline);
            display_inventory_slot(O_WEAPON_HAND, topline);
        }
        else if (slotnum == O_UP_IN_AIR && Player.possessions[O_UP_IN_AIR] &&
                 twohandedp(Player.possessions[O_UP_IN_AIR]->id))
        {
            display_inventory_slot(O_READY_HAND, topline);
            display_inventory_slot(O_WEAPON_HAND, topline);
            display_inventory_slot(slotnum, topline);
        }
        else
        {
            display_inventory_slot(slotnum, topline);
        }
    else
    {
        display_inventory_slot(slotnum, topline);
    }
}
