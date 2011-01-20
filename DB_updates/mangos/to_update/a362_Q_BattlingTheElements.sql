-- Q: Battling the Elements

-- See Quest Invisibility
DELETE FROM spell_area WHERE spell = 61209;
INSERT INTO spell_area VALUES
(61209, 4495, 12967,1,0,0,0,2,1); -- Fjorn's Anvil

-- Kill Credit for Forging the Alliance after completing Battling the Elements
DELETE FROM quest_end_scripts WHERE id = 12967;
INSERT INTO quest_end_scripts VALUES
(12967, 0, 15, 55960, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Kill Credit for Forging the Alliance after completing Battling the Elements");

-- Seething Revenants spawns
DELETE FROM creature WHERE id = 30387;
INSERT INTO creature (id, map, spawnMask, phaseMask, equipment_id, position_x, position_y, position_z, orientation, spawndist, curhealth, MovementType) VALUES
(30387, 571, 1, 1, 0, 7191.64, -3669.66, 823.597, 5.67107, 30, 12600, 1),
(30387, 571, 1, 1, 0, 7201.64, -3660.66, 823.597, 3.67107, 30, 12600, 1),
(30387, 571, 1, 1, 0, 7208.64, -3650.66, 823.597, 2.67107, 30, 12600, 1),
(30387, 571, 1, 1, 0, 7211.64, -3655.66, 823.597, 5.67107, 30, 12600, 1),
(30387, 571, 1, 1, 0, 7226.64, -3652.66, 823.597, 1.67107, 30, 12600, 1),
(30387, 571, 1, 1, 0, 7228.64, -3679.66, 823.597, 2.67107, 30, 12600, 1),
(30387, 571, 1, 1, 0, 7201.64, -3669.66, 823.597, 5.67107, 30, 12600, 1),
(30387, 571, 1, 1, 0, 7210.64, -3647.66, 823.597, 5.67107, 30, 12600, 1),
(30387, 571, 1, 1, 0, 7205.64, -3641.66, 823.597, 4.67107, 30, 12600, 1),
(30387, 571, 1, 1, 0, 7221.64, -3635.66, 823.597, 5.67107, 30, 12600, 1),
(30387, 571, 1, 1, 0, 7231.64, -3672.66, 823.597, 6.67107, 30, 12600, 1),
(30387, 571, 1, 1, 0, 7221.64, -3639.66, 823.597, 3.67107, 30, 12600, 1),
(30387, 571, 1, 1, 0, 7232.64, -3665.66, 823.597, 2.67107, 30, 12600, 1),
(30387, 571, 1, 1, 0, 7228.64, -3660.66, 823.597, 5.67107, 30, 12600, 1),
(30387, 571, 1, 1, 0, 7222.64, -3649.66, 823.597, 4.67107, 30, 12600, 1);

DELETE FROM creature_template_addon WHERE entry = 30387;
INSERT INTO creature_template_addon VALUES
(30387, 0, 0, 1, 0, 0, 0, 0, "", "61208 0 61209 0");

-- problems with targeting faction
UPDATE creature_template SET faction_A = 190, faction_H = 190 WHERE entry = 30387;

DELETE FROM creature_ai_scripts WHERE id = 3038702;
INSERT INTO creature_ai_scripts VALUES
(3038702, 30387, 6, 0, 100, 1, 0, 0, 0, 0, 33, 30125, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Seething Revenant - Kill Credit upon death");

-- vehicle info:
UPDATE creature_template SET faction_A = 1080, faction_H = 1080 WHERE entry = 30124;
DELETE FROM creature_template_addon WHERE entry = 30124;
INSERT INTO creature_template_addon VALUES
(30124, 0, 0, 1, 0, 0, 0, 176, "", "61208 0 61209 0");

DELETE FROM npc_spellclick_spells WHERE npc_entry = 30123;
INSERT INTO npc_spellclick_spells VALUES (30123, 55957, 12967, 1, 12967, 3);

DELETE FROM vehicle_data WHERE entry = 176;
INSERT INTO vehicle_data VALUES (176, 4|8, 56750, 56753, 0, 0, 56752, 0, 0, 0, 0, 0, 0);

DELETE FROM vehicle_seat_data WHERE seat IN (2072, 2073, 2074, 2075);
INSERT INTO vehicle_seat_data VALUES
(2072, 3),
(2073, 2),
(2074, 2),
(2075, 2);
