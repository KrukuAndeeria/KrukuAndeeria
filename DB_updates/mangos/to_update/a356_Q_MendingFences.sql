-- Q: Mending Fences

UPDATE creature_template SET minhealth = 12600, maxhealth = 12600, minmana = 7988, maxmana = 7988, minlevel = 80, maxlevel = 80, faction_A = 2107, faction_H = 2107 WHERE entry = 29927;

DELETE FROM spell_area WHERE spell IN (55012, 72914) AND area IN (4439, 4495);
INSERT INTO spell_area VALUES
-- Frostfield Lake
(55012, 4439, 12841,0,0,0,0,2,1),
(72914, 4439, 12841,0,0,0,0,2,1),
-- Fjorn's Anvil
(55012, 4495, 12841,0,0,0,0,2,1),
(72914, 4495, 12841,0,0,0,0,2,1);
