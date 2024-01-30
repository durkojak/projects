package cz.cvut.fit.durkojak.tjv.semestralka.domain;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.Id;
import jakarta.persistence.ManyToMany;

import java.util.ArrayList;
import java.util.Collection;
import jakarta.persistence.*;
@Entity
@Table(name = "Tournament")
public class Tournament implements EntityWithId<Long> {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long idTournament;

    private String tournamentName;

    private Long prizePool;

    private String location;
    @ManyToMany
    @JsonIgnoreProperties({"participatedTournaments","rosterOfTeam"})
    private Collection<Team> teamsParticipating = new ArrayList<>();

    public Long getIdTournament() {
        return idTournament;
    }

    public void setIdTournament(Long idTournament) {
        this.idTournament = idTournament;
    }

    public String getTournamentName() {
        return tournamentName;
    }

    public void setTournamentName(String tournamentName) {
        this.tournamentName = tournamentName;
    }

    public Long getPrizePool() {
        return prizePool;
    }

    public void setPrizePool(Long prizePool) {
        this.prizePool = prizePool;
    }

    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public Collection<Team> getTeamsParticipating() {
        return teamsParticipating;
    }

    public void setTeamsParticipating(Collection<Team> teamsParticipating) {
        this.teamsParticipating = teamsParticipating;
    }

    @Override
    public Long getId() {
        return this.idTournament;
    }

    @Override
    public void setId(Long newId){this.idTournament = newId;}
}
