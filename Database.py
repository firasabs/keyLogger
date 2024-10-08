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

#Close the database connection
def close_db(conn):
    conn.close()
