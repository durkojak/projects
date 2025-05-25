import React, { useState } from "react";
import api from "../api/api.tsx";
import "../styles/AdminPage.css";

const AdminPage: React.FC = () => {
    const [resetInProgress, setResetInProgress] = useState(false);
    const [recalculationInProgress, setRecalculationInProgress] = useState(false);
    const [suggestionsInProgress, setSuggestionsInProgress] = useState(false);
    const [suggestionOptions, setSuggestionOptions] = useState({
        similarity: 'cosine',
        numMovies: 5,
        numNeighbors: 5,
        kappa: 1.0,
        minimalRatingsThreshold: 5,
    });

    const handleResetDatabase = () => {
        setResetInProgress(true);
        api.post('/admin/loadDB')
            .then(response => {
                alert('Database reset successful');
                setResetInProgress(false);
            })
            .catch(error => {
                console.error(error);
                alert('Error resetting database');
                setResetInProgress(false);
            });
    };

    const handleRecalculateTrending = () => {
        setRecalculationInProgress(true);
        api.post('/admin/generate/trending')
            .then(response => {
                alert('Trending films recalculated successfully');
                setRecalculationInProgress(false);
            })
            .catch(error => {
                console.error(error);
                alert('Error recalculating trending films');
                setRecalculationInProgress(false);
            });
    };

    const handleRecalculateSuggestions = () => {
        setSuggestionsInProgress(true);
        api.post('/admin/user/recommendations', suggestionOptions, { timeout: 10 * 60 * 1000 }) // 10 minutes
            .then(response => {
                alert('Suggestions recalculated successfully');
            })
            .catch(error => {
                console.error(error);
                alert('Error recalculating suggestions');
            })
            .finally(() => {
                setSuggestionsInProgress(false);
            });
    };


    const handleOptionChange = (event: React.ChangeEvent<HTMLInputElement>) => {
        const { name, value } = event.target;
        setSuggestionOptions({
            ...suggestionOptions,
            [name]: value,
        });
    };

    return (
        <div className="admin-container">
            <h1 className="admin-title">Admin Dashboard</h1>
            <div className="admin-actions">
                <h2>Admin Actions</h2>

                {/* Reset Database Button */}
                <button
                    onClick={handleResetDatabase}
                    className="admin-btn admin-reset-btn"
                    disabled={resetInProgress}
                >
                    {resetInProgress ? "Resetting..." : "Reset Database"}
                </button>

                {/* Recalculate Trending Films Button */}
                <button
                    onClick={handleRecalculateTrending}
                    className="admin-btn admin-recalc-btn"
                    disabled={recalculationInProgress}
                >
                    {recalculationInProgress ? "Recalculating..." : "Recalculate Trending Films"}
                </button>

                {/* Recalculate Suggestions Form */}
                <div className="admin-recalculate-form">
                    <h3>Recalculate Suggestions</h3>
                    <form onSubmit={(e) => { e.preventDefault(); handleRecalculateSuggestions(); }}>
                        <div className="admin-form-group">
                            <label htmlFor="similarity">Similarity Metric</label>
                            <select
                                name="similarity"
                                value={suggestionOptions.similarity}
                                onChange={handleOptionChange}
                                className="admin-select"
                            >
                                <option value="cosine">Cosine</option>
                                <option value="pearson">Pearson</option>
                                <option value="spearman">Spearman</option>
                            </select>
                        </div>

                        <div className="admin-form-group">
                            <label htmlFor="numMovies">Number of result Suggestions</label>
                            <input
                                type="number"
                                name="numMovies"
                                value={suggestionOptions.numMovies}
                                onChange={handleOptionChange}
                                className="admin-input"
                            />
                        </div>

                        <div className="admin-form-group">
                            <label htmlFor="numNeighbors">Number of Neighbors</label>
                            <input
                                type="number"
                                name="numNeighbors"
                                value={suggestionOptions.numNeighbors}
                                onChange={handleOptionChange}
                                className="admin-input"
                            />
                        </div>

                        <div className="admin-form-group">
                            <label htmlFor="minimalRatingsThreshold">Minimal Ratings Threshold</label>
                            <input
                                type="number"
                                name="minimalRatingsThreshold"
                                value={suggestionOptions.minimalRatingsThreshold}
                                onChange={handleOptionChange}
                                className="admin-input"
                            />
                        </div>

                        <div className="admin-form-group">
                            <label htmlFor="kappa">Kappa</label>
                            <input
                                type="number"
                                step="0.1"
                                name="kappa"
                                value={suggestionOptions.kappa}
                                onChange={handleOptionChange}
                                className="admin-input"
                            />
                        </div>

                        <button
                            type="submit"
                            className="admin-btn admin-recalc-suggestions-btn"
                            disabled={suggestionsInProgress}
                        >
                            {suggestionsInProgress ? "Recalculating..." : "Recalculate Suggestions"}
                        </button>

                    </form>
                </div>
            </div>
        </div>
    );
};

export default AdminPage;
