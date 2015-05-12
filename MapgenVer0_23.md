
```
Usage: ./mapgen [-h] [-t terraformation] [-s special] [-m change] [-b type] [-v] [-V] [-f file]

Example: ./mapgen -t toxic -t upoor -t lowg -t heavyg -t tiny -t small -f SAVE10.GAM

Options:
  -h [-H] This help.

  -t Terraform
      toxic - Toxic planets become radiated
      upoor - Ultra Poor planets become poor
      lowg - Low Gravity planets become Normal Gravity
      heavyg - Heavy Gravity planets become Normal Gravity
      tiny - Tiny planets become small
      small - Small planets become medium
      flathw - Flattens unoccupied planets in HomeWorlds:
        They become Abundant, Toxics and Rads become Barren,
        gravity become Normal except for one planet,
        it become the same gravity as occupied planet, size is set in order
        Large, Large again, Medium, Small untill
        there are no more planets to modify. Gaias become Terrain.
      fixedhw - Implies `flathw`. Planets become:
        Large Swamp, Large Tundra, Medium Arid, Small Gaia. All abundant.

  -s Specials Change
      splint - Splinter replaced by gem deposits.
      arti - Arti planets still exist, but don't give techs anymore.

  -m Monsters Change
      grav - Guarded planets become normal gravity if they are not ultrarich.
      terraform - Guarded rich & urich planets are terraformed.
        Toxics, Rads, Barrens, Deserts become Tundra.
      monst - Does the same thing as -mgrav and -mterraform.

  -v Verbose debugging output(CHEAT!)

  -V Print Version and exit

  -f file Edit 'file' instead of SAVE10.GAM
```