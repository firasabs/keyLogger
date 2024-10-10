import sqlite3
from datetime import datetime, timedelta

def connect_db():  # create or connect to db
    conn = sqlite3.connect('keylog.db')
    return conn

# Create the keystrokes table (if not exists)
def create_table(conn):
    cursor = conn.cursor()
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS keystrokes (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
        key TEXT NOT NULL
    )
    ''')
    conn.commit()

# Insert keys (data) into the database
def save_keystroke(conn, key):
    cursor = conn.cursor()
    
    # Get the current time in UTC and convert it to Jerusalim local time (UTC+3)
    utc_now = datetime.utcnow()  # Get current UTC time
    local_offset = timedelta(hours=3)  # Israel is UTC+3
    local_time = utc_now + local_offset  # Adjust to local time
    
    # Format the local time to only include hours, minutes, and seconds
    formatted_time = local_time.strftime("%Y-%m-%d %H:%M:%S")

    # Insert key and local timestamp into the database
    cursor.execute("INSERT INTO keystrokes (timestamp, key) VALUES (?, ?)", (formatted_time, key))
    conn.commit()

# Close the database connection
def close_db(conn):
    conn.close()