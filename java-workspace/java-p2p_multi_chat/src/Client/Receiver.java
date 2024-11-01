package src.Client;

import src.Client.File.FileReceiver;
import src.Client.File.FileSender;

import java.io.DataInputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketException;

public class Receiver extends Thread {
    Socket socket;
    DataInputStream in;

    public Receiver(Socket socket) {
        this.socket = socket;

        try {
            in = new DataInputStream(this.socket.getInputStream());
        } catch (Exception e) {
            System.out.println("Exception:" + e);
        }
    }

    public String[] getMsgParse(String msg) {
        String[] tmpArr = msg.split("[|]");

        return tmpArr;
    }


    @Override
    public void run() {
        while (in != null) {
            try {
                String msg = in.readUTF();
                String[] msgArr = getMsgParse(msg.substring(msg.indexOf("|") + 1));

                if (msg.startsWith("logon#yes")) {
                    Client.chatState = 1;
                    System.out.println(msgArr[0]);
                    System.out.print("Input Room Name: ");
                } else if (msg.startsWith("logon#no")) {
                    Client.chatState = 0;
                    System.out.print("Already exist. Input Other Name: ");
                } else if (msg.startsWith("enterRoom#yes")) {
                    System.out.println("Entered " + msgArr[0] + ".");
                    Client.chatState = 2;
                } else if (msg.startsWith("enterRoom#no")) {
                    System.out.println("Room Name " + msgArr[0] + " not exist.");
                    System.out.print("Input Room Name: ");
                } else if (msg.startsWith("show")) {
                    System.out.println(msgArr[0]);
                } else if (msg.startsWith("say")) {
                    System.out.println("[" + msgArr[0] + "] " + msgArr[1]);
                } else if (msg.startsWith("whisper")) {
                    System.out.println("[Whisper][" + msgArr[0] + "] " + msgArr[1]);
                } else if (msg.startsWith("req_private")) {
                    Client.chatState = 3;
                    System.out.println(msgArr[0]);
                    System.out.print("Choose: ");

                } else if (msg.startsWith("req_fileSend")) {
                    Client.chatState = 5;
                    System.out.println(msgArr[0]);
                    System.out.print("Choose: ");
                    sleep(100);
                } else if (msg.startsWith("fileSender")) {
                    System.out.println("fileSender:" + InetAddress.getLocalHost().getHostAddress());
                    System.out.println("fileSender:" + msgArr[0]);
                    try {
                        new FileSender(msgArr[0]).start();
                    } catch (Exception e) {
                        System.out.println("src.Client.File.FileSender 쓰레드 오류:");
                        e.printStackTrace();
                    }
                } else if (msg.startsWith("fileReceiver")) {
                    System.out.println("fileReceiver:" + InetAddress.getLocalHost().getHostAddress());
                    System.out.println("fileReceiver:" + msgArr[0] + "/" + msgArr[1]);

                    String ip = msgArr[0];
                    String fileName = msgArr[1];

                    try {
                        new FileReceiver(ip, fileName).start();
                    } catch (Exception e) {
                        System.out.println("src.Client.File.FileSender 쓰레드 오류:");
                        e.printStackTrace();
                    }
                } else if (msg.startsWith("req_exit")) {

                }
            } catch (SocketException e) {
                System.out.println("Exception:" + e);
                System.out.println("Server disconnected.");
                return;
            } catch (Exception e) {
                System.out.println("src.Client.Receiver:run() Exception:" + e);

            }
        }
    }
}
 