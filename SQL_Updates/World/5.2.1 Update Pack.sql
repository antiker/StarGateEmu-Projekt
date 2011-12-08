UPDATE `creature_template` SET `ScriptName`='boss_corla' WHERE `entry`=39679;
UPDATE `creature_template` SET `ScriptName`='boss_romogg_bonecrusher' WHERE `entry`=39665;
UPDATE `creature_template` SET `ScriptName`='boss_karsh' WHERE `entry`=39698;
UPDATE `creature_template` SET `ScriptName`='boss_bella' WHERE `entry`=39700;
-- UPDATE `creature_template` SET `ScriptName`='bc_teleport' WHERE `entry`=1000000;
UPDATE `creature_template` SET `ScriptName`='boss_lord_obsidius' WHERE `entry`=39705;
UPDATE `creature_template` SET `ScriptName`='npc_shade_obsidius' WHERE `entry`=40817;
UPDATE `creature_template` SET `ScriptName`='mob_chains_of_woe' WHERE `entry`=40447;

UPDATE creature_template SET AIname = "" WHERE entry IN (39679,39665,39698,39700,1000000,39705,40817,40447);