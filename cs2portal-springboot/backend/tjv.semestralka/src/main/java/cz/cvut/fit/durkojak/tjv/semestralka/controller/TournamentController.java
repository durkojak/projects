package cz.cvut.fit.durkojak.tjv.semestralka.controller;

import cz.cvut.fit.durkojak.tjv.semestralka.domain.Tournament;
import cz.cvut.fit.durkojak.tjv.semestralka.service.TournamentService;
import org.springframework.http.HttpStatus;
import org.springframework.http.HttpStatusCode;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.server.ResponseStatusException;

import java.util.Optional;

@RestController
@RequestMapping(value = "/tournament")
@CrossOrigin(origins = "http://localhost:9000")
public class TournamentController {

    private TournamentService tournamentService;

    public TournamentController(TournamentService tournamentService) {
        this.tournamentService = tournamentService;
    }

    @PostMapping
    public Tournament create(@RequestBody Tournament data) {
        try {
            return tournamentService.create(data);
        } catch (IllegalArgumentException e) {
            throw new ResponseStatusException(HttpStatus.CONFLICT);
        }
    }

    @GetMapping("/{idTournament}")
    public Optional<Tournament> readById(@PathVariable Long idTournament) {
        return tournamentService.readById(idTournament);
    }

    @GetMapping
    public Iterable<Tournament> getAll() {
        return tournamentService.readAll();
    }

    @PutMapping("/{idTournament}")
    public void update(@PathVariable Long idTournament, @RequestBody Tournament updatedData) {
        try {
            tournamentService.update(idTournament, updatedData);
        } catch (IllegalArgumentException e) {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND);
        }
    }

    @DeleteMapping("/{idTournament}")
    public void deleteById(@PathVariable Long idTournament) {

        try {
            tournamentService.deleteById(idTournament);
        } catch (IllegalArgumentException e) {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND);
        }
    }

}
