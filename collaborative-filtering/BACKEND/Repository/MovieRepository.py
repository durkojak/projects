from typing import Optional

from sqlalchemy.orm import Session, joinedload
from BACKEND.Models.models import Movie  # Assuming the Movie class is in the models module

class MovieRepository:
    def __init__(self, session: Session):
        self.session = session

    def create(self, in_movie : Movie) -> Movie:
        """
        Create a new movie.
        """
        movie = Movie(
            title=in_movie.title,
            release_date=in_movie.release_date,
            video_release_date=in_movie.video_release_date,
            imdb_url=in_movie.imdb_url
        )
        self.session.add(movie)
        self.session.commit()
        return movie

    def get_by_id(self, movie_id: int) -> Optional[Movie]:
        """
        Get a movie by its ID.
        """
        return self.session.query(Movie).filter(Movie.id == movie_id).first()

    def get_all(self) -> list:
        movies = self.session.query(Movie).options(
            joinedload(Movie.ratings)
        ).all()
        return movies

    def update(self, movie_id: int, in_movie : Movie) -> Optional[Movie]:
        """
        Update a movie by its ID.
        """
        movie = self.get_by_id(movie_id)
        if movie:
            if movie.title:
                movie.title = in_movie.title
            if movie.release_date:
                movie.release_date = in_movie.release_date
            if movie.video_release_date:
                movie.video_release_date = in_movie.video_release_date
            if movie.imdb_url:
                movie.imdb_url = in_movie.imdb_url

            self.session.commit()
            return movie
        return None

    def delete(self, movie_id: int) -> bool:
        """
        Delete a movie by its ID.
        """
        movie = self.get_by_id(movie_id)
        if movie:
            self.session.delete(movie)
            self.session.commit()
            return True
        return False
