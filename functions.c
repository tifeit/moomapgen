#include "mapgen.h"

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
			switch (ptrPlanet->nPlanetGravity) {

			case 0: //LowG
				printf("nPlanetGravity: %.2X\n", 1);
				break;
			case 1: //NormalG
				printf("nPlanetGravity: %.2X\n", 0);
				break;
			case 2: //HeavyG
				printf("nPlanetGravity: %.2X\n", 2);
				break;
			}
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

		if ((flags & FLG_NOTOXIC) && aPlanets[i].nEnvClass == 0)
			aPlanets[i].nEnvClass = 1;

		if ((flags & FLG_NOUPOOR) && aPlanets[i].nMineralClass == 0)
			aPlanets[i].nMineralClass = 2;

		if ((flags & FLG_NOLG) && aPlanets[i].nPlanetGravity == 0) {
			if (aPlanets[i].nColonyID == 0xffff)
				aPlanets[i].nPlanetGravity = 1;
		}

		if ((flags & FLG_NOHG) && aPlanets[i].nPlanetGravity == 2)
			if (aPlanets[i].nColonyID == 0xffff)
			aPlanets[i].nPlanetGravity = 1;

		if ((flags & FLG_NOTINY) && aPlanets[i].nPlanetSize == 0) {

			if (flags & FLG_NOSMALL)
				aPlanets[i].nPlanetSize = 2;

			else {

				srand(time(NULL));
				aPlanets[i].nPlanetSize = rand() % 4 + 1;
			}
		}

		if ((flags & FLG_NOSMALL) && aPlanets[i].nPlanetSize == 1)
			aPlanets[i].nPlanetSize = 2;

		if (specialsFlags) {

			if ((specialsFlags & FLG_SPLINT) && aPlanets[i].nPlanetSpecial == SPLINTER_COLONY) {

				aStarSystems[aPlanets[i].nStarID].nSpecial = GEM_DEPOSITS; //Setting gem flag to star.
				aPlanets[i].nPlanetSpecial = GEM_DEPOSITS; //Setting gem flag to planet.

				if (verbose) printf("%s | Splinter\n", aStarSystems[aPlanets[i].nStarID].sName);
			}

			if ((specialsFlags & FLG_NONATIVES) && aPlanets[i].nPlanetSpecial == NATIVES) {

				aStarSystems[aPlanets[i].nStarID].nSpecial = GOLD_DEPOSITS; //Setting gold flag to star.
				aPlanets[i].nPlanetSpecial = GOLD_DEPOSITS; //Setting gold flag to planet.

				if (verbose) printf("%s | Natives\n", aStarSystems[aPlanets[i].nStarID].sName);
			}

			if ((specialsFlags & FLG_ARTI) && aPlanets[i].nPlanetSpecial == ANCIENT_ARTIFACTS) {

				aStarSystems[aPlanets[i].nStarID].bArtifactsGaveApp = 1;

				if (verbose) printf("%s | Arti\n", aStarSystems[aPlanets[i].nStarID].sName);
			}
		}

		if ((monsterFlags & FLG_LEADERS) && aStarSystems[aPlanets[i].nStarID].nSpecial == MAROONED_HERO) {

			aStarSystems[aPlanets[i].nStarID].nSpecial = PIRATE_CACHE;

			if (verbose) printf("%s | Marooned hero\n", aStarSystems[aPlanets[i].nStarID].sName);
		}
	}

	if (monsterFlags) {

		unsigned char location = 0;

		for (i = 0; i != MAX_SHIPS; i++) {

			//Search for monster ships
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

									ptrPlanet->nFoodBase = 1;
									ptrPlanet->nEnvClass = TUNDRA;

									if (verbose) printf("%s | Monster Terraform\n", aStarSystems[aShips[i].location].sName);

								}
							}
						}
					}
				}

				if ((monsterFlags & FLG_LEADERS) && (aStarSystems[location].nSpecial == PIRATE_CACHE || aStarSystems[location].nSpecial == SPACE_DEBRIS)) {
					aStarSystems[location].nSpecial = MAROONED_HERO;
					if (verbose) printf("%s | Pirate cache or debris\n", aStarSystems[aShips[i].location].sName);
				}
			}
		}
	}
}

