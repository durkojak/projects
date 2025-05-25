import React, { useState } from "react";
import '../styles/MovieGrid.css'


interface Movie {
    id: number;
    title: string;
    rating?: number;
}

interface MovieGridProps {
    moviesToShow: Movie[];
    updateReview: (movieId: number, rating: number) => void;
    removeReview: (movieId: number) => void;
}

const MovieGrid: React.FC<MovieGridProps> = ({ moviesToShow, updateReview, removeReview }) => {
    const [expandedMovie, setExpandedMovie] = useState<number | null>(null);

    const toggleExpand = (movieId: number) => {
        setExpandedMovie(expandedMovie === movieId ? null : movieId);
    };

    return (
        <div className="movie-grid">
            {moviesToShow.map((movie) => (
                <div
                    key={movie.id}
                    className="movie-card border p-4 cursor-pointer"
                    onClick={() => toggleExpand(movie.id)}
                >
                    <div className="flex justify-between">
                        <span>{movie.title}</span>
                    </div>
                    <div className="stars">
                        {[1, 2, 3, 4, 5].map((star) => (
                            <span
                                key={`${movie.id}-star-${star}`}
                                className={`star ${star <= (movie.rating ?? 0) ? 'filled' : ''}`}
                            >
                                ★
                            </span>
                        ))}
                    </div>

                    {expandedMovie === movie.id && (
                        <div className="movie-details">
                            <div className="rating-container">
                                {[1, 2, 3, 4, 5].map((star) => (
                                    <button
                                        key={`${movie.id}-rate-${star}`}
                                        className={`star-button ${star <= (movie.rating ?? 0) ? 'selected' : ''}`}
                                        onClick={(e) => {
                                            e.stopPropagation();
                                            updateReview(movie.id, star);
                                        }}
                                    >
                                        ★
                                    </button>
                                ))}
                            </div>
                            <button
                                className="remove-review-button"
                                onClick={(e) => {
                                    e.stopPropagation();
                                    removeReview(movie.id);
                                }}
                            >
                                Remove Review
                            </button>
                        </div>
                    )}
                </div>
            ))}
        </div>
    );
};

export default MovieGrid;
