CREATE OR REPLACE TRIGGER budget_big_enough
BEFORE INSERT ON SPONSOR_PROFESSIONAL_TEAM
FOR EACH ROW
DECLARE
    v_sponsor_id SPONSOR_PROFESSIONAL_TEAM.ID_SPONSOR%TYPE;
    v_professional_team_id SPONSOR_PROFESSIONAL_TEAM.ID_PROFESSIONAL_TEAM%TYPE;
    v_is_in_top_five INTEGER;
    v_budget SPONSOR.SPONSOR_BUDGET%TYPE;
    v_duplicate_count INTEGER;
BEGIN
    v_sponsor_id := :NEW.ID_SPONSOR;
    v_professional_team_id := :NEW.ID_PROFESSIONAL_TEAM;
    DBMS_OUTPUT.PUT_LINE('AHOJ');

    SELECT COUNT(*)
    INTO v_duplicate_count
    FROM SPONSOR_PROFESSIONAL_TEAM d
    WHERE d.ID_SPONSOR = v_sponsor_id AND d.ID_PROFESSIONAL_TEAM = v_professional_team_id;

    IF v_duplicate_count > 0 THEN
        RAISE_APPLICATION_ERROR(-20001, 'Sponsorship relation already exists.');
    END IF;


    SELECT COUNT(*)
    INTO v_is_in_top_five
    FROM PROFESSIONAL_TEAM p
    WHERE p.TEAM_RANKING <= 5 AND p.ID_PROFESSIONAL_TEAM = v_professional_team_id;

    DBMS_OUTPUT.PUT_LINE('IS IN TOP FIVE' || v_is_in_top_five);

    IF v_is_in_top_five > 0 THEN
        SELECT s.SPONSOR_BUDGET
        INTO v_budget
        FROM SPONSOR s
        WHERE s.ID_SPONSOR = v_sponsor_id;

        DBMS_OUTPUT.PUT_LINE('DEBUG V BUDGET ' || v_budget);

        IF v_budget > 200000 THEN
             RAISE_APPLICATION_ERROR(-20002, 'Sponsorship budget must be at least 200,000.');
        END IF;
    END IF;
END;
