from sqlalchemy.orm import Session
from BACKEND.Models.models import Rating
from typing import List
from BACKEND.config import DATABASE_PATH
from BACKEND.similarity_funcs.spearman_similarity import spearman_similarity

def get_user_ratings(session: Session, user_id: int) -> List[Rating]:
    return session.query(Rating).filter(Rating.user_id == user_id).all()

def example_spearman_similarity(session: Session, user_id_1: int, user_id_2: int) -> float:
    ratings_user1 = get_user_ratings(session, user_id_1)
    ratings_user2 = get_user_ratings(session, user_id_2)
    return spearman_similarity(ratings_user1, ratings_user2)

from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

engine = create_engine(f'sqlite:///{DATABASE_PATH}')
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

with SessionLocal() as session:
    similarity_score = example_spearman_similarity(session, 1, 2)
    print(f"Spearman similarity between user 1 and user 2: {similarity_score:.3f}")