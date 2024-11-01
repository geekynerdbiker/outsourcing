package src.Client;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

public class Client {
    static boolean chatmode = false;
    static int chatState = 0;

    public static void main(String[] args) throws UnknownHostException, IOException {
        try {
            String ServerIP = "localhost";
            Socket socket = new Socket(ServerIP, 8484);
            System.out.println("Server connected");

            Thread sender = new Sender(socket);
            Thread receiver = new Receiver(socket);

            sender.start();
            receiver.start();

        } catch (Exception e) {
            System.out.println("Exception [MultiClient class]:" + e);
        }
    }
}