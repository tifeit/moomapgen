#ifndef STRUCT_H_
#define STRUCT_H_

#ifdef __GNUC__
	#define STRUCT_TYPE struct
	#define STRUCT_TYPE_END __attribute__((__packed__));
#else
	#define STRUCT_TYPE _Packed struct
	#define STRUCT_TYPE_END ;
#endif

#include <stdbool.h>
typedef unsigned char uchar;
typedef char schar;
typedef unsigned int uint;
typedef signed int sint;

//Save Data
#define MAX_POPS        42
#define MAX_PLAYERS      8
#define MAX_LEADERS     67
#define MAX_RACES       14
#define N_POP_PLAYERS (MAX_PLAYERS+2)
#define N_POP_RACES (MAX_RACES+2)
#define MAX_BUILDINGS           49
#define MAX_SYSTEMS 72
#define MAX_PLANETS 360
#define MAX_PLAYERS 8
#define MAX_SHIPS 500
#define MAX_COLONIES 250
#define  MAX_TECH_FIELDS                83
#define  MAX_TECH_APPLICATIONS         212
#define STAR_OFFSET 0x17ad3
#define PLANET_OFFSET 0x162e9
#define SHIP_OFFSET 0x21F58
#define COLONY_OFFSET   0x25D
#define PLAYER_OFFSET 0x1aa0e
#define LEADER_OFFSET 0x19a9b

#define NUM_OF_STARS_OFFSET 0x17ad1
#define NUM_OF_PLANETS_OFFSET 0x162e7
#define NUM_OF_PLAYERS_OFFSET 0x1aa0c

//Specials
#define NO_SPECIAL                       0
#define STABLE_WORMHOLE                  1
#define SPACE_DEBRIS                     2
#define PIRATE_CACHE                     3
#define GOLD_DEPOSITS                    4
#define GEM_DEPOSITS                     5
#define NATIVES                          6
#define SPLINTER_COLONY                  7
#define MAROONED_HERO                    8
#define SPACE_MONSTER                    9
#define ANCIENT_ARTIFACTS                10
#define ORION_STAR_SYSTEM_SPECIAL        11
#define MAX_SYSTEM_AND_PLANET_SPECIALS   12
#define MAX_PLANET_SPECIALS              (MAX_SYSTEM_AND_PLANET_SPECIALS)

//Terraforming flags
#define FLG_NOTOXIC		1
#define FLG_NOUPOOR		2
#define FLG_NOLG		4
#define FLG_NOHG		8
#define FLG_NOTINY		16
#define	FLG_NOSMALL		32

#define FLG_CALC		1
#define FLG_RING		2

//Homeworld flags
#define FLG_FLATHW		1
#define FLG_FIXEDHW		2
#define FLG_GAIA		4
#define FLG_RICHHW		8
#define FLG_HUGEHW		16
#define FLG_GOODHW		32

//Splinter flags
#define FLG_SPLINT		1
#define FLG_ARTI		2
#define FLG_NONATIVES	4
#define FLG_HERO		8

//Monster flags
#define FLG_GRAV		1
#define FLG_TERRAFORM	2

//Mineral richness
#define ULTRA_POOR            0
#define POOR                  1
#define ABUNDANT              2
#define RICH                  3
#define ULTRA_RICH            4
#define MAX_MINERAL_CLASSES   5

//Enviromental class
#define TOXIC         0
#define RADIATED      1
#define BARREN        2
#define DESERT        3
#define TUNDRA        4
#define OCEAN         5
#define SWAMP         6
#define ARID          7
#define TERRAN        8
#define GAIA          9

//Gravity
#define LOW_G                 0
#define NORMAL_G              1
#define HEAVY_G               2
#define MAX_PLANET_GRAVITIES  3

//Size
#define TINY	0
#define	SMALL	1
#define	MEDIUM	2
#define	LARGE	3
#define HUGEPLANET	4

//Leader status
#define OFFICER_DEAD            (-2)
#define OFFICER_NOT_IN_USE      (-1)  //an unassigned mercenary
#define OFFICER_IN_POOL          0
#define OFFICER_ASSIGNED         1
#define OFFICER_UNASSIGNED       2      //in limbo between pool and ship
#define OFFICER_BEING_CLONED     3      //not used
#define OFFICER_WAITING          4      //in queue, not in pool or assigned...no maintenance
#define OFFICER_MAROONED         5      //assigned to a planet , or, in the case of SHIP heroes, just not assigned.

