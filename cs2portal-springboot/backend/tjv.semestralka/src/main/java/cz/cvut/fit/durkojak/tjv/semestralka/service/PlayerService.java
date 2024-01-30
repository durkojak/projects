package cz.cvut.fit.durkojak.tjv.semestralka.service;

import cz.cvut.fit.durkojak.tjv.semestralka.domain.Player;
import cz.cvut.fit.durkojak.tjv.semestralka.domain.Team;
import cz.cvut.fit.durkojak.tjv.semestralka.repository.PlayerRepository;
import org.springframework.stereotype.Component;
import org.springframework.stereotype.Service;

@Component
public interface PlayerService extends CrudService<Player, Long> {


    void leaveTeam(Long playerId, Long teamId);

    void changeFavGun(Long playerId,String favGun);


    void changeKd(Long playerId, double newKd);


}
