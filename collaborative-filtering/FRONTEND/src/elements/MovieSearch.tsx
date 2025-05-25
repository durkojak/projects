import React, {useEffect, useState} from "react";
import '../styles/MovieSearch.css'; // Import the CSS file
import Autosuggest from 'react-autosuggest';
import api from "../api/api.tsx";  // Assuming you're using Axios for API calls

type Props = {
    searchId: string;
    setSearchId: (id: string) => void;
    searchedMovie: {
        movie: { id: number; title: string };
        rating: number | null;
    } | null;
    handleSearch: () => void;
    handleRating: (movieId: number, rating: number) => void;
};

const MovieSearch: React.FC<Props> = ({ searchId, setSearchId, searchedMovie, handleSearch, handleRating }) => {
    const [suggestions, setSuggestions] = React.useState<{ id: string; title: string }[]>([]);
    const [searchTitle, setSearchTitle] = useState(""); // Store the title

    // Fetch suggestions based on user input
    const onSuggestionsFetchRequested = async ({ value }: { value: string }) => {
        try {
            const response = await api.post('/movies/search', { query: value });
            const data = await response.data; // Assuming it returns [{ id, title }]
            setSuggestions(data);
        } catch (error) {
            console.error("Error fetching suggestions:", error);
        }
    };

    // Clear suggestions when user clears input
    const onSuggestionsClearRequested = () => {
        setSuggestions([]);
    };

    // Handle the suggestion selection (fetch movie by ID)
    const onSuggestionSelected = async (_e: any, { suggestion }: any) => {
        setSearchId(suggestion.id); // Set the input field to the selected movie title
        setSearchTitle(suggestion.title)
    };

    useEffect(() => {
        if (searchId) {
            handleSearch();
        }
    }, [searchId]);

    useEffect(() => {
        if (searchedMovie) {
            // Do something when searchedMovie is updated, like logging the movie or performing additional logic
            console.log("Movie data updated:", searchedMovie);
            // You could also trigger UI changes, handle side effects, etc.
        }
    }, [searchedMovie]);


    return (
        <div className="movie-search-container">
            <h2 className="movie-search-header">Search Movie by Title</h2>
            <div className="movie-search-input-container">
                <Autosuggest
                    suggestions={suggestions}
                    onSuggestionsFetchRequested={onSuggestionsFetchRequested}
                    onSuggestionsClearRequested={onSuggestionsClearRequested}
                    getSuggestionValue={(suggestion) => suggestion.title} // Use the movie title as input value
                    renderSuggestion={(suggestion) => <div className="suggestion-item">{suggestion.title}</div>} // Render suggestions as movie titles
                    inputProps={{
                        placeholder: "Enter movie title...",
                        value: searchTitle,
                        onChange: (_e, { newValue }) => {
                            setSearchTitle(newValue)
                        }, // Update searchId as the user types
                        className: "movie-search-input"
                    }}
                    onSuggestionSelected={onSuggestionSelected} // Handle the suggestion selection
                />
            </div>

            {searchedMovie && (
                <div className="movie-search-results">
                    <h3 className="movie-search-title">
                        {searchedMovie.movie.title} (ID: {searchedMovie.movie.id})
                    </h3>
                    <p className="movie-search-rating">
                        Your Rating: {searchedMovie.rating ?? 'Not rated yet'}
                    </p>
                    <div className="movie-search-rating">
                        {[1, 2, 3, 4, 5].map((r) => (
                            <button
                                key={r}
                                onClick={() => handleRating(searchedMovie.movie.id, r)}
                            >
                                {r}⭐
                            </button>
                        ))}
                    </div>
                </div>
            )}
        </div>
    );
};

export default MovieSearch;
