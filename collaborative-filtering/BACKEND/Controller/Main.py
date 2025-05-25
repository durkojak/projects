from datetime import datetime, UTC
from flask import Flask, Blueprint, jsonify, request
from BACKEND.Repository.SessionFactory import get_session
from BACKEND.Repository.UserRepository import UserRepository
from BACKEND.Repository.MovieRepository import MovieRepository
from BACKEND.Repository.RatingRepository import RatingRepository
from BACKEND.Models.models import Movie, Rating, User, CurrentlyTrending
from BACKEND.Service.TrendingGenerator import TrendingGenerator
from BACKEND.similarity_funcs.movie_recommendations import get_movie_recommendations
from BACKEND.similarity_funcs.cosine_similarity import cosine_similarity
from BACKEND.similarity_funcs.pearson_similarity import pearson_similarity
from BACKEND.similarity_funcs.spearman_similarity import spearman_similarity
from DB.scripts.load_db import main as load_db

from rapidfuzz import process, fuzz

api = Blueprint('api', __name__)

@api.route('/admin/loadDB', methods=['POST'])
def resetDB():
    try:
        load_db()
        return jsonify({"status": "success", "message": "Database loaded"}), 200
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@api.route('/admin/user/recommendations', methods=['POST'])
def get_all_users_recommendations():
    # Parse the JSON body of the request
    params = request.json

    # Now extract values from the JSON payload
    similarity_metric = params.get('similarity', 'cosine').lower()
    num_movies = int(params.get('numMovies', 5))
    num_neighbors = int(params.get('numNeighbors', 5))
    kappa = float(params.get('kappa', 1.0))
    ratingsthreshold = int(params.get('minimalRatingsThreshold', 5))

    print(similarity_metric, num_movies, num_neighbors, ratingsthreshold, kappa)

    # Map similarity metric to the corresponding function
    similarity_fn_map = {
        'cosine': cosine_similarity,
        'pearson': pearson_similarity,
        'spearman': spearman_similarity
    }
    similarity_fn = similarity_fn_map.get(similarity_metric)

    if similarity_fn is None:
        return jsonify({"error": "Invalid similarity metric"}), 400

    with get_session() as session:
        # Get all users from the database
        all_users = session.query(User).all()
        all_ratings = session.query(Rating).all()

        # Import Suggestion model
        from BACKEND.Models.models import Suggestion

        # Dictionary to store recommendations for all users
        all_recommendations = {}


        # Calculate recommendations for each user
        for user in all_users:
            user_recommendations = get_movie_recommendations(
                active_user_id=user.id,
                all_ratings=all_ratings,
                similarity_fn=similarity_fn,
                num_movies=num_movies,
                num_neighbors=num_neighbors,
                kappa=kappa,
                minimum_amount_of_ratings = ratingsthreshold
            )

            # Store recommendations in dictionary for API response
            all_recommendations[user.id] = [
                {"movie_id": movie_id, "predicted_rating": predicted_score}
                for movie_id, predicted_score in user_recommendations
            ]

            # Clear previous suggestions for this user
            session.query(Suggestion).filter(Suggestion.user_id == user.id).delete()

            # Insert new suggestions into the database
            for movie_id, predicted_score in user_recommendations:
                new_suggestion = Suggestion(
                    user_id=user.id,
                    movie_id=movie_id,
                    predicted_rating=predicted_score
                )
                session.add(new_suggestion)

        # Commit all changes to the database
        session.commit()

        # Return recommendations for all users
        return jsonify(all_recommendations)

@api.route('/admin/generate/trending', methods=['POST'])
def generate_trending():
    generator = TrendingGenerator()
    generator.generate_top_20_trending_movies()
    return jsonify("trending movies generated"), 200

@api.route('/user/<int:user_id>/recommendations', methods=['GET'])
def get_user_recommendations(user_id):
    with get_session() as session:
        # Check if user exists
        userRepository = UserRepository(session)
        user = userRepository.get_by_id(user_id)

        if user is None:
            return jsonify({"error": "User not found"}), 404

        # Query the suggestions table for this user
        # Assuming you have a Suggestion model imported
        from BACKEND.Models.models import Suggestion, Movie

        # Join with Movie to get movie titles
        recommendations = session.query(
            Suggestion.movie_id,
            Movie.title,
            Suggestion.predicted_rating
        ).join(
            Movie, Suggestion.movie_id == Movie.id
        ).filter(
            Suggestion.user_id == user_id
        ).order_by(
            Suggestion.predicted_rating.desc()
        ).all()

        # Format the results
        result = [
            {
                "movie_id": movie_id,
                "movie_title": title,
                "predicted_rating": predicted_rating
            }
            for movie_id, title, predicted_rating in recommendations
        ]

        if not result:
            return jsonify({"message": "User has to review more films to access this feature"}), 200

        return jsonify(result), 200

