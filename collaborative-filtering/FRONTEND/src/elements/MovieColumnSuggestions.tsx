import React from 'react';
import {useEffect, useState} from "react";
import "../styles/MovieColumn.css"
import moviePage from "../pages/MoviePage.tsx";

type Suggestion = {
    movie_id: number;
    movie_title: string;
    predicated_rating: number;
};

type Movie = {
    id: number;
    title: string;
    rating?: number; // If the user has rated the movie
};

type MovieColumnProps = {
    title: string;
    movies: Suggestion[];
    reviewedMovies: Movie[];  // Receive the reviewedMovies prop
    updateReview: (movieId: number, rating: number) => void;
};

const MovieColumnSuggestions: React.FC<MovieColumnProps> = ({ title, movies, reviewedMovies, updateReview}) => {
    const [userRatings, setUserRatings] = useState<Record<number, number>>({});

    useEffect(() => {
        // Map user ratings from reviewedMovies
        const ratings = reviewedMovies.reduce((acc: Record<number, number>, movie: any) => {
            acc[movie.id] = movie.rating;
            return acc;
        }, {});

        setUserRatings(ratings);
    }, [reviewedMovies]);

    return (
        <div className="movie-column">
            <h2 className="movie-column-title">{title}</h2>
            <div className="movie-list">
                {(() => {
                    if (movies.length === 0 || movies.message) {
                        return <p>{movies.message}</p>;
                    } else {
                        return movies.map(movie => {
                            const userRating = userRatings[movie.movie_id] || 0; // Default to 0 if no rating from user
                            return (
                                <div key={movie.movie_id} className="movie-item">
                                    <div className="movie-header">
                                        <span className="movie-title">{movie.movie_title}</span>
                                    </div>
                                    <div className="stars">
                                        {[1, 2, 3, 4, 5].map(star => (
                                            <button
                                                key={`${movie.movie_id}-rate-${star}`}
                                                className={`star-button ${star <= userRating ? 'selected' : ''}`}
                                                onClick={() => updateReview(movie.movie_id, star)}
                                            >
                                                ★
                                            </button>
                                        ))}
                                    </div>
                                    <p className="avg-rating">Predicated Rating: {movie.predicated_rating.toFixed(1)}</p>
                                </div>
                            );
                        });
                    }
                })()}
            </div>
        </div>
    );

};

export default MovieColumnSuggestions;
