#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

extern unsigned char verbose;

void tohex(void *string, unsigned int length) {
	unsigned char i;
	unsigned char *point;

	point = (unsigned char *) string;

	for (i = 0; i != length; i++) {

		printf("%.2X ", *point++);
	}
	printf("\n");
}

void printSystem(struct star* starSystem, struct planet *aPlanets) {

	unsigned char i;
	struct planet *ptrPlanet;

	printf( "%s (%d, %d) nSize: %d nOwner: %d nPicture: %d nStarType: %d nSpecial: %d nBlockaded: %d bvBlocadedBy: %d nVisited: %d \n"
			"nJustVisited: %d nStarOwner: %d\n", starSystem->sName, starSystem->nXpos, starSystem->nYpos, starSystem->nSize, starSystem->nOwner,
			starSystem->nPicture, starSystem->nStarType, starSystem->nSpecial, starSystem->nBlocaded, starSystem->bvBlockadedBy[0], starSystem->nVisited,
			starSystem->nJustVisited, starSystem->nStarOwner);


	//Displaying Homeworld info
	for ( i = 0; i != 5; i++ ) {

		if (starSystem->aPlanet[i] != 0xffff) {

			ptrPlanet = &aPlanets[starSystem->aPlanet[i]];
			printf("\nPlanet #%d\n", i);
			printf("nColonyID: %.2X\n", ptrPlanet->nColonyID);
			printf("nStarID: %.2X\n", ptrPlanet->nStarID);
			printf("nOrbit: %.2X\n", ptrPlanet->nOrbit);
			printf("nPlanetType: %.2X\n", ptrPlanet->nPlanetType);
			printf("nPlanetSize: %.2X\n", ptrPlanet->nPlanetSize);
			printf("nPlanetGravity: %.2X\n", ptrPlanet->nPlanetGravity);
			printf("nEnvClass: %.2X\n", ptrPlanet->nEnvClass);
			printf("nDrawingID: %.2X\n", ptrPlanet->nDrawingID);
			printf("nMineralClass: %.2X\n", ptrPlanet->nMineralClass);
			printf("nFoodBase: %.2X\n", ptrPlanet->nFoodBase);
			printf("nTerraformsDone: %.2X\n", ptrPlanet->nTerraformsDone);
			printf("nPlanetSpecial: %.2X\n", ptrPlanet->nPlanetSpecial);
			printf("nFlags: %.2X\n", ptrPlanet->nFlags);
		}
	}
}

void getFileData(void *storage, unsigned long length, unsigned long offset, FILE *fp) {

	fseek(fp, offset, SEEK_SET);
	fread(storage, length, 1, fp);
}

void getHwCoords(struct star *aStarSystems, unsigned int aHwCoordinates[][3], unsigned char nNumOfStars, struct planet *aPlanets) {

	unsigned char i;

	//Finding HomeWorlds
	for (i = 0; i != nNumOfStars; i++) {

		if(aStarSystems[i].nStarOwner != 0xff) {

			aHwCoordinates[aStarSystems[i].nStarOwner][0] = aStarSystems[i].nXpos;
			aHwCoordinates[aStarSystems[i].nStarOwner][1] = aStarSystems[i].nYpos;
			aHwCoordinates[aStarSystems[i].nStarOwner][2] = i;

			if (verbose) {

/*				printf("HomeWorld:\n");
				printSystem(&aStarSystems[i], aPlanets);
				printf("--------\n");
*/
			}
		}
	}
}

void terraform(struct star *aStarSystems, struct planet *aPlanets, struct ship *aShips, unsigned short nPlanets, unsigned short nStars,
	unsigned int flags, unsigned int specialsFlags, unsigned int monsterFlags) {

	unsigned int i, j;
	struct planet *ptrPlanet;

	for (i = 0; i!= nPlanets; i++) {

		if (flags & FLG_NOTOXIC && aPlanets[i].nEnvClass == 0)
			aPlanets[i].nEnvClass = 1;

		if (flags & FLG_NOUPOOR && aPlanets[i].nMineralClass == 0)
			aPlanets[i].nMineralClass = 1;

		if (flags & FLG_NOLG && aPlanets[i].nPlanetGravity == 0)
			aPlanets[i].nPlanetGravity = 1;

		if (flags & FLG_NOHG && aPlanets[i].nPlanetGravity == 2)
			aPlanets[i].nPlanetGravity = 1;

		if (flags & FLG_NOTINY && aPlanets[i].nPlanetSize == 0) {

			if (flags & FLG_NOSMALL)
				aPlanets[i].nPlanetSize = 2;

			else
				aPlanets[i].nPlanetSize = 1;
		}

		if (flags & FLG_NOSMALL && aPlanets[i].nPlanetSize == 1)
			aPlanets[i].nPlanetSize = 2;

		if (specialsFlags) {

			if (specialsFlags & FLG_SPLINT && aPlanets[i].nPlanetSpecial == SPLINTER_COLONY) {

				aStarSystems[aPlanets[i].nStarID].nSpecial = GEM_DEPOSITS; //Setting gem flag to star.
				aPlanets[i].nPlanetSpecial = GEM_DEPOSITS; //Setting gem flag to planet.

				if (verbose) printf("%s | Splinter\n", aStarSystems[aPlanets[i].nStarID].sName);
			}

			if (specialsFlags & FLG_ARTI && aPlanets[i].nPlanetSpecial == ANCIENT_ARTIFACTS) {

				aStarSystems[aPlanets[i].nStarID].bArtifactsGaveApp = 1;

				if (verbose) printf("%s | Arti\n", aStarSystems[aPlanets[i].nStarID].sName);
			}
		}
	}

	if (monsterFlags) {

		unsigned char location = 0;

		for (i = 0; i != MAX_SHIPS; i++) {

			if (aShips[i].d.name[0] != 0 && aShips[i].owner > 8) {

				location = aShips[i].location;

				//For each planet in this system.
				for (j = 0; j != 5; j++ ) {

					//If planet exist
					if (aStarSystems[location].aPlanet[j] != 0xffff) {

						ptrPlanet = &aPlanets[aStarSystems[location].aPlanet[j]];

						if (monsterFlags & FLG_GRAV) {

							ptrPlanet->nPlanetGravity = 1;

							if (verbose) printf("%s | Gravity\n", aStarSystems[aShips[i].location].sName);
						}

						if (monsterFlags & FLG_TERRAFORM) {

							if (ptrPlanet->nMineralClass == RICH || ptrPlanet->nMineralClass == ULTRA_RICH) {

								if (ptrPlanet->nEnvClass == TOXIC || ptrPlanet->nEnvClass == RADIATED
									|| ptrPlanet->nEnvClass == DESERT || ptrPlanet->nEnvClass == BARREN) {

									ptrPlanet->nEnvClass = TUNDRA;

									if (verbose) printf("%s | Monster Terraform\n", aStarSystems[aShips[i].location].sName);

								}
							}
						}
					}
				}
			}
		}
	}
}

