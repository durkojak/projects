from collections import defaultdict
from typing import List, Dict, Tuple, Callable
from math import isnan
from BACKEND.Models.models import Rating
from BACKEND.Repository.SessionFactory import get_session

def get_movie_recommendations(
    active_user_id: int,
    all_ratings: List[Rating],
    similarity_fn: Callable[[List[Rating], List[Rating]], float],
    num_movies: int = 5,
    num_neighbors: int = 5,
    kappa: float = 1.0,
    minimum_amount_of_ratings: int = 5
) -> List[Tuple[int, float]]:

    with get_session() as session:
        active_user_rating_count = session.query(Rating).filter(Rating.user_id == active_user_id).count()
        if active_user_rating_count < minimum_amount_of_ratings:
            return []


    # Step 1: Group all ratings by user
    user_ratings: Dict[int, List[Rating]] = defaultdict(list)
    for r in all_ratings:
        user_ratings[r.user_id].append(r)

    if active_user_id not in user_ratings:
        return []

    active_ratings = user_ratings[active_user_id]
    active_rated_movie_ids = {r.item_id for r in active_ratings}
    active_avg = sum(r.value for r in active_ratings) / len(active_ratings)

    # Step 2: Compute similarity between active user and others
    similarities = []
    for other_user_id, ratings in user_ratings.items():
        if other_user_id == active_user_id:
            continue
        sim = similarity_fn(active_ratings, ratings)
        if not isnan(sim) and sim > 0:
            similarities.append((other_user_id, sim))

    # Step 3: Get top similar users
    top_similar_users = sorted(similarities, key=lambda x: x[1], reverse=True)[:num_neighbors]

    # Step 4: Aggregate contributions from similar users
    movie_contributions = defaultdict(float)

    for other_user_id, sim in top_similar_users:
        other_ratings = user_ratings[other_user_id]
        other_avg = sum(r.value for r in other_ratings) / len(other_ratings)

        for r in other_ratings:
            if r.item_id in active_rated_movie_ids:
                continue  # skip already rated
            contribution = sim * (r.value - other_avg)
            movie_contributions[r.item_id] += contribution

    # Step 5: Predict scores
    predicted_ratings = []
    for movie_id, contribution in movie_contributions.items():
        raw_score = active_avg + kappa * contribution
        predicted_score = min(5.0, max(1.0, raw_score)) # toto robim preto lebo apparently je mozne ze prediction bude aj vacsi ako 5, neviem tu matiku za tym ale chatbot ma gaslightuje ze to tak moze byt
        predicted_ratings.append((movie_id, predicted_score))


    predicted_ratings.sort(key=lambda x: x[1], reverse=True)
    return predicted_ratings[:num_movies]

