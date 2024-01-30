package cz.cvut.fit.durkojak.tjv.semestralka.service;

import cz.cvut.fit.durkojak.tjv.semestralka.domain.EntityWithId;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Component;

import java.util.Optional;
@Component
public abstract class CrudServiceImpl<T extends EntityWithId<ID>, ID> implements CrudService<T,ID> {
    @Override
    public T create(T e) {
        if(e.getId() == null){
            System.out.println("ID is missing");
        }
        else if (getRepository().existsById(e.getId())) {
            throw new IllegalArgumentException("Entity with ID " + e.getId() + " already exists.");
        }

        return getRepository().save(e);
    }

    @Override
    public Optional<T> readById(ID id) {
        return getRepository().findById(id);
    }

    @Override
    public Iterable<T> readAll() {
        return getRepository().findAll();
    }

    @Override
    public void update(ID id, T e) {
        if (getRepository().existsById(id)) {
            e.setId(id);
            getRepository().save(e);
        } else {
            throw new IllegalArgumentException("Entity with ID " + id + " not found");
        }

    }

    @Override
    public void deleteById(ID id) {
        if (!getRepository().existsById(id)){
            throw new IllegalArgumentException("Entity with ID " + id + " not found");
        }
        getRepository().deleteById(id);

    }

    protected abstract JpaRepository<T, ID> getRepository();
}