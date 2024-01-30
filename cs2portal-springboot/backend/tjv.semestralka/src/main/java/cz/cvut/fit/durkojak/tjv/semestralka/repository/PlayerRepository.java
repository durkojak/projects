package cz.cvut.fit.durkojak.tjv.semestralka.repository;

import cz.cvut.fit.durkojak.tjv.semestralka.domain.Player;
import cz.cvut.fit.durkojak.tjv.semestralka.domain.Team;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

import java.util.List;
@Repository
public interface PlayerRepository extends JpaRepository<Player,Long> {

    List<Player> findByFavGun(String favGun);
    List<Player> findByNickname(String nickname);

    List<Player> findByMemberOf(Team team);

    List<Player> findByKdRatioGreaterThanEqual(double kdRatio);

    List<Player> findByKdRatioLessThanEqual(double kdRatio);


}
