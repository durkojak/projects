create or replace PACKAGE sponsor_pkg authid current_user AS
  PROCEDURE add_new_sponsor(id INTEGER, new_sponsor_name VARCHAR2, new_sponsor_budget INTEGER);
  PROCEDURE delete_sponsor(id INTEGER);
  PROCEDURE update_sponsor(id INTEGER, new_sponsor_name VARCHAR2, new_sponsor_budget INTEGER);
END sponsor_pkg;

create or replace PACKAGE BODY sponsor_pkg AS

  PROCEDURE add_new_sponsor(id INTEGER, new_sponsor_name VARCHAR2, new_sponsor_budget INTEGER) AS
    current_total_budget INTEGER;
  BEGIN
    -- vypocitanie current total budgetu sponsorov
    SELECT SUM(s.SPONSOR_BUDGET) INTO current_total_budget FROM SPONSOR s;
    DBMS_OUTPUT.PUT_LINE('Current total budget is : ' || current_total_budget);
    IF current_total_budget + new_sponsor_budget > 2000000 THEN
      DBMS_OUTPUT.PUT_LINE('ERROR!!!');
      RAISE_APPLICATION_ERROR(-20001, 'Total sponsorship budget exceeds 2000000.');
    END IF;
    DBMS_OUTPUT.PUT_LINE('INSERTING NEW!');
    INSERT INTO SPONSOR(id_sponsor, sponsor_name, sponsor_budget) VALUES (id, new_sponsor_name, new_sponsor_budget);
  END add_new_sponsor;


  PROCEDURE delete_sponsor(id INTEGER) AS
  BEGIN
      DELETE FROM SPONSOR WHERE id = SPONSOR.ID_SPONSOR;
  END delete_sponsor;


  PROCEDURE update_sponsor(id INTEGER, new_sponsor_name VARCHAR2, new_sponsor_budget INTEGER) AS
      current_total_budget INTEGER;
      before_update_budget INTEGER; -- sponsor budget pred updateom
  BEGIN
    -- vypocitanie current total budgetu sponsorov
    SELECT SUM(s.SPONSOR_BUDGET) INTO current_total_budget FROM SPONSOR s;

    SELECT s.SPONSOR_BUDGET INTO before_update_budget FROM SPONSOR s WHERE id = ID_SPONSOR;

    IF current_total_budget - before_update_budget + new_sponsor_budget > 2000000 THEN
        RAISE_APPLICATION_ERROR(-20001, 'Total sponsorship budget exceeds 2000000.');
    end if;

  UPDATE SPONSOR
  SET SPONSOR_NAME = new_sponsor_name,
      SPONSOR_BUDGET = new_sponsor_budget
  WHERE SPONSOR.ID_SPONSOR = id;

  END update_sponsor;
END sponsor_pkg;
