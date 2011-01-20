-- Q: Forging an Alliance

-- Son of Hodir instead of King Jokkum was spawned
UPDATE creature SET id = 30105 WHERE guid = 106321;

-- add spawn for Njormel
DELETE FROM creature WHERE id = 30099;
INSERT INTO creature (id, map, spawnMask, phaseMask, equipment_id, position_x, position_y, position_z, orientation, spawndist, curhealth, MovementType) VALUES
(30099, 571, 1, 1, 0, 7174.5, -3511.85, 833.682, 5.88107, 0, 50400, 0);

-- add spawn for Snorri
DELETE FROM creature WHERE id = 30123;
INSERT INTO creature (id, map, spawnMask, phaseMask, equipment_id, position_x, position_y, position_z, orientation, spawndist, curhealth, MovementType) VALUES
(30123, 571, 1, 1, 0, 7153.71, -3535.85, 833.682, 5.67107, 0, 50400, 0);
-- update basic stats for Snorri NPC and vehicle and Njormeld
UPDATE creature_template SET minlevel = 80, maxlevel = 80, minhealth = 50400, maxhealth = 50400 WHERE entry IN (30123, 30124, 30099);

-- Force Reaction for Sons of Hodir
DELETE FROM spell_area WHERE spell = 55953;
INSERT INTO spell_area VALUES
(55953, 4438, 12924,1,0,0,0,2,1), -- Dun Niffelem
(55953, 4495, 12924,1,0,0,0,2,1); -- Fjorn's Anvil
