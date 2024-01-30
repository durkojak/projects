package cz.cvut.fit.durkojak.tjv.semestralka.repository;

import cz.cvut.fit.durkojak.tjv.semestralka.domain.Tournament;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface TournamentRepository extends JpaRepository<Tournament, Long> {


}
