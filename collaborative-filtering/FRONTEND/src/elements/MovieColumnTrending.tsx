import React from 'react';
import {useEffect, useState} from "react";
import "../styles/MovieColumn.css"

type Trending = {
    id: number;
    title: string;
    rating: number;
    num_ratings: number;
};

type Movie = {
    id: number;
    title: string;
    rating?: number; // If the user has rated the movie
};

type MovieColumnProps = {
    title: string;
    movies: Trending[];
    reviewedMovies: Movie[];  // Receive the reviewedMovies prop
    updateReview: (movieId: number, rating: number) => void;
};

const MovieColumnTrending: React.FC<MovieColumnProps> = ({ title, movies, reviewedMovies, updateReview}) => {
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
                {movies.map(movie => {
                    const userRating = userRatings[movie.id] || 0; // Default to 0 if no rating from user
                    return (
                        <div key={movie.id} className="movie-item">
                            <div className="movie-header">
                                <span className="movie-title">{movie.title}</span>
                                <span className="review-count">({movie.num_ratings} reviews)</span>
                            </div>
                            <div className="stars">
                                {[1, 2, 3, 4, 5].map(star => (
                                    <button
                                        key={`${movie.id}-rate-${star}`}
                                        className={`star-button ${star <= userRating ? 'selected' : ''}`}
                                        onClick={() => updateReview(movie.id, star)}
                                    >
                                        ★
                                    </button>
                                ))}
                            </div>
                            <p className="avg-rating">Avg. Rating: {movie.rating.toFixed(1)}</p>
                        </div>
                    );
                })}
            </div>
        </div>
    );
};

export default MovieColumnTrending;
