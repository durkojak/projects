DELETE from tournament_teams_participating;
DELETE from player;
DELETE from team;
DELETE from tournament;

ALTER SEQUENCE player_id_player_seq RESTART WITH 1;
ALTER SEQUENCE team_id_team_seq RESTART WITH 1;
ALTER SEQUENCE tournament_id_tournament_seq RESTART WITH 1;


INSERT INTO team (team_name, global_ranking, language_team) VALUES ('Ninjas in Pyjamas', 1, 'Slovak');
INSERT INTO team (team_name, global_ranking, language_team) VALUES ('Natus Vincere', 2, 'Czech');
INSERT INTO team (team_name, global_ranking, language_team) VALUES ('Velocity Vipers', 4, 'Slovak');
INSERT INTO team (team_name, global_ranking, language_team) VALUES ('Eternal Elites', 5, 'Spanish');
INSERT INTO team (team_name, global_ranking, language_team) VALUES ('Golden Guardians', 3, 'English');
INSERT INTO team (team_name, global_ranking, language_team) VALUES ('Red Phoenix', 6, 'English');


INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player1', 0.5, 'AK-47', 1);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player2', 3.0, 'AWP', null);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player3', 0.8, 'M4A1-S', 2);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player4', 2.2, 'Desert Eagle', 3);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player5', 1.5, 'P90', null);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player6', 0.8, 'AK-47', 4);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player7', 3.2, 'AWP', 5);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player8', 1.9, 'M4A1-S', 6);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player9', 2.1, 'USP-S', null);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player10', 2.7, 'Glock-18', 1);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player11', 1.4, 'Nova', 2);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player12', 2.9, 'FAMAS', 3);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player13', 3.1, 'AWP', null);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player14', 1.8, 'UMP-45', 4);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player15', 2.3, 'AK-47', 5);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player16', 3.5, 'AWP', 6);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player17', 1.6, 'M4A4', 1);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player18', 2.0, 'Desert Eagle', 2);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player19', 2.8, 'P250', 3);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player20', 3.2, 'AWP', null);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player21', 0.9, 'Galil AR', 4);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player22', 2.4, 'SSG 08', 5);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player23', 3.0, 'M4A1-S', 6);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player24', 0.1, 'UMP-45', null);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player25', 1.7, 'Five-SeveN', 1);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player26', 2.6, 'MP9', 2);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player27', 0.3, 'AWP', 3);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player28', 1.5, 'M4A4', 4);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player29', 2.2, 'P90', 5);
INSERT INTO player (nickname, kd_ratio, fav_gun, member_of_id_team) VALUES ('Player30', 0.9, 'Desert Eagle', 6);

INSERT INTO tournament(tournament_name, location, prize_pool) VALUES ('IEM','Katowice',10000000);
INSERT INTO tournament(tournament_name, location, prize_pool) VALUES ('DreamHack','Malmo',500000);
INSERT INTO tournament(tournament_name, location, prize_pool) VALUES ('PGL','Rio de Janeiro',250000);

INSERT INTO tournament_teams_participating(participated_tournaments_id_tournament , teams_participating_id_team) VALUES (1,1);
INSERT INTO tournament_teams_participating(participated_tournaments_id_tournament, teams_participating_id_team) VALUES (1,2);
INSERT INTO tournament_teams_participating(participated_tournaments_id_tournament, teams_participating_id_team) VALUES (1,5);
INSERT INTO tournament_teams_participating(participated_tournaments_id_tournament, teams_participating_id_team) VALUES (2,1);
INSERT INTO tournament_teams_participating(participated_tournaments_id_tournament, teams_participating_id_team) VALUES (2,2);
INSERT INTO tournament_teams_participating(participated_tournaments_id_tournament, teams_participating_id_team) VALUES (2,3);
INSERT INTO tournament_teams_participating(participated_tournaments_id_tournament, teams_participating_id_team) VALUES (2,4);
INSERT INTO tournament_teams_participating(participated_tournaments_id_tournament, teams_participating_id_team) VALUES (2,5);

