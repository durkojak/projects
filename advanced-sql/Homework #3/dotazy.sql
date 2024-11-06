-- 10 muzska

WITH RodovaLinie(v_jmeno, v_pohlavie, id_vydra, id_otec, id_matka, generace) AS (
    SELECT deti.JMENO, deti.POHLAVI, deti.CV, deti.OTEC, deti.MATKA, 0 AS generace
    FROM VYDRA deti
    WHERE deti.CV = 10
    UNION ALL
    SELECT rodicia.JMENO, rodicia.POHLAVI, rodicia.CV, rodicia.OTEC, rodicia.MATKA, generace + 1
    FROM VYDRA rodicia
    INNER JOIN RodovaLinie ON ( rodicia.CV = RodovaLinie.id_otec )

)
SELECT DISTINCT RodovaLinie.v_jmeno,generace FROM  RodovaLinie WHERE generace != 0 ORDER BY generace;

-- 10 zenska

WITH RodovaLinie(v_jmeno, v_pohlavie, id_vydra, id_otec, id_matka, generace) AS (
    SELECT deti.JMENO, deti.POHLAVI, deti.CV, deti.OTEC, deti.MATKA, 0 AS generace
    FROM VYDRA deti
    WHERE deti.CV = 10
    UNION ALL
    SELECT rodicia.JMENO, rodicia.POHLAVI, rodicia.CV, rodicia.OTEC, rodicia.MATKA, generace + 1
    FROM VYDRA rodicia
    INNER JOIN RodovaLinie ON ( rodicia.CV = RodovaLinie.id_matka )

)
SELECT DISTINCT RodovaLinie.v_jmeno,generace FROM  RodovaLinie WHERE generace != 0 ORDER BY generace;

-- 10 obe 

WITH RodovaLinie(v_jmeno, v_pohlavie, id_vydra, id_otec, id_matka, generace) AS (
    SELECT deti.JMENO, deti.POHLAVI, deti.CV, deti.OTEC, deti.MATKA, 0 AS generace
    FROM VYDRA deti
    WHERE deti.CV = 10
    UNION ALL
    SELECT rodicia.JMENO, rodicia.POHLAVI, rodicia.CV, rodicia.OTEC, rodicia.MATKA, generace + 1
    FROM VYDRA rodicia
    INNER JOIN RodovaLinie ON ( ( rodicia.CV = RodovaLinie.id_otec OR rodicia.CV = RodovaLinie.id_matka ) )

)
SELECT DISTINCT RodovaLinie.v_jmeno,generace FROM  RodovaLinie WHERE generace != 0 ORDER BY generace;
