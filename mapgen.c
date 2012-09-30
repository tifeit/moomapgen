#include "mapgen.h"

struct star *ptrSystem;
struct galaxy galaxy;
unsigned char nNumOfPlayers, nNumOfStars;
unsigned short nNumOfPlanets;
unsigned int aHwCoordinates[MAX_PLAYERS][3];
unsigned char verbose = 0;

int main(int argc, char *argv[]) {

	unsigned int opt;
	FILE *fp, *fp2;
	unsigned int terraformFlags = 0, hwFlags = 0, specialsFlags = 0, monsterFlags = 0, balanceFlags = 0;

	unsigned char byte;

	char sSaveFile[100] = "SAVE10.GAM";
	char sBakFile[100] = "MAPGEN.GAM";

	time_t t;
	struct tm *tmp;
	t = time(NULL);
	tmp = localtime(&t);
	strftime(sBakFile, sizeof(sBakFile), "%y%m%d%H.GAM", tmp);

	while ((opt = getopt(argc, argv, "ht:s:m:b:f:vV")) != -1) {
		switch (opt) {
			case 'h':
			case 'H':
				printf("Usage: %s [-h] [-t terraformation] [-s special] [-m change] [-b type] [-v] [-V] [-f file]\n\n"

					"Example: %s -t toxic -t upoor -t lowg -t heavyg -t tiny -t small -f SAVE10.GAM\n\n"

					"Options:\n"
					"  -h [-H] This help.\n\n"

					"  -t Terraform\n"
					"      toxic - Toxic planets become radiated\n"
					"      upoor - Ultra Poor planets become poor\n"
					"      lowg - Low Gravity planets become Normal Gravity\n"
					"      heavyg - Heavy Gravity planets become Normal Gravity\n"
					"      tiny - Tiny planets become small\n"
					"      small - Small planets become medium\n"
					"      flathw - Flattens unoccupied planets in HomeWorlds:\n"
					"        They become Abundant, Toxics and Rads become Barren,\n"
					"        gravity become Normal except for one planet,\n"
					"        it become the same gravity as occupied planet, size is set in order\n"
					"        Large, Large again, Medium, Small untill\n"
					"        there are no more planets to modify. Gaias become Terrain.\n", argv[0], argv[0]);
				getchar();
				printf(
					"      fixedhw - Implies `flathw`. Planets become:\n"
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
					"  -s Specials Change\n"
					"      splint - Splinter replaced by gem deposits.\n"
					"      arti - Arti planets still exist, but don't give techs anymore.\n\n"

					"  -m Monsters Change\n"
					"      grav - Guarded planets become normal gravity, even ultrarich now.\n"
					"      terraform - Guarded rich & urich planets are terraformed.\n"
					"        Toxics, Rads, Barrens, Deserts become Tundra.\n"
					"      monst - Does the same thing as -mgrav and -mterraform.\n\n"

					"  -b Balance Galaxy\n"
					"	   showring1 - Make planets in 6 parsecs distance visible to players\n"
					"      showring2 - Make planets in 10 parsecs distance visible to players\n"
					"	   calc - Calculate opponent starts and print out results\n\n"
					"  -v Verbose debugging output(CHEAT!)\n\n"

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

					if (strstr(optarg, "showring1")) {
						balanceFlags |= FLG_RING1;
					}

					if (strstr(optarg, "showring1")) {
						balanceFlags |= FLG_RING1;
					}
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

	fclose(fp2);

	//Try to read all save data, its useless, for sure, cause exact structure size and offsets are not precide.
	getFileData(&galaxy, sizeof galaxy, 0, fp);

	//Reading Star Systems information.
	getFileData(&galaxy.aStars, sizeof galaxy.aStars, STAR_OFFSET, fp);

	//Reading Planets information.
	getFileData(&galaxy.aPlanets, sizeof galaxy.aPlanets, PLANET_OFFSET, fp);

	//Reading Ships information.
	getFileData(&galaxy.aShips, sizeof galaxy.aShips, SHIP_OFFSET, fp);

	//Reading Players information.
	getFileData(&galaxy.aPlayers, sizeof galaxy.aPlayers, PLAYER_OFFSET, fp);

	getFileData(&nNumOfStars, sizeof nNumOfStars, NUM_OF_STARS_OFFSET, fp);
	galaxy.nNumOfStars = &nNumOfStars;

	getFileData(&nNumOfPlanets, sizeof nNumOfPlanets, NUM_OF_PLANETS_OFFSET, fp);
	galaxy.nNumOfPlanets = &nNumOfPlanets;

	getFileData(&nNumOfPlayers, sizeof nNumOfPlayers, NUM_OF_PLAYERS_OFFSET, fp);
	galaxy.nNumOfPlayers = &nNumOfPlayers;

	getHwCoords(galaxy.aStars, aHwCoordinates, nNumOfStars, galaxy.aPlanets);
	galaxy.aHwCoordinates = (unsigned int *) aHwCoordinates;

	//All planets terraformation.
	if (terraformFlags || specialsFlags || monsterFlags)
		terraform(galaxy.aStars, galaxy.aPlanets, galaxy.aShips, nNumOfPlanets, nNumOfStars, terraformFlags, specialsFlags, monsterFlags);

	//Homeworld modification.
	if (hwFlags) {

		modifyHW(&galaxy, hwFlags);
	}

	//Map generation.
	if (balanceFlags) {

		balanceGalaxy(&galaxy);
	}

	//Writing Planets information.
	fseek(fp, PLANET_OFFSET, SEEK_SET);

	fwrite(&galaxy.aPlanets, sizeof galaxy.aPlanets, 1, fp);

	//Writing Star Systems information.
	fseek(fp, STAR_OFFSET, SEEK_SET);

	fwrite(&galaxy.aStars, sizeof galaxy.aStars, 1, fp);

	//Writing Star Systems ammount.
	fseek(fp, NUM_OF_STARS_OFFSET, SEEK_SET);

	fwrite(&nNumOfStars, sizeof nNumOfStars, 1, fp);

	fclose(fp);

	exit(0);
}
