package src.Client.File;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class FileSender extends Thread{
    String filePath;
    public FileSender() {

    }
    public FileSender(String filePath) {
        this.filePath = filePath;
    }


    @Override
    public void run() {
        try {
            ServerSocket serverSocket = new ServerSocket(9990);
            System.out.println("File server start.");
            serverSocket.setSoTimeout(5000);

            Socket socket = serverSocket.accept();
            System.out.println("Start Upload.");
            FileInputStream fis = new FileInputStream(filePath);
            BufferedInputStream bis = new BufferedInputStream(fis);

            OutputStream out = socket.getOutputStream();
            BufferedOutputStream bos = new BufferedOutputStream(out);

            int r=0;
            while((r = bis.read())!=-1){
                bos.write(r);
            }

            System.out.println("Upload done!");

            bos.close();
            bis.close();
            out.close();
            fis.close();
            socket.close();
            serverSocket.close();

        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("Upload failed.");
        }
    }
}