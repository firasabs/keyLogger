import sqlite3
try:
    db = sqlite3.connect('keystrokes.db') #connecting to a data base
    cursor = db.cursor() # @cursor a parameter, let as execute
     # This method accepts a MySQL query
    cursor.execute("CREATE TABLE IF NOT EXISTS keystrocke(client TEXT, keys TEXT, time INTEGER)")
    db.commit()    
except Exception as e:
    print("cannot open db:", e)
if db:
    db.close()