STRUCT_TYPE star {

	char sName[15];									//Star System Name										00-0E	15	bytes
	unsigned short int nXpos;						//X Position											0F-10	2	bytes
	unsigned short int nYpos;						//Y Position											11-12 	2	bytes
	unsigned char nSize;							//Star Size 0=Large 3=Tiny								13		1	byte
	unsigned char nOwner;							//System Primary Owner 0-7 player (PlayerID)			14		1	byte
	unsigned char nPicture;						//Picture												15		1	byte
	unsigned char nStarType;						//Star Type												16		1	bytes
	unsigned char nLastPlayerSelected[MAX_PLAYERS];	//bookeeping											17-27	8	bytes
	unsigned char aBHBlocks[(MAX_SYSTEMS + 7)/8];	//If bit is set there is a hole between stars					9	bytes
	unsigned char nSpecial;							//SystemSpecial													1	byte
	unsigned char nWormSystem;						//0-127 Wormhole leads to "system" FF - no wormhole				1	byte
	unsigned char nBlocaded;						//Is star blocaded												1	byte
	unsigned char bvBlockadedBy[MAX_PLAYERS];		//Bit vector tells who blockade system							1	byte
	char nVisited;                   // bitvector tells whether each player has ever visited							1
	char nJustVisited;              // bitvector tells whether each player 1st visited on prev turn					1
	char bvIgnoreColonyShips; // bitvector tells if each player requested ignore colony ships						1
	                             // reset each time a new colony ship enters star
	char bvIgnoreCombatShips; // bitvector tells if each player requested ignore combat ships
	                             // (the much requested "don't make me hit Only Blockade" feature)
	                             // reset each time a new combat ship enters star
	unsigned char nStarOwner;			// 0..7 or -1																1
	unsigned char bvPlayerHasColony;          // bitvector tells whether each player has a colony					1
	unsigned char nWarpIdict;		//Warp Interdictor 0 none, 1-8 owner (PlayerID-1)						39		1	byte
	char next_wfi_in_list;           // bookeeping
	char bvHasTachion;                // bitvector tells whether each player has a tachyon
	char bvHasSubspace;               // bitvector tells whether each player has a subspace
	char bvHasStarGate;               // bitvector tells whether each player has a stargate
	char bvHasJumpgate;               // bitvector tells whether each player has a jumpgate
	unsigned char nArtemisNet;		//Artemis Systemr 0 none, 1-8 owner (PlayerID-1)	3F		1	byte
	char bvStagepoint;              // bitvector tells whether star is stagepoint for each AI
	char has_dimensional_portal;     // bitvector
	char aOfficerIndex[MAX_PLAYERS]; //officers are now at stars and not colonies
	unsigned short int aPlanet[5];	//Link to planets table								4A-53 10	bytes
	unsigned short int relocate_ship_to[MAX_PLAYERS]; //star index all ships will be relocated TO
	char not_used1;                     //
	char not_used2;                     //
	char not_used3;                     //
	char aSurrenderTo[MAX_PLAYERS];    // normally -1, else player to give colonies to
	char bNebula;	                    // is this star in a nebula?
	char bArtifactsGaveApp;           // has the ancient artifacts app been given out yet?
} STRUCT_TYPE_END

STRUCT_TYPE planet {

	unsigned short int nColonyID;	//Link to colonies table
	unsigned char nStarID;			//Link to stars table
	unsigned char nOrbit;			//Orbit 0-4
	unsigned char nPlanetType;		//Planet type 1=Asteroid 2=Gas Planet 3=Planet
	unsigned char nPlanetSize;		//Planet size 0=Tiny 1=Small 2=Medium 3=Large 4=Huge
	unsigned char nPlanetGravity;	//Planet gravity 0=Low Gravity 1=Normal 2=Heavy Gravity
	unsigned char nGroup;			//Not used
	unsigned char nEnvClass;		//Enviromental class 0=Toxic 1=Radiated 2=Barren 3=Desert 4=Tundra
									//5=Ocean 6=Swamp 7=Arid 8=Terr 9=Gaia
	unsigned char nDrawingID;		//0-5 image in planets.lbx
									//@todo Find and insert correlation between image and planet environment
	unsigned char nMineralClass;	//Planet Mineral Class 0=upoor 1=poor 2=abundant 3=rich 4=ultrarich
	unsigned char nFoodBase;		//@todo Find out how foodbase correlates with enviromental class
	unsigned char nTerraformsDone;	//Number of terraforming done
	unsigned char nMaxFarms;		//Unknown 2=Tiny 4=Small 5=Medium 7=Large A=Huge
	unsigned char nMaxPopulation;
	unsigned char nPlanetSpecial;	//0=None 1=? 2=Space Debris 3=Pirate Cache 4=Gold Deposits 5=Gem Deposits
									//6=Natives 7=Splinter Colony 8=Hero A=Artifacts world B=Orion
	unsigned char nFlags;			//2=Soil Enrichment
} STRUCT_TYPE_END

