package cz.cvut.fit.durkojak.tjv.semestralka.repository;

import cz.cvut.fit.durkojak.tjv.semestralka.domain.Team;
import jakarta.transaction.Transactional;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

import java.util.List;
@Repository
public interface TeamRepository extends JpaRepository<Team,Long> {

    @Modifying
    @Transactional
    @Query("DELETE FROM Player p WHERE p.memberOf IN (SELECT t FROM Team t WHERE t.globalRanking < 30 AND p.kdRatio < 1)")
    void deletePlayersWithLowKDAndLowTeamRanking();

}
