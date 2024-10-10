import socket
serverIp = '127.0.0.1'
serverPort = 12345
# Simple client setup
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((serverIp, serverPort))  # Connect to the server
client_socket.send("hello server, from client ".encode('utf-8'))  # Send a simple message
client_socket.close()  # Close the connection
