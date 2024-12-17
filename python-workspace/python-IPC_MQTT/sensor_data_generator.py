import socket
import random
import time


def generate_sensor_data():
    return {"temperature": round(random.uniform(20, 30), 2), "humidity": round(random.uniform(40, 60), 2)}


def send_data_to_ipc_server():
    host = '127.0.0.1'
    port = 5000

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        client_socket.connect((host, port))
        while True:
            data = generate_sensor_data()
            client_socket.sendall(f"{data}\n".encode('utf-8'))
            print("Sent:", data)
            time.sleep(2)


if __name__ == "__main__":
    send_data_to_ipc_server()
