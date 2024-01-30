package cz.cvut.fit.durkojak.tjv.semestralka.controller;

import cz.cvut.fit.durkojak.tjv.semestralka.domain.Player;
import cz.cvut.fit.durkojak.tjv.semestralka.domain.Team;
import cz.cvut.fit.durkojak.tjv.semestralka.domain.Tournament;
import cz.cvut.fit.durkojak.tjv.semestralka.service.PlayerService;
import cz.cvut.fit.durkojak.tjv.semestralka.service.TeamService;
import cz.cvut.fit.durkojak.tjv.semestralka.service.TournamentService;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.HttpStatusCodeException;
import org.springframework.web.server.ResponseStatusException;

import java.util.Optional;


@RestController
@RequestMapping(value = "/team")
@CrossOrigin(origins = "http://localhost:9000")
public class TeamController {

    private TeamService teamService;

    private PlayerService playerService;

    private TournamentService tournamentService;

    public TeamController(TeamService teamService, PlayerService playerService, TournamentService tournamentService) {
        this.teamService = teamService;
        this.playerService = playerService;
        this.tournamentService = tournamentService;
    }

    @PostMapping
    public Team create(@RequestBody Team data) {
        try {
            return teamService.create(data);
        } catch (IllegalArgumentException e) {
            throw new ResponseStatusException(HttpStatus.CONFLICT);
        }
    }

    @GetMapping("/{idTeam}")
    public Optional<Team> readById(@PathVariable Long idTeam) {
        return teamService.readById(idTeam);
    }

    @GetMapping
    public Iterable<Team> getAll() {
        return teamService.readAll();
    }

    @PutMapping("/{idTeam}")
    public void update(@PathVariable Long idTeam, @RequestBody Team updatedData) {
        try {
            teamService.update(idTeam, updatedData);
        } catch (IllegalArgumentException e) {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND);
        }
    }

    @PutMapping("/tournament/{teamId}/{tournamentId}")
    public void addTeamToTournament(@PathVariable Long teamId, @PathVariable Long tournamentId) {
        try {
            teamService.addTeamToTournament(teamId, tournamentId);
        } catch (IllegalArgumentException e) {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND);
        }
    }

    @PutMapping("/player/{teamId}/{playerId}")
    public void addPlayerToTeam(@PathVariable Long playerId, @PathVariable Long teamId) {
        try {
            teamService.addPlayerToTeam(playerId, teamId);
        } catch (IllegalArgumentException e) {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND);
        }
    }

    @DeleteMapping("/{idTeam}")
    public void deleteById(@PathVariable Long idTeam) {
        Optional<Team> teamOpt = teamService.readById(idTeam);

        if (!teamOpt.isPresent()) {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND);
        }

        Team team = teamOpt.get();


        for (Player player : team.getRosterOfTeam()) {
            player.setMemberOf(null);
            playerService.update(player.getIdPlayer(), player);
        }

        for (Tournament tournament : team.getParticipatedTournaments()) {
            tournament.getTeamsParticipating().remove(team);
            tournamentService.update(tournament.getIdTournament(), tournament);
        }
        teamService.deleteById(idTeam);
    }

    @DeleteMapping
    public void deletePlayersWithLowKDAndLowTeamRanking() {
        teamService.deletePlayersWithLowKDAndLowTeamRanking();
    }
}

