import sqlite3
import os
from BACKEND.config import GENRE_DATASET_PATH
from BACKEND.config import DATABASE_PATH

db_path = DATABASE_PATH
genre_file = GENRE_DATASET_PATH

# Create or connect to the SQLite database
conn = sqlite3.connect(db_path)
cursor = conn.cursor()

# Create the genres table
cursor.execute('''
CREATE TABLE IF NOT EXISTS genres (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL UNIQUE
)
''')

# Read the genre data from file
genres = []

if os.path.exists(genre_file):
    with open(genre_file, 'r') as f:
        for line in f:
            line = line.strip()
            if line:
                # Split by the pipe character
                parts = line.split('|')
                if len(parts) == 2:
                    name = parts[0]
                    genre_id = int(parts[1])
                    genres.append((genre_id, name))
    
    # Insert genres into the table
    for genre_id, name in genres:
        cursor.execute('INSERT OR IGNORE INTO genres (id, name) VALUES (?, ?)', (genre_id, name))
    
    # Commit the changes
    conn.commit()
    print(f"Successfully added {len(genres)} genres to the database.")
    print(f"Database updated at: {db_path}")
else:
    print(f"Error: File '{genre_file}' not found.")

# Query and display the genres to verify
cursor.execute('SELECT * FROM genres ORDER BY id')
results = cursor.fetchall()
print("\nGenres in database:")
for row in results:
    print(f"ID: {row[0]}, Genre: {row[1]}")

# Close the connection
conn.close()