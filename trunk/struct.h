#ifdef __GNUC__
	#define STRUCT_TYPE struct
	#define STRUCT_TYPE_END __attribute__((__packed__));
#else
	#define STRUCT_TYPE _Packed struct
	#define STRUCT_TYPE_END ;
#endif

STRUCT_TYPE starSystem {

	char sName[15];		//Star System Name									00-0E	15	bytes
	unsigned short int nXpos;		//X Position										0F-10	2	bytes
	unsigned short int nYpos;		//Y Position										11-12 	2	bytes
	unsigned char nSize;			//Star Size 0=Large 3=Tiny							13		1	byte
	unsigned char nOwner;			//System Primary Owner 0-7 player (PlayerID)		14		1	byte
	unsigned char nUnknown;			//Unknown											15		1	byte
	unsigned char nStarType;		//Star Type											16		1	bytea
									//0=Blue 1=White 2=Yellow 3=Orange 4=Red 5=Brown 6=BlackHole
	unsigned char sUnknown[17];		//Unknown											17-27	17	bytes
	unsigned char nSpecial;			//SystemSpecial										28		1	byte
									//0=None 1=Space Debris 3=Pirate Cache 4=Gold Deposites 5=Gem Deposites
									//6=Natives 7=Splinter Colony 8=Hero A=Artifacts World B=Orion
	unsigned char nWormSystem;		//0-127 Wormhole leads to "system" FF - no wormhole	29		1	byte
	unsigned char sUnknown2[15];	//Unknown											2A-38	15	bytes 
	unsigned char nWarpIdict;		//Warp Interdictor 0 none, 1-8 owner (PlayerID-1)	39		1	byte
	unsigned char sUnknown3[5];		//Unknown											3A-3E	5	bytes
	unsigned char nArtemisNet;		//Artemis Systemr 0 none, 1-8 owner (PlayerID-1)	3F		1	byte	
	unsigned char sUnknown4[10];	//Unknown											40-49 10	bytes
	unsigned short int aPlanet[5];	//Link to planets table								4A-53 10	bytes
	unsigned char sUnknown5[29];	//Unknown											54-70 29	bytes
} STRUCT_TYPE_END

//typedef struct starSystem starSystem_t;

STRUCT_TYPE planet {

	unsigned short int nColonyID;	//Link to colonies table
	unsigned char nStarID;			//Link to stars table
	unsigned char nOrbit;			//Orbit 0-4
	unsigned char nPlanetType;		//Planet type 1=Asteroid 2=Gas Planet 3=Planet
	unsigned char nPlanetSize;		//Planet size 0=Tiny 1=Small 2=Medium 3=Large 4=Huge
	unsigned char nPlanetGravity;	//Planet gravity 0=Low Gravity 1=Normal 2=Heavy Gravity
	unsigned char nUnknown;			//Unknown
	unsigned char nEnvClass;		//Enviromental class 0=Toxic 1=Radiated 2=Barren 3=Desert 4=Tundra
									//5=Ocean 6=Swamp 7=Arid 8=Terr 9=Gaia
	unsigned char nDrawingID;		//0-5 image in planets.lbx
									//@todo Find and insert correlation between image and planet environment
	unsigned char nMineralClass;	//Planet Mineral Class 0=upoor 1=poor 2=abundant 3=rich 4=ultrarich
	unsigned char nFoodBase;		//@todo Find out how foodbase correlates with enviromental class
	unsigned char nTerraformsDone;	//Number of terraforming done
	unsigned char nUnknown2;		//Unknown 2=Tiny 4=Small 5=Medium 7=Large A=Huge
	unsigned char nUnknown3;
	unsigned char nPlanetSpecial;	//0=None 1=? 2=Space Debris 3=Pirate Cache 4=Gold Deposits 5=Gem Deposits
									//6=Natives 7=Splinter Colony 8=Hero A=Artifacts world B=Orion
	unsigned char nFlags;			//2=Soil Enrichment
} STRUCT_TYPE_END

//typedef struct planet planet_t;
