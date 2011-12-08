-- (18119) Improved Soul Fire (Rank 1)
DELETE FROM `spell_proc_event` WHERE `entry` IN (18119);
INSERT INTO `spell_proc_event` VALUES (18119, 0x00, 0x05, 0x00000000, 0x00000080, 0x00000000, 0x00010000, 0x00000000, 0, 100, 0);
-- (18120) Improved Soul Fire (Rank 2)
DELETE FROM `spell_proc_event` WHERE `entry` IN (18120);
INSERT INTO `spell_proc_event` VALUES (18120, 0x00, 0x05, 0x00000000, 0x00000080, 0x00000000, 0x00010000, 0x00000000, 0, 100, 0);

-- (84583) Lambs to the Slaughter (Rank 1)
DELETE FROM `spell_proc_event` WHERE `entry` IN (84583);
INSERT INTO `spell_proc_event` VALUES (84583, 0x00, 0x04, 0x02000000, 0x00000000, 0x00000000, 0x00000010, 0x00000000, 0, 100, 0);
-- (84587) Lambs to the Slaughter (Rank 2)
DELETE FROM `spell_proc_event` WHERE `entry` IN (84587);
INSERT INTO `spell_proc_event` VALUES (84587, 0x00, 0x04, 0x02000000, 0x00000000, 0x00000000, 0x00000010, 0x00000000, 0, 100, 0);
-- (84588) Lambs to the Slaughter (Rank 3)
DELETE FROM `spell_proc_event` WHERE `entry` IN (84588);
INSERT INTO `spell_proc_event` VALUES (84588, 0x00, 0x04, 0x02000000, 0x00000000, 0x00000000, 0x00000010, 0x00000000, 0, 100, 0);

-- (46913) Bloodsurge (Rank 1)
DELETE FROM `spell_proc_event` WHERE `entry` IN (46913);
INSERT INTO `spell_proc_event` VALUES (46913, 0x00, 0x04, 0x00000000, 0x00000400, 0x00000000, 0x00000010, 0x00000000, 0, 10, 0);
-- (46914) Bloodsurge (Rank 2)
DELETE FROM `spell_proc_event` WHERE `entry` IN (46914);
INSERT INTO `spell_proc_event` VALUES (46914, 0x00, 0x04, 0x00000000, 0x00000400, 0x00000000, 0x00000010, 0x00000000, 0, 20, 0);
-- (46915) Bloodsurge (Rank 3)
DELETE FROM `spell_proc_event` WHERE `entry` IN (46915);
INSERT INTO `spell_proc_event` VALUES (46915, 0x00, 0x04, 0x00000000, 0x00000400, 0x00000000, 0x00000010, 0x00000000, 0, 30, 0);

-- (47230) Fel Synergy (Rank 1)
DELETE FROM `spell_proc_event` WHERE `entry` IN (47230);
INSERT INTO `spell_proc_event` VALUES (47230, 0x00, 0x05, 0x00000000, 0x00000000, 0x00000000, 0x00851154, 0x00000000, 0, 50, 0);
-- (47231) Fel Synergy (Rank 2)
DELETE FROM `spell_proc_event` WHERE `entry` IN (47231);
INSERT INTO `spell_proc_event` VALUES (47231, 0x00, 0x05, 0x00000000, 0x00000000, 0x00000000, 0x00051154, 0x00000000, 0, 100, 0);

-- Judgements of the bold
DELETE FROM `spell_proc_event` WHERE `entry` IN (31878,89901);
INSERT INTO `spell_proc_event` VALUES
(89901,0,10,8388608,0,0,0,262144,0,0,0);

-- (17796) Shadow and Flame (Rank 2)
DELETE FROM `spell_proc_event` WHERE `entry` IN (17796);
INSERT INTO `spell_proc_event` VALUES (17796, 0x00, 0x05, 0x00000001, 0x00000040, 0x00000000, 0x00011150, 0x00000000, 0, 0, 0);
-- (17801) Shadow and Flame (Rank 3)
DELETE FROM `spell_proc_event` WHERE `entry` IN (17801);
INSERT INTO `spell_proc_event` VALUES (17801, 0x00, 0x05, 0x00000001, 0x00000040, 0x00000000, 0x00011150, 0x00000000, 0, 0, 0);
-- (17793) Shadow and Flame (Rank 1)
DELETE FROM `spell_proc_event` WHERE `entry` IN (17793);
INSERT INTO `spell_proc_event` VALUES (17793, 0x00, 0x05, 0x00000001, 0x00000040, 0x00000000, 0x00011150, 0x00000000, 0, 0, 0);

-- (47258) Backdraft (Rank 1)
DELETE FROM `spell_proc_event` WHERE `entry` IN (47258);
INSERT INTO `spell_proc_event` VALUES (47258, 0x00, 0x05, 0x00000000, 0x00800000, 0x00000000, 0x00011000, 0x00010000, 0, 0, 0);
-- (47259) Backdraft (Rank 2)
DELETE FROM `spell_proc_event` WHERE `entry` IN (47259);
INSERT INTO `spell_proc_event` VALUES (47259, 0x00, 0x05, 0x00000000, 0x00800000, 0x00000000, 0x00011000, 0x00010000, 0, 0, 0);

-- (47260) Backdraft (Rank 3)
DELETE FROM `spell_proc_event` WHERE `entry` IN (47260);
INSERT INTO `spell_proc_event` VALUES (47260, 0x00, 0x05, 0x00000000, 0x00800000, 0x00000000, 0x00011000, 0x00010000, 0, 0, 0);


-- (54278) Empowered Imp
DELETE FROM `spell_proc_event` WHERE `entry` IN (54278);
INSERT INTO `spell_proc_event` VALUES (54278, 0x00, 0x05, 0x00001000, 0x00000000, 0x00000000, 0x00010000, 0x00000000, 0, 0, 0);

DELETE FROM spell_linked_spell WHERE spell_trigger='-82691';
INSERT INTO spell_linked_spell (spell_trigger, spell_effect, TYPE, COMMENT) VALUES (-82691, 91264, 0, 'Ring of frost immune');