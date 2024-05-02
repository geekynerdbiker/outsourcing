import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.util.Scanner;

public class Client {
    static Socket socket;

    static void startClient() {
        Thread thread = new Thread() {
            @Override
            public void run() {
                try {
                    socket = new Socket();
                    socket.connect(new InetSocketAddress("localhost", 5000));
                    System.out.println("[Connected]");
                } catch (Exception e) {
                    System.out.println("[No Response]");
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

    static void stopClient() {
        try {
            System.out.println("[Disconnected]");
            if (socket != null && !socket.isClosed()) {
                socket.close();
            }
        } catch (IOException e) {
        }
    }

    static void receive() {
        while (true) {
            try {
                byte[] byteArr = new byte[100];
                InputStream inputStream = socket.getInputStream();

                int readByteCount = inputStream.read(byteArr);
                if (readByteCount == -1) {
                    throw new IOException();
                }

                String data = new String(byteArr, 0, readByteCount, "UTF-8");
                System.out.println(data);
            } catch (Exception e) {
                System.out.println("[No Connection]");
                stopClient();
                break;
            }
        }
    }

    static void send(String data) {
        Thread thread = new Thread() {
            @Override
            public void run() {
                try {
                    byte[] byteArr = data.getBytes("UTF-8");
                    OutputStream outputStream = socket.getOutputStream();
                    outputStream.write(byteArr);
                    outputStream.flush();
                } catch (Exception e) {
                    System.out.println("[No Connection]");
                    stopClient();
                }
            }
        };
        thread.start();
    }


    public static void main(String[] args) {
        startClient();
        while (true) {
            Scanner sc = new Scanner(System.in);
            String message = sc.nextLine();
            if (message.equals("/stop"))
                break;
            send(message);
        }
        stopClient();
    }
}