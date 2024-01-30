package cz.cvut.fit.durkojak.tjv.semestralka.service;

import cz.cvut.fit.durkojak.tjv.semestralka.domain.Player;
import cz.cvut.fit.durkojak.tjv.semestralka.domain.Team;
import cz.cvut.fit.durkojak.tjv.semestralka.repository.PlayerRepository;
import cz.cvut.fit.durkojak.tjv.semestralka.repository.TeamRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Service;

import java.util.Collection;
import java.util.Optional;

@Service
public class PlayerServiceImpl extends CrudServiceImpl<Player, Long> implements PlayerService {
    private PlayerRepository playerRepository;
    private TeamRepository teamRepository;

    @Autowired
    public PlayerServiceImpl(PlayerRepository playerRepository, TeamRepository teamRepository) {
        this.playerRepository = playerRepository;
        this.teamRepository = teamRepository;
    }
    public PlayerServiceImpl() {
    }

    @Override
    public void leaveTeam(Long playerId, Long teamId) {
        Optional<Player> optPlayer = playerRepository.findById(playerId);
        Optional<Team> optTeam = teamRepository.findById(teamId);

        if (optTeam.isEmpty() || optPlayer.isEmpty()) {
            throw new IllegalArgumentException("invalid ID");
        }

        Team team = optTeam.get();
        Player player = optPlayer.get();

        team.getRosterOfTeam().remove(player);
        player.setMemberOf(null);
        teamRepository.save(team);
        playerRepository.save(player);
    }

    @Override
    public void changeFavGun(Long playerId, String favGun) {
        Optional<Player> optPlayer = playerRepository.findById(playerId);
        if (optPlayer.isEmpty()) {
            throw new IllegalArgumentException("invalid ID");
        }

        Player player = optPlayer.get();
        player.setFavGun(favGun);
        playerRepository.save(player);
    }

    @Override
    public void changeKd(Long playerId, double newKd) {
        Optional<Player> optPlayer = playerRepository.findById(playerId);
        if (optPlayer.isEmpty()) {
            throw new IllegalArgumentException("invalid ID");
        }

        Player player = optPlayer.get();
        player.setKdRatio(newKd);
        playerRepository.save(player);
    }


    @Override
    protected JpaRepository<Player, Long> getRepository() {
        return playerRepository;
    }
}
