# BI-VWM: Collaborative Filtering System

## Overview
A recommendation system built for the BI-VWM course that implements collaborative filtering algorithms to suggest items to users based on their preferences and rating patterns.

## Dataset
This project uses the [MovieLens dataset](https://grouplens.org/datasets/movielens/), which contains user ratings for movies. The dataset includes information about users, movies, genres, and ratings.

## Database Setup
The system uses SQLite for data storage. To set up or reset the database, execute the following command from project root:

```bash
python3 -m DB.scripts.load_db
```

This script will:
1. Create a new `recommender.db` file (or reload an existing one)
2. Load all necessary tables in the correct order
3. Populate the database with data from the MovieLens dataset

## Backend Setup
The system uses Flask for backend services. To start backend, execute the following command from project root:

```bash
python3.12 -m BACKEND.App
```

## Frontend Setup

```bash
npm run dev
```

## Database Schema
- **users**: User information including age, gender, and geographic data
- **movies**: Movie information including titles and release dates
- **genres**: Movie genre categories
- **movie_genres**: Junction table linking movies to their genres
- **ratings**: User ratings for movies with timestamps


## Available Similarity Metrics

### Cosine Similarity
Located in `similarity_funcs/cosine_similarity.py`, this function measures the cosine of the angle between two users' rating vectors. 

### Pearson Similarity
Located in `similarity_funcs/pearson_similarity.py`, this function calculates the Pearson correlation coefficient between two users' ratings. 

### Spearman Similarity
Located in `similarity_funcs/spearman_similarity.py`, this function computes the Spearman rank correlation between users. 

## Movie Recommendation System
The `movie_recommendations.py` module uses these similarity metrics to generate personalized movie recommendations. It:
- Finds users similar to the target user
- Identifies movies the target user hasn't rated
- Predicts ratings for those movies based on similar users' opinions
- Recommends movies with the highest predicted ratings

## Testing the Functions
To test these functions with your own parameters:
1. Navigate to the `Tests/` folder
2. Select which test you want to execute
3. Try different parameters like number of neighbors or recommendation thresholds
4. Run the test script

## API

### Admin recalculation of suggestions with custom params
The API endpoint is /admin/user/recommendations GET request, after this point using ? and & you can put in parameters regarding **Similarity Function** , **Number of movies that should be recommended**, **Amount of similar users used for this analysis** and the value of **Kappa** from the formula. **NOTE : ITS RETURNING RECALCULATED VALUES BUT NOT INSERTING TO SUGGESTIONS**

Example of a GET request : `http://localhost:5050/admin/user/recommendations?similarity=pearson&num_movies=10&num_neighbors=20&kappa=1.5`

### GET suggestions for specific user

/user/{user_id}/recommendations


## Deadline
`30.4.2025 16:15`

## Team Members
- Jakub Ďurkovič (durkojak)
- Kryštof Jelínek (jelinkry)

## Technologies
- Python
- SQLite
- Collaborative filtering algorithms


## Dependencies
- Backend - install(to your virtual or normal evironment) with "pip install -r requirements.txt"
- Frontend - knihovny pouzite pro frontend jsou definovany v souboru package.json
