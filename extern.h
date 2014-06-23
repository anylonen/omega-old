/* omega copyright (c) 1987,1988,1989 by Laurence Raphael Brothers */
/* extern.h -- function declarations */

#include "newrand.h"
#include "stats.h"
#include "omega.h"
#include "abyss.h"
#include "aux1.h"
#include "aux2.h"
#include "aux3.h"
#include "bank.h"
#include "character.h"
#include "city.h"
#include "command1.h"
#include "command2.h"
#include "command3.h"
#include "country.h"
#include "effect1.h"
#include "effect2.h"
#include "effect3.h"
#include "env.h"
#include "etc.h"
#include "file.h"
#include "gen1.h"
#include "gen2.h"
#include "guild1.h"
#include "guild2.h"

/* house.c functions */

void load_house( int, int );
void make_house_npc( int, int );
void make_mansion_npc( int, int );

/* inv.c functions */

void do_inventory_control( void );
int  key_to_index( signed char );
signed char index_to_key( int );
long get_money( long );
char* cashstr( void );
char* itemid( pob );
int baditem( int );
int badobject( char );
int cursed( pob );
int find_and_remove_item( int, int );
int find_item( pob*, int, int );
int get_inventory_slot( void );
int get_item_number( pob );
int get_to_pack( pob );
int getitem( Symbol );
int getitem_prompt (char*, Symbol);
int item_useable( pob, int );
int objequal( struct object*, struct object* );
int slottable( pob, int );
int take_from_pack( int, int );
pob detach_money( long );
pob split_item( int, pob );
void add_to_pack( pob );
void conform_lost_object( pob );
void conform_lost_objects( int, pob );
void conform_unused_object( pob );
void dispose_lost_objects( int, pob );
void drop_at( int, int, pob );
void drop_from_slot( int );
void drop_money( void );
void fixpack( void );
void gain_item( pob );
void give_money( struct monster* );
void givemonster( struct monster*, struct object* );
void inventory_control( void );
void item_inventory( int );
void lose_all_items( void );
void merge_item( int );
void p_drop_at( int, int, int, pob );
void pack_extra_items( pob );
void pickup_at( int, int );
void put_to_pack( int );
void setchargestr( pob, char* );
void setnumstr( pob, char* );
void setplustr( pob, char* );
void show_inventory_slot( int, int );
void switch_to_slot( int );
void top_inventory_control( void );

/* item.c functions */

void shuffle( int [], int );
char* bootname( int );
char* cloakname( int );
char* grotname( void );
char* potionname( int );
char* ringname( int );
char* scrollname( int );
char* stickname( int );
int itemblessing( void );
int itemcharge( void );
int itemplus( void );
int twohandedp( int );
pob create_object( int );
void item_use( struct object* );
void make_armor( pob, int );
void make_artifact( pob, int );
void make_boots( pob, int );
void make_cash( pob, int );
void make_cloak( pob, int );
void make_corpse( pob, struct monster* );
void make_food( pob, int );
void make_potion( pob, int );
void make_ring( pob, int );
void make_scroll( pob, int );
void make_shield( pob, int );
void make_stick( pob, int );
void make_thing( pob, int );
void make_weapon( pob, int );

/* itemf1.c functions */

void i_accuracy( pob );
void i_acquire( pob );
void i_alert( pob );
void i_augment( pob );
void i_azoth( pob );
void i_bless( pob );
void i_breathing( pob );
void i_charge( pob );
void i_clairvoyance( pob );
void i_corpse( pob );
void i_cure( pob );
void i_deflect( pob );
void i_displace( pob );
void i_enchant( pob );
void i_fear_resist( pob );
void i_flux( pob );
void i_food( pob );
void i_heal( pob );
void i_hero( pob );
void i_id( pob );
void i_illuminate( pob );
void i_immune( pob );
void i_invisible( pob );
void i_jane_t( pob );
void i_key( pob );
void i_knowledge( pob );
void i_lembas( pob );
void i_levitate( pob );
void i_mondet( pob );
void i_neutralize_poison( pob );
void i_no_op( pob );
void i_nothing( pob );
void i_objdet( pob );
void i_pepper_food( pob );
void i_perm_accuracy( pob );
void i_perm_agility( pob );
void i_perm_displace( pob );
void i_perm_hero( pob );
void i_perm_illuminate( pob );
void i_perm_invisible( pob );
void i_perm_levitate( pob );
void i_perm_negimmune( pob );
void i_perm_protection( pob );
void i_perm_speed( pob );
void i_perm_truesight( pob );
void i_pick( pob );
void i_poison_food( pob );
void i_pow( pob );
void i_raise_portcullis( pob );
void i_regenerate( pob );
void i_restore( pob );
void i_sleep_self( pob );
void i_speed( pob );
void i_spells( pob );
void i_stim( pob );
void i_teleport( pob );
void i_trap( pob );
void i_truesight( pob );
void i_warp( pob );
void i_wish( pob );

