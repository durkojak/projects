
DROP FUNCTION IF EXISTS remove_all();

CREATE or replace FUNCTION remove_all() RETURNS void AS $$
DECLARE
    rec RECORD;
    cmd text;
BEGIN
    cmd := '';

    FOR rec IN SELECT
            'DROP SEQUENCE ' || quote_ident(n.nspname) || '.'
                || quote_ident(c.relname) || ' CASCADE;' AS name
        FROM
            pg_catalog.pg_class AS c
        LEFT JOIN
            pg_catalog.pg_namespace AS n
        ON
            n.oid = c.relnamespace
        WHERE
            relkind = 'S' AND
            n.nspname NOT IN ('pg_catalog', 'pg_toast') AND
            pg_catalog.pg_table_is_visible(c.oid)
    LOOP
        cmd := cmd || rec.name;
    END LOOP;

    FOR rec IN SELECT
            'DROP TABLE ' || quote_ident(n.nspname) || '.'
                || quote_ident(c.relname) || ' CASCADE;' AS name
        FROM
            pg_catalog.pg_class AS c
        LEFT JOIN
            pg_catalog.pg_namespace AS n
        ON
            n.oid = c.relnamespace WHERE relkind = 'r' AND
            n.nspname NOT IN ('pg_catalog', 'pg_toast') AND
            pg_catalog.pg_table_is_visible(c.oid)
    LOOP
        cmd := cmd || rec.name;
    END LOOP;

    EXECUTE cmd;
    RETURN;
END;
$$ LANGUAGE plpgsql;

select remove_all();



-- End of removing

CREATE TABLE equipment (
    id_equipment SERIAL NOT NULL,
    brand VARCHAR(40) NOT NULL,
    model VARCHAR(40)
);
ALTER TABLE equipment ADD CONSTRAINT pk_equipment PRIMARY KEY (id_equipment);

CREATE TABLE gun (
    id_player INTEGER NOT NULL,
    name_of_gun VARCHAR(40) NOT NULL,
    kills INTEGER NOT NULL,
    adr INTEGER NOT NULL,
    hs_ratio DOUBLE PRECISION
);
ALTER TABLE gun ADD CONSTRAINT pk_gun PRIMARY KEY (id_player);

CREATE TABLE keyboard (
    id_equipment INTEGER NOT NULL,
    rgb BOOLEAN NOT NULL
);
ALTER TABLE keyboard ADD CONSTRAINT pk_keyboard PRIMARY KEY (id_equipment);

CREATE TABLE map (
    id_map SERIAL NOT NULL,
    name VARCHAR(40) NOT NULL
);
ALTER TABLE map ADD CONSTRAINT pk_map PRIMARY KEY (id_map);

CREATE TABLE monitor (
    id_equipment INTEGER NOT NULL,
    resolution VARCHAR(20) NOT NULL,
    hertz INTEGER NOT NULL
);
ALTER TABLE monitor ADD CONSTRAINT pk_monitor PRIMARY KEY (id_equipment);

CREATE TABLE mouse (
    id_equipment INTEGER NOT NULL,
    dpi INTEGER NOT NULL,
    sensitivity DOUBLE PRECISION NOT NULL
);
ALTER TABLE mouse ADD CONSTRAINT pk_mouse PRIMARY KEY (id_equipment);

CREATE TABLE player (
    id_player SERIAL NOT NULL,
    keyboard_id_equipment INTEGER NOT NULL,
    id_map INTEGER NOT NULL,
    mouse_id_equipment INTEGER NOT NULL,
    monitor_id_equipment INTEGER NOT NULL,
    id_professional_team INTEGER,
    id_role INTEGER NOT NULL,
    nickname VARCHAR(40) NOT NULL,
    language VARCHAR(40) NOT NULL,
    kd_ratio DOUBLE PRECISION NOT NULL
);
ALTER TABLE player ADD CONSTRAINT pk_player PRIMARY KEY (id_player);

CREATE TABLE professional_team (
    id_professional_team SERIAL NOT NULL,
    professional_team_id_profession INTEGER,
    global_ranking INTEGER NOT NULL,
    team_name VARCHAR(40) NOT NULL,
    language VARCHAR(40) NOT NULL
);
ALTER TABLE professional_team ADD CONSTRAINT pk_professional_team PRIMARY KEY (id_professional_team);

CREATE TABLE role (
    id_role SERIAL NOT NULL,
    name_of_role VARCHAR(40) NOT NULL
);
ALTER TABLE role ADD CONSTRAINT pk_role PRIMARY KEY (id_role);

CREATE TABLE sponsor (
    id_sponsor SERIAL NOT NULL,
    id_tournament INTEGER,
    name VARCHAR(40) NOT NULL,
    gaming_equipment VARCHAR(40) NOT NULL,
    country VARCHAR(40) NOT NULL
);
ALTER TABLE sponsor ADD CONSTRAINT pk_sponsor PRIMARY KEY (id_sponsor);

