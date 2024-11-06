create procedure team_sponsor_relation_fill(num_rows INTEGER) authid current_user
as
    v_sponsor_size INTEGER;
    v_team_size INTEGER;
    v_index INTEGER;
    v_start INTEGER;
    v_end INTEGER;
    v_idSponsor INTEGER;
    v_idTeam INTEGER;
    v_combinationCount INTEGER;

begin
    SELECT COUNT(*) INTO v_start FROM SPONSOR_PROFESSIONAL_TEAM;
    SELECT COUNT(*) INTO v_sponsor_size FROM SPONSOR;
    SELECT COUNT(*) INTO v_team_size FROM PROFESSIONAL_TEAM;

    v_index := 0;
    v_end := v_start + num_rows;

    IF v_end > v_sponsor_size * v_team_size THEN
        DBMS_OUTPUT.PUT_LINE('Param exceeds the limit');
        return;
    ELSE
        WHILE v_index < v_end LOOP
            v_idSponsor := ROUND(DBMS_RANDOM.VALUE(1,v_sponsor_size));
            v_idTeam := ROUND(DBMS_RANDOM.VALUE(1,v_team_size));


            SELECT COUNT(*)
            INTO v_combinationCount
            FROM SPONSOR_PROFESSIONAL_TEAM
            WHERE id_sponsor = v_idSponsor AND id_professional_team = v_idTeam;

            IF v_combinationCount = 0 THEN
                INSERT INTO SPONSOR_PROFESSIONAL_TEAM (id_sponsor, id_professional_team)
                VALUES (v_idSponsor, v_idTeam);
                v_index := v_index + 1;
            END IF;
            end loop;
    end if;

end;
/