void modifyHW(struct galaxy *galaxy, unsigned int flags) {

	unsigned char i, j, nDonePlanets = 0, nHwGravity;
	struct planet *ptrPlanet;
	struct star *ptrSystem;

	for (j = 0; j != *galaxy->nNumOfPlayers; j++, nDonePlanets = 0) {

		ptrSystem = &galaxy->aStars[galaxy->aPlanets[galaxy->aPlayers[j].home_planet_id].nStarID];

		//Finding HomeWorld planet gravity
		for (i = 0; i != 5; i++ ) {

			if ( ptrSystem->aPlanet[i] != 0xffff )
				if (galaxy->aPlanets[ptrSystem->aPlanet[i]].nColonyID != 0xffff)
					nHwGravity = galaxy->aPlanets[ptrSystem->aPlanet[i]].nPlanetGravity;
		}

		//Flatting HomeWorld
		for (i = 0; i != 5; i++ ) {

			if (ptrSystem->aPlanet[i] != 0xffff && galaxy->aPlanets[ptrSystem->aPlanet[i]].nColonyID == 0xffff) {

				ptrPlanet = &galaxy->aPlanets[ptrSystem->aPlanet[i]];

				if ((flags & FLG_FLATHW) || (flags & FLG_FIXEDHW)) {

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
						case 3: //Terrain
							if (nHwGravity == LOW_G)
								ptrPlanet->nPlanetGravity = LOW_G;
							else
								ptrPlanet->nPlanetGravity = NORMAL_G;

							ptrPlanet->nPlanetSize = MEDIUM;
						break;
					}
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

						ptrPlanet->nEnvClass = TERRAN;
						ptrPlanet->nFoodBase = 2;
						ptrPlanet->nMineralClass = POOR;

					}
				}

				//Makes last planet gaia if we have to.
				if (flags & FLG_GAIA) {

					if (nDonePlanets == 3) {

						if (galaxy->aPlayers[j].creative || galaxy->aPlayers[j].aquatic || galaxy->aPlayers[j].environment_immune) {

							ptrPlanet->nEnvClass = TERRAN;
							ptrPlanet->nFoodBase = 2;
							ptrPlanet->nMineralClass = POOR;

						} else {

							ptrPlanet->nEnvClass = GAIA;
							ptrPlanet->nFoodBase = 3;
							ptrPlanet->nMineralClass = POOR;
							ptrPlanet->nPlanetSize = SMALL;
						}
					}
				}

				//Make first planet rich if we have to.
				if (flags & FLG_RICHHW) {

					if (nDonePlanets == 0) {

						ptrPlanet->nMineralClass = RICH;
					}
				}

				//Make first planet huge if we have to.
				if (flags & FLG_HUGEHW) {

					if (nDonePlanets == 0) {

						ptrPlanet->nPlanetSize = HUGEPLANET;
					}
				}

				//Make first planet good if we have to.
				if (flags & FLG_GOODHW) {

					if (nDonePlanets == 0) {

						ptrPlanet->nEnvClass = TERRAN;
						ptrPlanet->nFoodBase = 2;
					}
				}

				nDonePlanets++;
			}
		}
	}
}

