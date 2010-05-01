#ifndef STRUCT_H_
#define STRUCT_H_

#ifdef __GNUC__
	#define STRUCT_TYPE struct
	#define STRUCT_TYPE_END __attribute__((__packed__));
#else
	#define STRUCT_TYPE _Packed struct
	#define STRUCT_TYPE_END ;
#endif

//Save Data
#define MAX_SYSTEMS 72
#define MAX_PLANETS 360
#define MAX_PLAYERS 8
#define MAX_SHIPS 500
#define STAR_OFFSET 0x17ad3
#define PLANET_OFFSET 0x162e9
#define SHIP_OFFSET 0x21F58

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

#define FLG_CELL		1

//Homeworld flags
#define FLG_FLATHW		1
#define FLG_FIXEDHW		2

//Splinter flags
#define FLG_SPLINT		1
#define FLG_ARTI		2

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

STRUCT_TYPE starSystem {

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

//typedef struct starSystem starSystem_t;

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

STRUCT_TYPE galaxy {

	struct starSystem *aStars;
	struct planet *aPlanets;
	unsigned char *nNumOfPlayers, *nNumOfStars;
	unsigned short *nNumOfPlanets;
	unsigned int *aHwCoordinates;
} STRUCT_TYPE_END

STRUCT_TYPE planetInfo {

	struct starSystem *aStars;
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


#endif /*STRUCT_H_*/
