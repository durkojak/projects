from BACKEND.config import DATABASE_PATH
from sqlalchemy.orm import Session
from typing import List, Callable
from BACKEND.Models.models import Rating
from BACKEND.similarity_funcs.pearson_similarity import pearson_similarity
from BACKEND.similarity_funcs.cosine_similarity import cosine_similarity
from BACKEND.similarity_funcs.spearman_similarity import spearman_similarity
from BACKEND.similarity_funcs import movie_recommendations

from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker


def get_all_ratings(session: Session) -> List[Rating]:
    return session.query(Rating).all()


def example_recommendations(
    session: Session,
    user_id: int,
    similarity_fn: Callable,
    num_movies: int = 5,
    num_neighbors: int = 5,
    kappa: float = 1.0
):
    all_ratings = get_all_ratings(session)
    recommendations = movie_recommendations.get_movie_recommendations(
        active_user_id=user_id,
        all_ratings=all_ratings,
        similarity_fn=similarity_fn,
        num_movies=num_movies,
        num_neighbors=num_neighbors,
        kappa=kappa
    )
    print(f"Recommendations for user {user_id}:")
    for movie_id, predicted_score in recommendations:
        print(f"Movie ID {movie_id} → Predicted Rating: {predicted_score:.2f}")


# ---- Run the test ----
if __name__ == "__main__":
    engine = create_engine(f'sqlite:///{DATABASE_PATH}')
    SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

    with SessionLocal() as session:
        example_recommendations(
            session=session,
            user_id=1,
            similarity_fn=cosine_similarity,  # or spearman_similarity
            num_movies=10,
            num_neighbors=5,
            kappa=1.0
        )
