import socket
# Simple server setup
serverIp = '127.0.0.1'
serverPort = 5050
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((serverIp, serverPort))
server_socket.listen(1)  # Listen for one connection
print("[LISTENING] Server is listening on 127.0.0.1:5050")
 
conn, addr = server_socket.accept()  # Accept the connection
print(f"[CONNECTED] {addr} connected.")

data = conn.recv(1024).decode('utf-8')  # Receive message
print(f"[RECEIVED] Message from client: {data}")

conn.close()  # Close the connection
