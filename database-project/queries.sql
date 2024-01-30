-- Vypíš tímy, ktoré nehrajú na žiadnom turnaji.
--
select team_name from professional_team
except
select team_name from professional_team p
    join tournament_professional_team tpt on tpt.id_professional_team = p.id_professional_team
;
-- 
select team_name from professional_team p
    where p.id_professional_team not in (select tournament_professional_team.id_professional_team from tournament_professional_team)
;
    
    

-- Ktorý hráči používajú myš Zowie a majú dpi 800?

select name from sponsor
    join sponsor_professional_team using (id_sponsor)
    join professional_team using(id_professional_team)
    where global_ranking = 1
    
--Vyber tých sponzorov, ktorí sponzorujú iba anglicky hovoriace tímy.

select name from sponsor
    join sponsor_professional_team using (id_sponsor)
    join professional_team using(id_professional_team)
    where language = 'English'
    
except

select name from sponsor
    join sponsor_professional_team using (id_sponsor)
    join professional_team using(id_professional_team)
    where language != 'English'
    
    
-- Nájdi nového sponzora pre top1 tím
insert into sponsor_professional_team(
select sponsor.id_sponsor,sponsor_professional_team.id_professional_team from sponsor_professional_team
    cross join sponsor
    join professional_team using(id_professional_team)
    where global_ranking = 1
order by random() limit 1
);

select team_name,sponsor.name from professional_team
    join sponsor_professional_team using(id_professional_team)
    join sponsor using(id_sponsor)
    where global_ranking = 1;

rollback;
