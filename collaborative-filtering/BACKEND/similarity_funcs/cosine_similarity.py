import math
from math import sqrt
from BACKEND.Models.models import Rating
from typing import List

def cosine_similarity(ratings_a: List[Rating], ratings_b: List[Rating]) -> float:
    # Convert lists to dicts: {item_id: rating}
    ratings_a_dict = {rating.item_id: rating.value for rating in ratings_a}
    ratings_b_dict = {rating.item_id: rating.value for rating in ratings_b}

    # Find common rated items
    common_movie_ids = list(set(ratings_a_dict) & set(ratings_b_dict))
    n = len(common_movie_ids)

    if n == 0:
        return 0.0  # No overlap = no similarity

    # Create aligned rating vectors
    a_vals = [ratings_a_dict[movie_id] for movie_id in common_movie_ids]
    b_vals = [ratings_b_dict[movie_id] for movie_id in common_movie_ids]


    # Calculate dot product - skalarny sucin, horna cast vzorca kosinovej podobnosti
    dot_product = 0
    for i in range(len(a_vals)):
        dot_product += a_vals[i] * b_vals[i]
    # Calculate magnitudes - velkosti vektorov, dolna cast vzorca kosinovej podobnosti
    mag_a = sqrt(sum(a ** 2 for a in a_vals))
    mag_b = sqrt(sum(b ** 2 for b in b_vals))

    # Avoid division by zero
    if mag_a == 0 or mag_b == 0:
        return 0.0

    similarity = dot_product / (mag_a * mag_b)
    return similarity



