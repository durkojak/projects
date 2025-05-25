import sqlite3
from BACKEND.config import DATABASE_PATH

# Path to the database file
db_path = DATABASE_PATH

# Create or connect to the SQLite database
conn = sqlite3.connect(db_path)
cursor = conn.cursor()

# Create the suggestions table
cursor.execute('''
CREATE TABLE IF NOT EXISTS suggestions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    movie_id INTEGER NOT NULL,
    predicted_rating REAL NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users (id),
    FOREIGN KEY (movie_id) REFERENCES movies (id)
)
''')



# Commit the changes
conn.commit()
print(f"Successfully created empty suggestions table in the database.")
print(f"Database updated at: {db_path}")

# Close the connection
conn.close()