void balanceGalaxy(struct galaxy *galaxy, unsigned int balanceFlags, int rings) {

	int i, j, k, l, sum, parsec, capModifier, raceSpecial, raceGravity, numOfPlanets, rangeFromHW, z, monster, government;
	struct star *ptrHW[8], *ptrStar;
	struct planet *ptrPlanet[5];

	int aPlanetWeight[10][5];

	FILE *fpWeight, *fpCsv;

	char str[100];


	fpWeight = fopen("mgweight.txt", "rb");
	fpCsv = fopen("autosave.csv", "w");

	if (fpCsv != NULL) {
		fprintf(fpCsv,"player number; government; capacity modifier; race special; race gravity; star name; number of planets; range from hw; monster; special;"
		"planet 1 size; planet 1 climate; planet 1 richness; planet 1 gravity;planet 1 special;"
		"planet 2 size; planet 2 climate; planet 2 richness; planet 2 gravity;planet 2 special;"
		"planet 3 size; planet 3 climate; planet 3 richness; planet 3 gravity;planet 3 special;"
		"planet 4 size; planet 4 climate; planet 4 richness; planet 4 gravity;planet 4 special;"
		"planet 5 size; planet 5 climate; planet 5 richness; planet 5 gravity;planet 5 special;\n");

	} else {

		fprintf(stderr, "Can not open autosav.csv");
		exit(1);
	}

	if (fpWeight == NULL) {

		fprintf(stderr, "Can not open mgweight.txt");
		exit(1);

	} else {

		fgets(str, 100, fpWeight); //skip line
		for (i = 0; i != 10; i++) {

			fgets(str, 100, fpWeight);
			sscanf(str, "%*s %d %d %d %d %d", &aPlanetWeight[i][0], &aPlanetWeight[i][1], &aPlanetWeight[i][2], &aPlanetWeight[i][3], &aPlanetWeight[i][4]);
		}
	}

	for (i = 0; i != 8; i++) {

		if (galaxy->aPlayers[i].home_planet_id == 0)
			continue;

		ptrHW[i] = &galaxy->aStars[galaxy->aPlanets[galaxy->aPlayers[i].home_planet_id].nStarID];
	}

	for (i = 0; i != 8; i++) {

		if (galaxy->aPlayers[i].home_planet_id == 0)
			continue;

		/*printf("%s Aquatic: %d Subterr: %d Tolerant: %d Cyber: %d %s\n", galaxy->aPlayers[i].race_name,
				galaxy->aPlayers[i].aquatic,
				galaxy->aPlayers[i].subterranean,
				galaxy->aPlayers[i].environment_immune,
				galaxy->aPlayers[i].cybernetic,
				ptrHW->sName);*/

		for (j = 0; j!=MAX_SYSTEMS; j++) {

			ptrStar = &galaxy->aStars[j];
			if (ptrStar->sName[0] == 0 /*|| ptrStar == ptrHW*/)
				continue;

			sum = (ptrHW[i]->nXpos - ptrStar->nXpos)*(ptrHW[i]->nXpos - ptrStar->nXpos) +
				(ptrHW[i]->nYpos - ptrStar->nYpos)*(ptrHW[i]->nYpos - ptrStar->nYpos);

			parsec = (int)sqrt(sum/900);

			if (parsec*900 < sum) parsec++;

			if (parsec <= 15) {

				for (k = 0, numOfPlanets = 0; k != 5; k++) {

					ptrPlanet[k] = NULL;

					if (ptrStar->aPlanet[k] == 0xffff) {
						continue;
					}

					numOfPlanets++;

					ptrPlanet[k] = &galaxy->aPlanets[ptrStar->aPlanet[k]];

					//points+=aPlanetWeight[ptrPlanet->nEnvClass][ptrPlanet->nPlanetSize];

				}

				capModifier = 0;
				capModifier |= galaxy->aPlayers[i].aquatic ? 1 : 0;
				capModifier |= galaxy->aPlayers[i].subterranean ? 2 : 0;
				capModifier |= galaxy->aPlayers[i].environment_immune ? 4 : 0;

				raceSpecial = 1;
				if (galaxy->aPlayers[i].eats_minerals)
					raceSpecial = 0;
				if (galaxy->aPlayers[i].cybernetic)
					raceSpecial = 2;
				government = galaxy->aPlayers[i].current_government;
        
				raceGravity = 0;

				if (galaxy->aPlayers[i].low_g_world)
					raceGravity = -1;

				if (galaxy->aPlayers[i].heavy_g_world)
					raceGravity = 1;

				if ((balanceFlags & FLG_RING) && rings >= parsec )
					ptrStar->nVisited |= (char)pow(2,i);

				if (parsec == 0) rangeFromHW = 0;

				else if ( parsec !=0 && parsec <= 6) {
					rangeFromHW = 1;
				}

				else if (parsec > 6 && parsec <= 10) rangeFromHW = 2;
				else if (parsec > 11 && parsec <= 14) rangeFromHW = 3;
				else if (parsec == 15) rangeFromHW = 4;

				for (l = 0; l != 8; l++) {

					if (i == l) continue;

					if (galaxy->aPlayers[l].home_planet_id == 0)
						continue;

					sum = (ptrHW[l]->nXpos - ptrStar->nXpos)*(ptrHW[l]->nXpos - ptrStar->nXpos) +
						(ptrHW[l]->nYpos - ptrStar->nYpos)*(ptrHW[l]->nYpos - ptrStar->nYpos);

					parsec = (int)sqrt(sum/900);

					if (parsec*900 < sum) parsec++;

					if (parsec <= 20) {

						rangeFromHW = 4;
					}

				}

				monster = 0;
				for (z = 0; z != MAX_SHIPS; z++) {

					if (galaxy->aShips[z].d.name[0] != 0 && galaxy->aShips[z].owner > 8 && galaxy->aShips[z].location == j) {

						monster = 1;
					}
				}

				fprintf(fpCsv,"%d;%d;%d;%d;%d;%s;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;\n",
						i, //player number
						government, //race government
						capModifier, //capacify modifier
						raceSpecial, //race special
						raceGravity, //race gravity
						ptrStar->sName, //star name
						numOfPlanets, //number of planets
						rangeFromHW, //range from hw
						monster, //monster
						ptrStar->nSpecial, //special
						ptrPlanet[0] != NULL ? ptrPlanet[0]->nPlanetSize : 0, //planet 1 climate
						ptrPlanet[0] != NULL ? ptrPlanet[0]->nEnvClass : 0, //planet 1 climate
						ptrPlanet[0] != NULL ? ptrPlanet[0]->nMineralClass : 0, //planet 1 richness
						ptrPlanet[0] != NULL ? ptrPlanet[0]->nPlanetGravity : 0, //planet 1 gravity
						ptrPlanet[0] != NULL ? ptrPlanet[0]->nPlanetSpecial :0, //planet special

						ptrPlanet[1] != NULL ? ptrPlanet[1]->nPlanetSize : 0, //planet 1 climate
						ptrPlanet[1] != NULL ? ptrPlanet[1]->nEnvClass : 0, //planet 1 climate
						ptrPlanet[1] != NULL ? ptrPlanet[1]->nMineralClass : 0, //planet 1 richness
						ptrPlanet[1] != NULL ? ptrPlanet[1]->nPlanetGravity : 0, //planet 1 gravity
						ptrPlanet[1] != NULL ? ptrPlanet[1]->nPlanetSpecial :0, //planet special

						ptrPlanet[2] != NULL ? ptrPlanet[2]->nPlanetSize : 0, //planet 1 climate
						ptrPlanet[2] != NULL ? ptrPlanet[2]->nEnvClass : 0, //planet 1 climate
						ptrPlanet[2] != NULL ? ptrPlanet[2]->nMineralClass : 0, //planet 1 richness
						ptrPlanet[2] != NULL ? ptrPlanet[2]->nPlanetGravity : 0, //planet 1 gravity
						ptrPlanet[2] != NULL ? ptrPlanet[2]->nPlanetSpecial :0, //planet special

						ptrPlanet[3] != NULL ? ptrPlanet[3]->nPlanetSize : 0, //planet 1 climate
						ptrPlanet[3] != NULL ? ptrPlanet[3]->nEnvClass : 0, //planet 1 climate
						ptrPlanet[3] != NULL ? ptrPlanet[3]->nMineralClass : 0, //planet 1 richness
						ptrPlanet[3] != NULL ? ptrPlanet[3]->nPlanetGravity : 0, //planet 1 gravity
						ptrPlanet[3] != NULL ? ptrPlanet[3]->nPlanetSpecial :0, //planet special

						ptrPlanet[4] != NULL ? ptrPlanet[4]->nPlanetSize : 0, //planet 1 climate
						ptrPlanet[4] != NULL ? ptrPlanet[4]->nEnvClass : 0, //planet 1 climate
						ptrPlanet[4] != NULL ? ptrPlanet[4]->nMineralClass : 0, //planet 1 richness
						ptrPlanet[4] != NULL ? ptrPlanet[4]->nPlanetGravity : 0, //planet 1 gravity
						ptrPlanet[4] != NULL ? ptrPlanet[4]->nPlanetSpecial :0 //planet special
				);

				//printf("System: %s Parsec: %d Points: %d\n", galaxy->aStars[j].sName, parsec, points);
			}
			//totalPoints += points;
		}
		//printf("Total points: %d\n", totalPoints);
	}
	fclose(fpWeight);
	fclose(fpCsv);
	return;
}

