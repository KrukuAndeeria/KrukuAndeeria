DELETE from script_texts WHERE entry IN  (-1790000, -1790001, -1790002, -1790003, -1790004);
INSERT into script_texts (entry,content_default,type,comment) VALUES
(-1790000,'So then we too are cursed?',0,'AM_VRYKUL_SAY_1'),
(-1790001,'The gods have forsaken us! We must dispose of it before Ymiron is notified!',0,'AM_VRYKUL_SAY_2'),
(-1790002,' NO! You cannot! I beg of you! It is our child!',0,'AF_VRYKUL_SAY_1'),
(-1790003,'Then what are we to do, wife? The others cannot find out. Should they learn of this aberration, we will all be executed.',0,'AM_VRYKUL_SAY_3'),
(-1790004,'I... I will hide it. I will hide it until I find it a home, far away from here...',0,'AF_VRYKUL_SAY_2');
