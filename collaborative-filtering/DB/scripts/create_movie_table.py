import sqlite3
import os
import datetime

from BACKEND.config import DATABASE_PATH
from BACKEND.config import MOVIE_DATASET_PATH



# Path to the database file (in the DB folder)
db_path = DATABASE_PATH

# Path to the item file
item_file = MOVIE_DATASET_PATH

# Create or connect to the SQLite database
conn = sqlite3.connect(db_path)
cursor = conn.cursor()

# Create the movies table
cursor.execute('''
CREATE TABLE IF NOT EXISTS movies (
    id INTEGER PRIMARY KEY,
    title TEXT NOT NULL,
    release_date TEXT,
    video_release_date TEXT,
    imdb_url TEXT
)
''')

# Create the movie_genres table (many-to-many relationship)
cursor.execute('''
CREATE TABLE IF NOT EXISTS movie_genres (
    movie_id INTEGER,
    genre_id INTEGER,
    PRIMARY KEY (movie_id, genre_id),
    FOREIGN KEY (movie_id) REFERENCES movies (id),
    FOREIGN KEY (genre_id) REFERENCES genres (id)
)
''')

# Function to parse the date format
def parse_date(date_str):
    if not date_str:
        return None
    try:
        return datetime.datetime.strptime(date_str, '%d-%b-%Y').strftime('%Y-%m-%d')
    except ValueError:
        return None

# Read the movie data from file
movies_added = 0
genres_added = 0

if os.path.exists(item_file):
    with open(item_file, 'r', encoding='latin-1') as f:  # Using latin-1 encoding to handle special characters
        for line in f:
            fields = line.strip().split('|')
            if len(fields) >= 24:  # Ensure we have all fields
                movie_id = int(fields[0])
                title = fields[1]
                release_date = parse_date(fields[2])
                video_release_date = parse_date(fields[3])
                imdb_url = fields[4]
                
                # Insert movie data
                cursor.execute('''
                INSERT OR REPLACE INTO movies (id, title, release_date, video_release_date, imdb_url)
                VALUES (?, ?, ?, ?, ?)
                ''', (movie_id, title, release_date, video_release_date, imdb_url))
                movies_added += 1
                
                # Insert genre data - fields[5] through fields[23] are genre flags (0 or 1)
                for genre_id in range(19):  # 19 genres (0-18)
                    is_genre = int(fields[5 + genre_id])
                    if is_genre == 1:
                        cursor.execute('''
                        INSERT OR REPLACE INTO movie_genres (movie_id, genre_id)
                        VALUES (?, ?)
                        ''', (movie_id, genre_id))
                        genres_added += 1
    
    # Commit the changes
    conn.commit()
    print(f"Successfully added {movies_added} movies and {genres_added} genre associations to the database.")
    print(f"Database updated at: {db_path}")
else:
    print(f"Error: File '{item_file}' not found.")



results = cursor.fetchall()
current_movie_id = None
for row in results:
    movie_id, title, release_date, genre = row
    if movie_id != current_movie_id:
        print(f"\nID: {movie_id}, Title: {title}, Released: {release_date}")
        print(f"Genres: {genre}", end="")
        current_movie_id = movie_id
    else:
        print(f", {genre}", end="")

# Close the connection
conn.close()