UPDATE `creature_template` SET `ScriptName`='npc_neptulon' WHERE `entry`=40792;
UPDATE `creature_template` SET `ScriptName`='boss_ozumat' WHERE `entry`=44566;
UPDATE `creature_template` SET `ScriptName`='boss_erunak_stonespeaker' WHERE `entry`=40825;
UPDATE `creature_template` SET `ScriptName`='boss_mindbender_ghursha' WHERE `entry`=40788;
UPDATE `creature_template` SET `ScriptName`='boss_lady_nazjar' WHERE `entry`=40586;
UPDATE `creature_template` SET `ScriptName`='boss_commander_ulthok' WHERE `entry`=40765;

UPDATE creature_template SET AIname = "" WHERE entry IN (40792,44566,40825,40788,40586,40765);