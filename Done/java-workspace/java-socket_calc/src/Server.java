import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Server {
    private static ExecutorService threadPool;
    private static ServerSocket serverSocket;
    private static List<Client> connections = new Vector<Client>();

    public static void main(String[] args) {
        startServer();
    }

    private static void startServer() {
        threadPool = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
        try {
            serverSocket = new ServerSocket();
            serverSocket.bind(new InetSocketAddress("localhost", 5000));
        } catch (IOException e) {
            if (!serverSocket.isClosed())
                stopServer();
            e.printStackTrace();
        }

        Runnable runnable = new Runnable() {
            @Override
            public void run() {
                System.out.println("[Server Start]");
                while (true) {
                    try {
                        Socket socket = serverSocket.accept();
                        System.out.println("[Connected: " + socket.getRemoteSocketAddress() + ": " + Thread.currentThread().getName() + "]");
                        Client client = new Client(socket);
                        connections.add(client);
                        System.out.println("[" + connections.size() + " Client Connected]");
                    } catch (Exception e) {
                        if (!serverSocket.isClosed()) {
                            stopServer();
                        }
                        break;
                    }
                }
            }
        };
        threadPool.submit(runnable);
    }

    private static void stopServer() {
        try {
            // 모든 소켓 닫기
            Iterator<Client> iterator = connections.iterator();
            while (iterator.hasNext()) {
                Client client = iterator.next();
                client.socket.close();
                iterator.remove();
            }

            if (serverSocket != null && !serverSocket.isClosed()) {
                serverSocket.close();
            }

            if (threadPool != null && !threadPool.isShutdown()) {
                threadPool.shutdown();
            }

            System.out.println("[Server Closed]");
        } catch (Exception e) {
        }
    }

    static class Client {
        Socket socket;

        Client(Socket socket) {
            this.socket = socket;
            receive();
        }

        void receive() {
            Runnable runnable = new Runnable() {
                @Override
                public void run() {
                    try {
                        while (true) {
                            byte[] byteArr = new byte[100];
                            InputStream inputStream = socket.getInputStream();
                            int readByteCount = inputStream.read(byteArr);

                            if (readByteCount == -1) {
                                throw new IOException();
                            }

                            System.out.println("[REQUEST: " + socket.getRemoteSocketAddress() + ": " + Thread.currentThread().getName() + "]");
                            String data = new String(byteArr, 0, readByteCount, "UTF-8");

                            String s = "", err = "", etype = "";
                            double res = 0;

                            if (data.equals("/quit"))
                                break;

                            ArrayList<String> params = new ArrayList<>();
                            StringTokenizer stringTokenizer = new StringTokenizer(data, " ");

                            while (stringTokenizer.hasMoreTokens())
                                params.add(stringTokenizer.nextToken());

                            if (params.size() > 3) {
                                etype = "Incorrect";
                                err = "Too many arguments.";
                            } else if (params.size() < 3) {
                                etype = "Incorrect";
                                err = "Not enough arguments.";
                            } else {
                                try {
                                    int op1 = Integer.parseInt(params.get(1));
                                    int op2 = Integer.parseInt(params.get(2));

                                    switch (params.get(0)) {
                                        case "ADD":
                                            res = op1 + op2;
                                            break;
                                        case "SUB":
                                            res = op1 - op2;
                                            break;
                                        case "MUL":
                                            res = op1 * op2;
                                            break;
                                        case "DIV":
                                            if (op2 == 0) {
                                                etype = "Incorrect";
                                                err = "Divided by zero.";
                                            }
                                            res = op1 / (double) op2;

                                            break;
                                        default:
                                            etype = "Incorrect";
                                            err = "No match operation.";
                                            break;
                                    }
                                } catch (NumberFormatException e) {
                                    etype = "Incorrect";
                                    err = "Invalid operand.";
                                }
                            }

                            if (!err.equals(""))
                                Client.this.send(etype + ": " + err);
                            else
                                Client.this.send("Answer: " + res);
//
                            if (params.equals("/stop")) {
                                stopServer();
                            }
                        }
                    } catch (Exception e) {
                        try {
                            connections.remove(Client.this);
                            System.out.println("[No Response: " + socket.getRemoteSocketAddress() + ": " + Thread.currentThread().getName() + "]");
                            socket.close();
                        } catch (IOException e2) {
                        }
                    }
                }
            };
            threadPool.submit(runnable);
        }

        void send(String data) {
            Runnable runnable = new Runnable() {
                @Override
                public void run() {
                    try {
                        byte[] byteArr = data.getBytes("UTF-8");
                        OutputStream outputStream = socket.getOutputStream();
                        outputStream.write(byteArr);
                        outputStream.flush();
                    } catch (Exception e) {
                        try {
                            System.out.println("[No Response: " + socket.getRemoteSocketAddress() + ": " + Thread.currentThread().getName() + "]");
                            connections.remove(Client.this);
                            socket.close();
                        } catch (IOException e2) {
                        }
                    }
                }
            };
            threadPool.submit(runnable);
        }
    }
}