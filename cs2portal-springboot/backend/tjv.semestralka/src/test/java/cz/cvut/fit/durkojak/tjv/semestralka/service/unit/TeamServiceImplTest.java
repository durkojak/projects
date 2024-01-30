package cz.cvut.fit.durkojak.tjv.semestralka.service.unit;

import cz.cvut.fit.durkojak.tjv.semestralka.domain.Player;
import cz.cvut.fit.durkojak.tjv.semestralka.domain.Team;
import cz.cvut.fit.durkojak.tjv.semestralka.repository.PlayerRepository;
import cz.cvut.fit.durkojak.tjv.semestralka.repository.TeamRepository;
import cz.cvut.fit.durkojak.tjv.semestralka.service.TeamServiceImpl;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;

import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;
@SpringBootTest
class TeamServiceImplTest {
    @Autowired
    TeamServiceImpl teamServiceImpl;

    @MockBean
    private PlayerRepository playerRepository;
    @MockBean
    private TeamRepository teamRepository;



    @Test
    void addPlayerToTeamSuccesful() {
        Player p1 = new Player();
        p1.setFavGun("AWP");
        p1.setNickname("testPlayer");
        p1.setIdPlayer(1L);

        Team t1 = new Team();
        t1.setIdTeam(2L);

        Mockito.when(teamRepository.findById(t1.getId())).thenReturn(Optional.of(t1));
        Mockito.when(playerRepository.findById(p1.getId())).thenReturn(Optional.of(p1));

        teamServiceImpl.addPlayerToTeam(p1.getIdPlayer(),t1.getIdTeam());

        Mockito.verify(teamRepository, Mockito.times(1)).save(Mockito.any());
        Mockito.verify(playerRepository, Mockito.times(1)).save(Mockito.any());

        Mockito.verify(teamRepository,Mockito.times(1)).findById(Mockito.any());
        Mockito.verify(playerRepository,Mockito.times(1)).findById(Mockito.any());

    }
    @Test
    void addPlayerToTeamThrowsExceptionInvalidTeamId(){
        Player p1 = new Player();
        p1.setIdPlayer(1L);

        Team t1 = new Team();
        t1.setIdTeam(2L);

        Mockito.when(teamRepository.findById(t1.getId())).thenReturn(Optional.empty());
        Mockito.when(playerRepository.findById(p1.getId())).thenReturn(Optional.of(p1));

        assertThrows(IllegalArgumentException.class,
                () -> teamServiceImpl.addPlayerToTeam(p1.getIdPlayer(), t1.getIdTeam()),
                "Team with ID " + t1.getIdTeam() + " does not exist");

        Mockito.verify(teamRepository, Mockito.never()).save(Mockito.any());
        Mockito.verify(playerRepository, Mockito.never()).save(Mockito.any());

    }

    @Test
    void addPlayerToTeamThrowsExceptionInvalidPlayerId(){
        Player p1 = new Player();
        p1.setIdPlayer(1L);

        Team t1 = new Team();
        t1.setIdTeam(2L);

        Mockito.when(teamRepository.findById(t1.getId())).thenReturn(Optional.of(t1));
        Mockito.when(playerRepository.findById(p1.getId())).thenReturn(Optional.empty());

        assertThrows(IllegalArgumentException.class,
                () -> teamServiceImpl.addPlayerToTeam(p1.getIdPlayer(), t1.getIdTeam()),
                "Player with ID " + p1.getIdPlayer() + " does not exist");

        Mockito.verify(teamRepository, Mockito.never()).save(Mockito.any());
        Mockito.verify(playerRepository, Mockito.never()).save(Mockito.any());

    }
}