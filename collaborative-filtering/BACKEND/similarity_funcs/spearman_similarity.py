from sqlalchemy.orm import Session
from BACKEND.Models.models import Rating
from typing import List
from BACKEND.config import DATABASE_PATH

def rank(values: List[float]) -> List[float]:
    # Enumerate the values to get pairs of (index, value)
    enumerated_values = enumerate(values)

    # Create a list of tuples (value, index) from the enumerated values
    value_index_pairs = [(val, i) for i, val in enumerated_values]

    # Sort the list of tuples by value
    # rank 1 je najhorsie hodnotenie, sice v zadani je ze rank 1 je najlepsie ale to je jedno viacmenej
    # ide o relativnu poziciu iba
    sorted_vals = sorted(value_index_pairs)

    # Create a list to hold the ranks
    ranks = [0] * len(values)
    i = 0
    # Iterate through the sorted list and assign ranks
    while i < len(values):
        # same bude sluzit na to aby som ukladal indexy ( poziciu ) hodnoteni aby som ziskal potom average rank

        same = [i]
        while i + 1 < len(values) and sorted_vals[i][0] == sorted_vals[i + 1][0]:
            i += 1
            same.append(i)
        avg_rank = sum(s + 1 for s in same) / len(same)
        for s in same:
            ranks[sorted_vals[s][1]] = avg_rank
        i += 1
    return ranks

def spearman_similarity(ratings_a: List[Rating], ratings_b: List[Rating]) -> float:
    # najprv vytvorim array kde mame pary id_filmu : rating (1-5)

    ratings_a_dict = {rating.item_id: rating.value for rating in ratings_a}
    ratings_b_dict = {rating.item_id: rating.value for rating in ratings_b}

    # najde spolocne hodnotene filmy pomocou intersection
    common_movie_ids = list(set(ratings_a_dict) & set(ratings_b_dict))
    n = len(common_movie_ids)

    if n < 2:
        return 0  # Not enough data to compute similarity

    # vytvorim pole hodnot ratingov pre kazdeho uzivatela, pozicia v a_vals b_vals zodpoveda tomu istemu filmu, value je hodnotenie
    # od daneho pouzivatela
    a_vals = []
    for movie_id in common_movie_ids:
        a_vals.append(ratings_a_dict[movie_id])

    b_vals = []
    for movie_id in common_movie_ids:
        b_vals.append(ratings_b_dict[movie_id])


    a_ranks = rank(a_vals)
    b_ranks = rank(b_vals)

    d_squared = 0
    for i in range(n):
        d_squared += (a_ranks[i] - b_ranks[i]) ** 2


    return 1 - (6 * d_squared) / (n * (n**2 - 1))