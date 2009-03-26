void tohex(void *string, unsigned int length) {
	unsigned char i;
	unsigned char buff[2];
	unsigned char *point;

	point = string;

	for (i = 0; i != length; i++) {

		printf("%.2X ", *point++);
	}
	printf("\n");
}

void printSystem(struct starSystem* starSystem) {
	
	printf("%s (%d, %d) Size: %d Owner: %d nUnknown: %d nStarType: %d\n", starSystem->sName, starSystem->nXpos, starSystem->nYpos,
		starSystem->nSize, starSystem->nOwner, starSystem->nUnknown, starSystem->nStarType);
	tohex(starSystem->sUnknown, sizeof starSystem->sUnknown);
	tohex(starSystem->sUnknown2, sizeof starSystem->sUnknown2);
	tohex(starSystem->sUnknown3, sizeof starSystem->sUnknown3);
	tohex(starSystem->sUnknown4, sizeof starSystem->sUnknown4);
	tohex(starSystem->sUnknown5, sizeof starSystem->sUnknown5);

}

struct starSystem createStarSystem(int i) {

	struct starSystem star;
	unsigned char c = 0;

	sprintf(star.sName, "Star_%d", i);
	star.nXpos = 1+rand()%300;
	star.nYpos = 1+rand()%300;
	star.nSize = rand()%3;
	star.nOwner = 0;
	star.nStarType = 0;
	star.nSpecial = 0;
	star.nWormSystem = 0xff;
	star.nWarpIdict = 0;
	star.nArtemisNet = 0;
	star.aPlanet[0] = star.aPlanet[1]=star.aPlanet[2]=star.aPlanet[3]=star.aPlanet[4]=0xffff;
		
	//Fill unknown with nulls
	star.nUnknown = 0x00;
	for (c=0; c!=17; c++) star.sUnknown[c] = 0;
	for (c=0; c!=15; c++) star.sUnknown2[c] = 15;
	for (c=0; c!=5; c++) star.sUnknown3[c] = 5;
	for (c=0; c!=10; c++) star.sUnknown4[c] = 10;
	for (c=0; c!=29; c++) star.sUnknown5[c] = 29;


	return star;
}

void getFileData(void *storage, unsigned long length, unsigned long offset, FILE *fp) {

	fseek(fp, offset, SEEK_SET);
	fread(storage, length, 1, fp);
}

void calcPlanetsNum(struct starSystem *aStarSystems, unsigned int aHwCoordinates[][3], unsigned char nNumOfStars) {

	unsigned char i;

	//Finding HomeWorlds
	for (i = 0; i != nNumOfStars; i++) {

		if(aStarSystems[i].sUnknown2[13] != 0xff) {
			aHwCoordinates[aStarSystems[i].sUnknown2[13]][0] = aStarSystems[i].nXpos;
			aHwCoordinates[aStarSystems[i].sUnknown2[13]][1] = aStarSystems[i].nYpos;
			aHwCoordinates[aStarSystems[i].sUnknown2[13]][2] = i;
		}
	}
}

void terraform(struct planet *aPlanets, unsigned short nPlanets, unsigned int flags) {

	unsigned int i;
		
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
	}
}

void modifyHW(struct planet *aPlanets, struct starSystem* ptrSystem, unsigned int nSystemID, unsigned int flags) {
	
	unsigned char i, nDonePlanets = 0, nHwGravity;
	struct planet *aHwPlanets;
	struct planet *ptrPlanet;
	char nSetGravity = 0;

	if (flags & FLG_FLATHW) {


		//Finding HomeWorld planet gravity
		for ( i = 0; i != 5; i++ ) {
		
			if ( ptrSystem->aPlanet[i] != 0xffff )
				if (aPlanets[ptrSystem->aPlanet[i]].nColonyID != 0xffff)
					nHwGravity = aPlanets[ptrSystem->aPlanet[i]].nPlanetGravity;
		}

		//Flatting HomeWorld
		for ( i = 0; i != 5; i++ ) {
		
			if (ptrSystem->aPlanet[i] != 0xffff && aPlanets[ptrSystem->aPlanet[i]].nColonyID == 0xffff) {
				
				ptrPlanet = &aPlanets[ptrSystem->aPlanet[i]];

				//Make them abundant
				ptrPlanet->nMineralClass = 2;

				//Make toxics and radioactive barren
				if (ptrPlanet->nEnvClass < 2)
					ptrPlanet->nEnvClass = 2;

				//Set Gravity
				if (!nSetGravity) {
					ptrPlanet->nPlanetGravity = nHwGravity;
					nSetGravity = 1;
				}
				else
					ptrPlanet->nPlanetGravity = 1;

				//Set Size
				if (nDonePlanets == 0 || nDonePlanets == 1)
					ptrPlanet->nPlanetSize = 3;
				else if (nDonePlanets == 2)
					ptrPlanet->nPlanetSize = 2;
				else
					ptrPlanet->nPlanetSize = 1;
				nDonePlanets++;
			}
		}
	}
}
