package cz.cvut.fit.durkojak.tjv.semestralka.service.controller;


import cz.cvut.fit.durkojak.tjv.semestralka.controller.PlayerController;
import cz.cvut.fit.durkojak.tjv.semestralka.domain.Player;
import cz.cvut.fit.durkojak.tjv.semestralka.service.PlayerService;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mockito;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.http.MediaType;
import org.springframework.test.context.junit.jupiter.SpringExtension;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultHandlers;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;

import java.util.Optional;

import static org.mockito.Mockito.doThrow;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@ExtendWith(SpringExtension.class)
@WebMvcTest(PlayerController.class)
@AutoConfigureMockMvc
public class PlayerControllerMvcTest {

    @Autowired
    private MockMvc mockMvc;

    @MockBean
    private PlayerService playerService;

    private Player player;

    @BeforeEach
    void setUp(){
        player = new Player();
        player.setNickname("HttpTestPlayer");
        player.setIdPlayer(1L);
        player.setFavGun("Glock-18");
        player.setKdRatio(1.0);
        player.setMemberOf(null);

    }

    @Test
    public void create() throws Exception{
        Mockito.when(playerService.create(Mockito.any())).thenReturn(player);

        mockMvc.perform(
                MockMvcRequestBuilders
                        .post("/player")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content("{\n" +
                                "  \"nickname\": \"HttpTestPlayer\",\n" +
                                "  \"kdRatio\": 1.0,\n" +
                                "  \"favGun\": \"Glock-18\",\n" +
                                "  \"memberOf\": null\n" +
                                "}")
        )
                .andDo(MockMvcResultHandlers.print())
                .andExpect(status().isOk())
                .andExpect(MockMvcResultMatchers.jsonPath("$.nickname", Matchers.is("HttpTestPlayer")))
                .andExpect(MockMvcResultMatchers.jsonPath("$.kdRatio", Matchers.is(1.0)))
                .andExpect(MockMvcResultMatchers.jsonPath("$.favGun", Matchers.is("Glock-18")))
                .andExpect(MockMvcResultMatchers.jsonPath("$.memberOf").doesNotExist());
    }

    @Test
    public void getById() throws Exception {
        Long playerId = player.getIdPlayer();;


        Mockito.when(playerService.readById(Mockito.any())).thenReturn(Optional.of(player));

        mockMvc.perform(MockMvcRequestBuilders
                        .get("/player/{id}", playerId)
                        .contentType(MediaType.APPLICATION_JSON))
                .andDo(MockMvcResultHandlers.print())
                .andExpect(status().isOk())
                .andExpect(MockMvcResultMatchers.jsonPath("$.nickname", Matchers.is("HttpTestPlayer")))
                .andExpect(MockMvcResultMatchers.jsonPath("$.kdRatio", Matchers.is(1.0)))
                .andExpect(MockMvcResultMatchers.jsonPath("$.favGun", Matchers.is("Glock-18")))
                .andExpect(MockMvcResultMatchers.jsonPath("$.memberOf").doesNotExist());
    }

    @Test
    public void deleteThrowsException() throws Exception{
        Long playerId = 3L;

        doThrow(IllegalArgumentException.class).when(playerService).deleteById(playerId);


        mockMvc.perform(
                MockMvcRequestBuilders
                        .delete("/player/{id}", playerId)
                        .contentType(MediaType.APPLICATION_JSON)
                )
                .andExpect(status().isNotFound());
    }

}
