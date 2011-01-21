-- quest Territorial Trespass

DELETE from event_scripts where id=19714;
INSERT into event_scripts (id,delay,command,datalong,datalong2,x,y,z,o,data_flags,comments ) VALUES
(19714,2,10,30461,30000,7089.79,-918.39,1067.44,6.21,0x01,"Summon veranus(quest 13051)");