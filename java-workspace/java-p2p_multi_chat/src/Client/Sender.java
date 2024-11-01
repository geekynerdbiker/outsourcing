package src.Client;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.SocketException;
import java.util.Scanner;

public class Sender extends Thread {
    Socket socket;
    DataOutputStream out;
    String name;

    public Sender(Socket socket) {
        this.socket = socket;
        try {
            out = new DataOutputStream(this.socket.getOutputStream());
        } catch (Exception e) {
            System.out.println("Exception:" + e);
        }
    }

    @Override
    public void run() {
        Scanner s = new Scanner(System.in);

        System.out.print("Input Name: ");
        while (out != null) {
            try {
                String msg = s.nextLine();
                if (msg == null || msg.trim().equals("")) {
                    msg = " ";
                }

                if (Client.chatState == 0) {
                    if (!msg.trim().equals("")) {
                        name = msg;
                        out.writeUTF("req_logon|" + msg);
                    } else {
                        System.out.print("Input name without whitespace.\r\n" +
                                "Input Name: ");
                    }
                } else if (Client.chatState == 1) {
                    if (!msg.trim().equals("")) {
                        out.writeUTF("req_enterRoom|" + name + "|" + msg);
                    } else {
                        System.out.println("Input room name without whitespace.\r\n" +
                                "Input Room Name: ");
                    }
                } else if (msg.trim().startsWith("/")) {
                    if (msg.equalsIgnoreCase("/exit")) {
                        System.out.println("Exit Client.");
                        System.exit(0);
                        break;
                    } else {
                        out.writeUTF("req_cmdMsg|" + name + "|" + msg);
                    }
                } else if (Client.chatState == 3) {
                    msg = msg.trim();

                    if (msg.equalsIgnoreCase("y")) {
                        out.writeUTF("private|yes");
                    } else if (msg.equalsIgnoreCase("n")) {
                        out.writeUTF("private|no");
                    } else {
                        System.out.println("Invalid Input.");
                        out.writeUTF("private|no");
                    }
                    Client.chatState = 2;
                } else if (Client.chatState == 5) {
                    if (msg.trim().equalsIgnoreCase("y")) {
                        out.writeUTF("fileSend|yes");
                    } else if (msg.trim().equalsIgnoreCase("n")) {
                        out.writeUTF("fileSend|no");
                    } else {
                        System.out.println("Invalid Input.");
                        out.writeUTF("fileSend|no");
                    }
                    Client.chatState = 2;

                } else {
                    out.writeUTF("req_say|" + name + "|" + msg);
                }
            } catch (SocketException e) {
                System.out.println("src.Client.Sender:run() Exception:" + e);
                System.out.println("Server disconnected.");
                return;
            } catch (IOException e) {
                System.out.println("Exception:" + e);
            }
        }
    }
}