import socket
serverIp = '127.0.0.1'
serverPort = 5050
# Simple client setup
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((serverIp, serverPort))  # Connect to the server
client_socket.send("Hello, Server its me the client".encode('utf-8'))  # Send a simple message
client_socket.close()  # Close the connection
