UPDATE `creature_template` SET `ScriptName`='boss_ammunae' WHERE `entry`=39731;
UPDATE `creature_template` SET `ScriptName`='boss_temple_guardian_anhuur' WHERE `entry`=39425;
UPDATE `creature_template` SET `ScriptName`='boss_anraphet' WHERE `entry`=39788;
UPDATE `creature_template` SET `ScriptName`='boss_isiset' WHERE `entry`=39587;
UPDATE `creature_template` SET `ScriptName`='boss_ptah' WHERE `entry`=39428;
UPDATE `creature_template` SET `ScriptName`='boss_rajh' WHERE `entry`=39378;
UPDATE `creature_template` SET `ScriptName`='boss_setesh' WHERE `entry`=39732;

UPDATE creature_template SET AIname = "" WHERE entry IN (39731,39425,39788,39587,39428,39378,39732);