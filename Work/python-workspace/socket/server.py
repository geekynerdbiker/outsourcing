import random
import socket
from _thread import *

host = '127.0.0.1'
port = 8484
ThreadCount = 0

clients = []
matrix = [[[0 for row in range(10)] for col in range(10)] for x in range(6)]

tick = 0
order = [[1, 1, 0, 0], [1, 0, 1, 0], [1, 0, 0, 1], [0, 1, 1, 0], [0, 1, 1, 0], [0, 0, 1, 1]]

rnd = 0
matrixA, matrixB = None, None
matrixInvited = [[0 for row in range(10)] for col in range(10)]


def handler(conn, addr):
    global matrixA, matrixB
    while True:
        try:
            data = conn.recv(2048)
            message = data.decode('utf-8')

            if not data:
                print('>> Disconnected ' + addr)
                break

            if len(clients) < 4:
                conn.send(str.encode('>> Waiting for remain clients to connect'))
            else:
                for i in range(4):
                    if conn == clients[i][0]:
                        if order[tick][i] == 1:
                            if matrixA is None:
                                matrixA = list(message)
                            elif matrixB is None:
                                matrixB = list(message)
                            else:
                                continue
                            conn.send(str.encode('>> Server: ' + message))
                        else:
                            row = random.randint(0, 10)
                            col = random.randint(0, 10)

                            while matrixInvited[row][col] != 0:
                                row = random.randint(0, 10)
                                col = random.randint(0, 10)

                            column = []
                            for c in range(10):
                                column.append(matrixB[c][col])
                            conn.send(str.encode(str(['cal', str(matrixA[row]), str(column)])))
                            matrix[rnd][row][col] = int(message)

            recv = '>> Server: ' + message
        except ConnectionResetError as e:
            print('>> Disconnected ' + addr)
            break
        finally:
            conn.close()

    if conn in clients:
        clients.remove(conn)


def start():
    server = socket.socket()
    try:
        server.bind((host, port))
    except socket.error as e:
        print(str(e))

    print('>> Server is listing on the port ' + {port} + '...')
    server.listen()

    try:
        while True:
            client, addr = server.accept()
            print('>> Connected to: ' + addr[0] + ':' + str(addr[1]))

            clients.append((client, ''))
            start_new_thread(handler, (client, addr))
    finally:
        server.close()

# start()