/* itemf2.c functions */

void i_defend( pob );
void i_demonblade( pob );
void i_desecrate( pob );
void i_lightsabre( pob );
void i_mace_disrupt( pob );
void i_normal_armor( pob );
void i_normal_shield( pob );
void i_normal_weapon( pob );
void i_perm_breathing( pob );
void i_perm_burden( pob );
void i_perm_deflect( pob );
void i_perm_energy_resist( pob );
void i_perm_fear_resist( pob );
void i_perm_fire_resist( pob );
void i_perm_gaze_immune( pob );
void i_perm_knowledge( pob );
void i_perm_poison_resist( pob );
void i_perm_regenerate( pob );
void i_perm_strength( pob );
void i_victrix( pob );
void weapon_acidwhip( int, pob, struct monster* );
void weapon_arrow( int, pob, struct monster* );
void weapon_bare_hands( int, struct monster* );
void weapon_bolt( int, pob, struct monster* );
void weapon_defend( int, pob, struct monster* );
void weapon_demonblade( int, pob, struct monster* );
void weapon_desecrate( int, pob, struct monster* );
void weapon_firestar( int, pob, struct monster* );
void weapon_lightsabre( int, pob, struct monster* );
void weapon_mace_disrupt( int, pob, struct monster* );
void weapon_normal_hit( int, pob, struct monster* );
void weapon_scythe( int, pob, struct monster* );
void weapon_tangle( int, pob, struct monster* );
void weapon_victrix( int, pob, struct monster* );
void weapon_vorpal( int, pob, struct monster* );

/* itemf3.c functions */

int orbcheck( char );
void i_antioch( pob );
void i_apport( pob );
void i_crystal( pob );
void i_death( pob );
void i_disintegrate( pob );
void i_dispel( pob );
void i_disrupt( pob );
void i_enchantment( pob );
void i_fear( pob );
void i_fireball( pob );
void i_firebolt( pob );
void i_helm( pob );
void i_hide( pob );
void i_juggernaut( pob );
void i_kolwynia( pob );
void i_holding( pob );
void i_lball( pob );
void i_lbolt( pob );
void i_life( pob );
void i_missile( pob );
void i_orbair( pob );
void i_orbdead( pob );
void i_orbearth( pob );
void i_orbfire( pob );
void i_orbmastery( pob );
void i_orbwater( pob );
void i_planes( pob );
void i_polymorph( pob );
void i_sceptre( pob );
void i_sleep_other( pob );
void i_snowball( pob );
void i_stargem( pob );
void i_summon( pob );
void i_symbol( pob );
void i_serenity( pob );

/* lev.c functions */

int difficulty( void ); /* this function in util.c if MSDOS defined */
pmt m_create( int, int, int, int );
pmt make_creature( int );
void make_country_monsters( Symbol );
void make_site_monster( int, int, int );
void make_site_treasure( int, int, int );
void make_specific_treasure( int, int, int );
void populate_level( int );
void stock_level( void );
void wandercheck( void );

/* map.c functions */
map* map_open(enum map_identifier);
void map_setLevel(map*, int);
int map_getWidth(map*);
int map_getLength(map*);
int map_getDepth(map*);
char map_getSiteChar(map*, int, int);
void map_close(map*);

/* mmelee.c functions */

char random_loc( void );
int monster_hit( struct monster*, char, int );
void m_hit( struct monster*, int );
void monster_melee( struct monster*, char, int );
void tacmonster( struct monster* );
void transcribe_monster_actions( struct monster* );

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

/* mon.c functions */

