# Popis řešení

## Integritní omezení 1

- Pri sponzorovani timu v top 5 musi byt budget aspon nad 200000 a zaroven sponzor nemoze 2x sponzorovat ten isty tim


### Způsob řešeni 

- Pomocou triggeru : budget_big_enough 

## Integritní omezení 2

- Suma sponsorship budgetov nemoze presiahnut 2 000 000.

### Způsob řešeni 

- Implementoval som to pomocou package sponsor_pkg kde som vytvoril procedury ktore nahradzuju dml operace : add_new_sponsor, delete_sponsor a update_sponsor