CREATE TABLE tournament (
    id_tournament SERIAL NOT NULL,
    name VARCHAR(40) NOT NULL,
    prize_pool INTEGER NOT NULL,
    place VARCHAR(40) NOT NULL
);
ALTER TABLE tournament ADD CONSTRAINT pk_tournament PRIMARY KEY (id_tournament);

CREATE TABLE sponsor_professional_team (
    id_sponsor INTEGER NOT NULL,
    id_professional_team INTEGER NOT NULL
);
ALTER TABLE sponsor_professional_team ADD CONSTRAINT pk_sponsor_professional_team PRIMARY KEY (id_sponsor, id_professional_team);

CREATE TABLE tournament_professional_team (
    id_tournament INTEGER NOT NULL,
    id_professional_team INTEGER NOT NULL
);
ALTER TABLE tournament_professional_team ADD CONSTRAINT pk_tournament_professional_team PRIMARY KEY (id_tournament, id_professional_team);

ALTER TABLE gun ADD CONSTRAINT fk_gun_player FOREIGN KEY (id_player) REFERENCES player (id_player) ON DELETE CASCADE;

ALTER TABLE keyboard ADD CONSTRAINT fk_keyboard_equipment FOREIGN KEY (id_equipment) REFERENCES equipment (id_equipment) ON DELETE CASCADE;

ALTER TABLE monitor ADD CONSTRAINT fk_monitor_equipment FOREIGN KEY (id_equipment) REFERENCES equipment (id_equipment) ON DELETE CASCADE;

ALTER TABLE mouse ADD CONSTRAINT fk_mouse_equipment FOREIGN KEY (id_equipment) REFERENCES equipment (id_equipment) ON DELETE CASCADE;

ALTER TABLE player ADD CONSTRAINT fk_player_keyboard FOREIGN KEY (keyboard_id_equipment) REFERENCES keyboard (id_equipment) ON DELETE CASCADE;
ALTER TABLE player ADD CONSTRAINT fk_player_map FOREIGN KEY (id_map) REFERENCES map (id_map) ON DELETE CASCADE;
ALTER TABLE player ADD CONSTRAINT fk_player_mouse FOREIGN KEY (mouse_id_equipment) REFERENCES mouse (id_equipment) ON DELETE CASCADE;
ALTER TABLE player ADD CONSTRAINT fk_player_monitor FOREIGN KEY (monitor_id_equipment) REFERENCES monitor (id_equipment) ON DELETE CASCADE;
ALTER TABLE player ADD CONSTRAINT fk_player_professional_team FOREIGN KEY (id_professional_team) REFERENCES professional_team (id_professional_team) ON DELETE CASCADE;
ALTER TABLE player ADD CONSTRAINT fk_player_role FOREIGN KEY (id_role) REFERENCES role (id_role) ON DELETE CASCADE;

ALTER TABLE professional_team ADD CONSTRAINT fk_professional_team_profession FOREIGN KEY (professional_team_id_profession) REFERENCES professional_team (id_professional_team) ON DELETE CASCADE;

ALTER TABLE sponsor ADD CONSTRAINT fk_sponsor_tournament FOREIGN KEY (id_tournament) REFERENCES tournament (id_tournament) ON DELETE CASCADE;

ALTER TABLE sponsor_professional_team ADD CONSTRAINT fk_sponsor_professional_team_sp FOREIGN KEY (id_sponsor) REFERENCES sponsor (id_sponsor) ON DELETE CASCADE;
ALTER TABLE sponsor_professional_team ADD CONSTRAINT fk_sponsor_professional_team_pr FOREIGN KEY (id_professional_team) REFERENCES professional_team (id_professional_team) ON DELETE CASCADE;

ALTER TABLE tournament_professional_team ADD CONSTRAINT fk_tournament_professional_team FOREIGN KEY (id_tournament) REFERENCES tournament (id_tournament) ON DELETE CASCADE;
ALTER TABLE tournament_professional_team ADD CONSTRAINT fk_tournament_professional_te_1 FOREIGN KEY (id_professional_team) REFERENCES professional_team (id_professional_team) ON DELETE CASCADE;


-- io checks

--io3
ALTER TABLE tournament ADD CONSTRAINT poolcheck check ( tournament.prize_pool >= 100000  );

--io5
ALTER TABLE professional_team ADD CONSTRAINT acadcheck check (id_professional_team != professional_team_id_profession);

--io4
ALTER TABLE map ADD CONSTRAINT mapcheck check (name in ('Ancient','Mirage','Dust','Inferno','Overpass','Nuke','Train'));

--io2
ALTER TABLE gun ADD CONSTRAINT hscheck check (name_of_gun = 'AWP' or hs_ratio IS NOT NULL);
