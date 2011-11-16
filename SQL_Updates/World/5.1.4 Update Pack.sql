DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_gen_profession_research';
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_item_book_of_glyph_mastery';
INSERT INTO `spell_script_names` 
(`spell_id`,`ScriptName`) VALUES(60893, 'spell_gen_profession_research'),
(61177, 'spell_gen_profession_research'),
(61288, 'spell_gen_profession_research'),
(61756, 'spell_gen_profession_research'),
(64323, 'spell_item_book_of_glyph_mastery');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (4987,85673);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(4987,'spell_pal_cleanse'),
(85673,'spell_pal_word_of_glory');

DELETE FROM `spell_proc_event` WHERE `entry` IN (85117,86172);
INSERT INTO `spell_proc_event` VALUES 
(85117,0,10,8388608,2228354,40960,67600,0,0,100,0),
(86172,0,10,8388608,2228354,40960,67600,0,0,100,0);