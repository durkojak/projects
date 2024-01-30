package cz.cvut.fit.durkojak.tjv.semestralka.domain;

import com.fasterxml.jackson.annotation.JsonBackReference;
import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import jakarta.persistence.*;

import java.util.Objects;

@Entity
@Table(name = "Player")
public class Player implements EntityWithId<Long> {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long idPlayer;

    private String nickname;

    private double kdRatio;

    private String favGun;
    @ManyToOne
    @JsonIgnoreProperties({"rosterOfTeam","participatedTournaments"})
    private Team memberOf;

    public Player() {
    }

    public Player(String nickname, String favGun) {
        this.nickname = nickname;
        this.favGun = favGun;
    }

    public Long getIdPlayer() {
        return idPlayer;
    }

    public void setIdPlayer(Long idPlayer) {
        this.idPlayer = idPlayer;
    }

    public String getNickname() {
        return nickname;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }

    public double getKdRatio() {
        return kdRatio;
    }

    public void setKdRatio(double kdRatio) {
        this.kdRatio = kdRatio;
    }

    public String getFavGun() {
        return favGun;
    }

    public void setFavGun(String favGun) {
        this.favGun = favGun;
    }

    public Team getMemberOf() {
        return memberOf;
    }

    public void setMemberOf(Team memberOf) {
        this.memberOf = memberOf;
    }

    @Override
    public Long getId() {
        return idPlayer;
    }

    @Override
    public void setId(Long newId){this.idPlayer = newId;}

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Player player = (Player) o;
        return Objects.equals(idPlayer, player.idPlayer) &&
                Objects.equals(nickname, player.nickname) &&
                Objects.equals(favGun, player.favGun);
    }


}
