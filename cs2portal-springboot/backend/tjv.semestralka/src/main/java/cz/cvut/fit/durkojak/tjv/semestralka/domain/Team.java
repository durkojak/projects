package cz.cvut.fit.durkojak.tjv.semestralka.domain;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.JsonManagedReference;
import jakarta.persistence.*;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Objects;

@Entity
@Table(name = "Team")
public class Team implements EntityWithId<Long> {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long idTeam;
    private String teamName;
    private int globalRanking;
    private String languageTeam;
    @OneToMany(mappedBy = "memberOf", fetch = FetchType.EAGER)
    @JsonIgnoreProperties("memberOf")
    private Collection<Player> rosterOfTeam = new ArrayList<>();
    @ManyToMany(mappedBy = "teamsParticipating",fetch = FetchType.EAGER)
    @JsonIgnoreProperties("teamsParticipating")
    private Collection<Tournament> participatedTournaments = new ArrayList<>();

    public Long getIdTeam() {
        return idTeam;
    }

    public void setIdTeam(Long idTeam) {
        this.idTeam = idTeam;
    }

    public String getTeamName() {
        return teamName;
    }

    public void setTeamName(String teamName) {
        this.teamName = teamName;
    }

    public int getGlobalRanking() {
        return globalRanking;
    }

    public void setGlobalRanking(int globalRanking) {
        this.globalRanking = globalRanking;
    }

    public String getLanguageTeam() {
        return languageTeam;
    }

    public void setLanguageTeam(String languageTeam) {
        this.languageTeam = languageTeam;
    }

    public Collection<Player> getRosterOfTeam() {
        return rosterOfTeam;
    }

    public void setRosterOfTeam(Collection<Player> rosterOfTeam) {
        this.rosterOfTeam = rosterOfTeam;
    }

    public Collection<Tournament> getParticipatedTournaments() {
        return participatedTournaments;
    }

    public void setParticipatedTournaments(Collection<Tournament> participatedTournaments) {
        this.participatedTournaments = participatedTournaments;
    }

    @Override
    public Long getId() {
        return this.idTeam;
    }

    @Override
    public void setId(Long newId){this.idTeam = newId;}

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Team team = (Team) o;
        return Objects.equals(idTeam, team.idTeam);
    }
}
