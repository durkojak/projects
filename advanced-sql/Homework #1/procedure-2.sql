create procedure team_table_fill(num_rows INTEGER) authid current_user
as
    v_start INTEGER;
    v_end INTEGER;
    v_index INTEGER;

    TYPE TEAM_RANKINGS IS TABLE OF INTEGER;
    TYPE TEAM_NAMES IS TABLE OF VARCHAR(40);

    arrTeamRankings TEAM_RANKINGS;
    arrTeamNames TEAM_NAMES;
BEGIN
    select count(*) into v_start from PROFESSIONAL_TEAM;
    v_index := v_start + 1;
    v_end := v_start + num_rows;

    SELECT TEAM_NAME BULK COLLECT INTO arrTeamNames FROM TEAM_NAMES;
    SELECT TEAM_RANKING BULK COLLECT INTO arrTeamRankings FROM TEAM_RANKINGS;

    while v_start < v_end LOOP
        INSERT INTO PROFESSIONAL_TEAM(id_professional_team, team_name, team_ranking)
        VALUES (v_index,arrTeamNames(ROUND(DBMS_RANDOM.VALUE(1,10))),arrTeamRankings(round(DBMS_RANDOM.VALUE(1,10))));
        v_index := v_index + 1;
        v_start := v_start + 1;
        COMMIT;
        end loop;
end;
/


