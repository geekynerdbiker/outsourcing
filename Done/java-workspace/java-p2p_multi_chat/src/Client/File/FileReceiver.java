package src.Client.File;

import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;

public class FileReceiver extends Thread {
    Socket socket;
    InputStream in;
    FileOutputStream fos;
    String filename;
    BufferedInputStream bis;
    BufferedOutputStream bos;

    public FileReceiver() {

    }

    public FileReceiver(String ip, String filename) {
        try {
            this.filename = filename;
            socket = new Socket(ip, 9990);
            System.out.println("Start download.");
            in = socket.getInputStream();
            bis = new BufferedInputStream(in);

        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        try {
            String fileSeparator = System.getProperty("file.separator");

            File f = new File("Download");
            if (!f.isDirectory()) {
                f.mkdir();
            }

            fos = new FileOutputStream("Download" + fileSeparator + filename);
            bos = new BufferedOutputStream(fos);
            int r = 0;
            while ((r = bis.read()) != -1) {
                bos.write(r);
            }
            System.out.println("Download" + fileSeparator + filename);
            System.out.println("Download done!");

        } catch (FileNotFoundException e) {
            System.out.println("Exception: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("Download failed.");
        } finally {
            try {
                fos.close();
                in.close();
                bis.close();
                bos.close();
                socket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }
}