STRUCT_TYPE Pop_Info {
           unsigned short player:4;           // player id or POP_ANDROID or POP_NATIVE
           unsigned short loyalty:3;          // player id
           unsigned short job:2;              // 0-farmer, 1-worker, 2-scientist
           unsigned short employed:1;
           unsigned short conquered:1;        // true iff loyalty != colony owner
} STRUCT_TYPE_END

STRUCT_TYPE s_leader_data {
        char            name[15];
        char            title[20];
        char            type;           //0-ship 1-colony
        short int       xp;
        unsigned int    general_skills; //bitvector for general skills
        unsigned int    special_skills; //bitvector includes either ship || colony skills
        unsigned char   tech_application[3];    // Application id's of inherent techs
        char            pict_num;

        short int  skill_value;             //
        char       level;                   //
        short int  location;                //
        char       eta;                     //
        char       display_level_popup;     //if TRUE, draw officer-made-level popup
        char       status;                  //
        char       player_index;            //
} STRUCT_TYPE_END

STRUCT_TYPE s_colony {

   char       owner;                         // 0..NUM_PLAYERS or -1                                  //1
   char       allocated_to;                  // bookeeping                                            //2
   short int  planet;                        // planet id                                             //4
   short int  officer;                       // not used                                              //6

   char  outpost_flag;                   // TRUE if an outpost                                        //7

   char  morale;                       // morale bonus +/-                                            //8
   short int  pollution;                     // production lost to pollution                          //10

   char  n_pops;                       // total population                                            //11
   char  specialty;                    // Colony specialty used in display only                       //12

   //   struct Pop_Info {
   //           unsigned player:4;           // player id or POP_ANDROID or POP_NATIVE
   //           unsigned loyalty:3;          // player id
   //           unsigned job:2;              // 0-farmer, 1-worker, 2-scientist
   //           unsigned employed:1;
   //           unsigned conquered:1;        // true iff loyalty != colony owner
   //   };

   struct Pop_Info pop[MAX_POPS];       //                                                            //

   short int   pop_roundoff[N_POP_PLAYERS];  // K toward next pop unit for each race
   short int   pop_growth[N_POP_PLAYERS];    // each race grows independently

   char  n_turns_existed;               // bookeeping
   char  food2_per_farmer;              // Food per farmer in half-units of food
   char  industry_per_worker;
   unsigned char  research_per_scientist;
   char  max_farms;                     //
   char  max_population;
   char  climate;

   short int   ground_strength;         // calculated for ai
   short int   space_strength;          // calculated for ai

   short int   total_production[3];     // gross amount produced  0-food, 1-industry, 2-research
   char  maintenance[3];                // how much is spent feeding people/androids 0-food, 1-industry, 2-research

   short int   imports[3];              // + means importing, - means surplus
                                        // (surplus exported only if unblockaded)

   char n_industry_recyclers;           // for recycling pollution reduction

   // for parcelling out food/metal in priority ordering:
   // counted in half units due to cybernetic woes.
   char food2_needed_for_our_empire;                   //-------------------------------
   char food2_needed_for_assimilated;                  //
   char food2_needed_for_conquered;                    //
   char food2_needed_for_natives;                      //these are all bookeeping entries
   char industry2_needed_for_our_empire;               //
   char industry2_needed_for_androids;                 //
   char industry2_needed_for_assimilated;              //
   char industry2_needed_for_conquered;                //
   char food2_needed_for_empire[MAX_PLAYERS];          //
   char industry2_needed_for_empire[MAX_PLAYERS];      //
   char n_food_replicated;                             //

   short int  producing[7];                            // building queue
   short int  just_produced;                           // if not -1, then colony completed this product last turn
   short int  production_spent;
   short int  n_industry_taxed;
   char       auto_building;
   short int  production_surplus;                      // for when production is changed
   short int  bought_outright;                         // amount of production bought
                                                       //---------------------------

   char occupation_points;                             // 240 points to assimilate 1 pop.
   char occupation_policy;                             // 0-genocide , 3-normal

   // military
   short int military[2];                              // 0-infantry, 1-tanks
   char tank_roundoff;
   char infantry_roundoff;

   char buildings[MAX_BUILDINGS];
   unsigned short int last_turn_building_destroyed;
	
	char filler[89];
} STRUCT_TYPE_END

STRUCT_TYPE planetInfo {

	struct star *aStars;
	struct planet *aPlanets;
	unsigned char *nNumOfPlayers, *nNumOfStars;
	unsigned short *nNumOfPlanets;
	unsigned int *aHwCoordinates;
} STRUCT_TYPE_END

#define MAX_SPECIALS 36
#define MAX_SHIP_WEAPONS 8

