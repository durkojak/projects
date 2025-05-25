import sqlite3
from BACKEND.config import DATABASE_PATH

# Path to the database file
db_path = DATABASE_PATH

# Create or connect to the SQLite database
conn = sqlite3.connect(db_path)
cursor = conn.cursor()

# Create the currently_trending table
cursor.execute('''
CREATE TABLE IF NOT EXISTS currently_trending (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    movie_id INTEGER NOT NULL,
    movie_name TEXT NOT NULL,
    average_rating REAL NOT NULL,
    num_ratings INTEGER NOT NULL,
    FOREIGN KEY (movie_id) REFERENCES movies (id)
)
''')

# Commit the changes
conn.commit()
print(f"Successfully created empty currently_trending table in the database.")
print(f"Database updated at: {db_path}")

# Close the connection
conn.close()