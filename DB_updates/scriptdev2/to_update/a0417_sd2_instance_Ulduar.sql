-- Instance Ulduar - script_texts

-- teleporters gossip
DELETE FROM `gossip_texts` WHERE `entry` BETWEEN -3603008 AND -3603000;
INSERT INTO `gossip_texts` (`entry`, `content_default`, `comment`) VALUES
(-3603000, "Expedition Base Camp", "Ulduar teleporter text 1"),
(-3603001, "Formation Grounds", "Ulduar teleporter text 2"),
(-3603002, "Colossal Forge", "Ulduar teleporter text 3"),
(-3603003, "Scrapyard", "Ulduar teleporter text 4"),
(-3603004, "Antechamber of Ulduar", "Ulduar teleporter text 5"),
(-3603005, "Shattered Walkway", "Ulduar teleporter text 6"),
(-3603006, "Conservatory of Life", "Ulduar teleporter text 7"),
(-3603007, "Spark of Imagination", "Ulduar teleporter text 8"),
(-3603008, "Prison of Yogg-Saron", "Ulduar teleporter text 9");

-- Ignis the Furnace Master
DELETE FROM `script_texts` WHERE `entry` BETWEEN -1610029 AND -1610020;
INSERT INTO `script_texts` VALUES
(-1610020,'Insolent whelps! Your blood will temper the weapons used to reclaim this world!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15564,1,0,0,'IGNIS_AGGRO'),
(-1610021,'Let the inferno consume you!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15567,1,0,0,'IGNIS_SCORCH_1'),
(-1610022,'BURN! Burn in the makers fire!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15568,1,0,0,'IGNIS_SCORCH_2'),
(-1610023,'I will burn away your impurities!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15566,1,0,0,'IGNIS_SLAG_POT'),
(-1610024,'Ignis the Furnace Master begins to cast Flame Jets!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'EMOTE_FLAME_JETS'),
(-1610025,'Arise, soldiers of the Iron Crucible! The Makers will be done! ',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15565,1,0,0,'IGNIS_SUMMON'),
(-1610026,'More scraps for the scrapheap!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15569,1,0,0,'IGNIS_SLAY_1'),
(-1610027,'Your bones will serve as kindling!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15570,1,0,0,'IGNIS_SLAY_2'),
(-1610028,'Let it be finished!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15571,1,0,0,'IGNIS_BERSERK'),
(-1610029,'I. Have. Failed.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15572,1,0,0,'IGNIS_DEATH');

-- Razorscale
DELETE FROM `script_texts` WHERE (`entry` BETWEEN -1603026 AND -1603020) OR (`entry` IN (-1603353, -1603354));
INSERT INTO `script_texts` VALUES
(-1603020,'Welcome, champions! All of our attempts at grounding her have failed. We could use a hand in bring her down with these harpoon guns.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15647,'0',0,0,'razorscale intro - commander'),
(-1603021,'Give us a moment to prepare to build the turrets.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,'1',NULL,NULL,'razor aggro 1 - eng'),
(-1603022,'Be on the lookout! Mole machines will be surfacing soon with those nasty Iron dwarves aboard!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,'1',0,0,'razor aggro 2 - commander'),
(-1603023,'Ready to move out, keep those dwarves off of our backs!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,'1',0,0,'razor aggro 3 - eng'),
(-1603024,'Move! Quickly! She won’t remain grounded for long.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,'1',0,0,'razor ground - commander'),
(-1603025,'Razorscale takes a deep breath...',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,'3',0,0,'razor deep breath'),
(-1603026,'Fires out! Let\'s rebuild those turrets!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,'1',0,0,'razor extinguish fires'),
(-1603353,'Harpoon Turret is ready for use!' ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'EMOTE_harpoon'),
(-1603354,'Razorscale grounded permanently!' ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'EMOTE_ground');

-- XT-002 Deconstructor
DELETE FROM `script_texts` WHERE `entry` BETWEEN -1610040 AND -1610030;
INSERT INTO `script_texts` VALUES
(-1610030,"New toys? For me? I promise I won't break them this time!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15724,1,0,0,'XT002 SAY_AGGRO'),
(-1610031,"So tired. I will rest for just a moment!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15725,1,0,0,'XT002 SAY_HEART_OPENED'),
(-1610032,"I'm ready to play!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15726,1,0,0,'XT002 SAY_HEART_CLOSED'),
(-1610033,"NO! NO! NO! NO! NO!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15727,1,0,0,'XT002 SAY_TYMPANIC_TANTRUM'),
(-1610034,"I... I think I broke it.",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15728,1,0,0,'XT002 SAY_SLAY_1'),
(-1610035,"I guess it doesn't bend that way.",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15729,1,0,0,'XT002 SAY_SLAY_2'),
(-1610036,"I'm tired of these toys. I don't want to play anymore!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15730,1,0,0,'XT002 SAY_BERSERK'),
(-1610037,"You are bad... Toys... Very... Baaaaad!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15731,1,0,0,'XT002 SAY_DEATH'),
(-1610038,"Time for a new game! My old toys will fight my new toys!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15732,1,0,0,'XT002 SAY_SUMMON'),
(-1610039,"XT-002 Deconstructor's heart is exposed and leaking energy.",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'XT002 EMOTE_HEART'),
(-1610040,"XT-002 Deconstructor consumes a scrap bot to repair himself!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'XT002 EMOTE_REPAIR');

-- Iron Council
DELETE FROM `script_texts` WHERE `entry` BETWEEN -1603078 AND -1603056;
INSERT INTO `script_texts` VALUES
-- Brudir
(-1603056, "Whether the world\'s greatest gnats or the world\'s greatest heroes, you\'re still only mortal.", "","","","","","","","",15684, 1, 0, 0, 'BrundirAggro'),
(-1603057, "Stand still and stare into the light!", "","","","","","","","",15687, 1, 0, 0, 'BrundirWhirl'),
(-1603058, "The power of the storm lives on...", "","","","","","","","",15689, 1, 0, 0, 'BrundirDeath1'),
(-1603059, "You rush headlong into the maw of madness!", "","","","","","","","",15690, 1, 0, 0, 'BrundirDeath2'),
(-1603060, "A merciful kill!", "","","","","","","","",15685, 1, 0, 0, 'BrundirSlay1'),
(-1603061, "HAH!", "","","","","","","","",15686, 1, 0, 0, 'BrundirSlay2'),
(-1603062, "This meeting of the Assembly of Iron is adjourned!", "","","","","","","","",15691, 1, 0, 0, 'BrundirBerserk'),
(-1603063, "Let the storm clouds rise and rain down death from above!", "","","","","","","","",15688, 1, 0, 0, 'BrundirFly'),
-- Molgeim
(-1603064,"Nothing short of total decimation will suffice!","","","","","","","","",15657,1,0,0,"MolgeimAggro"),
(-1603065, "The legacy of storms shall not be undone...", "","","","","","","","",15662, 1, 0, 0, "MolgeimDeath1"),
(-1603066, "What have you gained from my defeat? You are no less doomed, mortals...", "","","","","","","","",15663, 1, 0, 0, 'MolgeimDeath2'),
(-1603067, "Decipher this!", "","","","","","","","",15660, 1, 0, 0, 'MolgeimDeathRune'),
(-1603068, "Face the lightning surge!", "","","","","","","","",15661, 1, 0, 0, 'MolgeimSummon'),
(-1603069, "The world on suffers yet another insignificant loss!", "","","","","","","","",15658, 1, 0, 0, 'MolgeimSlay1'),
(-1603070, "Death is the price of your arrogance.", "","","","","","","","",15659, 1, 0, 0, 'MolgeimSlay2'),
(-1603071, "This meeting of the Assembly of Iron is adjourned!", "","","","","","","","",15664, 1, 0, 0, 'MolgeimBerserk'),
-- Steelbreaker
(-1603072, "You will not defeat the Assembly of Iron so easily, invaders!", "","","","","","","","",15674, 1, 0, 0, 'SteelAggro'),
(-1603073, "My death only serves to hasten your demise.", "","","","","","","","",15678, 1, 0, 0, 'SteelDeath1'),
(-1603074, "Impossible!", "","","","","","","","",15679, 1, 0, 0, 'SteelDeath2'),
(-1603075, "So fragile and weak!", "","","","","","","","",15675, 1, 0, 0, 'SteelSlay1'),
(-1603076, "Flesh... such a hindrance.", "","","","","","","","",15676, 1, 0, 0, 'SteelSlay2'),
(-1603077, "You seek the secrets of Ulduar? Then take them!", "","","","","","","","",15677, 1, 0, 0, 'SteelOverwhelming'),
(-1603078, "This meeting of the Assembly of Iron is adjourned!", "","","","","","","","",15680, 1, 0, 0, 'SteelBerserk');

-- Kologarn:
DELETE FROM script_texts WHERE entry BETWEEN -1603137 AND -1603126;
INSERT INTO script_texts (entry, content_default, content_loc1, content_loc2, content_loc3, content_loc4, content_loc5, content_loc6, content_loc7, content_loc8, sound, type, language, emote, comment) VALUES
(-1603126, "None shall pass!", "","","","","","","","",15586, 1, 0, 0, 'KologarnAggro'),
(-1603127, "OBLIVION!", "","","","","","","","",15591, 1, 0, 0, 'Kologarn shockweave'),
(-1603128, "I will squeeze the life from you!", "","","","","","","","",15592, 1, 0, 0, 'Kologarn grab'),
(-1603129, "Just a scratch!", "","","","","","","","",15589, 1, 0, 0, 'left arm lost'),
(-1603130, "Only a flesh wound!", "","","","","","","","",15590, 1, 0, 0, 'right arm lost'),
(-1603131, "KOL-THARISH!", "","","","","","","","",15587, 1, 0, 0, 'KologarnSlay1'),
(-1603132, "YOU FAIL!", "","","","","","","","",15588, 1, 0, 0, 'KologarnSlay2'),
(-1603133, "I am invincible!", "","","","","","","","",15594, 1, 0, 0, 'KologarnBerserk'),
(-1603134, "Master, they come...", "","","","","","","","",15593, 1, 0, 0, 'Kologarndeath'),
(-1603135,'The Right Arm has regrown!' ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'EMOTE_right hand'),
(-1603136,'The Left Arm has regrown!' ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'EMOTE_left hand'),
(-1603137,'Kologarn casts Stone Grip!' ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'EMOTE_stone grip');

-- Auriaya:
DELETE FROM script_texts WHERE entry BETWEEN -1603144 AND -1603138;
INSERT INTO script_texts (entry, content_default, content_loc1, content_loc2, content_loc3, content_loc4, content_loc5, content_loc6, content_loc7, content_loc8, sound, type, language, emote, comment) VALUES
(-1603138,"Some things are better left alone!","","","","","","","","",15473,1,0,0,"auriaya aggro"),
(-1603139,"The secret dies with you!","","","","","","","","",15474,1,0,0,"auriaya Slay 2"),
(-1603140,"There is no escape!","","","","","","","","",15475,1,0,0,"auriaya Slay 1"),
(-1603141,"You waste my time!","","","","","","","","",15477,1,0,0,"auriaya berserk"),
(-1603142,"Auriaya screams in agony.","","","","","","","","",15476,2,0,0,"auriaya death"),
(-1603143,'Auriaya begins to cast Terrifying Screech.' ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'EMOTE_screech'),
(-1603144,'Auriaya begins to activate the Feral Defender!' ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'EMOTE_defender');
