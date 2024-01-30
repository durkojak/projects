package cz.cvut.fit.durkojak.tjv.semestralka.domain;

public interface EntityWithId<ID> {
    ID getId();

    void setId(ID newId);
}