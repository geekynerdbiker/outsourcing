'''
  ETTTP_Client_skeleton.py
 
  34743-02 Information Communications
  Term Project on Implementation of Ewah Tic-Tac-Toe Protocol
 
  Skeleton Code Prepared by JeiHee Cho
  May 24, 2023
 
 '''

import random
import tkinter as tk
from socket import *
import _thread

from ETTTP_TicTacToe_skeleton import TTT, check_msg

if __name__ == '__main__':
    SERVER_IP = '127.0.0.1'
    MY_IP = '127.0.0.1'
    SERVER_PORT = 12000
    SIZE = 1024
    SERVER_ADDR = (SERVER_IP, SERVER_PORT)

    with socket(AF_INET, SOCK_STREAM) as client_socket:
        client_socket.connect(SERVER_ADDR)

        ###################################################################
        # Receive who will start first from the server
        msg = client_socket.recv(SIZE).decode()

        # 메세지가 유효하지 않다면 Quit
        msg_valid_check = check_msg(msg, MY_IP)
        if msg_valid_check is False or msg_valid_check[0] != 'SEND':
            client_socket.close()
            TTT.quit()

        # player 설정
        # 서버 먼저 시작
        if msg_valid_check[1] == 'ME':
            player = 'YOU'
            start = 0

        # 클라이언트 먼저 시작
        else:
            player = "ME"
            start = 1

        ######################### Fill Out ################################
        # Send ACK
        client_socket.send(f"ACK ETTTP/1.0\r\nHost:{MY_IP}\r\nFirst-Move:{player}\r\n\r\n".encode())

        ###################################################################

        # Start game
        root = TTT(target_socket=client_socket, src_addr=MY_IP, dst_addr=SERVER_IP)
        root.play(start_user=start)
        root.mainloop()
        client_socket.close()
