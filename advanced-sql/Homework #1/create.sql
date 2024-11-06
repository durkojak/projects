CREATE TABLE professional_team (
    id_professional_team INTEGER,
    team_name VARCHAR2(40) NOT NULL,
    CONSTRAINT pk_professional_team PRIMARY KEY (id_professional_team)

);

CREATE TABLE sponsor (
    id_sponsor INTEGER,
    sponsor_name VARCHAR2(40) NOT NULL,
    CONSTRAINT pk_sponsor PRIMARY KEY (id_sponsor)
);

CREATE TABLE sponsor_professional_team (
    id_sponsor NUMBER NOT NULL,
    id_professional_team NUMBER NOT NULL,
    CONSTRAINT pk_spt PRIMARY KEY (id_sponsor, id_professional_team)
);
