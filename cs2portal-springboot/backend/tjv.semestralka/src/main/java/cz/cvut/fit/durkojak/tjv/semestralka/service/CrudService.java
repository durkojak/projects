package cz.cvut.fit.durkojak.tjv.semestralka.service;

import org.springframework.stereotype.Component;

import java.util.Optional;
@Component
public interface CrudService<T, ID> {
    T create(T e);
    Optional<T> readById(ID id);
    Iterable<T> readAll();
    void update(ID id, T e);
    void deleteById(ID id);
}
