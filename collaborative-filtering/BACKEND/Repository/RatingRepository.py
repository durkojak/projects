from typing import Optional
from sqlalchemy.orm import Session
from BACKEND.Models.models import Rating  # Assuming the Rating class is in the models module

class RatingRepository:
    def __init__(self, session: Session):
        self.session = session

    def create(self, in_rating: Rating) -> Rating:
        """
        Create a new rating.
        """
        rating = Rating(
            user_id=in_rating.user_id,
            item_id=in_rating.item_id,
            value=in_rating.value,
            timestamp=in_rating.timestamp,
            date_time=in_rating.date_time
        )
        self.session.add(rating)
        self.session.commit()
        return rating

    def get_by_id(self, user_id: int, movie_id: int) -> Optional[Rating]:
        """
        Get a rating by its user and movie IDs.
        """
        return self.session.query(Rating).filter(Rating.user_id == user_id, Rating.item_id == movie_id).first()

    def get_all(self) -> list:
        """
        Get all ratings.
        """
        return self.session.query(Rating).all()

    def update(self, user_id: int, movie_id: int, in_rating: Rating) -> Optional[Rating]:
        """
        Update a rating by its user and movie IDs.
        """
        rating = self.get_by_id(user_id, movie_id)
        if rating:
            if in_rating.value is not None:
                rating.rating = in_rating.value
            if in_rating.timestamp is not None:
                rating.timestamp = in_rating.timestamp
            if in_rating.date_time:
                rating.date_time = in_rating.date_time

            self.session.commit()
            return rating
        return None

    def delete(self, user_id: int, movie_id: int) -> bool:
        """
        Delete a rating by its user and movie IDs.
        """
        rating = self.get_by_id(user_id, movie_id)
        if rating:
            self.session.delete(rating)
            self.session.commit()
            return True
        return False
