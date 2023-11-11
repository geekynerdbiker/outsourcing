import random
import socket

host = '127.0.0.1'
port = 8484

client = socket.socket()
matrix = [[[random.randint(0, 100) for row in range(10)] for col in range(10)]]

try:
    client.connect((host, port))
except socket.error as e:
    print(str(e))

while True:
    conn = client.recv(1024)
    message = list(conn.decode('utf-8'))

    if message[0] == 'cal':
        value = 0
        for i in range(10):
            value += message[1][i] * message[2][i]
        client.send(str.encode(str(['res', str(value)])))
    else:
        client.send(str.encode(str(matrix)))
