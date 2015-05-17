#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

// Outputs variable in hexademical form.
void tohex(void *string, unsigned int length);

// Outputs star system contents.
void printSystem(struct star* starSystem, struct planet *aPlanets);

// Reads SAVE file.
void getFileData(void *storage, unsigned long length, unsigned long offset, FILE *fp);

//Finds Homeworld's coordinates.
void getHwCoords(struct star *aStarSystems, unsigned int aHwCoordinates[][3], unsigned char nNumOfStars, struct planet *aPlanets);

//Terraforms planets according to given flags.
void terraform(struct star *aStarSystems, struct planet *aPlanets, struct ship *aShips, unsigned short nPlanets, unsigned short nStars,
	unsigned int flags, unsigned int splinterFlags, unsigned int monsterFlags);

//Terraforms homeworld according to given flags.
void modifyHW(struct galaxy *galaxy, unsigned int flags);

//BalanceGalaxy.
void balanceGalaxy(struct galaxy *galaxy, unsigned int balanceFlags, int rings);

//Merge provided galaxies
void mergeGalaxies(struct galaxy *galaxies, unsigned char nFiles, struct galaxyHeader *galaxyHeader);

#endif /*FUNCTIONS_H_*/
