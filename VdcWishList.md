# New Priority List (04.05.2015); previous upd (20/10/2014): #
  1. Fix TIME WARP FACILITATOR BUG: Phasing Cloak, Cloaking Device? and Black Hole Generator works incorrectly when TWF is present in combat;
  1. Fix Stasis Field mechanics - ships released from the stasis trap should be able to move in the round they were released; now they lose their turn until next round of combat;
  1. Make Phase Shifter jump range infinite - i.e. the whole battlefield;
  1. Make Quantum Detonator special an achievement - very high priority!
  1. Fix BHG bug - it should immobilize only in round 2.
  1. Make shield recharge special (i.e. multiphased shileds in VDC v55) an achievement - automatically installed on all ships;
  1. Find offsets for autorepair and cybernetic restoration percentages, especially for repairment of internals. Current values are 20 (10) and 10 (5) for structure and internals for autorepair and cybernetic respectively - partly done.
  1. Make Autorepair Unit an achievement - so that not required to put it as a special on a ship, but it works automatically, like cybernetic race. Definitely needed.
  1. Regeneration special (#39) find out if it can be used to repair destroyed internals and ship specials in combat.
  1. Add new interface features - 1)Add a function, which can copy building queue of one planet to all the rest planets;  2) Add an info output how much the planet got stored production (retrieve this number and display it); 3) Add an info output how many colonists a planet is expecting to arrive next turn; 4)Add an info output about remaining shield's hp; 5) Add possibility to save and load ship designs in ship construction window;
  1. Fix Autobuild function in a way to allow your own buildings priority list;
  1. Global FIX - Add ability to save (dump) combat data when it stalls (hangs) showing - waiting for opponent - message. Add ability to restore combat data by pressing a special key, for instance ALT+F12.
  1. Mutation Bug (desynch issue); - Done
  1. Feudal Bug (ships costs issue);
  1. Allow starbases to use all available modifications for the beams and torpedoes - actually level 1 mods will be enough!
  1. Star bases: add torpedoes instead of the missiles, when torpedo tech becomes available.
  1. Reprogram cost of androids in the following way: Farmers - 50 BC, Scientists - 75 BC, Workers - 100 BC.
  1. Increase the range for ground batteries installation and starbases - questionable.
  1. Disable enveloping mod of torpeodoes vs planets. i.e. it shouldn't multiply damage by 4 if torpedo got this mod installed. Explanation - how a torpedo can possibly envelop the whole planet?!!! addition: not only for torpedoes, but for stellar converter too! - ADDED damper field to planetary defense, working on fixing recharge issue of plsma torps;
  1. Add Hard Shields effect to class XX shield, so that it becomes naturally immune to SP effects and transporters;

---


> Implemented features
  1. Fix plasma torpedoes dissipation bug for the speed higher than 23(24). - partly fixed.
  1. Find offsets for the weapons miniaturization coefficients. - DONE.
  1. Fix bug with HEF to give correct bonuses to the different beam-mods.
  1. Fix Structural Analyzer bonus (decrease multiplier from 2.0 to 1.6); - DONE.
  1. Add to Sensors ability to decloak the stealth field and cloaking device equipped ships;   - DONE
  1. Weapons allocation percentage on starbases/battlestation/star fortresses. (Heavy mount is 25%, want to increase it);   - DONE
  1. Re-arrange Terafoming progressive cost for flat cost or even decreasing cost with cost multiplier=2/3 - DONE
  1. Reduce number of combat rounds from 50 to 20;  - DONE
  1. Disable requirement to click OK every time on raid confirmation window. Example: When you hit autobattle then when the same window pops up it stays for about 5-7 seconds, then AI removes it automatically. But when you are controlling your ships, you have to press OK or battle doesn't go futher from this point(opponent will see the screen: waiting for opponent message till it is confirmed by pressing OK button). Would be good if it was the same as in autobattle - message dissapeared automatically after a short pause, and no need for confirmation. - DONE.
  1. Increase the frequency of restoration of fighters in Fighter Garrison from 10 rounds to 3(or 4) rounds. -  DONE.
  1. Fix amount of fighters in replacement to full value after the first wave was partly destroyed and managed to get back to the base (it starts sending broken number of fighters after that).
  1. Find a way to seperate cost of building of Androids (50 pp)from the cost of freighters, since they use the same offset. - DONE
  1. Make the Antarans attack earlier. There is almost certainly a delay that has been set to stop them attacking before approx. turn 180  - DONE
  1. Find Scanners bonuses for reducing missile evasion: tachyon scanner -20; neutronium scanner -40; sensors -70.  - DONE
  1. Find the Leaders offering time matrix; - DONE
  1. Tractor beams. Fix number of beams required to stop different classes of ships in the following manner: Num of beams=2^class; remove miniaturization to tractor beams.- DONE.
  1. Raid. Raid calculations. Bugs with the raid: desynch on raiding starbase with no marines (killed by neutron blaster); Zero Marines Raid bug (game stalls in MP, when you raid with zero marines); - partly Done.
  1. AI ship designing; weapons allocation on AI ships in %, defining specials for the AI ships to be placed invariably, when they are available  - DONE;
  1. Telepathy- Fix telepathy skills of the leaders (adds wrong bonus); - DONE.
  1. Add New type of planetary defense fields - Planetary Damper Field, which would be given additionally to Damper field technology (2 in 1). Planetary Damper field would reduce damage against planet by 3/4. - DONE


---


