#include "random_events.h"
#include "glob.h"

void indoors_random_event(void)
{
    pml ml;
    pol ol;

    switch (random_range(1000))
    {
        case 0:
            print3("You feel an unexplainable elation.");
            morewait();
            break;

        case 1:
            print3("You hear a distant rumbling.");
            morewait();
            break;

        case 2:
            print3("You realize your fly is open.");
            morewait();
            break;

        case 3:
            print3("You have a sudden craving for a pecan twirl.");
            morewait();
            break;

        case 4:
            print3("A mysterious healing flux settles over the level.");
            morewait();

            for (ml = Level->mlist; ml != NULL; ml = ml->next)
                if (ml->m->hp > 0)
                {
                    ml->m->hp = Monsters[ml->m->id].hp;
                }

            Player.hp = max(Player.hp, Player.maxhp);
            break;

        case 5:
            print3("You discover an itch just where you can't scratch it.");
            morewait();
            break;

        case 6:
            print3("A cosmic ray strikes!");
            p_damage(10, UNSTOPPABLE, "a cosmic ray");
            morewait();
            break;

        case 7:
            print3("You catch your second wind....");
            Player.maxhp++;
            Player.hp = max(Player.hp, Player.maxhp);
            Player.mana = max(Player.mana, calcmana());
            morewait();
            break;

        case 8:
            print3("You find some spare change in a hidden pocket.");
            morewait();
            Player.cash += Player.level * Player.level + 1;
            break;

        case 9:
            print3("You feel strangely lucky.");
            morewait();
            break;

        case 10:
            print3("You trip over something hidden in a shadow...");
            morewait();
            ol = ((pol) checkmalloc(sizeof(oltype)));
            ol->thing = create_object(difficulty()); /* FIXED!  12/30/98 */
            assert(ol->thing); /* WDT I want to make sure... */
            ol->next = Level->site[Player.x][Player.y].things;
            Level->site[Player.x][Player.y].things = ol;
            pickup();
            break;

        case 11:
            print3("A mysterious voice echoes all around you....");
            morewait();
            hint();
            morewait();
            break;
#if 0
#ifdef NEW_BANK

        case 12:
        {
            int num_accounts;
            bank_account* account;
            num_accounts = 0;

            for (account = bank; account; account = account->next_account)
            {
                if (account->player && account->balance > 0)
                {
                    ++num_accounts;
                    account->balance = 0;
                }
            }

            if (num_accounts)
            {
                print3( "You feel unlucky." );
            }
            else
            {
                print3( "You feel lucky." );
            }
        }
        break;

        case 13:
        {
            int num_accounts;
            bank_account* account;
            num_accounts = 0;

            for (account = bank; account; account = account->next_account)
                if (account->player && account->balance > 0)
                {
                    ++num_accounts;
                }

            if (num_accounts)
            {
                num_accounts = random_range(num_accounts);

                for (account = bank; account; account = account->next_account)
                {
                    if (account->player)
                    {
                        if (0 == num_accounts)
                        {
                            account->balance += random_range( 4000 ) + 1000;
                            break;
                        }

                        --num_accounts;
                    }
                }

                print3( "You feel lucky." );
            }
            else
            {
                print3( "You feel unlucky." );
            }
        }
        break;
#else /* !NEW_BANK */

        case 12:
            if (Balance > 0)
            {
                print3("You get word of the failure of your bank!");
                Balance = 0;
            }
            else
            {
                print3("You feel lucky.");
            }

            break;

        case 13:
            if (Balance > 0)
            {
                print3("You get word of a bank error in your favor!");
                Balance += 5000;
            }
            else
            {
                print3("You feel unlucky.");
            }

            break;
#endif /* !NEW_BANK */
#endif /* 0 */
    }

    dataprint();
    showflags();
}

