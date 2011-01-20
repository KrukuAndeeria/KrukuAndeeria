-- Quest: The Warm Up
UPDATE creature_template SET MovementType = 0, AIName = "EventAI" WHERE entry = 29352;
UPDATE creature SET MovementType = 0, spawndist = 0 WHERE id = 29352;
UPDATE creature_template SET minlevel = 80, maxlevel = 80, minhealth = 37800, maxhealth = 37800, faction_A = 14, faction_H = 14 WHERE entry = 29918;

DELETE FROM creature_ai_scripts WHERE creature_id = 29352;
INSERT INTO creature_ai_scripts VALUES
(2935201,  29352, 6, 0, 100, 1, 0, 0, 0, 0, 33, 30221, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Kirkraag - Kill Credit upon death");


DELETE FROM creature_template_addon WHERE entry = 29918;
INSERT INTO creature_template_addon VALUES
(29918, 0, 0, 0, 0, 0, 0, 173, "", "");

DELETE FROM vehicle_data WHERE entry = 173;
INSERT INTO vehicle_data VALUES
(173, 0x02|0x04|0x08, 6603, 0, 0, 54459, 54458, 54460, 0, 0, 0, 0, 0);

DELETE FROM vehicle_seat_data WHERE seat = 2069;
INSERT INTO vehicle_seat_data VALUES
(2069, 1);
