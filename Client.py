import socket
Server_ip  = '127.0.0.1'
Server_Port = 5050
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(Server_ip,Server_Port)
message = "Hello from  client"
client_socket.send(message.encode())  # Encode the message to bytes before sending
# Step 4: Receive a response from the server
#response = client_socket.recv(1024)  # Receive data from server (buffer size of 1024 bytes)
#print(f"Response from server: {response.decode('utf-8')}")  # Decode and print server response
client_socket.close() #close the connection
