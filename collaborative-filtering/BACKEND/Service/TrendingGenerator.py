import copy
from datetime import datetime, timezone

from six import moves
from sqlalchemy import delete

from ..Models.models import Movie, CurrentlyTrending
from ..Repository.MovieRepository import MovieRepository
from ..Repository.SessionFactory import get_session

class TrendingGenerator:
    def generate_top_20_trending_movies(self):
        with get_session() as session:
            movieRepository = MovieRepository(session)
            movies = movieRepository.get_all()

            # Calculate the trending score for each movie
            movies_with_scores = [(movie, self.calculate_trending_score(movie)) for movie in movies]

            # Sort movies by trending score (highest to lowest) and take the top 20
            sorted_movies = sorted(movies_with_scores, key=lambda x: x[1], reverse=True)

            # Now copy only the top 20 to avoid session detachment issues
            top_20_movies = [(copy.deepcopy(movie), score) for movie, score in sorted_movies[:20]]


            session.execute(delete(CurrentlyTrending))

            for movie, score in top_20_movies:
                avg_rating = sum([r.value for r in movie.ratings]) / len(movie.ratings) if movie.ratings else 0

                trending_entry = CurrentlyTrending(
                    movie_id=movie.id,
                    movie_name=movie.title,
                    average_rating=avg_rating,
                    num_ratings=len(movie.ratings)
                )
                session.add(trending_entry)

            session.commit()
            print("✅ Top 20 trending movies saved.")

    @staticmethod
    def calculate_trending_score(movie: Movie) -> float:
        """
        Calculate the trending score of a movie based on:
        - Average rating
        - Number of ratings
        - Recency of ratings
        """
        num_ratings = len(movie.ratings)
        if num_ratings == 0:
            return 0  # No ratings, no trending score

        # Calculate the average rating of the movie
        avg_rating = sum([rating.value for rating in movie.ratings]) / num_ratings

        # Find the latest rating timestamp
        latest_rating = max(movie.ratings, key=lambda r: r.timestamp)

        #get time and convert timestamp
        current_utc_time = datetime.now(timezone.utc)
        latest_rating_datetime = datetime.fromtimestamp(latest_rating.timestamp, tz=timezone.utc)

        # Assuming latest_rating.timestamp is a timezone-aware datetime object
        days_since_last_rating = (current_utc_time - latest_rating_datetime).days

        # Recency factor: more recent ratings should weigh more
        recency_factor = 1.0 / (days_since_last_rating + 1)  # Decay factor: newer ratings are more influential

        # Calculate trending score: higher rating, more ratings, and recent ratings lead to a higher score
        trending_score = avg_rating * num_ratings * recency_factor
        print(movie.title, trending_score ,recency_factor)
        return trending_score