@api.route('/trending', methods=['GET'])
def trending_Movies():
    with get_session() as session:
        # Query all rows from the `currently_trending` table
        top_movies = session.query(CurrentlyTrending).all()

        # Serialize the data to return in JSON format
        serialized_movies = [{
            "id": trending.movie_id,
            "title": trending.movie_name,
            "rating": trending.average_rating,
            "num_ratings": trending.num_ratings
        } for trending in top_movies]

        # Return the serialized data as JSON
        return jsonify(serialized_movies)

@api.route('/user/register', methods=['POST'])
def register_user():
    data = request.get_json()

    try:
        user_id = int(data.get("id"))
        age = int(data.get("age"))
        gender = str(data.get("gender"))
        occupation = str(data.get("occupation"))
        zip_code = str(data.get("zip_code"))
    except (TypeError, ValueError):
        return jsonify({"error": "Invalid or missing fields"}), 400

    with get_session() as session:
        userRepository = UserRepository(session)
        if userRepository.get_by_id(user_id):
            return jsonify({"error": "User already exists"}), 409

        new_user = User(
            id=user_id,
            age=age,
            gender=gender,
            occupation=occupation,
            zip_code=zip_code
        )
        userRepository.create(new_user)
        return jsonify({"message": "User registered successfully"}), 201

@api.route('/user/<int:user_id>/exists', methods=['GET'])
def user_exists(user_id):
    with get_session() as session:
        userRepository = UserRepository(session)
        user = userRepository.get_by_id(user_id)

        if user is None:
            return jsonify({"exists": False}), 200  # Not Found

        return jsonify({"exists": True}), 200

@api.route('/user/<int:user_id>/movies', methods=['GET'])
def get_movies(user_id):
    with get_session() as session:
        # Get the user repository
        userRepository = UserRepository(session)
        user = userRepository.get_by_id(user_id)

        if user is None:
            return jsonify({"error": "no user with this id found"}),  404

        # Query to get the films, their ids, and ratings
        result = session.query(Movie.id, Movie.title, Rating.value).join(Rating, Rating.item_id == Movie.id).filter(
            Rating.user_id == user_id).all()

        # Prepare the result in the desired format
        movies = [{"id": movie_id, "title": title, "rating": rating} for movie_id, title, rating in result]

        # Return the movies and ratings as JSON response
        return jsonify(movies)

@api.route('/user/<int:user_id>/movie/<int:movie_id>', methods=['GET'])
def get_user_movie_rating(user_id, movie_id):
    with get_session() as session:
        # Check if user exists
        userRepository = UserRepository(session)
        user = userRepository.get_by_id(user_id)
        if user is None:
            return jsonify({"error": "User not found"}), 404

        # Check if movie exists
        movie = session.query(Movie).filter_by(id=movie_id).first()
        if movie is None:
            return jsonify({"error": "Movie not found"}), 404

        # Try to find the rating
        rating = session.query(Rating).filter_by(user_id=user_id, item_id=movie_id).first()

        return jsonify({
            "movie": {
                "id": movie.id,
                "title": movie.title
            },
            "rating": rating.value if rating else None
        }), 200

@api.route('/user/<int:user_id>/movies/<int:movie_id>/rate', methods=['POST'])
def add_rating(user_id, movie_id):
    data = request.get_json()
    rating_value = data.get('rating')

    if rating_value is None or not (1 <= rating_value <= 5):
        return jsonify({"error": "Invalid rating. Must be between 1 and 5."}), 400

    with get_session() as session:
        userRepository = UserRepository(session)
        movieRepository = MovieRepository(session)
        ratingRepository = RatingRepository(session)
        user = userRepository.get_by_id(user_id)
        movie = movieRepository.get_by_id(movie_id)

        if not user or not movie:
            return jsonify({"error": "User or Movie not found"}), 404

        existing_rating = ratingRepository.get_by_id(user_id, movie.id)
        if existing_rating:
            return jsonify({"error": "Rating already exists. Only update is possible"}), 400

        now = datetime.now(UTC)
        timestamp = int(now.timestamp())
        date_time = now.strftime('%Y-%m-%d %H:%M:%S')

        new_rating = Rating(user_id=user_id, item_id=movie_id, value=rating_value, timestamp=timestamp, date_time=date_time)
        session.add(new_rating)
        session.commit()

        return jsonify({"message": "Rating added successfully", "rating": rating_value}), 201