STRUCT_TYPE s_ship_weapons {
   short int  type;
   char       count;
   char       current_count;      // damaged if < count
   char       firing_arc;         // 1-F, 2-FX, 4-Bx, 8-B, 16-360
   short int  specials;           // bit vector
   char       ammo;               // valid for missiles only
} STRUCT_TYPE_END

STRUCT_TYPE s_ship_design {

   char  name[16];
   char  size;
   char  ship_type;
   char  shield_type;
   char  ftl_type;
   char  speed;
   char  computer_type;
   char  armor_type;
   char  special_device_flags[(MAX_SPECIALS+7)/8];
   struct s_ship_weapons ship_weapon[MAX_SHIP_WEAPONS];
   char  picture_num;
   char  previous_owner;
   short int  cost;
   unsigned char combat_speed;
   unsigned short int  date_of_design;

} STRUCT_TYPE_END

//Ship structure
STRUCT_TYPE ship {

   struct s_ship_design d;
   char       owner;
   char       status;
   short int  location;
   short int  x;
   short int  y;
   char       group_has_navigator; // does the moving group have navigator?
   char       travelling_speed;    // possibly less than ftl_type
   char       turns_left;          // until arrival

   char       shield_damage_percent;
   char       drive_damage_percent;
   char       computer_damage;


   char       crew_quality;
   short int  crew_experience;
   short int  officer_index;
   char       special_device_damage_flags[5];  //bit vector Set if Special is damaged
   short int  armor_damage;
   short int  structural_damage;
   char       mission;                  // AI Field
   char       just_built;

} STRUCT_TYPE_END

enum {
   maintenance_building,
   maintenance_freighter,
   maintenance_ship,
   maintenance_spy,
   maintenance_tribute,
   maintenance_leader,
   n_maintenance_classes
};

STRUCT_TYPE Settler_Info {
      unsigned source_colony:8; // colony id or MAX_COLONIES if already in space (cannot be redirected)
      unsigned dest_planet:8;   // planet id
      unsigned player:4;        // player id or POP_ANDROID or POP_NATIVE
      unsigned eta:4;           // if settler, takes this many turns to arrive
      unsigned job:2;
} STRUCT_TYPE_END

