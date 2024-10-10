import sqlite3
def connect_db(): #create or connect to db
    conn = sqlite3.connect('keylog.db')
    return conn

#Create the keystrokes table (if not exists)
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

#Insert keys (data) into the database
def save_keystroke(conn, key):
    cursor = conn.cursor()
    cursor.execute("INSERT INTO keystrokes (key) VALUES (?)", (key,))
    conn.commit()
    """
# Function to fetch and display all stored keystrokes
def get_all_keystrokes(conn):
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM keystrokes")
    rows = cursor.fetchall()  # Fetch all rows from the table

    for row in rows:
        print(row)  # Print each row (ID, timestamp, key)
        """
#Close the database connection
def close_db(conn):
    conn.close()
