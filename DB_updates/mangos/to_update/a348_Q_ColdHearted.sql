-- Cold Hearted
-- flying Captive Drakes - summon freed drake - vehicle
UPDATE creature_template SET IconName = "vehichleCursor" WHERE entry = 29708;

UPDATE creature_template SET ScriptName = "mob_brunnhildar_prisoner" WHERE entry = 29639;

REPLACE INTO creature_template_addon VALUES
(29709, 0, 50331648, 1, 0, 0, 1024, 194, "", "48602 0 48602 2");

DELETE FROM spell_script_target WHERE entry = 55046;
INSERT INTO spell_script_target VALUES (55046, 1, 29639);

DELETE FROM npc_spellclick_spells WHERE npc_entry = 29708;
INSERT INTO npc_spellclick_spells VALUES (29708, 55028, 12856, 1, 12856, 3);

DELETE FROM vehicle_data WHERE entry = 194;
INSERT INTO vehicle_data VALUES (194, 4|8, 55046, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM vehicle_seat_data WHERE seat IN (2102, 2113, 2108, 2115);
INSERT INTO vehicle_seat_data VALUES
(2102, 1),
(2113, 0),
(2108, 0),
(2115, 0);
