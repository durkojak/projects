package cz.cvut.fit.durkojak.tjv.semestralka;

import cz.cvut.fit.durkojak.tjv.semestralka.service.PlayerService;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.stereotype.Component;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Arrays;

@SpringBootApplication
@RestController
public class CSPortalApplication {

    public static void main(String[] args) {

        SpringApplication.run(CSPortalApplication.class, args);
    }
    @GetMapping
    public String hello() {
        return "Server is running!";
    }
}