@api.route('/user/<int:user_id>/movies/<int:movie_id>/rate', methods=['PUT'])
def update_rating(user_id, movie_id):
    data = request.get_json()
    rating_value = data.get('rating')

    if rating_value is None or not (1 <= rating_value <= 5):
        return jsonify({"error": "Invalid rating. Must be between 1 and 5."}), 400

    with get_session() as session:
        ratingRepository = RatingRepository(session)
        userRepository = UserRepository(session)
        movieRepository = MovieRepository(session)
        rating = ratingRepository.get_by_id(user_id, movie_id)
        if not userRepository.get_by_id(user_id):
            return jsonify({"error": "User not found. "}), 404

        if not movieRepository.get_by_id(movie_id):
            return jsonify({"error": "movie not found. "}), 404

        if rating:
            # Update the existing rating
            now = datetime.now(UTC)
            rating.value = rating_value
            rating.timestamp = int(now.timestamp())
            rating.date_time = now.strftime('%Y-%m-%d %H:%M:%S')
        else:
            # Create a new rating if it doesn't exist
            now = datetime.now(UTC)
            timestamp = int(now.timestamp())
            date_time = now.strftime('%Y-%m-%d %H:%M:%S')

            rating = Rating(user_id=user_id, item_id=movie_id, value=rating_value, timestamp=timestamp,
                            date_time=date_time)
            session.add(rating)

        session.commit()

        return jsonify({"message": "Rating updated successfully", "rating": rating_value, "timestamp": rating.timestamp, "date_time": rating.date_time}), 200

@api.route('/user/<int:user_id>/movies/<int:movie_id>/rate', methods=['DELETE'])
def delete_rating(user_id, movie_id):
    with get_session() as session:
        ratingRepository = RatingRepository(session)
        rating = ratingRepository.get_by_id(user_id, movie_id)
        if not rating:
            return jsonify({"error": "Rating not found"}), 404

        ratingRepository.delete(user_id, movie_id)
        session.commit()
        return jsonify({"message": "Rating deleted successfully"}), 200

from rapidfuzz import process, fuzz
from flask import request, jsonify

@api.route('/movies/search', methods=['POST'])
def search_movies():
    data = request.get_json()

    # Get the 'query' from the JSON body, default to an empty string if not present
    query = data.get('query', '').strip()
    print(f"Query: {query}")
    if not query:
        return jsonify({"error": "Query parameter is required"}), 400

    with get_session() as session:
        # Fetch movies as a list of tuples (id, title)
        movies = session.query(Movie.id, Movie.title).all()

        # Create a list of tuples (id, title)
        names_and_ids = [(movie.id, movie.title) for movie in movies]
        print(f"Names and IDs: {names_and_ids}")

        # Use Rapidfuzz to score all movies
        results = process.extract(
            query=query,
            choices=[title for _, title in names_and_ids],  # titles for comparison
            limit=50
        )
        print("Rapidfuzz Results:", results)

        # Now enhance scores for titles that start with the query
        suggestions = []
        for result in results:
            title = result[0]  # Title is at index 0
            score = result[1]  # Score is at index 1
            # Find the id for this title
            matching_id = None
            for movie_id, movie_title in names_and_ids:
                if movie_title == title:
                    matching_id = movie_id
                    break

            # Check if the title starts with the query (case insensitive)
            if title.lower().startswith(query.lower()):
                score += 50  # Boost score for exact prefix match

            suggestions.append((matching_id, title, score))

        # Sort suggestions by score (highest first)
        suggestions.sort(key=lambda x: x[2], reverse=True)

        top_suggestions = suggestions[:5]

        # Prepare the final list of suggestions with ids
        final_suggestions = [
            {"id": suggestion[0], "title": suggestion[1]}
            for suggestion in top_suggestions
        ]

        return jsonify(final_suggestions), 200