void outdoors_random_event(void)
{
    int num, i, j;
    pob ob;

    switch (random_range(300))
    {
        case 0:
            switch (Country[Player.x][Player.y].current_terrain_type)
            {
                case TUNDRA:
                    mprint("It begins to snow. Heavily.");
                    break;

                case DESERT:
                    mprint("A sandstorm swirls around you.");
                    break;

                default:
                    if ((Date > 75) && (Date < 330))
                    {
                        mprint("You are drenched by a sudden downpour!");
                    }
                    else
                    {
                        mprint("It begins to snow. Heavily.");
                    }
            }

            morewait();
            mprint("Due to the inclement weather conditions, you have become lost.");
            morewait();
            Precipitation += random_range(12) + 1;
            setgamestatus(LOST);
            break;

        case 1:
            mprint("You enter a field of brightly colored flowers...");
            mprint("Wow, man! These are some pretty poppies...");
            morewait();
            mprint("poppies...");
            morewait();
            mprint("poppies...");
            morewait();
            print3("You become somewhat disoriented...");
            setgamestatus(LOST);
            break;

        case 2:
            mprint("You discover a sprig of athelas growing lonely in the wild.");
            morewait();
            mprint("Using your herbalist lore you cook a cake of lembas....");
            morewait();
            ob = ((pob) checkmalloc(sizeof(objtype)));
            *ob = Objects[OB_LEMBAS];
            gain_item(ob);
            break;

        case 3:
            if (Precipitation > 0)
            {
                mprint("You are struck by a bolt of lightning!");
                p_damage(random_range(25), ELECTRICITY, "a lightning strike");
                morewait();
            }
            else
            {
                mprint("You feel static cling");
            }

            break;

        case 4:
            mprint("You find a fast-food establishment.");
            morewait();
            l_commandant();
            break;

        case 5:
            mprint("A weird howling tornado hits from out of the West!");
            morewait();
            mprint("You've been caught in a chaos storm!");
            morewait();
            num = random_range(300);

            if (num < 10)
            {
                mprint("Your cell-structure was disrupted!");
                p_damage(random_range(100), UNSTOPPABLE, "a chaos storm");
                morewait();
            }
            else if (num < 20)
            {
                mprint("The chaos storm warps your frame!");
                morewait();
                mprint("Your statistical entropy has been maximized.");
                morewait();
                mprint("You feel average...");
                morewait();
                toggle_item_use(TRUE); /* FIXED! 12/30/98 */
                Player.str = Player.maxstr = Player.con = Player.maxcon =
                                                 Player.dex = Player.maxdex = Player.agi = Player.maxagi =
                                                         Player.iq = Player.maxiq = Player.pow = Player.maxpow =
                                                                 ((Player.maxstr + Player.maxcon + Player.maxdex + Player.maxagi +
                                                                         Player.maxiq + Player.maxpow + 12) / 6);
                toggle_item_use(FALSE); /* FIXED! 12/30/98 */
            }
            else if (num < 30)
            {
                mprint("Your entire body glows with an eerie flickering light.");
                morewait();
                toggle_item_use(TRUE); /* FIXED! 12/30/98 */

                for (i = 1; i < MAXITEMS; i++)
                    if (Player.possessions[i] != NULL)
                    {
                        Player.possessions[i]->plus++;

                        if (Player.possessions[i]->objchar == STICK)
                        {
                            Player.possessions[i]->charge += 10;
                        }

                        Player.possessions[i]->blessing += 10;
                    }

                toggle_item_use(FALSE); /* FIXED! 12/30/98 */
                cleanse(1);
                mprint("You feel filled with energy!");
                morewait();
                Player.maxpow += 5;
                Player.pow += 5;
                Player.mana = Player.maxmana = calcmana() * 5;
                mprint("You also feel weaker. Paradoxical, no?");
                morewait();
                Player.con -= 5;
                Player.maxcon -= 5;

                if (Player.con < 3)
                {
                    p_death("congestive heart failure");
                }
            }
            else if (num < 40)
            {
                mprint("Your entire body glows black.");
                morewait();
                dispel(-1);
                dispel(-1);
                Player.pow -= 10;
                Player.mana = 0;
            }
            else if (num < 60)
            {
                mprint("The storm deposits you in a strange place....");
                morewait();
                setPlayerXY( random_range(COUNTRY_WIDTH), random_range(COUNTRY_LENGTH));
                screencheck(Player.x, Player.y);
            }
            else if (num < 70)
            {
                mprint("A tendril of the storm condenses and falls into your hands.");
                morewait();
                ob = ((pob) checkmalloc(sizeof(objtype)));
                make_artifact(ob, -1);
                gain_item(ob);
            }
            else if (num < 80)
            {
                if (gamestatusp(MOUNTED))
                {
                    mprint("Your horse screams as he is transformed into an");
                    morewait();
                    mprint("imaginary unseen dead tortoise.");
                    morewait();
                    mprint("You are now on foot.");
                    morewait();
                    resetgamestatus(MOUNTED);
                }
                else
                {
                    mprint("You notice you are riding a horse. Odd. Very odd....");
                    morewait();
                    mprint("Now that's a horse of a different color!");
                    morewait();
                    setgamestatus(MOUNTED);
                }
            }
            else if (num < 90)
            {
                mprint("You feel imbued with godlike power....");
                morewait();
                wish(1);
            }
            else if (num < 100)
            {
                mprint("The chaos storm has wiped your memory!");
                morewait();
                mprint("You feel extraordinarily naive....");
                morewait();
                mprint("You can't remember a thing! Not even your name.");
                morewait();
                Player.xp = 0;
                Player.level = 0;

                for (i = 0; i < NUMRANKS; i++)
                {
                    Player.rank[i] = 0;
                }

                for (i = 0; i < NUMSPELLS; i++)
                {
                    Spells[i].known = FALSE;
                }

                rename_player();
            }
            else
            {
                mprint("You survive the chaos storm relatively unscathed.");
                morewait();
                mprint("It was a learning experience.");
                morewait();
                gain_experience(1000);
            }

            break;

        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            mprint("An encounter!");
            morewait();
            change_environment(E_TACTICAL_MAP);
            break;

        case 11:
            mprint("You find a Traveller's Aid station with maps of the local area.");
            morewait();

            if (gamestatusp(LOST))
            {
                resetgamestatus(LOST);
                mprint("You know where you are now.");
            }

            for (i = Player.x - 5; i < Player.x + 6; i++)
                for (j = Player.y - 5; j < Player.y + 6; j++)
                    if (inbounds(i, j))
                    {
                        c_set(i, j, SEEN);

                        if (Country[i][j].current_terrain_type !=
                                Country[i][j].base_terrain_type)
                        {
                            c_set(i, j, CHANGED);
                            Country[i][j].current_terrain_type =
                                Country[i][j].base_terrain_type;
                        }
                    }

            show_screen();
            break;

        case 12:
            if (! gamestatusp(MOUNTED))
            {
                mprint("You develop blisters....");
                p_damage(1, UNSTOPPABLE, "blisters");
            }

            break;

        case 13:
            mprint("You discover an itch just where you can't scratch it.");
            break;

        case 14:
            mprint("A cosmic ray strikes!");
            morewait();
            p_damage(10, UNSTOPPABLE, "a cosmic ray");
            break;

        case 15:
            mprint("You feel strangely lucky.");
            break;

        case 16:
            mprint("The west wind carries with it a weird echoing voice....");
            /* DAG hint() uses mprint, which should morewait() if needed */
            /* morewait(); */
            hint();
            morewait();
            break;
    }

    dataprint();
    showflags();
}