void mergeGalaxies(struct galaxy *galaxies, unsigned char nFiles) {

	//We start from the first player, to reorder first player's colonies/ships etc. so that his ones go first in array
	unsigned char i = 0; //Player
	unsigned int j = 0; //Iterator for current player's galaxy
	unsigned int c = 0; //Iterator for first player's colonies
	unsigned int l = 0; //Iterator for first player's leaders
	unsigned int s = 0; //Iterator for first player's ships
	//Getting data
	do {

		printf("Merging player: %s\n", galaxies[i].aPlayers[i].name);

		/*What to merge:
		 * galaxy->current_colony_count
		 * aPlayers
		 * aColonies + respective planets
		 * aShips
		 * aLeaders
		*/

		//The simplest one
		galaxies[0].aPlayers[i] = galaxies[i].aPlayers[i];

		//Go through all colonies array
		for (j = 0; j != MAX_COLONIES; j++) {

			//If we find colony, that  belong to current player, we should copy it to first player's galaxy
			if (galaxies[i].aColonies[j].owner == i) {

				//Replace first available colony
				galaxies[0].aColonies[c++] = galaxies[i].aColonies[j];
				//Copy this colony planet
				galaxies[0].aPlanets[galaxies[i].aColonies[j].planet] = galaxies[i].aPlanets[galaxies[i].aColonies[j].planet];
			}
		}

		//Go through all ships array
		for (j = 0; j != MAX_SHIPS; j++) {

			//If we find colony, that  belong to current player, we should copy it to first player's galaxy
			if (galaxies[i].aShips[j].owner == i) {

				//Replace first available ship
				galaxies[0].aShips[s++] = galaxies[i].aShips[j];
			}
		}

		//Go through all leaders array
		for (j = 0; j != MAX_LEADERS; j++) {

			//If we find colony, that  belong to current player, we should copy it to first player's galaxy
			if (galaxies[i].aLeaders[j].player_index == i) {

				//Replace first available ship
				galaxies[0].aLeaders[l++] = galaxies[i].aLeaders[j];
			}
		}

		galaxies[0].current_colony_count = c;

	} while (++i != nFiles);

	galaxies[0].game_type = 2;
}


