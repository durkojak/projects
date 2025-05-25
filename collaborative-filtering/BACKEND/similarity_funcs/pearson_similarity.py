from typing import List
from math import sqrt
from BACKEND.Models.models import Rating



def pearson_similarity(ratings_a: List[Rating], ratings_b: List[Rating]) -> float:
    # Convert to {item_id: rating}
    ratings_a_dict = {rating.item_id: rating.value for rating in ratings_a}
    ratings_b_dict = {rating.item_id: rating.value for rating in ratings_b}

    # Find common rated items
    common_movie_ids = list(set(ratings_a_dict) & set(ratings_b_dict))
    n = len(common_movie_ids)

    if n < 2:
        return 0.0  # Not enough data for correlation

    # Extract aligned ratings
    a_vals = [ratings_a_dict[movie_id] for movie_id in common_movie_ids]
    b_vals = [ratings_b_dict[movie_id] for movie_id in common_movie_ids]


    # Calculate means ( aritmeticky priemer )
    mean_a = sum(a_vals) / n
    mean_b = sum(b_vals) / n

    # Calculate numerator ( citatel ) and denominators ( menovatel )
    numerator = sum((a_vals[i] - mean_a) * (b_vals[i] - mean_b) for i in range(n))
    denominator_a = sqrt(sum((a - mean_a) ** 2 for a in a_vals))
    denominator_b = sqrt(sum((b - mean_b) ** 2 for b in b_vals))


    if denominator_a == 0 or denominator_b == 0:
        return 0.0  # Avoid division by zero

    similarity = numerator / (denominator_a * denominator_b)
    return similarity