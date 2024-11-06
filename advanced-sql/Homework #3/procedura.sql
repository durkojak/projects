create or replace procedure get_rodova_line(v_meno VARCHAR2, v_pohlavie VARCHAR2) AUTHID current_user AS

    v_starting_id INTEGER;
    v_starting_count INTEGER;

    CURSOR c_rodova_linie (v_cv INTEGER) IS
        WITH RodovaLinie(v_jmeno, v_pohlavie, id_vydra, id_otec, id_matka, generace) AS (
            SELECT deti.JMENO, deti.POHLAVI, deti.CV, deti.OTEC, deti.MATKA, 0 AS generace
            FROM VYDRA deti
            WHERE deti.CV = v_cv
            UNION ALL
            SELECT rodicia.JMENO, rodicia.POHLAVI, rodicia.CV, rodicia.OTEC, rodicia.MATKA, generace + 1
            FROM VYDRA rodicia
            INNER JOIN RodovaLinie ON (rodicia.CV = RodovaLinie.id_otec OR rodicia.CV = RodovaLinie.id_matka)
        )
    SELECT DISTINCT generace, RodovaLinie.v_jmeno, RodovaLinie.v_pohlavie
        FROM RodovaLinie
        WHERE generace != 0
        ORDER BY generace;


BEGIN
    SELECT COUNT(*) INTO v_starting_count FROM VYDRA WHERE VYDRA.JMENO = v_meno;

    IF v_starting_count = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Neexistujuca vydra');
        RETURN;
    end if;

    SELECT VYDRA.CV INTO v_starting_id FROM VYDRA WHERE VYDRA.JMENO = v_meno;


    IF v_pohlavie = 'mužská' THEN
        DBMS_OUTPUT.PUT_LINE('Hlada sa muzska linia...');
        FOR rec IN c_rodova_linie(v_starting_id) LOOP
            IF rec.v_pohlavie = 'M' THEN
            DBMS_OUTPUT.PUT_LINE(rec.v_jmeno || ' (' || rec.generace || ')');
            END IF;

            end loop;
    ELSIF v_pohlavie = 'ženská' THEN
        DBMS_OUTPUT.PUT_LINE('Hlada sa zenska linia...');
        FOR rec IN c_rodova_linie(v_starting_id) LOOP
            IF rec.v_pohlavie = 'Z' THEN
            DBMS_OUTPUT.PUT_LINE(rec.v_jmeno || ' (' || rec.generace || ')');
            END IF;

            end loop;
    ELSE
        DBMS_OUTPUT.PUT_LINE('Hladaju sa obe linie...');
        FOR rec IN c_rodova_linie(v_starting_id) LOOP
            DBMS_OUTPUT.PUT_LINE(rec.v_jmeno || ' (' || rec.generace || ')');
            end loop;
    END IF;
    DBMS_OUTPUT.PUT_LINE('Koniec hladania!');
end;
