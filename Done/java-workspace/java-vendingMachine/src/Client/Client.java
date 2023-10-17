package Client;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;

public class Client extends Application {
    public static Socket socket;

    public static void startClient() {
        Thread thread = new Thread() {
            public void run() {
                try {
                    socket = new Socket();
                    socket.connect(new InetSocketAddress("localhost", 5001));
                    Platform.runLater(() -> {
                        System.out.println("연결 성공");
                    });
                } catch (IOException e) {
                    if (!socket.isClosed()) {
                        stopClient();
                    }
                    return;
                }
                receive();
            }
        };
        thread.start();
    }

    static void receive() {
    }

    static void stopClient() {
        try {
            if (socket != null && !socket.isClosed())
                socket.close();
        } catch (Exception e) {
        }
    }


    @Override
    public void start(Stage primaryStage) throws Exception {

        startClient();
    }

    public static void main(String[] args) {
        launch(args);
    }

}
