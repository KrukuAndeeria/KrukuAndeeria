-- Utgarde Pinnacle

-- Svala Sorrowgrave
UPDATE creature_template SET ScriptName='npc_ritual_channeler' WHERE entry=27281;
-- Gortok Palehoof
UPDATE gameobject_template SET ScriptName='go_gortok_generator' WHERE entry=188593;
UPDATE creature_template SET ScriptName='npc_gortok_orb' WHERE entry=26086; -- 26688
UPDATE creature_template SET ScriptName='npc_worgen' WHERE entry=26683;
UPDATE creature_template SET ScriptName='npc_furlborg' WHERE entry=26684;
UPDATE creature_template SET ScriptName='npc_jormungar' WHERE entry=26685;
UPDATE creature_template SET ScriptName='npc_rhino' WHERE entry=26686;
-- Skadi the Ruthless
UPDATE gameobject_template SET ScriptName='go_skadi_harpoon_launcher', flags=flags|4 WHERE entry IN (192175, 192176, 192177);
UPDATE gameobject_template SET ScriptName='go_skadi_harpoon' WHERE entry=192539;
UPDATE creature_template SET ScriptName='boss_grauf' WHERE entry=26893;
-- King Ymiron
UPDATE creature_template SET ScriptName='npc_bjorn_sphere' WHERE entry = 27339;
UPDATE creature_template SET ScriptName='npc_avenging_spirit_summoner' WHERE entry = 27392;

REPLACE INTO spell_script_target (entry, type, targetEntry) values
(48277, 1, 27327),
(48331, 1, 27327),
(48642, 1, 26893),
(51368, 1, 26893),
(47670, 1, 26687),
(47670, 1, 26684),
(47670, 1, 26683),
(47670, 1, 26685),
(47670, 1, 26686),
(48385, 1, 27339);

-- vehicle data for Grauf
UPDATE creature_template SET VehicleEntry=40 WHERE entry IN (26893, 30775);

-- immune masks (charm, fear, root, silence, sleep, snare, stun, freeze, knockout, polymorph, banish, shackle, horror, sapped)
UPDATE creature_template SET mechanic_immune_mask=mechanic_immune_mask|1|16|64|256|512|1024|2048|4096|8192|65536|131072|524288|8388608|536870912
WHERE entry IN (26668,26687,26693,26861,30810,30774,30807,30788);

###### Emblem of Herosim ######
# Svala Sorrowgrave 30810
DELETE FROM creature_loot_template WHERE entry=30810 AND item=40752;
INSERT INTO creature_loot_template VALUES
(30810, 40752, 100, 5, 1, 1, 0, 0, 0);
# Gortok Palehoof 30774
DELETE FROM creature_loot_template WHERE entry=30774 AND item=40752;
INSERT INTO creature_loot_template VALUES
(30774, 40752, 100, 5, 1, 1, 0, 0, 0);
# Skadi the Ruthless 30807
DELETE FROM creature_loot_template WHERE entry=30807 AND item=40752;
INSERT INTO creature_loot_template VALUES
(30807, 40752, 100, 5, 1, 1, 0, 0, 0);
# King Ymiron 30788
DELETE FROM creature_loot_template WHERE entry=30788 AND item=40752;
INSERT INTO creature_loot_template VALUES
(30788, 40752, 100, 5, 1, 1, 0, 0, 0);

-- Restored Skadi, Grauf and door spawn :)
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(65440, 192173, 575, 3, 1, 477.496, -477.183, 103.064, -1.58825, 0, 0, -0.71325, 0.700909, 180, 0, 1);
REPLACE INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(126103, 26693, 575, 3, 1, 0, 0, 343.02, -507.325, 104.567, 2.96706, 86400, 0, 0, 1260000, 0, 0, 0),
(126052, 26893, 575, 3, 1, 0, 0, 341.741, -516.955, 104.669, 3.12414, 3600, 0, 0, 1260000, 0, 0, 0);



