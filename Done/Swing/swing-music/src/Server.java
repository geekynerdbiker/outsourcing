import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Random;

public class Server {

    public static void main(String[] args) {
        System.out.println("Server is ON!");

        try {
            ServerSocket s = new ServerSocket(8189);
            for (;;) {

                Socket incoming = s.accept();
                Thread Server_Thread = new Thread(new ThreadHandler(incoming)); //���ʺ��� ������� ��������
                Server_Thread.start();
            }
        } catch (Exception e) {
            System.out.println(e);
        }

    }
}

class ThreadHandler implements Runnable {
    private Socket incoming;
    private static final int DEFAULT_BUFFER_SIZE = 10000;
    private static final int FILE_TRANSFER_PORT_NUM = 9000;

    public ThreadHandler(Socket i) {
        this.incoming = i;
    }

    public void run() {
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(incoming.getInputStream()));
            PrintWriter out = new PrintWriter(incoming.getOutputStream(), true);

            transfer_song_info(in, out);
            System.out.println("Test");

            in.close();
            out.close();
            incoming.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void transfer_song_info(BufferedReader in, PrintWriter out) {
        transfer_music(in, out);
        transfer_lyrics(in, out);
        transfer_image(in, out);
    }

    public void transfer_music(BufferedReader in, PrintWriter out) {

        byte[] buffer = new byte[DEFAULT_BUFFER_SIZE];
        int readBytes;

        try {
            ServerSocket server = new ServerSocket(FILE_TRANSFER_PORT_NUM);
            out.println("Server Ready");
            Socket socket = server.accept();


            int song_id = Integer.parseInt(in.readLine());
            System.out.println("received id = " + song_id);


            ArrayList song_data = Database.getSong_info(song_id);
            String song_dir = (String) song_data.get(1);

            File file = new File(song_dir);
            FileInputStream fis = new FileInputStream(file);
            OutputStream os = socket.getOutputStream();

            out.println("Transfer Ready");

            System.out.println(in.readLine());

            while ((readBytes = fis.read(buffer)) > 0) {
                os.write(buffer, 0, readBytes);
            }
            os.close();
            fis.close();
            socket.close();
            server.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void transfer_lyrics(BufferedReader in, PrintWriter out) {
        byte[] buffer = new byte[DEFAULT_BUFFER_SIZE];
        int readBytes;

        try {
            ServerSocket server = new ServerSocket(FILE_TRANSFER_PORT_NUM);
            out.println("Server Ready");
            Socket socket = server.accept();


            int song_id = Integer.parseInt(in.readLine());
            System.out.println("received id = " + song_id);


            ArrayList song_data = Database.getSong_info(song_id);
            String lyrics_dir = (String) song_data.get(2);

            File file = new File(lyrics_dir);
            FileInputStream fis = new FileInputStream(file);
            OutputStream os = socket.getOutputStream();

            out.println("Transfer Ready");
            System.out.println(in.readLine());


            while ((readBytes = fis.read(buffer)) > 0) {
                os.write(buffer, 0, readBytes);
            }
            os.close();
            fis.close();
            socket.close();
            server.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void transfer_image(BufferedReader in, PrintWriter out) {
        byte[] buffer = new byte[DEFAULT_BUFFER_SIZE];
        int readBytes;

        try {
            ServerSocket server = new ServerSocket(FILE_TRANSFER_PORT_NUM);
            out.println("Server Ready");
            Socket socket = server.accept();

            int song_id = Integer.parseInt(in.readLine());
            System.out.println("received id = " + song_id);

            ArrayList song_data = Database.getSong_info(song_id);
            String image_dir = (String) song_data.get(3);

            File file = new File(image_dir);
            FileInputStream fis = new FileInputStream(file);
            OutputStream os = socket.getOutputStream();

            out.println("Transfer Ready");
            System.out.println(in.readLine());

            while ((readBytes = fis.read(buffer)) > 0) {
                os.write(buffer, 0, readBytes);
            }
            os.close();
            fis.close();
            socket.close();
            server.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}