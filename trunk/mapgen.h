#define MAX_SYSTEMS 72
#define MAX_PLANETS 360
#define MAX_PLAYERS 8
#define STAR_OFFSET 0x17ad3
#define PLANET_OFFSET 0x162e9
#define NUM_OF_STARS_OFFSET 0x17ad1
#define NUM_OF_PLANETS_OFFSET 0x162e7
#define NUM_OF_PLAYERS_OFFSET 0x1aa0c

#define FLG_NOTOXIC		1
#define FLG_NOUPOOR		2
#define FLG_NOLG		4
#define FLG_NOHG		8
#define FLG_NOTINY		16
#define	FLG_NOSMALL		32

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "struct.h"
#include "functions.c"

