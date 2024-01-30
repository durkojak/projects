package cz.cvut.fit.durkojak.tjv.semestralka.service;

import cz.cvut.fit.durkojak.tjv.semestralka.domain.Player;
import cz.cvut.fit.durkojak.tjv.semestralka.domain.Team;
import cz.cvut.fit.durkojak.tjv.semestralka.domain.Tournament;
import cz.cvut.fit.durkojak.tjv.semestralka.repository.PlayerRepository;
import cz.cvut.fit.durkojak.tjv.semestralka.repository.TeamRepository;
import cz.cvut.fit.durkojak.tjv.semestralka.repository.TournamentRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Service;

import java.util.Optional;

@Service
public class TeamServiceImpl extends CrudServiceImpl<Team,Long> implements TeamService{
    TeamRepository teamRepository;
    PlayerRepository playerRepository;

    TournamentRepository tournamentRepository;
    @Autowired
    public TeamServiceImpl(TeamRepository teamRepository, PlayerRepository playerRepository,TournamentRepository tournamentRepository) {
        this.teamRepository = teamRepository;
        this.playerRepository = playerRepository;
        this.tournamentRepository = tournamentRepository;
    }

    @Override
    protected JpaRepository<Team, Long> getRepository() {
        return teamRepository;
    }

    @Override
    public void updateGlobalRanking(Long teamId, int newGlobalRanking) {
        Optional<Team> optTeam = teamRepository.findById(teamId);

        if (optTeam.isEmpty()) {
            throw new IllegalArgumentException("invalid ID");
        }

        Team team = optTeam.get();

        team.setGlobalRanking(newGlobalRanking);
        teamRepository.save(team);
    }

    @Override
    public void changeTeamName(Long teamId, String newTeamName) {
        Optional<Team> optTeam = teamRepository.findById(teamId);

        if (optTeam.isEmpty()) {
            throw new IllegalArgumentException("invalid ID");
        }

        Team team = optTeam.get();

        team.setTeamName(newTeamName);
        teamRepository.save(team);
    }

    @Override
    public void changeLanguage(Long teamId, String newLanguage) {
        Optional<Team> optTeam = teamRepository.findById(teamId);

        if (optTeam.isEmpty()) {
            throw new IllegalArgumentException("invalid ID");
        }

        Team team = optTeam.get();

        team.setLanguageTeam(newLanguage);
        teamRepository.save(team);
    }



    @Override
    public void addTeamToTournament(Long teamId, long tournamentId) {
        Optional<Team> teamOpt = teamRepository.findById(teamId);
        if (!teamOpt.isPresent()) {
            throw new IllegalArgumentException("Team with ID " + teamId + " does not exist");
        }

        Team team = teamOpt.get();

        Optional<Tournament> tournamentOpt = tournamentRepository.findById(tournamentId);

        if (!tournamentOpt.isPresent()) {
            throw new IllegalArgumentException("Tournament with ID " + tournamentId + " does not exist");
        }
        Tournament tournament = tournamentOpt.get();

        // Add the tournament to the team and vice versa
        team.getParticipatedTournaments().add(tournament);
        tournament.getTeamsParticipating().add(team);

        teamRepository.save(team);
        tournamentRepository.save(tournament);
    }

    @Override
    public void addPlayerToTeam(Long playerId, Long teamId){
        Optional<Team> teamOpt = teamRepository.findById(teamId);
        if (!teamOpt.isPresent()) {
            throw new IllegalArgumentException("Team with ID " + teamId + " does not exist");
        }

        Team team = teamOpt.get();

        Optional<Player> playerOpt = playerRepository.findById(playerId);

        if (!playerOpt.isPresent()) {
            throw new IllegalArgumentException("Player with ID " + playerId + " does not exist");
        }

        Player player = playerOpt.get();



        team.getRosterOfTeam().add(player);
        player.setMemberOf(team);

        teamRepository.save(team);
        playerRepository.save(player);


    }

    @Override
    public void deletePlayersWithLowKDAndLowTeamRanking() {
        teamRepository.deletePlayersWithLowKDAndLowTeamRanking();
    }


}