void modifyHW(struct planet *aPlanets, struct star *ptrSystem, unsigned int nSystemID, unsigned int flags) {

	unsigned char i, nDonePlanets = 0, nHwGravity;
	struct planet *ptrPlanet;

	if (flags & FLG_FLATHW || flags & FLG_FIXEDHW) {


		//Finding HomeWorld planet gravity
		for (i = 0; i != 5; i++ ) {

			if ( ptrSystem->aPlanet[i] != 0xffff )
				if (aPlanets[ptrSystem->aPlanet[i]].nColonyID != 0xffff)
					nHwGravity = aPlanets[ptrSystem->aPlanet[i]].nPlanetGravity;
		}

		//Flatting HomeWorld
		for (i = 0; i != 5; i++ ) {

			if (ptrSystem->aPlanet[i] != 0xffff && aPlanets[ptrSystem->aPlanet[i]].nColonyID == 0xffff) {

				ptrPlanet = &aPlanets[ptrSystem->aPlanet[i]];

				//Make them abundant
				ptrPlanet->nMineralClass = 2;

				//Make toxics and radioactive barren
				if (ptrPlanet->nEnvClass < 2)
					ptrPlanet->nEnvClass = 2;

				//Make gaias terrain
				if (ptrPlanet->nEnvClass == 9) {

					ptrPlanet->nEnvClass = 8;
					ptrPlanet->nFoodBase = 2;
				}

				//Set Gravity & Size
				switch (nDonePlanets) {
					case 0: //Swamp
						ptrPlanet->nPlanetGravity = nHwGravity;
						ptrPlanet->nPlanetSize = LARGE;
					break;
					case 1: //Arid
						ptrPlanet->nPlanetGravity = NORMAL_G;
						ptrPlanet->nPlanetSize = LARGE;
					break;
					case 2: //Tundra
						if (nHwGravity == LOW_G)
							ptrPlanet->nPlanetGravity = LOW_G;
						else
							ptrPlanet->nPlanetGravity = NORMAL_G;

						ptrPlanet->nPlanetSize = LARGE;
					break;
					case 3: //Gaia
						if (nHwGravity == LOW_G)
							ptrPlanet->nPlanetGravity = LOW_G;
						else
							ptrPlanet->nPlanetGravity = NORMAL_G;

						ptrPlanet->nPlanetSize = SMALL;
					break;
				}

				//Make planet Enviroment Class fixed if we have to.
				if (flags & FLG_FIXEDHW) {

					if (nDonePlanets == 0) {

						ptrPlanet->nEnvClass = SWAMP;
						ptrPlanet->nFoodBase = 2;

					} else if (nDonePlanets == 1) {

						ptrPlanet->nEnvClass = ARID;
						ptrPlanet->nFoodBase = 1;

					} else if (nDonePlanets == 2) {

						ptrPlanet->nEnvClass = TUNDRA;
						ptrPlanet->nFoodBase = 1;
						ptrPlanet->nMineralClass = POOR;

					} else if (nDonePlanets == 3) {

						ptrPlanet->nEnvClass = GAIA;
						ptrPlanet->nFoodBase = 3;
						ptrPlanet->nMineralClass = POOR;
					}
				}

				nDonePlanets++;
			}
		}
	}
}

void balanceGalaxy(struct galaxy *galaxy) {

	int i;
	struct star *ptrHW;
	for (i = 0; i != 8; i++) {

		ptrHW = &galaxy->aStars[galaxy->aPlanets[galaxy->aPlayers[i].home_planet_id].nStarID];
		printf("%s; %s | x:%d y:%d;\n", galaxy->aPlayers[i].name, ptrHW->sName, ptrHW->nXpos, ptrHW->nYpos);
	}
}