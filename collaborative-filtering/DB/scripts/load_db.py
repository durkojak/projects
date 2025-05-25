import sqlite3
import os
import sys
import importlib.util
import time

from BACKEND.config import DATABASE_PATH
from BACKEND.config import SCRIPTS_FOLDER_PATH

def import_and_run_script(script_path):
    """Import a Python script and run it"""
    # Get the script name without extension
    script_name = os.path.basename(script_path).replace('.py', '')
    
    # Import the script as a module
    spec = importlib.util.spec_from_file_location(script_name, script_path)
    module = importlib.util.module_from_spec(spec)
    
    # Temporarily add the script's directory to the system path
    script_dir = os.path.dirname(script_path)
    sys.path.insert(0, script_dir)
    
    # Execute the module
    spec.loader.exec_module(module)
    
    # Remove the temporary path addition
    sys.path.pop(0)
    
    return True

def main():
    # Get the directory of the current script
    script_dir = SCRIPTS_FOLDER_PATH
    # Path to the database file
    db_path = DATABASE_PATH
    
    # Check if database exists
    if os.path.exists(db_path):
        print(f"Removing existing database: {db_path}")
        os.remove(db_path)
        print("Database removed successfully.")
    else:
        print("No existing database found.")
    
    # Create an empty database file
    print("Creating new empty database file...")
    conn = sqlite3.connect(db_path)
    conn.close()
    print(f"Created empty database at: {db_path}")
    
    # List of scripts to run in order
    scripts = [
        "create_genre_table.py",
        "create_movie_table.py",
        "create_user_table.py",
        "create_rating_table.py",
        "create_suggestions_table.py",
        "create_currently_trending_table.py",
    ]
    
    # Run each script in order
    for script in scripts:
        script_path = os.path.join(script_dir, script)
        if os.path.exists(script_path):
            print(f"\n{'='*50}")
            print(f"Running {script}...")
            print(f"{'='*50}\n")
            
            # Run the script by importing it
            start_time = time.time()
            try:
                success = import_and_run_script(script_path)
                end_time = time.time()
                if success:
                    print(f"Successfully completed {script} in {end_time - start_time:.2f} seconds.")
                else:
                    print(f"Error running {script}")
            except Exception as e:
                print(f"Error running {script}: {str(e)}")
        else:
            print(f"Script {script} not found at {script_path}")
    
    # Verify database was created and has tables
    if os.path.exists(db_path):
        conn = sqlite3.connect(db_path)
        cursor = conn.cursor()
        
        # Get list of tables
        cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
        tables = cursor.fetchall()
        
        print("\nDatabase created successfully with the following tables:")
        for table in tables:
            cursor.execute(f"SELECT COUNT(*) FROM {table[0]}")
            count = cursor.fetchone()[0]
            print(f"- {table[0]}: {count} records")
        
        conn.close()
    else:
        print("Error: Database was not created.")

if __name__ == "__main__":
    main()