create procedure sponsor_table_fill(num_rows INTEGER) authid current_user
as
    v_start INTEGER;
    v_end INTEGER;
    v_index INTEGER;

    TYPE SPONSOR_BUDGETS IS TABLE OF INTEGER;
    TYPE SPONSOR_NAMES IS TABLE OF VARCHAR(40);

    arrSponsorBudgets SPONSOR_BUDGETS;
    arrSponsorNames SPONSOR_NAMES;
begin
    SELECT COUNT(*) INTO v_start FROM SPONSOR;
    v_index := v_start + 1;
    v_end := v_start + num_rows;

    SELECT SPONSOR_NAME BULK COLLECT INTO arrSponsorNames FROM SPONSOR_NAMES;
    SELECT SPONSOR_BUDGET BULK COLLECT INTO arrSponsorBudgets FROM SPONSOR_BUDGETS;

    while v_start < v_end LOOP
        INSERT INTO SPONSOR(id_sponsor, sponsor_name, sponsor_budget)
        VALUES(v_index,arrSponsorNames(ROUND(DBMS_RANDOM.VALUE(1,10))),arrSponsorBudgets(ROUND(DBMS_RANDOM.VALUE(1,10))));
        v_index := v_index + 1;
        v_start := v_start + 1;
        COMMIT;
        end loop;

end;
/