STRUCT_TYPE s_player
 {
   char  picture;
   char  name[20];
   char  race_name[15];
   char  eliminated;
   char  race;
   char  color;
   char  personality;
   char  objectives;
   short int home_planet_id;

   short int network_player_id;         //bookeeping
   char  player_done_flags;             //bookeeping

   unsigned short int  dead_field;
   char  research_breakthrough;         // did they complete a field this turn?

   char  tax_rate;                      // taxes are 0,10,20,30,40,50% of industry production
   int   bc;                            // our current amount of cash

   short int  n_freighters;
   short int  surplus_freighters;       //bookeeping

   short int command_points;
   short int command_points_used;

   // sum of following 3 should be <= n_freighters * FREIGHTER_CAPACITY
   short int  food_freighted;
   short int  settlers_freighted;       // # settlers enroute, stored in settlers array:

//        struct Settler_Info {
//              unsigned source_colony:8; // colony id or MAX_COLONIES if already in space (cannot be redirected)
//              unsigned dest_planet:8;   // planet id
//              unsigned player:4;        // player id or POP_ANDROID or POP_NATIVE
//              unsigned eta:4;           // if settler, takes this many turns to arrive
//              unsigned job:2;
//        };


   struct Settler_Info settlers[25]; // slots < settlers_freighted are current settlers

   short int  total_pop;                  // of all our colonies

   // total amounts produced by all colonies this turn:
   short int  food_produced;
   short int  industry_produced;
   short int  research_produced;
   short int  bc_produced;

   // following are >0 if we had extra, <0 if we were short, this turn:
   short int  surplus_food; // only accounting for unblockaded colonies
   short int  surplus_bc;

   // maintenance bc costs:
   int total_maintenance;
   short int maintenance[n_maintenance_classes]; // sum == total_maintenance

   char  tech_fields[MAX_TECH_FIELDS];              // 0-UNRESEARCHABLE, 1-NOT_KNOWN, 2-ON_RESEARCH_LIST, 3-KNOWN
   char  tech_applications[MAX_TECH_APPLICATIONS];  // 0-UNRESEARCHABLE, 1-NOT_KNOWN, 2-ON_RESEARCH_LIST, 3-KNOWN

   int   research_accumulated; //Correct
   char  captured_orion;
   char  captured_antares;
   char  won_council_vote;
   int   player_defeated[MAX_PLAYERS]; //stardate or 0
   unsigned short int captured_population;
   char  last_attacker;

   char  ship_design_theme;      //AI FIELDS
   char  ship_special_theme;     //AI FIELDS
   char  tech_apps_learned[4];   //bookeeping
   //char  tech_modifiers[17];     //not in use

   char hyper_advanced_tech[8];  // LEVEL of hyper advanced tech achieved.

   int total_known_tech_cost;    // for history display

   //char knows_racial_stats;      //not used

   int last_tech_report_date[MAX_PLAYERS];  //not used

   // bitfields, tell whether given player knows the app:
   //uchar player_tech_applications[MAX_PLAYERS][(MAX_TECH_APPLICATIONS + 7) / 8];
   uchar player_tech_applications[MAX_PLAYERS][27];


   char  current_research_field;        // should be > 0, indicating which field
   char  current_research_application;  //
   char  got_new_app;                   // within the last turn; causes AI to redecide field to research

   int   ship_range;

   struct s_ship_design  ship_designs[6]; //Correct
   short int  ships_built[6];

   char  contact[MAX_PLAYERS];
   char just_established_contact;       // bitvector by player index
   char n_times_established_contact[MAX_PLAYERS];
   char  within_range[MAX_PLAYERS];     // tells if this player can reach that player
                                        // (contact is symmetric, within_range is not)

   char do_not_research;        // should the AI quit researching from now on?

   schar offensive_stagepoint;  //AI FIELD

   uchar best_ftl_drive;
   uchar ship_speed;

   char officer_for_hire;       // -1 or id of available officer this turn

   short int n_trade_pops;
   short int current_trade_agreement_level[MAX_PLAYERS];
   short int trade_agreement_goal[MAX_PLAYERS];

   short int n_research_pops;
   short int current_research_agreement_level[MAX_PLAYERS];
   short int research_agreement_goal[MAX_PLAYERS];

   char fighter_beam_type;
   char fighter_bomb_type;


   short int  total_research;                           //AI Field
   short int  total_ships;                              //AI Field
   unsigned long int total_ship_strength[MAX_PLAYERS];  //AI Field
   short int  total_colonies;                           //AI Field
   char  failed_to_expand;                              //AI Field


//diplomacy stuff
   char  first_contact[MAX_PLAYERS];
   char  relations[MAX_PLAYERS];
   char  base_relations[MAX_PLAYERS];

   char  treaty[MAX_PLAYERS];
   char  trade_treaty[MAX_PLAYERS];
   char  research_treaty[MAX_PLAYERS];
   short int  tribute_treaty[MAX_PLAYERS];

   char  diplomacy_incident[MAX_PLAYERS];
   char  diplomacy_message[MAX_PLAYERS];
   short int  diplomacy_severity[MAX_PLAYERS];
   short int  diplomacy_value[MAX_PLAYERS];
   short int  diplomacy_system[MAX_PLAYERS];

   short int  treaty_modifier[MAX_PLAYERS];
   short int  trade_modifier[MAX_PLAYERS];
   short int  tech_exchange_modifier[MAX_PLAYERS];
   short int  peace_modifier[MAX_PLAYERS];

   char  last_bad_diplomatic_incident[MAX_PLAYERS];
   char  broken_treaties_modifier[MAX_PLAYERS];
   char  last_broken_treaty[MAX_PLAYERS];
   char  last_gift[MAX_PLAYERS];

   short int  ship_war_losses[MAX_PLAYERS];          // 1) small, 2) medium, 3) large, etc.
   short int  colony_war_losses[MAX_PLAYERS];        // 1/killed or captured colonist + 10/captured or destroyed colony
   char  biological_weapons_flag[MAX_PLAYERS];       // T/F killed a colonist on one of your colonies
   char  time_since_last_attack[MAX_PLAYERS];        // when I attack X, set [X] to 0

   char  threats[MAX_PLAYERS];
   char  dishonored_flag[MAX_PLAYERS];
   char  peace_duration[MAX_PLAYERS];
   short int  last_turn_diplomacy_severity[MAX_PLAYERS];
   char  last_broken_treaty_type[MAX_PLAYERS];

   char  last_turn_treaty[MAX_PLAYERS];

   char  diplomacy_proposal_request[MAX_PLAYERS];          // 0) none, 1) First Offer, 2) Second Offer, 3) First Offer, Better 2nd Offer
   char  diplomacy_proposal_tribute_bribe[MAX_PLAYERS];    // 0) none, 1) 5%/year,     2) 10%/year      10% tribute for better offer
   char  diplomacy_proposal_tech_bribe1[MAX_PLAYERS];      //
   char  diplomacy_proposal_tech_bribe2[MAX_PLAYERS];      // better offer technology or
   short int  diplomacy_proposal_gold_bribe[MAX_PLAYERS];       // +50% for better offer
   char  diplomacy_proposal_war_player[MAX_PLAYERS];
   int   diplomacy_proposal_exchange_max_value[MAX_PLAYERS]; // tech exchange max value
   char  diplomacy_proposal_exchange_tech[MAX_PLAYERS];      // tech exchange max value
   short int  diplomacy_proposal_system_bribe[MAX_PLAYERS];

   short int  sneak_attack_planet;
   char  sneak_attack_message;
   char  sneak_attack_player; // planet's ownership could have changed before we arrive

   char  council_threat;
   short int  reward_amount[MAX_PLAYERS];
   char  reward_tech[MAX_PLAYERS];
   char  reward_attack_player[MAX_PLAYERS];


   short int  food_shortage_duration;

   char  trust_worthiness[MAX_PLAYERS];
   char  trust_breaker_player[MAX_PLAYERS];
   char  trust_breaker_treaty[MAX_PLAYERS];

   char  stop_spying_duration[MAX_PLAYERS];
   char  stop_blockading_duration[MAX_PLAYERS];
   char  war_buildup_duration; // nonzero means prepare for starting war in future

   short int  last_diplomacy_proposal_turn[MAX_PLAYERS];
   short int  diplomacy_proposal_rejection[MAX_PLAYERS];

   short int  opportunity_planet_num[MAX_PLAYERS];
   short int  opportunity_planet_value[MAX_PLAYERS];
   int  opportunity_actual_attacker_ratio[MAX_PLAYERS];


   //these are padding...
   short int  temp_diplomacy_dummy1[MAX_PLAYERS];

   char  diplomacy_demand_rejection_message[MAX_PLAYERS];

   char  last_diplomacy_threat_turn[MAX_PLAYERS];

   schar delayed_diplomacy_orders[MAX_PLAYERS]; // 10/9 by Russ
         // can be NONE, or DELAYED_DECLARE_WAR, DELAYED_MAKE_PEACE, DELAYED_BREAK_ALLIANCE

//
   char current_government;
   char pop_growth_bonus;
   char food_bonus;
   char production_bonus;
   char research_bonus;
   char tax_bonus;
   char ship_defense;
   char ship_attack;
   char ground_combat_bonus;
   char spying_bonus;

   char  low_g_world;
   char  heavy_g_world;
   char  aquatic;
   char  subterranean;
   char  large_home_world;
   char  rich_home_world;
   char  ancient_home_world;
   char  cybernetic;
   char  eats_minerals;
   char  repulsive;
   char  charismatic;
   char  uncreative;
   char  creative;
   char  environment_immune;
   char  fantastic_traders;
   char  telepathic;
   char  lucky;
   char  omniscience;
   char  stealthy_ships;
   char  trans_dimensional;
   char  warlord;

   // when they get evolution tech, players will interact with race screen
   // during start-o-turn reports, then during the next turn calc the
   // selected changes will be applied:  Meanwhile, they are briefly stored here:
   char   evolutionary_upgrade[31];
   char   picked_evolutionary_upgrade;  // false until they get evolution tech and pick new racial stats
   char   applied_evolutionary_upgrade; // false until they get evolution tech and new racial stats are actually applied

// Elemental history arrays:
   unsigned char  fleet_history[350];
   unsigned char  tech_history[350];
   unsigned char  population_history[350];
   unsigned char  production_history[350];

   uchar  spies[MAX_PLAYERS];
   char  history_btns;         //1-bit flags for history graph buttons
   char  ignoring;             //Set a bit to ignore a player

   char  peace_flags[MAX_PLAYERS];
   uchar cheated;                       //bitfield
   uint  stardate_last_offered_hero;
   char  current_zoom_level;            //
   sint  cur_map_x;                     // for hotseat games to restore mainscrn map
   sint  cur_map_y;                     //
   char council_voted_for;
   schar surrender_to;                  // normally -1, else a player id
   short int time_since_last_lucky_event;
   char  has_galactic_lore;
   uchar warned_about_cheating_player;  //BITFIELD based on player num
   uchar cheated_this_turn;             //0 == didn;t cheat this turn
   int tribute_income;
   char filler[39];                     // not used
} STRUCT_TYPE_END

