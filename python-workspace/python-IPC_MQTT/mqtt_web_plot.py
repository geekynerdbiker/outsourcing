import paho.mqtt.client as mqtt
import matplotlib.pyplot as plt
from flask import Flask, Response

app = Flask(__name__)
data_log = {"temperature": [], "humidity": []}


def on_message(client, userdata, msg):
    data = eval(msg.payload.decode())
    data_log["temperature"].append(data["temperature"])
    data_log["humidity"].append(data["humidity"])
    print("Received via MQTT:", data)


mqtt_client = mqtt.Client()
mqtt_client.on_message = on_message
mqtt_client.connect("127.0.0.1", 1883, 60)
mqtt_client.subscribe("sensor/data")
mqtt_client.loop_start()


@app.route('/')
def plot_graph():
    plt.figure(figsize=(6, 4))
    plt.plot(data_log["temperature"], label="Temperature (°C)")
    plt.plot(data_log["humidity"], label="Humidity (%)")
    plt.xlabel("Time")
    plt.ylabel("Value")
    plt.legend()
    plt.title("Real-time Sensor Data")
    plt.tight_layout()

    # 이미지 반환
    import io, base64
    img = io.BytesIO()
    plt.savefig(img, format='png')
    img.seek(0)
    return Response(img.getvalue(), mimetype='image/png')


if __name__ == "__main__":
    app.run(debug=True, port=8000)
