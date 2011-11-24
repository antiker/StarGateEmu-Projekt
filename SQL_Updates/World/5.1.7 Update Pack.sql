DELETE FROM `spell_script_names` WHERE `spell_id` = 90811;
INSERT INTO `spell_script_names` VALUES
(90811,'spell_pal_selfless_healer');

DELETE FROM `spell_proc_event` WHERE `entry` IN (85803,85804);
INSERT INTO `spell_proc_event` VALUES
(85803,0,10,0,0,16384,0,0,0,0,0),
(85804,0,10,0,0,16384,0,0,0,0,0);

DELETE FROM `spell_proc_event` WHERE `entry` IN (26022,26023);
INSERT INTO `spell_proc_event` VALUES
(26022,0,0,0,0,0,0,65536,0,0,8),
(26023,0,0,0,0,0,0,65536,0,0,8);