STRUCT_TYPE galaxy {
	
	int     version;                                                                                                                          //4
	char    description[37]; //- save game description                                                                                        //41
      int     turn;                                                                                                                             //45
	char    game_type;       //- 0:Single Player, 1:Hotseat, 2:Network, 3:Modem                                                               //46
	
      //SETTINGS 553 bytes
	char  end_of_turn_summary;                            //1
	char  end_of_turn_wait;                               //2
	char  random_events;                                  //3
	char  enemy_moves;                                    //4
	char  expanding_help;                                 //5
	char  auto_select_ships;                              //6
	char  animations_on;                                  //7
	char  auto_select_colony;                             //8
	char  show_relocation_lines;                          //9
	char  show_gnn_report;                                //10
	char  auto_delete_tg_housing;                         //11
	char  auto_saves;                                     //12
	
	char  only_show_serious_turn_summary_reports;         //13
	
	char  ship_initiative;                                //14
	char  option_14;                                      //15
	char  option_15;                                      //16
	char  option_16;                                      //17
	
	char sound_fx_on;                                     //18
	char sound_fx_level;                                  //19
	char music_on;                                        //20
	char music_level;                                     //21
	signed char active_save_slot;                         //22
	unsigned char  multi_player_game_type;                //23
	
	char net_game_name[9]; //char net_game_name[NET_GAME_NAME_LENGTH + 1]; //9 bytes //32
	char s_modem_comm_modem_settings[131]; //struct s_modem_comm modem_settings;           //131 bytes //163
	char s_modem_init_string_modem_init_string[11]; //struct s_modem_init_string modem_init_string; //11 bytes //174
	
	char  combat_speed_flag;                              //175
	char  combat_legal_moves_flag;                        //176
	char  combat_msl_impact_flag;                         //177
	char  combat_shield_arcs_flag;                        //178
	char  combat_grid_flag;                               //179
	
	char filler1[25];                                     //204
	unsigned char language;                               //205
	char xenons_exist_flag;                               //206
	char game_difficulty;                                 //207
	char number_of_players;                               //208
	char galaxy_size;                                     //209
	char galaxy_age;                                      //210
	char strategic_combat_flag;                           //211
	char starting_civilization_level;                     //212
	unsigned long start_of_game_seed;                     //216
	
	short int  sound_toggle;                              //218
	short int  mouse_driver;                              //220
	
	short int  release_version;                           //222
	
	char        dummy[10][20];                            //422
	short int   dummy2[10];                               //442
	short int   dummy3[10];                               //462
	char        dummy4[10];                               //472
	unsigned char       filler2[75];                      //547
	
      unsigned char questionable_filler[6];                 //553                                                                               //599

	unsigned long  random_seed;                           //557                                                                               //603
                              
	
	short int current_colony_count;                       //561                                                                                //605!!!!!CORRECT
	
	struct s_colony aColonies[250];                                                                                                           //90855

      short int current_planet_count;                                                                                                           //90857                                                                 
	
	struct planet aPlanets[360];                          //6120                                                                              //96977

      short int current_stars_count;                        //2                                                                                 //96979
	
	struct star aStars[MAX_SYSTEMS];                      //113х72=8136                                                                       //105115                      
	
	struct s_leader_data aLeaders[MAX_LEADERS];           //59*67=3953                                                                        //109068
      
      short int current_players_count;                      //2                                                                                 //109070
	
	struct s_player aPlayers[MAX_PLAYERS];                //3753*8=30024                                                                      //139094
	
      short int current_ships_count;                        //2                                                                                 //139096

	struct ship aShips[500];                              //129x500=64500                                                                     //203596
	
	unsigned char filler3[3316];
	
	short int  council_flag;
	short int  next_council_meeting_turn;
	
	short int  not_used[5];
	

		sint invasion_chance;
		
		sint off_resource_level;                       //resources used to buy new ships
		sint def_resource_level;                       //2-Sml, 5-Med, 12-Lrg, 30-Huge, 75-Titan
		
		sint n_def_ships[9];                           //Ship counts by size
		sint n_off_ships[9];                           //0-Sml, 1-Med, 2-Lrg, 3-Huge, 4-Titan, 5-8 not used
		sint n_off_ships_deployed[9];
	
		bool conquered;                                 //set to TRUE when antarans are dead
		int last_invasion_date;                         //stardate
		uchar displayed_report;                         //bookeeping

	
	struct planet *aPlanetsPtr;
	unsigned char *nNumOfPlayers, *nNumOfStars;
	unsigned short *nNumOfPlanets;
	unsigned int *aHwCoordinates;
} STRUCT_TYPE_END

