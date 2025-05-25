import os

# Get absolute path to the project root (bi-vwm)
PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# Define full path to the database
DATABASE_PATH = os.path.join(PROJECT_ROOT, "DB", "recommender.db")
SCRIPTS_FOLDER_PATH = os.path.join(PROJECT_ROOT, "DB", "scripts")

USER_DATASET_PATH = os.path.join(PROJECT_ROOT, "DB" ,"dataset", "u.user")
GENRE_DATASET_PATH = os.path.join(PROJECT_ROOT, "DB" ,"dataset", "u.genre")
MOVIE_DATASET_PATH = os.path.join(PROJECT_ROOT, "DB" ,"dataset", "u.item")
RATING_DATASET_PATH = os.path.join(PROJECT_ROOT, "DB" ,"dataset", "u.data")