package cz.cvut.fit.durkojak.tjv.semestralka.service;

import cz.cvut.fit.durkojak.tjv.semestralka.domain.Team;
import cz.cvut.fit.durkojak.tjv.semestralka.domain.Tournament;
import cz.cvut.fit.durkojak.tjv.semestralka.repository.TeamRepository;
import cz.cvut.fit.durkojak.tjv.semestralka.repository.TournamentRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Service;

import java.util.Optional;

@Service
public class TournamentServiceImpl extends CrudServiceImpl<Tournament, Long> implements TournamentService {

    private TournamentRepository tournamentRepository;
    private TeamRepository teamRepository;
    @Autowired
    public TournamentServiceImpl(TournamentRepository tournamentRepository, TeamRepository teamRepository) {
        this.tournamentRepository = tournamentRepository;
        this.teamRepository = teamRepository;
    }

    @Override
    protected JpaRepository<Tournament, Long> getRepository() {
        return tournamentRepository;
    }

    @Override
    public void updatePrizePool(Long tournamentId, Long newPrizePool) {
        Optional<Tournament> optTournament = tournamentRepository.findById(tournamentId);

        if (optTournament.isEmpty()) {
            throw new IllegalArgumentException("invalid ID");
        }

        Tournament tournament = optTournament.get();

        tournament.setPrizePool(newPrizePool);
        tournamentRepository.save(tournament);
    }

    @Override
    public void updateTournamentName(Long tournamentId, String newName) {
        Optional<Tournament> optTournament = tournamentRepository.findById(tournamentId);

        if (optTournament.isEmpty()) {
            throw new IllegalArgumentException("invalid ID");
        }

        Tournament tournament = optTournament.get();

        tournament.setTournamentName(newName);
        tournamentRepository.save(tournament);
    }

    @Override
    public void updateLocation(Long tournamentId, String newLocation) {
        Optional<Tournament> optTournament = tournamentRepository.findById(tournamentId);

        if (optTournament.isEmpty()) {
            throw new IllegalArgumentException("invalid ID");
        }

        Tournament tournament = optTournament.get();

        tournament.setLocation(newLocation);
        tournamentRepository.save(tournament);
    }

}