STRUCT_TYPE galaxyHeader {
	
	int     version;
	char    description[37]; //- save game description
	int     turn;
	char    game_type;       //- 0:Single Player, 1:Hotseat, 2:Network, 3:Modem
	
	char settings[557];
	
	short int current_colony_count;     //605
	
	struct s_colony aColonies[250];
	
	short int current_planet_count;
	
	struct planet aPlanets[360];
	
	short int current_stars_count;
	
	struct star aStars[MAX_SYSTEMS];
	
	struct s_leader_data aLeaders[MAX_LEADERS];
	
	short int current_players_count;
	
	struct s_player aPlayers[MAX_PLAYERS];
	
	short int current_ships_count;
	
	struct ship aShips[500];
	
	unsigned char filler3[3316];
	
	short int  council_flag;
	short int  next_council_meeting_turn;
	
	short int  not_used[5];
	
	
	sint invasion_chance;
	
	sint off_resource_level;                       //resources used to buy new ships
	sint def_resource_level;                       //2-Sml, 5-Med, 12-Lrg, 30-Huge, 75-Titan
	
	sint n_def_ships[9];                           //Ship counts by size
	sint n_off_ships[9];                           //0-Sml, 1-Med, 2-Lrg, 3-Huge, 4-Titan, 5-8 not used
	sint n_off_ships_deployed[9];
	
	bool conquered;                                 //set to TRUE when antarans are dead
	int last_invasion_date;                         //stardate
	uchar displayed_report;                         //bookeeping
	
} STRUCT_TYPE_END

