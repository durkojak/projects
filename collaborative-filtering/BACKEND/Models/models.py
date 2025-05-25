from typing import List

from sqlalchemy import Column, Integer, String, ForeignKey, Float
from sqlalchemy.orm import declarative_base, relationship, Mapped


# Create the base class for our models
Base = declarative_base()
class Genre(Base):
    __tablename__ = 'genres'

    id : int = Column(Integer, primary_key=True)
    name : str = Column(String, nullable=False, unique=True)

    movies : Mapped[List["Movie"]] = relationship("Movie", secondary="movie_genres", back_populates="genres")

    def __repr__(self):
        return f"<Genre(id={self.id}, name='{self.name}')>"

# Define the Movie class as an ORM model
class Movie(Base):
    __tablename__ = 'movies'

    id : int = Column(Integer, primary_key=True)
    title : str = Column(String, nullable=False)
    release_date : str = Column(String)
    video_release_date : str = Column(String)
    imdb_url : str = Column(String)

    # Relationship to the Genre table via the movie_genres table
    genres : Mapped[List["Genre"]] = relationship("Genre", secondary="movie_genres", back_populates="movies")
    ratings : Mapped[List["Rating"]] = relationship("Rating", backref="movie")

    def __repr__(self):
        return f"<Movie(id={self.id}, title='{self.title}', release_date='{self.release_date}')>"



class MovieGenre(Base):
    __tablename__ = 'movie_genres'

    movie_id : int = Column(Integer, ForeignKey('movies.id'), primary_key=True)
    genre_id : int = Column(Integer, ForeignKey('genres.id'), primary_key=True)


class User(Base):
    __tablename__ = 'users'

    id : int = Column(Integer, primary_key=True)
    age : int = Column(Integer, nullable=False)
    gender : str = Column(String, nullable=False)
    occupation : str = Column(String, nullable=False)
    zip_code : str = Column(String, nullable=False)

    ratings : Mapped[List["Rating"]] = relationship("Rating", backref="user")

    def __repr__(self):
        return f"<User(id={self.id}, age={self.age}, gender='{self.gender}', occupation='{self.occupation}', zip_code='{self.zip_code}')>"

class Rating(Base):
    __tablename__ = 'ratings'

    user_id : int = Column(Integer, ForeignKey('users.id'), primary_key=True)
    item_id : int = Column(Integer, ForeignKey('movies.id'), primary_key=True)
    value : int = Column(Integer, nullable=False)
    timestamp : int = Column(Integer, nullable=False)
    date_time : str = Column(String)

    def __repr__(self):
        return f"<Rating(user_id={self.user_id}, item_id={self.item_id}, value={self.value})>"

class Suggestion(Base):
    __tablename__ = 'suggestions'

    id: int = Column(Integer, primary_key=True)
    user_id: int = Column(Integer, ForeignKey('users.id'), nullable=False)
    movie_id: int = Column(Integer, ForeignKey('movies.id'), nullable=False)
    predicted_rating: int = Column(Float, nullable=False)

    # Relationships to User and Movie
    user: Mapped["User"] = relationship("User", backref="suggestions")
    movie: Mapped["Movie"] = relationship("Movie", backref="suggestions")

    def __repr__(self):
        return f"<Suggestion(user_id={self.user_id}, movie_id={self.movie_id}, predicted_rating={self.predicted_rating})>"

class CurrentlyTrending(Base):
    __tablename__ = 'currently_trending'

    id: int = Column(Integer, primary_key=True)
    movie_id: int = Column(Integer, ForeignKey('movies.id'), nullable=False)
    movie_name: str = Column(String, nullable=False)  # Store the movie name directly
    average_rating: float = Column(Float, nullable=False)  # Using Float to allow decimal ratings
    num_ratings: int = Column(Integer, nullable=False)

    # Relationship to Movie
    movie: Mapped["Movie"] = relationship("Movie", backref="trending_entries")

    def __repr__(self):
        return f"<CurrentlyTrending(movie_id={self.movie_id}, movie_name='{self.movie_name}', rating={self.rating})>"