create or replace procedure sponsor_pkg_unit_test authid current_user AS
    sponsor_count_before INTEGER;
    sponsor_count_after INTEGER;
    sum_budget_before INTEGER;
    sum_budget_after INTEGER;
    v_custom_exception EXCEPTION;
    PRAGMA EXCEPTION_INIT(v_custom_exception, -20001);
BEGIN
    DBMS_OUTPUT.PUT_LINE('Starting sponsor_pkg_unit_test.........');
    SELECT SUM(SPONSOR_BUDGET) INTO sum_budget_before FROM SPONSOR;
    SELECT COUNT(*) INTO sponsor_count_before FROM SPONSOR;

    DBMS_OUTPUT.PUT_LINE('Sponsor count before add : ' || sponsor_count_before);
    DBMS_OUTPUT.PUT_LINE('Sum of budget before add : ' || sum_budget_before);

    ----------------------------- SUCCESSFUL SCENARIOS -----------------------------------

    --------------------------- ADD NEW SPONSOR ------------------------------------
    DBMS_OUTPUT.PUT_LINE('*****  ADDING SPONSOR : SUCCESSFUL TEST WITH ID 11 AND BUDGET 17 ***********');
    SPONSOR_PKG.ADD_NEW_SPONSOR(11,'Successful test',17);

    SELECT SUM(SPONSOR_BUDGET) INTO sum_budget_after FROM SPONSOR;
    SELECT COUNT(*) INTO sponsor_count_after FROM SPONSOR;

    DBMS_OUTPUT.PUT_LINE('Sponsor count after success add : ' || sponsor_count_after);
    DBMS_OUTPUT.PUT_LINE('Sum of budget after success add : ' || sum_budget_after);

    -------------------------------DELETE SPONSOR - same as regular sql --------------
    DBMS_OUTPUT.PUT_LINE('********* DELETING USER WITH ID 11 **********');
    SPONSOR_PKG.DELETE_SPONSOR(11);

    SELECT SUM(SPONSOR_BUDGET) INTO sum_budget_after FROM SPONSOR;
    SELECT COUNT(*) INTO sponsor_count_after FROM SPONSOR;

    DBMS_OUTPUT.PUT_LINE('Sponsor count after deleting : ' || sponsor_count_after);
    DBMS_OUTPUT.PUT_LINE('Sum of budget after deleting : ' || sum_budget_after);

    ------------------------------- UPDATE SPONSOR -----------------------------

    DBMS_OUTPUT.PUT_LINE('*********** UPDATING USER WITH ID 10 ****************');
    SPONSOR_PKG.UPDATE_SPONSOR(10,'Updated success',781);

    SELECT SUM(SPONSOR_BUDGET) INTO sum_budget_after FROM SPONSOR;
    SELECT COUNT(*) INTO sponsor_count_after FROM SPONSOR;

    DBMS_OUTPUT.PUT_LINE('Sponsor count after success update : ' || sponsor_count_after);
    DBMS_OUTPUT.PUT_LINE('Sum of budget after success update : ' || sum_budget_after);

    ------------------------------- FAIL SCENARIOS -------------------------------
    
    
    -- ADD NEW SPONSOR - sum of budget will be over 2 mil
    BEGIN
        SPONSOR_PKG.ADD_NEW_SPONSOR(12,'Fail',457574454445);
        EXCEPTION
            WHEN v_custom_exception THEN
                DBMS_OUTPUT.PUT_LINE('Sponsorship budget exceeded when adding. EXCEPTION : -20001');
    end;

    -- UPDATE SPONSOR - updated budget will be over 2 mil
    BEGIN
        SPONSOR_PKG.UPDATE_SPONSOR(10,'Update failed',465454654165464);
        EXCEPTION
            WHEN v_custom_exception THEN
                DBMS_OUTPUT.PUT_LINE('Sponsorship budget exceeded when updating. EXCEPTION : -20001');
    end;



end;