char* mancorpse( void );
char* angeltype( int, int );
void determine_npc_behavior( pmt, int, int );
void m_abyss( struct monster* );
void m_altar( struct monster* );
void m_damage( struct monster*, int, int );
void m_remove( struct monster* );
void m_death( struct monster* );
void m_dropstuff( struct monster* );
void m_fire( struct monster* );
void m_lava( struct monster* );
void m_no_op( struct monster* );
void m_pickup( struct monster*, struct object* );
void m_pulse( struct monster* );
void m_trap_abyss( struct monster* );
void m_trap_acid( struct monster* );
void m_trap_blade( struct monster* );
void m_trap_dart( struct monster* );
void m_trap_disintegrate( struct monster* );
void m_trap_door( struct monster* );
void m_trap_fire( struct monster* );
void m_trap_manadrain( struct monster* );
void m_trap_pit( struct monster* );
void m_trap_sleepgas( struct monster* );
void m_trap_snare( struct monster* );
void m_trap_teleport( struct monster* );
void m_water( struct monster* );
void make_hiscore_npc( pmt, int );
void make_log_npc( struct monster* );
void monster_action( struct monster*, int );
void monster_move( struct monster* );
void monster_special( struct monster* );
void monster_strike( struct monster* );
void monster_talk( struct monster* );
void movemonster( struct monster*, int, int );
void strengthen_death( struct monster* );

/* move.c functions */

void l_abyss( void );
void l_air_station( void );
void l_arena_exit( void );
void l_balancestone( void );
void l_chaos( void );
void l_chaostone( void );
void l_circle_library( void );
void l_drop_every_portcullis( void );
void l_earth_station( void );
void l_enter_circle( void );
void l_enter_court( void );
void l_escalator( void );
void l_fire( void );
void l_fire_station( void );
void l_hedge( void );
void l_house_exit( void );
void l_lava( void );
void l_lawstone( void );
void l_lift( void );
void l_magic_pool( void );
void l_mindstone( void );
void l_no_op( void );
void l_portcullis_trap( void );
void l_raise_portcullis( void );
void l_rubble( void );
void l_sacrificestone( void );
void l_tactical_exit( void );
void l_temple_warning( void );
void l_throne( void );
void l_tome1( void );
void l_tome2( void );
void l_voice1( void );
void l_voice2( void );
void l_voice3( void );
void l_void( void );
void l_void_station( void );
void l_voidstone( void );
void l_water( void );
void l_water_station( void );
void l_whirlwind( void );
void stationcheck( void );

/* movef.c functions */

void m_movefunction( struct monster*, int );
void p_movefunction( int );
void sign_print( int, int, int ); /* this function in site1.c if MSDOS defined */

/* mspec.c functions */

void m_aggravate( struct monster* );
void m_huge_sounds( struct monster* );
void m_illusion( struct monster* );
void m_sp_acid_cloud( struct monster* );
void m_sp_angel( struct monster* );
void m_sp_av( struct monster* );
void m_sp_blackout( struct monster* );
void m_sp_bogthing( struct monster* );
void m_sp_court( struct monster* );
void m_sp_demon( struct monster* );
void m_sp_demonlover( struct monster* );
void m_sp_dragonlord( struct monster* );
void m_sp_eater( struct monster* );
void m_sp_escape( struct monster* );
void m_sp_explode( struct monster* );
void m_sp_ghost( struct monster* );
void m_sp_lair( struct monster* );
void m_sp_lw( struct monster* );
void m_sp_mb( struct monster* );
void m_sp_merchant( struct monster* );
void m_sp_mirror( struct monster* );
void m_sp_mp( struct monster* );
void m_sp_ng( struct monster* );
void m_sp_poison_cloud( struct monster* );
void m_sp_prime( struct monster* );
void m_sp_raise( struct monster* );
void m_sp_seductor( struct monster* );
void m_sp_servant( struct monster* );
void m_sp_spell( struct monster* );
void m_sp_surprise( struct monster* );
void m_sp_swarm( struct monster* );
void m_sp_were( struct monster* );
void m_sp_whistleblower( struct monster* );
void m_summon( struct monster* );
void m_thief_f( struct monster* );

/* mstrike.c functions */

void m_blind_strike( struct monster* );
void m_fireball( struct monster* );
void m_firebolt( struct monster* );
void m_lball( struct monster* );
void m_nbolt( struct monster* );
void m_snowball( struct monster* );
void m_strike_sonic( struct monster* );

/* mtalk.c functions */

