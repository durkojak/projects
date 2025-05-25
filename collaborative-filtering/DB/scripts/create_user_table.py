import sqlite3
import os
from BACKEND.config import DATABASE_PATH
from BACKEND.config import USER_DATASET_PATH


# Path to the user file
user_file = USER_DATASET_PATH
db_path = DATABASE_PATH

# Create or connect to the SQLite database
conn = sqlite3.connect(db_path)
cursor = conn.cursor()

# Create the users table
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY,
    age INTEGER NOT NULL,
    gender TEXT NOT NULL,
    occupation TEXT NOT NULL,
    zip_code TEXT NOT NULL
)
''')

# Read the user data from file
users_added = 0

if os.path.exists(user_file):
    with open(user_file, 'r', encoding='latin-1') as f:
        for line in f:
            fields = line.strip().split('|')
            if len(fields) == 5:
                user_id = int(fields[0])
                age = int(fields[1])
                gender = fields[2]
                occupation = fields[3]
                zip_code = fields[4]
                
                # Insert user data
                cursor.execute('''
                INSERT OR REPLACE INTO users (id, age, gender, occupation, zip_code)
                VALUES (?, ?, ?, ?, ?)
                ''', (user_id, age, gender, occupation, zip_code))
                users_added += 1
                
                # Commit every 100 users for better performance
                if users_added % 100 == 0:
                    conn.commit()
                    print(f"Processed {users_added} users...")
    
    # Final commit
    conn.commit()
    print(f"Successfully added {users_added} users to the database.")
    print(f"Database updated at: {db_path}")
else:
    print(f"Error: File '{user_file}' not found.")

# Sample query to verify the data
print("\nSample users in database:")
cursor.execute('''
SELECT id, age, gender, occupation, zip_code
FROM users
WHERE id <= 10
ORDER BY id
''')

results = cursor.fetchall()
for row in results:
    user_id, age, gender, occupation, zip_code = row
    print(f"ID: {user_id}, Age: {age}, Gender: {gender}, Occupation: {occupation}, Zip: {zip_code}")

# Distribution of users by gender
print("\nUser distribution by gender:")
cursor.execute('''
SELECT gender, COUNT(*) as count
FROM users
GROUP BY gender
''')

results = cursor.fetchall()
for row in results:
    gender, count = row
    print(f"{gender}: {count} users")

# Distribution by occupation
print("\nTop 10 occupations:")
cursor.execute('''
SELECT occupation, COUNT(*) as count
FROM users
GROUP BY occupation
ORDER BY count DESC
LIMIT 10
''')

results = cursor.fetchall()
for row in results:
    occupation, count = row
    print(f"{occupation}: {count} users")

# Age distribution
print("\nAge distribution:")
cursor.execute('''
SELECT 
    CASE
        WHEN age < 18 THEN 'Under 18'
        WHEN age BETWEEN 18 AND 24 THEN '18-24'
        WHEN age BETWEEN 25 AND 34 THEN '25-34'
        WHEN age BETWEEN 35 AND 44 THEN '35-44'
        WHEN age BETWEEN 45 AND 54 THEN '45-54'
        WHEN age >= 55 THEN '55+'
    END as age_group,
    COUNT(*) as count
FROM users
GROUP BY age_group
ORDER BY 
    CASE age_group
        WHEN 'Under 18' THEN 1
        WHEN '18-24' THEN 2
        WHEN '25-34' THEN 3
        WHEN '35-44' THEN 4
        WHEN '45-54' THEN 5
        WHEN '55+' THEN 6
    END
''')

results = cursor.fetchall()
for row in results:
    age_group, count = row
    print(f"{age_group}: {count} users")

# Close the connection
conn.close()