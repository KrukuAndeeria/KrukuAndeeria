-- Q: The Drakkensryd

DELETE FROM creature_ai_scripts WHERE creature_id = 29694;
INSERT INTO creature_ai_scripts VALUES
(2969401,  29694, 6, 0, 100, 1, 0, 0, 0, 0, 33, 29800, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Hyldsmeet Drakerider - Kill Credit upon death");

REPLACE INTO creature_template_addon VALUES
(29625, 0, 50331648, 1, 0, 0, 0, 183, "", "48602 0 48602 2");

DELETE FROM vehicle_data WHERE entry = 183;
INSERT INTO vehicle_data VALUES (183, 0x4C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM vehicle_seat_data WHERE seat IN (2100, 2101);
INSERT INTO vehicle_seat_data VALUES
(2100, 4),
(2101, 5);