#endif /*STRUCT_H_*/

/*		printf("int     version %d\n"
 "char    description[37] %s\n"
 "int     galaxy age %d\n"
 "int     game type %d\n"
 "char  end_of_turn_summary %d\n"
 "char  end_of_turn_wait %d\n"
 "char  random_events %d\n"
 "char  enemy_moves %d\n"
 "char  expanding_help %d\n"
 "char  auto_select_ships %d\n"
 "char  animations_on %d\n"
 "char  auto_select_colony %d\n"
 "char  show_relocation_lines %d\n"
 "char  show_gnn_report %d\n"
 "char  auto_delete_tg_housing %d\n"
 "char  auto_saves %d\n"
 "char  only_show_serious_turn_summary_reports %d\n"
 "char  ship_initiative %d\n"
 "char  option_14 %d\n"
 "char  option_15 %d\n"
 "char  option_16 %d\n"
 "char sound_fx_on %d\n"
 "char sound_fx_level %d\n"
 "char music_on %d\n"
 "char music_level %d\n"
 "signed char active_save_slot %d\n"
 "unsigned char  multi_player_game_type %d\n"
 "char net_game_name[NET_GAME_NAME_LENGTH + 1] %s\n"
 "struct s_modem_comm modem_settings %s\n"
 "struct s_modem_init_string modem_init_string %s\n"
 "char  combat_speed_flag %d\n"
 "char  combat_legal_moves_flag %d\n"
 "char  combat_msl_impact_flag %d\n"
 "char  combat_shield_arcs_flag %d\n"
 "char  combat_grid_flag %d\n"
 "char filler1[25] %s\n"
 "uchar language  %d\n"
 "char xenons_exist_flag  %d\n"
 "char game_difficulty %d\n"
 "char number_of_players %d\n"
 "char galaxy_size %d\n"
 "char galaxy_age %d\n"
 "char strategic_combat_flag %d\n"
 "char starting_civilization_level %d\n"
 "unsigned long start_of_game_seed %lu\n"
 "short int  sound_toggle %d\n"
 "short int  mouse_driver %d\n"
 "short int  release_version  %d\n"
 "char        dummy[10][20]  %s\n"
 "short int   dummy[10]  %s\n"
 "short int   dummy[10] %s\n"
 "char        dummy[10] %s\n"
 "uchar       filler2[75] %s\n"
 "unsigned long  random_seed  %lu\n"
 "short int current_colony_count  %d\n",
 gH->version, gH->description,gH->galaxy_age1, gH->game_type, gH->end_of_turn_summary, gH->end_of_turn_wait, gH->random_events,
 gH->enemy_moves, gH->expanding_help, gH->auto_select_ships, gH->animations_on, gH->auto_select_colony,
 gH->show_relocation_lines, gH->show_gnn_report, gH->auto_delete_tg_housing, gH->auto_saves,
 gH->only_show_serious_turn_summary_reports, gH->ship_initiative, gH->option_14, gH->option_15, gH->option_16,
 gH->sound_fx_on, gH->sound_fx_level, gH->music_on, gH->music_level, gH->active_save_slot, gH->multi_player_game_type,
 gH->net_game_name, gH->s_modem_comm_modem_settings, gH->s_modem_init_string_modem_init_string,
 gH->combat_speed_flag, gH->combat_legal_moves_flag, gH->combat_msl_impact_flag, gH->combat_shield_arcs_flag, gH->combat_grid_flag,
 gH->filler1, gH->language, gH->xenons_exist_flag,
 gH->game_difficulty, gH->number_of_players, gH->galaxy_size, gH->galaxy_age, gH->strategic_combat_flag, gH->starting_civilization_level,
 gH-> start_of_game_seed, gH->sound_toggle, gH->mouse_driver,gH->release_version,
 gH->dummy, gH->dummy2, gH->dummy3, gH->dummy4, gH->filler2,
 gH->random_seed, gH->current_colony_count);*/
