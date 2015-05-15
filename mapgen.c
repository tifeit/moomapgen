#include "mapgen.h"


struct star *ptrSystem;
struct galaxy galaxies[4];
struct galaxy *ptrGalaxy = &galaxies[0];

unsigned char nNumOfPlayers, nNumOfStars;
unsigned short nNumOfPlanets;
unsigned int aHwCoordinates[MAX_PLAYERS][3];
unsigned char verbose = 0;

int main(int argc, char *argv[]) {

	unsigned int opt;

	unsigned char rings = 0;
	unsigned char nFiles = 1;
	unsigned char i = 0;
	FILE *fp, *fp2;
	unsigned int terraformFlags = 0, hwFlags = 0, specialsFlags = 0, monsterFlags = 0, balanceFlags = 0;

	unsigned char byte;

	char sSaveFile[12] = "SAVE10.GAM";
	char sBakFile[13] = "MAPGEN.GAM";
	char aMergeFile[4][12] = {"SAVE10.GAM", "PLAYER2.GAM", "PLAYER3.GAM", "PLAYER4.GAM"};

	time_t t;
	struct tm *tmp;
	t = time(NULL);
	tmp = localtime(&t);
	strftime(sBakFile, sizeof(sBakFile), "%y%m%d%H.GAM", tmp);

	while ((opt = getopt(argc, argv, "ht:s:m:b:f:r:vV")) != -1) {
		switch (opt) {
			case 'h':
			case 'H':
				printf("Usage: %s [-h] [-t terraformation] [-s special] [-m change] [-b type] [-r numOfPlayersToMerge] [-`~ [-v] [-V] [-f file]\n\n"

					"Example: %s -t toxic -t upoor -t lowg -t heavyg -t tiny -t small -f SAVE10.GAM\n\n"

					"Options:\n"
					"  -h [-H] This help.\n\n"

					"  -t Terraform\n"
					"      toxic - Toxic planets become radiated\n"
					"      upoor - Huge Ultra Poor planets becomes poor. Other Ultra Poor planets become Abundant\n"
					"      lowg - Low Gravity planets become Normal Gravity\n"
					"      heavyg - Heavy Gravity planets become Normal Gravity\n"
					"      tiny - Tiny planets become randomly from Small to Large. With except for -tsmall flag, if it is used, they become Medium.\n"
					"      small - Small planets become medium\n"
					"      flathw - Flattens unoccupied planets in HomeWorlds:\n"
					"        They become Abundant, Toxics and Rads become Barren,\n"
					"        gravity become Normal except for one planet,\n"
					"        it become the same gravity as occupied planet, size is set in order\n"
					"        Large, Large again, Medium, Small untill\n"
					"        there are no more planets to modify. Gaias become Terrain.\n", argv[0], argv[0]);
				getchar();

				printf(
					"\n      fixedhw - Implies `flathw`. Planets become:\n"
					"        Large Abundant Swamp, Large Abundant Arid, Large Poor Tundra,\n"
					"        Medium Poor Terrain, all normalG.\n"
					"        If your homeworld is lowG, than all other planets except Arid\n"
					"        it becomes lowG.\n"
					"        If your homeworld is heavyG, than Swamp becomes heavyG, others\n"
					"        become normalG\n"
					"      gaia - DOES NOT imply fixedhw. Last planet become small poor gaia\n"
					"        unless you are creative or aquatic or tolerant.\n"
					"        elswise you get small poor terrain\n"
					"      richhw - Makes first unoccupied planet rich\n"
					"      hugehw - Makes first unoccupied planet huge\n"
					"      goodhw - Implies richw & hugehw. Makes first unoccupied planet terrain.\n\n"
						);
				getchar();
				printf(
					"\n  -s Specials Change\n"
					"      splint - Splinter replaced by gem deposits.\n"
					"      nonatives - Natives are replaced by gold deposits.\n"
					"      arti - Arti planets still exist, but don't give techs anymore.\n"
					"      hero - Systems with Marooned heroes get an asterisk before name.\n\n"

					"  -m Monsters Change\n"
					"      grav - Guarded planets become normal gravity, even ultrarich now.\n"
					//"      leaders - Marooned heroes under nonguarded planets become pirate stash.\n"
					"        Pirate stash and space debris under guarded planets become marooned heroes.\n"
					"      terraform - Guarded rich & urich planets are terraformed.\n"
					"        Toxics, Rads, Barrens, Deserts become Tundra.\n"
					"      monst - Does the same thing as -mgrav and -mterraform.\n\n"

					"  -b Balance Galaxy\n"
					"	   showringX - Make planets in X parsecs distance from HW visible to players\n"
					"	   calc - Calculate opponent starts and print out results\n\n"
					"  -v Verbose debugging output(CHEAT!)\n\n"

					"  -r Num of PLAYERX.GAM files to merge in 'filename'\n\n"

					"  -V Print Version and exit\n\n"

					"  -f file Edit 'file' instead of SAVE10.GAM\n\n");

					exit(0);
			break;
			case 't':
				if	    (strstr(optarg, "toxic"))
							terraformFlags |= FLG_NOTOXIC;

				else if (strstr(optarg, "upoor"))
							terraformFlags |= FLG_NOUPOOR;

				else if (strstr(optarg, "lowg"))
							terraformFlags |= FLG_NOLG;

				else if (strstr(optarg, "heavyg"))
							terraformFlags |= FLG_NOHG;

				else if (strstr(optarg, "tiny"))
							terraformFlags |= FLG_NOTINY;

				else if (strstr(optarg, "small"))
							terraformFlags |= FLG_NOSMALL;

				else if (strstr(optarg, "flathw"))
							hwFlags |= FLG_FLATHW;

				else if (strstr(optarg, "fixedhw"))
							hwFlags |= FLG_FIXEDHW;

				else if (strstr(optarg, "gaia"))
							hwFlags |= FLG_GAIA;

				else if (strstr(optarg, "richhw"))
							hwFlags |= FLG_RICHHW;

				else if (strstr(optarg, "hugehw"))
							hwFlags |= FLG_HUGEHW;

				else if (strstr(optarg, "goodhw"))
							hwFlags |= (FLG_GOODHW | FLG_RICHHW | FLG_HUGEHW);


				else {
						fprintf(stderr, "Unknown Terraform parameter %s.\nPress any key to continue.\n", optarg);
						getc(stdin);
						exit(1);
				}
			break;
			case 's':
				if		(strstr(optarg, "splint"))
							specialsFlags |= FLG_SPLINT;

				else if (strstr(optarg, "arti"))
							specialsFlags |= FLG_ARTI;
				
				else if (strstr(optarg, "nonatives"))
							specialsFlags |= FLG_NONATIVES;
				
				else if (strstr(optarg,"hero"))
							specialsFlags |= FLG_HERO;
				
				else {
						fprintf(stderr, "Unknown Special parameter %s.\nPress any key to continue.\n", optarg);
						getc(stdin);
						exit(1);
				}

			break;
			case 'm':
				if		(strstr(optarg, "grav"))
							monsterFlags |= FLG_GRAV;

				else if (strstr(optarg, "terraform"))
							monsterFlags |= FLG_TERRAFORM;

				else if (strstr(optarg, "monst")) {

							monsterFlags |= FLG_GRAV;
							monsterFlags |= FLG_TERRAFORM;

				} else {

						fprintf(stderr, "Unknown Monster parameter %s.\nPress any key to continue.\n", optarg);
						getc(stdin);
						exit(1);
				}
			break;
			case 'f':
				snprintf(sSaveFile, sizeof(sSaveFile), "%s", optarg);
			break;
			case 'v':
				verbose = 1;
			break;
			case 'V':
				printf("Version: %s\n", MAPGEN_VERSION);
				exit(0);
			case 'b':
					balanceFlags |= FLG_CALC;

					if (strstr(optarg, "showring") && sscanf(optarg, "showring%c",&rings)) {
						balanceFlags |= FLG_RING;
					}

			break;
			case 'r':
					nFiles = atoi(optarg);
					snprintf(aMergeFile[0], sizeof(aMergeFile[0]), "%s", sSaveFile);

			break;
			default:
				fprintf(stderr, "Usage: %s [-h] [-t terraform_type] [-f file]\nPress any key to continue.\n", argv[0]);
				getc(stdin);
				exit(1);
			break;
		}
	}

	printf("Visit http://code.google.com/p/moomapgen/ for adding feature requests.\n");

	fp = fopen(sSaveFile, "rb+");

	if (fp == NULL) {

		fprintf(stderr, "Can not open %s.\nPress any key to continue.", sSaveFile);
		getc(stdin);
		exit(1);
	}

	//Backup file.
	fp2 = fopen(sBakFile, "wb+");

	if (fp2 == NULL) {

		fprintf(stderr, "Can not open/create %s.\nPress any key to continue.", sBakFile);
		getc(stdin);
		exit(1);
	}

	while(!feof(fp)) {

			fread(&byte, 1, 1, fp);
			if (feof(fp)) break;
			fwrite(&byte, 1, 1, fp2);
	}

	fclose(fp);
	fclose(fp2);

	i = 0;
	do {

		fp = fopen(aMergeFile[i], "rb+");
		if (fp == NULL) {

			fprintf(stderr, "Can not open %s.\nPress any key to continue.", aMergeFile[i]);
			getc(stdin);
			exit(1);
		}
		ptrGalaxy = &galaxies[i];

		//Try to read all save data, its useless, for sure, cause exact structure size and offsets are not precise.
		getFileData(ptrGalaxy, sizeof galaxies[0], 0, fp);
		getFileData(ptrGalaxy->aStars, sizeof ptrGalaxy->aStars, STAR_OFFSET, fp);
		getFileData(ptrGalaxy->aPlanets, sizeof ptrGalaxy->aPlanets, PLANET_OFFSET, fp);
		getFileData(ptrGalaxy->aShips, sizeof ptrGalaxy->aShips, SHIP_OFFSET, fp);
		getFileData(ptrGalaxy->aPlayers, sizeof ptrGalaxy->aPlayers, PLAYER_OFFSET, fp);
		getFileData(ptrGalaxy->aColonies, sizeof ptrGalaxy->aColonies, PLAYER_OFFSET, fp);
		getFileData(ptrGalaxy->aLeaders, sizeof ptrGalaxy->aLeaders, LEADER_OFFSET, fp);
		getFileData(&nNumOfStars, sizeof nNumOfStars, NUM_OF_STARS_OFFSET, fp);
		getFileData(&nNumOfPlanets, sizeof nNumOfPlanets, NUM_OF_PLANETS_OFFSET, fp);
		getFileData(&nNumOfPlayers, sizeof nNumOfPlayers, NUM_OF_PLAYERS_OFFSET, fp);
		ptrGalaxy->nNumOfPlanets = &nNumOfPlanets;
		ptrGalaxy->nNumOfStars = &nNumOfStars;
		ptrGalaxy->nNumOfPlayers = &nNumOfPlayers;

		getHwCoords(ptrGalaxy->aStars, aHwCoordinates, nNumOfStars, ptrGalaxy->aPlanets);
		ptrGalaxy->aHwCoordinates = (unsigned int *) aHwCoordinates;

		fclose(fp);

	} while (++i != nFiles);

	fp = fopen(sSaveFile, "rb+");

	if (nFiles == 1) {

		//All planets terraformation.
		if (terraformFlags || specialsFlags || monsterFlags)
			terraform(ptrGalaxy->aStars, ptrGalaxy->aPlanets, ptrGalaxy->aShips, nNumOfPlanets, nNumOfStars, terraformFlags, specialsFlags, monsterFlags);

		//Homeworld modification.
		if (hwFlags) {

			modifyHW(ptrGalaxy, hwFlags);
		}

		//Map generation.
		if (balanceFlags) {

			balanceGalaxy(ptrGalaxy, balanceFlags, rings);
		}
	} else if (nFiles > 1) {

		mergeGalaxies (galaxies, nFiles);
	}

	//Writing Planets information.
	fseek(fp, PLANET_OFFSET, SEEK_SET);

	fwrite(&ptrGalaxy->aPlanets, sizeof ptrGalaxy->aPlanets, 1, fp);

	//Writing Star Systems information.
	fseek(fp, STAR_OFFSET, SEEK_SET);

	fwrite(&ptrGalaxy->aStars, sizeof ptrGalaxy->aStars, 1, fp);

	//Writing Star Systems ammount.
	fseek(fp, NUM_OF_STARS_OFFSET, SEEK_SET);

	fwrite(&nNumOfStars, sizeof nNumOfStars, 1, fp);

	fclose(fp);

	return 0;
}
