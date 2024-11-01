package src.Server;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;

public class Server {
    HashMap<String, HashMap<String, ServerRecThread>> globalMap;
    ServerSocket serverSocket = null;
    Socket socket = null;
    static int connUserCount = 0;

    public Server() {
        globalMap = new HashMap<String, HashMap<String, ServerRecThread>>();
        Collections.synchronizedMap(globalMap);

        HashMap<String, ServerRecThread> group01 = new HashMap<String, ServerRecThread>();
        Collections.synchronizedMap(group01);

        HashMap<String, ServerRecThread> group02 = new HashMap<String, ServerRecThread>();
        Collections.synchronizedMap(group02);

        HashMap<String, ServerRecThread> group03 = new HashMap<String, ServerRecThread>();
        Collections.synchronizedMap(group03);

        HashMap<String, ServerRecThread> group04 = new HashMap<String, ServerRecThread>();
        Collections.synchronizedMap(group04);

        HashMap<String, ServerRecThread> group05 = new HashMap<String, ServerRecThread>();
        Collections.synchronizedMap(group05);

        globalMap.put("Room1", group01);
        globalMap.put("Room2", group02);
        globalMap.put("Room3", group03);
        globalMap.put("Room4", group04);
        globalMap.put("Room5", group05);
    }

    public void init() {
        try {
            serverSocket = new ServerSocket(8484);
            System.out.println("src.Server.Server Started.");

            while (true) {
                socket = serverSocket.accept();
                System.out.println(socket.getInetAddress() + ":" + socket.getPort());
                Thread msr = new ServerRecThread(socket);
                msr.start();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void sendGroupMsg(String loc, String msg) {
        HashMap<String, ServerRecThread> gMap = globalMap.get(loc);
        Iterator<String> group_it = globalMap.get(loc).keySet().iterator();
        while (group_it.hasNext()) {
            try {
                ServerRecThread st = gMap.get(group_it.next());
                if (!st.chatMode) {
                    st.out.writeUTF(msg);
                }
            } catch (Exception e) {
                System.out.println("Exception:" + e);
            }
        }
    }

    public void sendPrivatePMsg(String loc, String fromName, String toName, String msg) {
        try {
            globalMap.get(loc).get(toName).out.writeUTF(msg);
            globalMap.get(loc).get(fromName).out.writeUTF(msg);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendToMsg(String loc, String fromName, String toName, String msg) {
        try {
            globalMap.get(loc).get(toName).out.writeUTF("whisper|" + fromName + "|" + msg);
            globalMap.get(loc).get(fromName).out.writeUTF("whisper|" + fromName + "|" + msg);

        } catch (Exception e) {
            System.out.println("Exception:" + e);
        }

    }

    public String getEachMapSize() {
        return getEachMapSize(null);
    }

    public String getEachMapSize(String loc) {
        Iterator global_it = globalMap.keySet().iterator();
        StringBuffer sb = new StringBuffer();

        int sum = 0;
        sb.append("[ Room List ]" + System.getProperty("line.separator"));
        while (global_it.hasNext()) {
            try {
                String key = (String) global_it.next();
                HashMap<String, ServerRecThread> it_hash = globalMap.get(key);

                int size = it_hash.size();
                sum += size;
                sb.append(key + ": (" + size + ")" + (key.equals(loc) ? "(*)" : "") + "\r\n");

            } catch (Exception e) {
                System.out.println("Exception:" + e);
            }
        }
        sb.append("\r\nCurrent users :" + sum + "\r\n");
        return sb.toString();
    }

    public boolean isNameGlobal(String name) {
        boolean result = false;
        Iterator<String> global_it = globalMap.keySet().iterator();
        while (global_it.hasNext()) {
            try {
                String key = global_it.next();
                HashMap<String, ServerRecThread> it_hash = globalMap.get(key);
                if (it_hash.containsKey(name)) {
                    result = true;
                    break;
                }

            } catch (Exception e) {
                System.out.println("isNameGlobla() Exception:" + e);
            }
        }

        return result;
    }


    public static void main(String[] args) {
        Server ms = new Server();
        ms.init();
    }

    class ServerRecThread extends Thread {

        Socket socket;
        DataInputStream in;
        DataOutputStream out;
        String name = "";
        String loc = "";
        String toNameTmp = null;
        String fileServerIP;
        String filePath;
        boolean chatMode;

        public ServerRecThread(Socket socket) {
            this.socket = socket;
            try {
                in = new DataInputStream(socket.getInputStream());
                out = new DataOutputStream(socket.getOutputStream());
            } catch (Exception e) {
                System.out.println("ServerRecThread Constructor Exception:" + e);
            }
        }

        public String showUserList() {

            StringBuilder output = new StringBuilder("[ User List ]\r\n");
            Iterator it = globalMap.get(loc).keySet().iterator();
            while (it.hasNext()) {
                try {
                    String key = (String) it.next();
                    if (key.equals(name)) {
                        key += " (*) ";
                    }
                    output.append(key + "\r\n");
                } catch (Exception e) {
                    System.out.println("Exception:" + e);
                }
            }
            output.append("Current users " + globalMap.get(loc).size() + "\r\n");
            System.out.println(output.toString());
            return output.toString();
        }

        public String[] getMsgParse(String msg) {
            System.out.println("msgParse():msg?   " + msg);
            String[] tmpArr = msg.split("[|]");
            return tmpArr;
        }


        @Override
        public void run() {
            HashMap<String, ServerRecThread> clientMap = null;

            try {
                while (in != null) {
                    String msg = in.readUTF();
                    String[] msgArr = getMsgParse(msg.substring(msg.indexOf("|") + 1));

                    if (msg.startsWith("req_logon")) {
                        if (!(msgArr[0].trim().equals("")) && !isNameGlobal(msgArr[0])) {
                            name = msgArr[0];
                            Server.connUserCount++;
                            out.writeUTF("logon#yes|" + getEachMapSize());
                        } else {
                            out.writeUTF("logon#no|err01");
                        }
                    } else if (msg.startsWith("req_enterRoom")) {
                        loc = msgArr[1];

                        if (isNameGlobal(msgArr[0])) {
                            out.writeUTF("logon#no|" + name);

                        } else if (globalMap.containsKey(loc)) {
                            sendGroupMsg(loc, "show|" + name + " entered.");
                            clientMap = globalMap.get(loc);
                            clientMap.put(name, this);
                            System.out.println(getEachMapSize());
                            out.writeUTF("enterRoom#yes|" + loc);
                        } else {
                            out.writeUTF("enterRoom#no|" + loc);
                        }


                    } else if (msg.startsWith("req_cmdMsg")) {
                        if (msgArr[1].trim().equals("/user")) {
                            out.writeUTF("show|" + showUserList());

                        } else if (msgArr[1].trim().startsWith("/whisper")) {
                            String[] msgSubArr = msgArr[1].split(" ", 3);
                            if (msgSubArr == null || msgSubArr.length < 3) {
                                out.writeUTF("show|Wrong command.\r\n usage : /whisper [username] [message].");
                            } else if (name.equals(msgSubArr[1])) {
                                out.writeUTF("show|Cannot whisper yourself.\r\n usage : /whisper [username] [message].");
                            } else {
                                String toName = msgSubArr[1];
                                String toMsg = msgSubArr[2];

                                if (clientMap.containsKey(toName)) {
                                    System.out.println("whisper!");
                                    sendToMsg(loc, name, toName, toMsg);

                                } else {
                                    out.writeUTF("show|No user exist.");
                                }
                            }
                        } else if (msgArr[1].trim().startsWith("/room")) {

                            String[] msgSubArr = msg.split(" ");
                            if (msgSubArr.length == 1) {
                                out.writeUTF("show|" + getEachMapSize(loc));
                            } else if (msgSubArr.length == 2) {
                                String tmpLoc = msgSubArr[1];

                                if (loc.equals(tmpLoc)) {
                                    out.writeUTF("show|Wrong command.\r\n" + "usage : Print room list : /room" + "\r\n usage : Change room : /room [room name].");
                                    continue;
                                }

                                if (globalMap.containsKey(tmpLoc) && !this.chatMode) {
                                    out.writeUTF("show|Change room " + loc + " to " + tmpLoc + ".");

                                    clientMap.remove(name);
                                    sendGroupMsg(loc, "show|" + name + "left chatroom.");

                                    System.out.println("Remove " + name + " from " + loc + ".");
                                    loc = tmpLoc;
                                    clientMap = globalMap.get(loc);
                                    sendGroupMsg(loc, "show|" + name + "entered chatroom.");
                                    clientMap.put(name, this);

                                } else {
                                    out.writeUTF("Cannot access room.\r\n");
                                }

                            } else {
                                out.writeUTF("show|Wrong command.\r\n " + "usage : Print room list : /room" + "\r\n usage : Change room : /room [room name].");

                            }
                        } else if (msgArr[1].trim().startsWith("/chat")) {
                            String[] msgSubArr = msgArr[1].split(" ", 2);


                            if (msgSubArr.length != 2) {
                                out.writeUTF("show|Wrong command.\r\n" + "usage : 1:1 chat : /chat [username]");
                                continue;
                            } else if (name.equals(msgSubArr[1])) {
                                out.writeUTF("show|Wrong command.\r\n" + "Cannot chat yourself.\r\n" + "usage : 1:1 chat : /chat [username]");
                                continue;
                            }

                            if (!chatMode) {

                                String toName = msgSubArr[1].trim();
                                out.writeUTF("show|Request 1:1 chat to " + toName + ".");
                                if (clientMap.containsKey(toName) && !clientMap.get(toName).chatMode) {
                                    clientMap.get(toName).out.writeUTF("req_private|[##] " + name + " send 1:1 chat request.\r\n Your answer (y/n):");
                                    toNameTmp = toName;
                                    clientMap.get(toNameTmp).toNameTmp = name;
                                } else {
                                    out.writeUTF("show|User not found.");
                                }

                            } else {
                                out.writeUTF("show|You are already in private chat");
                            }

                        } else if (msgArr[1].startsWith("/quit")) {

                            if (chatMode) {
                                chatMode = false;
                                out.writeUTF("show|Quit private chat with" + toNameTmp + ".");
                                clientMap.get(toNameTmp).chatMode = false;
                                clientMap.get(toNameTmp).out.writeUTF("show|"+name + " left private chat.");
                                toNameTmp = "";
                                clientMap.get(toNameTmp).toNameTmp = "";

                            } else {
                                out.writeUTF("show|Only can use while in private chat.");
                            }

                        } else if (msgArr[1].trim().startsWith("/send")) {

                            if (!chatMode) {
                                out.writeUTF("show|Only can use while in private chat.");
                                continue;
                            }

                            String[] msgSubArr = msgArr[1].split(" ", 2);
                            if (msgSubArr.length != 2) {
                                out.writeUTF("show|Wrong command.\r\n usage : /send [filepath]");
                                continue;
                            }
                            filePath = msgSubArr[1];
                            File sendFile = new File(filePath);
                            String availExtList = "txt,java,jpeg,jpg,png,gif,bmp";


                            if (sendFile.isFile()) {
                                String fileExt = filePath.substring(filePath.lastIndexOf(".") + 1);
                                if (availExtList.contains(fileExt)) {
                                    Socket s = globalMap.get(loc).get(toNameTmp).socket;
                                    System.out.println("s.getInetAddress(): FTP IP => " + s.getInetAddress());

                                    fileServerIP = s.getInetAddress().getHostAddress();
                                    clientMap.get(toNameTmp).out.writeUTF("req_fileSend|" + name + " is trying to send file [" + sendFile.getName() + "].\r\n" + "Your answer (y/n):");
                                    out.writeUTF("show|Try to send file [" + sendFile.getAbsolutePath() + "] to" + toNameTmp + ".");
                                } else {
                                    out.writeUTF("show|Not available file. \r\n[" + availExtList + "].");
                                }
                            } else {
                                out.writeUTF("show|File not exist.");
                            }
                        } else {
                            out.writeUTF("show|Wrong command.\r\n usage : /send [filepath]");
                        }

                    } else if (msg.startsWith("req_say")) {
                        if (!chatMode) {
                            sendGroupMsg(loc, "say|" + name + "|" + msgArr[1]);
                        } else {
                            sendPrivatePMsg(loc, name, toNameTmp, "say|" + name + "|" + msgArr[1]);
                        }
                    } else if (msg.startsWith("req_whisper")) {
                        if (msgArr[1].trim().startsWith("/whisper")) {
                            String[] msgSubArr = msgArr[1].split(" ", 3);
                            if (msgSubArr == null || msgSubArr.length < 3) {
                                out.writeUTF("show|Wrong command.\r\n usage : /whisper [username] [message].");
                            } else {
                                String toName = msgSubArr[1];
                                String toMsg = msgSubArr[2];
                                if (clientMap.containsKey(toName)) {
                                    sendToMsg(loc, name, toName, toMsg);

                                } else {
                                    out.writeUTF("show|User not found.");
                                }

                            }
                        }
                    } else if (msg.startsWith("private")) {
                        String result = msgArr[0];
                        if (result.equals("yes")) {
                            chatMode = true;
                            clientMap.get(toNameTmp).chatMode = true;
                            System.out.println("Change to private chat.");
                            try {
                                out.writeUTF("show|Start private chat with " + toNameTmp + ".");
                                clientMap.get(toNameTmp).out.writeUTF("show|Start private chat with " + toNameTmp + ".");
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                        } else {
                            clientMap.get(toNameTmp).out.writeUTF("show|" + name + " refused request.");
                        }

                    } else if (msg.startsWith("fileSend")) {
                        String result = msgArr[0];
                        if (result.equals("yes")) {
                            System.out.println("##fileSend##YES");
                            try {
                                String tmpfileServerIP = clientMap.get(toNameTmp).fileServerIP;
                                String tmpfilePath = clientMap.get(toNameTmp).filePath;

                                clientMap.get(toNameTmp).out.writeUTF("fileSender|" + tmpfilePath);
                                String fileName = new File(tmpfilePath).getName();
                                out.writeUTF("fileReceiver|" + tmpfileServerIP + "|" + fileName);

                                clientMap.get(toNameTmp).filePath = "";
                                clientMap.get(toNameTmp).fileServerIP = "";

                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                        } else {
                            clientMap.get(toNameTmp).out.writeUTF("show|" + name + " refused request.");
                        }
                    } else if (msg.startsWith("req_exit")) {
                    }
                }
            } catch (Exception e) {
                System.out.println("Server:run():" + e.getMessage() + "----> ");
            } finally {
                if (clientMap != null) {
                    clientMap.remove(name);
                    sendGroupMsg(loc, name + "left.");
                    System.out.println("Current users are " + (--Server.connUserCount) + ".");
                }
            }
        }
    }
}
 