-- Q: Into the Pit

UPDATE creature_template SET faction_A = 2109, faction_H = 2109 WHERE entry = 30174;
DELETE FROM spell_area WHERE spell = 55012 AND area = 4535;
