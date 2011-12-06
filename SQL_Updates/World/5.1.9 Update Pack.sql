UPDATE creature_template SET scriptname = "boss_erudax" WHERE entry = 40484;
UPDATE creature_template SET scriptname = "mob_erudax" WHERE entry = 40600;
UPDATE creature_template SET scriptname = "boss_drahga" WHERE entry = 40319;
UPDATE creature_template SET scriptname = "boss_throngus" WHERE entry = 40177;
UPDATE creature_template SET scriptname = "mob_valiona" WHERE entry = 45992;
UPDATE creature_template SET scriptname = "boss_general_umbriss" WHERE entry = 39625;
UPDATE creature_template SET scriptname = "npc_malveillant" WHERE entry = 39984;
UPDATE creature_template SET scriptname = "npc_habitant" WHERE entry = 45467;
UPDATE creature_template SET AIname = "" WHERE entry IN (39625,40484,40600,40319,40177,45992,39984,45467);

UPDATE creature_model_info SET combat_reach =10.4 WHERE modelid =31498 LIMIT 1;

DELETE FROM spell_script_names WHERE spell_id IN (74670, 90250, 74846, 91939, 74859, 74634, 90249, 74853);
INSERT INTO spell_script_names VALUES (74670, "spell_eclair");
INSERT INTO spell_script_names VALUES (90250, "spell_ecliar_h");
INSERT INTO spell_script_names VALUES (74846, "spell_plaie");
INSERT INTO spell_script_names VALUES (91939, "spell_plaie_h");
INSERT INTO spell_script_names VALUES (74859, "spell_apparition");
INSERT INTO spell_script_names VALUES (74634, "spell_scouss");
INSERT INTO spell_script_names VALUES (90249, "spell_scouss_h");
INSERT INTO spell_script_names VALUES (74853, "spell_berserk");

DELETE FROM script_texts WHERE npc_entry = 39625;
DELETE FROM script_texts WHERE entry = -1800000;
DELETE FROM script_texts WHERE entry = -1800001;
DELETE FROM script_texts WHERE entry = -1800002;
DELETE FROM script_texts WHERE entry = -1800003;
DELETE FROM script_texts WHERE entry = -1800004;

INSERT INTO script_texts (npc_entry, entry, content_default, sound, type) VALUES (39625, -1800000, "Millionen mehr erwarten meinen Befehl. Ihr habt keine Chance!", 18530, 1);
INSERT INTO script_texts (npc_entry, entry, content_default, sound, type) VALUES (39625, -1800001, "Schuetzt die Nachhut! Alexstraszas Brut faellt ueber uns her!", 18537, 1);
INSERT INTO script_texts (npc_entry, entry, content_default, sound, type) VALUES (39625, -1800002, "Gewuerm, euer Fressen wartet!",18531, 1);
INSERT INTO script_texts (npc_entry, entry, content_default, sound, type) VALUES (39625, -1800003, "Greift an, ihr feiges Gewuerm!",18535, 1);
INSERT INTO script_texts (npc_entry, entry, content_default, sound, type) VALUES (39625, -1800004, "Tod ist meine einzige Option!",18533, 1);

