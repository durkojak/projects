package cz.cvut.fit.durkojak.tjv.semestralka.service;

import cz.cvut.fit.durkojak.tjv.semestralka.domain.Tournament;
import org.springframework.stereotype.Component;

@Component
public interface TournamentService extends CrudService<Tournament,Long>{

    void updatePrizePool(Long tournamentId, Long newPrizePool);
    void updateTournamentName(Long tournamentId, String newName);
    void updateLocation(Long tournamentId, String newLocation);



}
