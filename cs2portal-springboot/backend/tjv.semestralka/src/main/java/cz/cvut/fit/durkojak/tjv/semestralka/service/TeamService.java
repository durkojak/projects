package cz.cvut.fit.durkojak.tjv.semestralka.service;

import cz.cvut.fit.durkojak.tjv.semestralka.domain.Team;
import org.springframework.stereotype.Component;

@Component
public interface TeamService extends CrudService<Team,Long>{

    void updateGlobalRanking(Long teamId,int newGlobalRanking);
    void changeTeamName(Long teamId,String newTeamName);

    void changeLanguage(Long teamId, String newLanguage);

    void addTeamToTournament(Long teamId, long tournamentId);

    void addPlayerToTeam(Long playerId, Long teamId);

    void deletePlayersWithLowKDAndLowTeamRanking();
}
