from typing import Optional
from sqlalchemy.orm import Session
from BACKEND.Models.models import Genre  # Assuming the Genre class is in the models module

class GenreRepository:
    def __init__(self, session: Session):
        self.session = session

    def create(self, in_genre: Genre) -> Genre:
        """
        Create a new genre.
        """
        genre = Genre(
            name=in_genre.name
        )
        self.session.add(genre)
        self.session.commit()
        return genre

    def get_by_id(self, genre_id: int) -> Optional[Genre]:
        """
        Get a genre by its ID.
        """
        return self.session.query(Genre).filter(Genre.id == genre_id).first()

    def get_all(self) -> list:
        """
        Get all genres.
        """
        return self.session.query(Genre).all()

    def update(self, genre_id: int, in_genre: Genre) -> Optional[Genre]:
        """
        Update a genre by its ID.
        """
        genre = self.get_by_id(genre_id)
        if genre:
            if genre.name:
                genre.name = in_genre.name

            self.session.commit()
            return genre
        return None

    def delete(self, genre_id: int) -> bool:
        """
        Delete a genre by its ID.
        """
        genre = self.get_by_id(genre_id)
        if genre:
            self.session.delete(genre)
            self.session.commit()
            return True
        return False
