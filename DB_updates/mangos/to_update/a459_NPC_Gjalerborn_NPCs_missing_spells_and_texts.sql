-- Adding spells and texts for NPCs in Location Gjalerbron (Howling Fjord)

-- Add spells and texts for Necrolord (24014)
UPDATE creature_template SET AIName='EventAI' WHERE entry=24014;
-- Text
DELETE FROM creature_ai_texts WHERE entry IN (-240141,-240142);
INSERT INTO creature_ai_texts VALUES
(-240141,'More ingredients to fuel our rituals here.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,0,0,0,'Necrolord Say1'),
(-240142,'You too will serve the Lich King.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,0,0,0,'Necrolord Say2');
-- EventAi
DELETE FROM creature_ai_scripts WHERE id IN (2401400,2401401,2401402);
INSERT INTO creature_ai_scripts VALUES
(2401400,24014,4,0,100,0,0,0,0,0,11,18267,1,0,23,1,0,0,1,-240238,-240142,0,'Necrolord - Cast Curse of Weakness and Say on Aggro'),
(2401401,24014,0,0,100,1,1000,1000,10000,10000,11,9613,1,0,0,0,0,0,0,0,0,0,'Necrolord - Cast Shadowbolt '),
(2401402,24014,0,0,100,1,4000,4000,10000,10000,11,17173,1,0,0,0,0,0,0,0,0,0,'Necrolord - Cast Drain Life');

-- Add spells and texts for Gjalerbron Warrior (23991)
UPDATE creature_template SET AIName='EventAI' WHERE entry=23991;
-- Text
DELETE FROM creature_ai_texts WHERE entry=-239911;
INSERT INTO creature_ai_texts VALUES
(-239911,'Look what has come to play.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,0,0,0,'Gjalerbron Warrior Say1');
-- EventAi
DELETE FROM creature_ai_scripts WHERE id IN (2399100,2399101);
INSERT INTO creature_ai_scripts VALUES
(2399100,23991,4,0,100,0,0,0,0,0,11,13730,1,0,23,1,0,0,1,-239911,0,0,'Gjalerbron Warrior - Cast Demoralizing Shout and Say on Aggro'),
(2399101,23991,0,0,100,1,1000,1000,10000,10000,11,10966,1,0,0,0,0,0,0,0,0,0,'Gjalerbron Warrior - Cast Uppercut');

-- Add spells and texts for Gjalerbron Rune-Caster (23990)
UPDATE creature_template SET AIName='EventAI' WHERE entry=23990;
-- Text
DELETE FROM creature_ai_texts WHERE entry IN (-239901,-239902);
INSERT INTO creature_ai_texts VALUES
(-239901,'You tiny creatures disgust me.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,0,0,0,'Gjalerbron Rune-Caster Say1'),
(-239902,'There will be no everlasting life for you.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,0,0,0,'Gjalerbron Rune-Caster Say2');
-- EventAi
DELETE FROM creature_ai_scripts WHERE id IN (2399000,2399001,2399002);
INSERT INTO creature_ai_scripts VALUES
(2399000,23990,4,0,100,0,0,0,0,0,11,34787,1,0,23,1,0,0,1,-239901,-239902,0,'Gjalerbron Rune-Caster - Cast Freezing Circle and Say on Aggro'),
(2399001,23990,0,0,100,1,1000,1000,5000,5000,11,9672,1,0,0,0,0,0,0,0,0,0,'Gjalerbron Rune-Caster - Cast Frostbolt'),
(2399002,23990,0,0,100,1,4000,4000,15000,15000,11,43453,1,0,0,0,0,0,0,0,0,0,'Gjalerbron Rune-Caster - Cast Rune Ward');

-- Add spell for NPC Gjalerbron Sleep Watcher (23989)
UPDATE creature_template SET AIName='EventAI' WHERE entry=23989;
-- EventAi
DELETE FROM creature_ai_scripts WHERE id=2398900;
INSERT INTO creature_ai_scripts VALUES
(2398900,23989,0,0,100,1,1000,1000,7000,7000,11,66290,1,0,0,0,0,0,0,0,0,0,'Gjalerbron Sleep Watcher - Cast Sleep');

-- Add spells for NPC Sepulchral Overseer (23993)
UPDATE creature_template SET AIName='EventAI' WHERE entry=23993;
-- EventAi
DELETE FROM creature_ai_scripts WHERE id IN (2399300,2399301,2399302);
INSERT INTO creature_ai_scripts VALUES
(2399300,23993,4,0,100,0,0,0,0,0,11,43556,1,0,23,1,0,0,1,-239901,-239902,0,'Sepulchral Overseer - Cast Curse of the Sepulcher on Aggro'),
(2399301,23993,0,0,100,1,1000,1000,5000,5000,11,12737,1,0,0,0,0,0,0,0,0,0,'Sepulchral Overseerr - Cast Frostbolt'),
(2399302,23993,0,0,100,1,4000,4000,10000,10000,11,22744,1,0,0,0,0,0,0,0,0,0,'Sepulchral Overseer - Cast Chains of Ice');
