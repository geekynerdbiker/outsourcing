import socket
import mariadb
import paho.mqtt.client as mqtt
import ast


def connect_to_db():
    return mariadb.connect(user="youruser", password="yourpassword", database="sensordb", host="127.0.0.1")


mqtt_client = mqtt.Client()
mqtt_client.connect("127.0.0.1", 1883, 60)


def save_to_db(cursor, data):
    cursor.execute("INSERT INTO sensor_data (temperature, humidity) VALUES (?, ?)",
                   (data["temperature"], data["humidity"]))


def handle_client_connection():
    host = '127.0.0.1'
    port = 5000

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((host, port))
        server_socket.listen(1)
        print("IPC Server Started... Waiting for sensor data")

        conn, _ = server_socket.accept()
        with conn:
            db_conn = connect_to_db()
            cursor = db_conn.cursor()

            while True:
                data = conn.recv(1024).decode('utf-8')
                if not data:
                    break
                sensor_data = ast.literal_eval(data.strip())
                print("Received:", sensor_data)

                save_to_db(cursor, sensor_data)
                db_conn.commit()

                mqtt_client.publish("sensor/data", str(sensor_data))
                print("Sent to MQTT:", sensor_data)


if __name__ == "__main__":
    handle_client_connection()
