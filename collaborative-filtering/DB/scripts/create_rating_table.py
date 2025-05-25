import sqlite3
import os
import datetime

from BACKEND.config import DATABASE_PATH
from BACKEND.config import RATING_DATASET_PATH


# Path to the database file (in the DB folder)
db_path = DATABASE_PATH

# Path to the data file
data_file = RATING_DATASET_PATH

# Create or connect to the SQLite database
conn = sqlite3.connect(db_path)
conn.execute("PRAGMA foreign_keys = ON")  # Enable foreign key constraints
cursor = conn.cursor()

# Create the ratings table with a composite primary key and foreign keys
cursor.execute('''
CREATE TABLE IF NOT EXISTS ratings (
    user_id INTEGER NOT NULL,
    item_id INTEGER NOT NULL,
    value INTEGER NOT NULL,
    timestamp INTEGER NOT NULL,
    date_time TEXT,
    PRIMARY KEY (user_id, item_id),
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (item_id) REFERENCES movies(id)
)
''')

# Optional: Create indices for faster queries
cursor.execute('CREATE INDEX IF NOT EXISTS idx_ratings_user_id ON ratings (user_id)')
cursor.execute('CREATE INDEX IF NOT EXISTS idx_ratings_item_id ON ratings (item_id)')

# Function to convert timestamp to readable datetime
def convert_timestamp(timestamp):
    return datetime.datetime.fromtimestamp(int(timestamp)).strftime('%Y-%m-%d %H:%M:%S')

# Read the ratings data from file
ratings_added = 0
batch_size = 1000  # Process in batches for better performance
batch = []

if os.path.exists(data_file):
    with open(data_file, 'r', encoding='latin-1') as f:
        for line in f:
            # Strip and split by tabs or spaces (the file might use either)
            fields = line.strip().split()
            if len(fields) == 4:
                user_id = int(fields[0])
                item_id = int(fields[1])
                value = int(fields[2])
                timestamp = int(fields[3])
                date_time = convert_timestamp(timestamp)
                
                # Add to batch
                batch.append((user_id, item_id, value, timestamp, date_time))
                
                # When batch is full, insert and commit
                if len(batch) >= batch_size:
                    cursor.executemany('''
                    INSERT OR REPLACE INTO ratings (user_id, item_id, value, timestamp, date_time)
                    VALUES (?, ?, ?, ?, ?)
                    ''', batch)
                    
                    conn.commit()
                    ratings_added += len(batch)
                    batch = []
                    print(f"Processed {ratings_added} ratings...")
    
    # Insert any remaining records
    if batch:
        cursor.executemany('''
        INSERT OR REPLACE INTO ratings (user_id, item_id, value, timestamp, date_time)
        VALUES (?, ?, ?, ?, ?)
        ''', batch)
        
        conn.commit()
        ratings_added += len(batch)
    
    print(f"Successfully added {ratings_added} ratings to the database.")
    print(f"Database updated at: {db_path}")
else:
    print(f"Error: File '{data_file}' not found.")

# Sample query to verify the data
print("\nSample ratings in database:")
cursor.execute('''
SELECT user_id, item_id, value, date_time
FROM ratings
LIMIT 10
''')

results = cursor.fetchall()
for row in results:
    user_id, item_id, value, date_time = row
    print(f"User: {user_id}, Item: {item_id}, Rating: {value}, Date: {date_time}")

# Rating distribution
print("\nRating distribution:")
cursor.execute('''
SELECT value, COUNT(*) as count
FROM ratings
GROUP BY value
ORDER BY value
''')

results = cursor.fetchall()
for row in results:
    value, count = row
    print(f"Rating {value}: {count} ratings ({count/ratings_added*100:.1f}%)")

# User activity stats
print("\nMost active users:")
cursor.execute('''
SELECT user_id, COUNT(*) as rating_count
FROM ratings
GROUP BY user_id
ORDER BY rating_count DESC
LIMIT 5
''')

results = cursor.fetchall()
for row in results:
    user_id, count = row
    print(f"User {user_id}: {count} ratings")

# Most rated items
print("\nMost rated items:")
cursor.execute('''
SELECT item_id, COUNT(*) as rating_count, AVG(value) as avg_rating
FROM ratings
GROUP BY item_id
ORDER BY rating_count DESC
LIMIT 5
''')

results = cursor.fetchall()
for row in results:
    item_id, count, avg = row
    print(f"Item {item_id}: {count} ratings, Avg rating: {avg:.2f}")

# Close the connection
conn.close()