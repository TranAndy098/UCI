import socket

PORT = 2020
HOST = "127.0.0.1"

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as srv:
	srv.bind((HOST, PORT))
	srv.listen()

	print("server listening on port", PORT)

	connection, address = srv.accept()

	with connection:
		print("client connected")
		
		while True:
			rec_msg = connection.recv(4096)
			
			print("echo", rec_msg)

			if not rec_msg:
				break
			connection.sendall(rec_msg)
			
		print("client disconnected")