void m_talk_animal( struct monster* );
void m_talk_archmage( struct monster* );
void m_talk_assassin( struct monster* );
void m_talk_beg( struct monster* );
void m_talk_burble( struct monster* );
void m_talk_demonlover( struct monster* );
void m_talk_druid( struct monster* );
void m_talk_ef( struct monster* );
void m_talk_evil( struct monster* );
void m_talk_gf( struct monster* );
void m_talk_greedy( struct monster* );
void m_talk_guard( struct monster* );
void m_talk_hint( struct monster* );
void m_talk_horse( struct monster* );
void m_talk_hungry( struct monster* );
void m_talk_hyena( struct monster* );
void m_talk_im( struct monster* );
void m_talk_man( struct monster* );
void m_talk_merchant( struct monster* );
void m_talk_mimsy( struct monster* );
void m_talk_mp( struct monster* );
void m_talk_ninja( struct monster* );
void m_talk_parrot( struct monster* );
void m_talk_prime( struct monster* );
void m_talk_robot( struct monster* );
void m_talk_scream( struct monster* );
void m_talk_seductor( struct monster* );
void m_talk_servant( struct monster* );
void m_talk_silent( struct monster* );
void m_talk_slithy( struct monster* );
void m_talk_stupid( struct monster* );
void m_talk_thief( struct monster* );
void m_talk_titter( struct monster* );
void m_talk_maharaja( struct monster* );

/* priest.c functions */

int check_sacrilege( int );
void answer_prayer( void );
void hp_req_print( void );
void hp_req_test( void );
int increase_priest_rank( int );
void l_altar( void );
void make_hp( pob );

/* save.c functions */

int ok_outdated( int );
int restore_game( char* );
void restore_hiscore_npc( pmt, int );
pob restore_item( FILE*, int );
pol restore_itemlist( FILE*, int );
void restore_country( FILE*, int );
void restore_level( FILE*, int );
void restore_monsters( FILE*, plv, int );
void restore_player( FILE*, int );
int save_game( int, char* );
int save_country( FILE* );
int save_item( FILE*, pob );
int save_itemlist( FILE*, pol );
int save_level( FILE*, plv );
int save_monsters( FILE*, pml );
int save_player( FILE* );

/* scr.c functions */

void omega_title( void );
int mcigetc( void );
long parsenum( char* message );
char* msgscanstring( void );
Symbol getspot( int, int, int );
char lgetc( void );
char menugetc( void );
char mgetc( void );
void cinema_hide (void);
void cinema_blank (void);
void cinema_print_line (int line, char* text);
int cinema_interact_line (int line, char* choices, char* text);
int cinema_ynq_line (int line, char* prompt);
int cinema_getnum_line (int line, char* prompt);
int cinema_confirm(char* action_description);
int cinema_ynq(char* action_description);
int cinema_interact(char* choices, char* line1, char* line2, char* line3);
void cinema_scene(char* line1, char* line2, char* line3);
int ynq( void );
int ynq1( void );
int ynq2( void );
int getnumber( int );
int litroom( int, int );
int move_slot( int, int, int );
int stillonblock( void );
void blankoutspot( int, int );
void blotspot( int, int );
void buffercycle( char* );
int bufferappend( char* );
void bufferprint( void );
void checkclear( void );
void clear_if_necessary( void );
void clear_screen( void );
void clearmsg( void );
void clearmsg1( void );
void clearmsg3( void );
void colour_on( void );
void colour_off( void );
void commanderror( void );
void comwinprint( void );
void dataprint( void );
void deathprint( void );
void display_bigwin( void );
void display_death( char* );
void display_inventory_slot( int, int );
void display_option_slot( int );
void display_options( void );
void display_pack( void );
void display_possessions( void );
void display_quit( void );
void display_win( void );
void dobackspace( void );
void dodrawspot( int, int );
void draw_explosion( Symbol, int, int );
void drawmonsters( int );
void drawomega( void );
void drawplayer( void );
void drawscreen( void );
void drawspot( int, int );
void drawvision( int, int );
void endgraf( void );
void erase_level( void );
void erase_monster( struct monster* );
void hide_line( int );
void initgraf( void );
void levelrefresh( void );
void lightspot( int, int );
void locprint( char* );
void maddch( char );
void menuaddch( char );
void menuclear( void );
void menulongprint( long );
void menunumprint( int );
void menuprint( char* );
void menuspellprint( int );
void showmenu( void );
void mlongprint( long );
void mnumprint( int );
void morewait( void );
void mprint( char* );
void nprint1( char* );
void nprint2( char* );
void nprint3( char* );
void phaseprint( void );
void bank_init( void );
void plotchar( Symbol, int, int );
void plotmon( struct monster* );
void plotspot( int, int, int );
void print1( char* );
void print2( char* );
void print3( char* );
void putspot( int, int, Symbol );
void redraw( void );
void screencheck( int, int );
void setlastxy( int, int );
void show_screen( void );
void omshowcursor( int, int );
void showflags( void );
void spreadroomdark( int, int, int );
void spreadroomlight( int, int, int );
void timeprint( void );
void xredraw( void );

