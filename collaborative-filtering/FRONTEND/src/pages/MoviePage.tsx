import React, { useEffect, useState } from 'react';
import { useParams, useNavigate } from 'react-router-dom';
import MovieGrid from "../elements/MovieGrid.tsx";
import api from "../api/api.tsx"
import {getUserId} from "../api/utils.tsx";

import '../styles/MoviePage.css'
import MovieSearch from '../elements/MovieSearch.tsx'
import MovieColumnTrending from "../elements/MovieColumnTrending.tsx";
import MovieColumnSuggestions from "../elements/MovieColumnSuggestions.tsx";

type Movie = {
    id: number;
    title: string;
    rating?: number; // If the user has rated the movie
};

type Suggestion = {
    movie_id: number;
    movie_title: string;
    predicated_rating: number;
};

type Trending = {
    id: number;
    title: string;
    rating: number;
    num_ratings: number;
};

type MovieSearchResult = {
    movie: {
        id: number;
        title: string;
    };
    rating: number | null;
};

const MoviePage: React.FC = () => {
    const navigate = useNavigate();
    const { id } = useParams<{ id: string }>();
    const [reviewedMovies, setReviewedMovies] = useState<Movie[]>([]);
    const [suggestions, setSuggestions] = useState<Suggestion[]>([]);
    const [trending, setTrending] = useState<Trending[]>([]);
    const [countdown, setCountdown] = useState<number | null>(null);
    const [showAllMovies, setShowAllMovies] = useState(false);  // New state for toggling movie list visibility

    const [searchId, setSearchId] = useState('');
    const [searchedMovie, setSearchedMovie] = useState<MovieSearchResult | null>(null);


    useEffect(() => {
        const userId = getUserId();

        if (!userId) {
            // User is not logged in, start countdown
            const countdownStart = 5; // Number of seconds before redirecting
            setCountdown(countdownStart);

            const countdownInterval = setInterval(() => {
                setCountdown(prev => {
                    if (prev === null || prev <= 1) {
                        clearInterval(countdownInterval);
                        setTimeout(() => navigate('/'), 0); // Redirect to login page after the current render cycle
                        return null;
                    }
                    return prev - 1;
                });
            }, 1000);

            return () => clearInterval(countdownInterval); // Cleanup if component unmounts
        }

        // User is logged in, fetch movie data
        api.get(`/user/${userId}/movies`) // API call for reviewed movies
            .then(response => setReviewedMovies(response.data))
            .catch(error => {
                if (error.response && error.response.status === 404) {
                  alert(`User with ID ${userId} doesn't exist.`); // Notify the user
                  window.location.href = '/'; // Redirect to home or another page
                } else {
                  console.error(error); // Handle other errors
                }
              });

        api.get('/trending')
        .then(response => setTrending(response.data))
        .catch(error => console.error('Error fetching trending movies:', error));

        api.get(`/user/${userId}/recommendations`)
        .then(response => {
            console.log(response.data)
            const suggestionsData: Suggestion[] = response.data.map((movie: any) => ({
                movie_id: movie.movie_id,
                movie_title: movie.movie_title,
                predicated_rating: movie.predicted_rating
            }));
            setSuggestions(suggestionsData)
            console.log(suggestions)
        })
        .catch(error => console.error('Error fetching recommended movies:', error));


        }, [navigate]);

    if (!getUserId()) {
    // If no userId in localStorage, only show countdown
        return (
            <div className="countdown-text">
                <p>You need to log in first</p>
                <p>Redirecting in {countdown} seconds...</p>
            </div>
        );
    }

    const handleRating = (movieId: number, rating: number) => {
        api.put(`/user/${getUserId()}/movies/${movieId}/rate`, { rating })
            .then(() => {
                // Check if the movie has already been reviewed
                const movieIndex = reviewedMovies.findIndex(movie => movie.id === movieId);

                if (movieIndex !== -1) {
                    // Movie exists in reviewedMovies, update rating
                    setReviewedMovies(prev =>
                        prev.map(movie =>
                            movie.id === movieId ? { ...movie, rating } : movie
                        )
                    );
                } else {
                    // Movie is not reviewed yet, add it
                    const newMovie = {
                        id: movieId,
                        title: trending.find(movie => movie.id === movieId)?.title ||
                            searchedMovie?.movie.title ||
                            suggestions.find(movie => movie.movie_id == movieId)?.movie_title||
                            '',
                        rating
                    };
                    setReviewedMovies(prev => [...prev, newMovie]);
                }
                setSearchedMovie(prev =>
                    prev && prev.movie.id === movieId
                        ? { ...prev, rating }
                        : prev
                );
            })
            .catch(error => console.error(error));
    };



    const removeReview = (movieId: number) => {
        api.delete(`/user/${getUserId()}/movies/${movieId}/rate`)
            .then(() => {
                setReviewedMovies(prev => prev.filter(movie => movie.id !== movieId));

                setSearchedMovie(prev =>
                    prev && prev.movie.id === movieId
                        ? { ...prev, rating: null } // Set the rating to null
                        : prev
                );
            })
            .catch(error => console.error(error));
    };

    const handleSearch = async () => {
        const userId = localStorage.getItem("userId");
        if (!userId || !searchId) return;

        try {
            const response = await api.get(`/user/${userId}/movie/${searchId}`);
            setSearchedMovie(response.data);
        } catch (error) {
            alert("Movie not found or you are not logged in.");
            setSearchedMovie(null);
        }
    };


    const moviesToShow = showAllMovies ? reviewedMovies : reviewedMovies.slice(0, 12);  // Show all or just the first 12

    return (
        <div className="p-4">
            <h1 className="text-2xl font-bold mb-4">Movies</h1>

            <MovieSearch
                searchId={searchId}
                setSearchId={setSearchId}
                searchedMovie={searchedMovie}
                handleSearch={handleSearch}
                handleRating={handleRating}
            />

            <div className="mb-8">
                <h2 className="text-xl font-bold mb-2">Reviewed Movies</h2>
                    <MovieGrid
                        moviesToShow={moviesToShow}
                        updateReview={handleRating}
                        removeReview={removeReview}
                    />
                <button
                    className="show-more-btn"
                    onClick={() => setShowAllMovies(!showAllMovies)} // Toggle state
                >
                    {showAllMovies ? 'Show Less' : 'Show More'}
                </button>
            </div>

            <div>
                <div className="movie-colums-div">
                    <MovieColumnTrending
                        title="Currently Trending"
                        movies={trending}
                        reviewedMovies={reviewedMovies}
                        updateReview={handleRating}
                    /> {/* Sem později dosadíš trending data */}
                    <MovieColumnSuggestions
                        title="Suggestions"
                        movies={suggestions}
                        reviewedMovies={reviewedMovies}
                        updateReview={handleRating}
                    />
                </div>
            </div>
        </div>
    );
};

export default MoviePage;
