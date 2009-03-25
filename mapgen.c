#define MAPGEN_VERSION "Concept"
#include "mapgen.h"

struct starSystem aStarSystems[MAX_SYSTEMS];
struct planet aPlanets[MAX_PLANETS];
unsigned char nNumOfPlayers, nNumOfStars, nNumOfPlanets;
unsigned int aHwCoordinates[MAX_PLAYERS][2];

int main(int argc, char *argv[]) {

	unsigned int i;
	FILE *fp;
	unsigned int terraformFlags = 0, opt;
	char sSaveFile[100] = "SAVE10.GAM";

	while ((opt = getopt(argc, argv, "ht:f:V")) != -1) {
		switch (opt) {
		
			case 't':
				if      (strstr(optarg, "toxic"))
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

				else {
						fprintf(stderr, "Unknown Terraform parameter %s\n", optarg);
						exit(1);
				}
			break;
			case 'h':
				printf("Usage: %s [-h] [-t] [-V] [-f file]\n\n"

					"Example: %s -t toxic -t upoor -t lowg -t heavyg -t tiny -t small -f SAVE10.GAM\n\n"

					"Options:\n"
					"  -h             This help.\n\n"

					"  -t             Terraform\n"
					"                   toxic - Toxic planets become radiated\n"
					"                   upoor - Ultra Poor planets become poor\n"
					"                   lowg - Low Gravity planets become Normal Gravity\n"
					"                   heavyg - Heavy Gravity planets become Normal Gravity\n"
					"                   tiny - Tiny planets become small\n"
					"                   small - Small planets become medium\n\n"
					"  -f file        Edit 'file' instead of SAVE10.GAM\n\n"

					"  -V             Print Version and exit\n\n", argv[0], argv[0]);
					exit(0);
			break;
			case 'f':
				sprintf(sSaveFile, "%s", optarg);
			break;
			case 'V':
				printf("Version: %s\n\n", MAPGEN_VERSION);
				exit(0);
			default:
				fprintf(stderr, "Usage: %s [-h] [-t terraform_type] [-f file]\n", argv[0]);
				exit(1);
			break;
		}
	}
	
	fp = fopen(sSaveFile, "rb+");
	
	if (fp == NULL) {
	
		fprintf(stderr, "Can not open %s", sSaveFile);
		return 0;
	}

	//Reading Star Systems information.
	getFileData(aStarSystems, sizeof aStarSystems, STAR_OFFSET, fp);
	
	//Reading Planets information.	
	getFileData(&aPlanets, sizeof aPlanets, PLANET_OFFSET, fp);

	getFileData(&nNumOfStars, sizeof nNumOfStars, NUM_OF_STARS_OFFSET, fp);
	getFileData(&nNumOfPlanets, sizeof nNumOfPlanets, NUM_OF_PLANETS_OFFSET, fp);
	getFileData(&nNumOfPlayers, sizeof nNumOfPlayers, NUM_OF_PLAYERS_OFFSET, fp);

	calcPlanetsNum(aStarSystems, aHwCoordinates, nNumOfStars);

	if (terraformFlags != 0) 
		terraform(aPlanets, nNumOfPlanets, terraformFlags);
	

	//Writing Planets information.
	fseek(fp, PLANET_OFFSET, SEEK_SET);

	fwrite(&aPlanets, sizeof aPlanets, 1, fp);

	//Wrighting Star Systems information.
	fseek(fp, STAR_OFFSET, SEEK_SET);

	fwrite(&aStarSystems, sizeof aStarSystems, 1, fp);

	fclose(fp);

	return 0;
}