/* site1.c functions */

void buyfromstock( int, int );
void l_alchemist( void );
void l_armorer( void );
void l_casino( void );
void l_club( void );
void l_commandant( void );
void l_crap( void );
void l_diner( void );
void l_dpw( void );
void l_gym( void );
void l_healer( void );
void l_library( void );
void l_pawn_shop( void );
void l_statue_wake( void );
void l_tavern( void );
void statue_random( int, int );
void wake_statue( int, int, int );

/* site2.c functions */

void cureforpay( void );
void gymtrain( int*, int* );
void healforpay( void );
void l_adept( void );
void l_brothel( void );
void l_cartographer( void );
void l_charity( void );
void l_condo( void );
void l_countryside( void );
void l_house( void );
void l_hovel( void );
void l_mansion( void );
void l_oracle( void );
void l_safe( void );
void l_trifid( void );
void l_vault( void );
void pacify_guards( void );
void send_to_jail( void );
void l_tourist( void );

/* spell.c functions */

char* spellid( int );
int getspell( void );
int spellparse( void );
void cast_spell( int );
void initspells( void );
void s_accuracy( void );
void s_alert( void );
void s_apport( void );
void s_bless( void );
void s_breathe( void );
void s_clairvoyance( void );
void s_cure( void );
void s_desecrate( void );
void s_disintegrate( void );
void s_dispel( void );
void s_disrupt( void );
void s_drain( void );
void s_enchant( void );
void s_fear( void );
void s_firebolt( void );
void s_haste( void );
void s_heal( void );
void s_hellfire( void );
void s_hero( void );
void s_identify( void );
void s_invisible( void );
void s_knowledge( void );
void s_lball( void );
void s_levitate( void );
void s_missile( void );
void s_mondet( void );
void s_objdet( void );
void s_polymorph( void );
void s_regenerate( void );
void s_restore( void );
void s_return( void );
void s_ritual( void );
void s_sanctify( void );
void s_sanctuary( void );
void s_shadowform( void );
void s_sleep( void );
void s_summon( void );
void s_teleport( void );
void s_truesight( void );
void s_warp( void );
void s_wish( void );
void showknownspells( int, int );

/* time.c functions */

void fix_phantom( struct monster* );
void time_clock( int );

/* trap.c functions */

void l_trap_abyss( void );
void l_trap_acid( void );
void l_trap_blade( void );
void l_trap_dart( void );
void l_trap_disintegrate( void );
void l_trap_door( void );
void l_trap_fire( void );
void l_trap_manadrain( void );
void l_trap_pit( void );
void l_trap_siren( void );
void l_trap_sleepgas( void );
void l_trap_snare( void );
void l_trap_teleport( void );

/* util.c functions */

void setPlayerXY( int, int );
long calc_points( void );
char* getarticle( char* );
char* month( void );
char* ordinal( int );
char* salloc( char* );
char inversedir( int );
void init_perms( void );
int confirmation( void );
char cryptkey( char* );
int day( void );
int distance( int, int, int, int );
int hitp( int, int );
int hour( void );
int inbounds( int, int );
int los_p( int, int, int, int );
int m_unblocked( struct monster*, int, int );
int nighttime( void );
int offscreen( int, int );
int ok_to_free( plv );
void free_level( plv );
void free_mons_and_objs( pml );
void free_obj( pob, int );
pob copy_obj( pob );
void free_objlist( pol );
void* checkmalloc( unsigned int );
unsigned random_range( unsigned int );
int screenmody( int );
int screenmodx( int );
int showhour( void );
int showminute( void );
int strmem( char, char* );
char* strjoin(char*, char*);

/* pdump.c functions */

void player_dump( void );
int strprefix( char*, char* );
int unblocked( int, int );
int view_los_p( int, int, int, int );
int view_unblocked( int, int );
void calc_weight( void );
void change_to_game_perms( void );
void change_to_user_perms( void );
void do_los( Symbol, int*, int*, int, int );
void do_object_los (Symbol, int*, int*, int, int);
void findspace( int*, int*, int );
int try_findspace( int*, int*, int );
void initdirs( void );
#ifdef NO_USLEEP
void usleep( int );
#endif

/* village.c functions */

void assign_village_function( int, int, int );
void load_village( int, int );
void make_food_bin( int, int );
void make_guard( int, int );
void make_horse( int, int );
void make_merchant( int, int );
void make_sheep( int, int );
void special_village_site( int, int, int );
