create or replace procedure trigger_unit_test authid current_user AS
    v_exception_sponsorship_exists EXCEPTION;
    PRAGMA EXCEPTION_INIT(v_exception_sponsorship_exists,-20001);
    v_exception_low_budget EXCEPTION;
    PRAGMA EXCEPTION_INIT(v_exception_low_budget,-20002);
BEGIN
    DBMS_OUTPUT.PUT_LINE('Starting trigger unit test.........');

    DBMS_OUTPUT.PUT_LINE('Test 1 : Sponsorship relation already exists.');
    BEGIN
        INSERT INTO SPONSOR_PROFESSIONAL_TEAM (ID_SPONSOR, ID_PROFESSIONAL_TEAM) VALUES (5,10);
        EXCEPTION
            WHEN v_exception_sponsorship_exists THEN
                DBMS_OUTPUT.PUT_LINE('Sponsorship already exists! Error : -20001');

    end;
    DBMS_OUTPUT.PUT_LINE('Test 2 : Budget of sponsor is too low to sponsor top 5 team');
    BEGIN
        INSERT INTO SPONSOR_PROFESSIONAL_TEAM (ID_SPONSOR, ID_PROFESSIONAL_TEAM) VALUES (1,2);
        EXCEPTION
            WHEN v_exception_low_budget THEN
                DBMS_OUTPUT.PUT_LINE('Budget of the sponsor is too low! Error : -20002');
    end;

    DBMS_OUTPUT.PUT_LINE('Test 3 : Successful test');
    INSERT INTO SPONSOR_PROFESSIONAL_TEAM (ID_SPONSOR, ID_PROFESSIONAL_TEAM) VALUES (6,1);

    DBMS_OUTPUT.PUT_LINE('All test passed.');



end;


