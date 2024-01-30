package cz.cvut.fit.durkojak.tjv.semestralka.controller;

import cz.cvut.fit.durkojak.tjv.semestralka.domain.Player;
import cz.cvut.fit.durkojak.tjv.semestralka.service.PlayerService;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.server.ResponseStatusException;

import java.awt.*;
import java.util.Optional;

@RestController
@RequestMapping(value = "/player", produces = MediaType.APPLICATION_JSON_VALUE)
@CrossOrigin(origins = "http://localhost:9000")
public class PlayerController {

    private PlayerService playerService;

    public PlayerController(PlayerService playerService) {
        this.playerService = playerService;
    }

    @PostMapping
    public Player create(@RequestBody Player data) {
        try {
            return playerService.create(data);
        } catch (IllegalArgumentException e) {
            throw new ResponseStatusException(HttpStatus.CONFLICT);
        }
    }

    @GetMapping("/{idPlayer}")
    public Optional<Player> readById(@PathVariable Long idPlayer) {
        return playerService.readById(idPlayer);
    }

    @GetMapping
    public Iterable<Player> getAll() {
        return playerService.readAll();
    }

    @PutMapping("/{idPlayer}")
    public void update(@PathVariable Long idPlayer, @RequestBody Player updatedData) {
        try {
            playerService.update(idPlayer, updatedData);
        } catch (IllegalArgumentException e) {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND);
        }
    }

    @DeleteMapping("/{idPlayer}")
    public void deleteById(@PathVariable Long idPlayer) {
        try {
            playerService.deleteById(idPlayer);
        } catch (IllegalArgumentException e) {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND);
        }
    }


}
