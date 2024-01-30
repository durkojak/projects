package cz.cvut.fit.durkojak.tjv.semestralka.service.repository;

import cz.cvut.fit.durkojak.tjv.semestralka.domain.Player;
import cz.cvut.fit.durkojak.tjv.semestralka.repository.PlayerRepository;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

@DataJpaTest
public class PlayerRepositoryTest {

    @Autowired
    PlayerRepository playerRepository;

    @Test
    void findByFavGunAWP(){
        var p1 = new Player();
        var p2 = new Player();
        var p3 = new Player();

        p1.setNickname("Player1");
        p1.setFavGun("AWP");
        p1.setIdPlayer(1L);

        p2.setNickname("Player2");
        p2.setFavGun("AK-47");
        p2.setIdPlayer(2L);

        p3.setNickname("Player3");
        p3.setFavGun("AWP");
        p3.setIdPlayer(3L);

        playerRepository.save(p1);
        playerRepository.save(p2);
        playerRepository.save(p3);

        var res = playerRepository.findByFavGun("AWP");
        Assertions.assertIterableEquals(List.of(p1,p3),res);
        Assertions.assertEquals(2, res.size());
    }

    @Test
    void findByFavGunNotInRepo(){
        var p1 = new Player();
        var p2 = new Player();
        var p3 = new Player();

        p1.setNickname("Player1");
        p1.setFavGun("AWP");
        p1.setIdPlayer(1L);

        p2.setNickname("Player2");
        p2.setFavGun("AK-47");
        p2.setIdPlayer(2L);

        p3.setNickname("Player3");
        p3.setFavGun("AWP");
        p3.setIdPlayer(3L);

        playerRepository.save(p1);
        playerRepository.save(p2);
        playerRepository.save(p3);

        var res = playerRepository.findByFavGun("M4A4");
        assertTrue(res.isEmpty(), "The result should be empty");
        assertEquals(0, res.size(), "The result size should be 0");
    }

    @Test
    void findByFavGunEmptyRepo(){
        var resEmptyRepo = playerRepository.findByFavGun("AWP");
        assertTrue(resEmptyRepo.isEmpty(), "The result should be empty for an empty repository");
    }

    @Test
    void findByFavGunCaseInsensitiveNotSupported(){
        var p1 = new Player();
        var p2 = new Player();
        var p3 = new Player();

        p1.setNickname("Player1");
        p1.setFavGun("AWP");
        p1.setIdPlayer(1L);

        p2.setNickname("Player2");
        p2.setFavGun("AK-47");
        p2.setIdPlayer(2L);

        p3.setNickname("Player3");
        p3.setFavGun("AWP");
        p3.setIdPlayer(3L);

        playerRepository.save(p1);
        playerRepository.save(p2);
        playerRepository.save(p3);

        var resEmptyRepo = playerRepository.findByFavGun("awp");
        assertTrue(resEmptyRepo.isEmpty(), "Project doesn't support case insensitive therefore it should be empty");
    }
}
