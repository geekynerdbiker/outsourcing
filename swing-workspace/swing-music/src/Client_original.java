import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GridLayout;
import java.awt.TextArea;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;



public class Client_original {
	final int DEFAULT_BUFFER_SIZE = 10000;
	final static int FILE_TRANSFER_PORT_NUM = 9000;
	
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		try {
			// 1. ���� �����
				String IP = "127.0.0.1"; // ������ ������(������ �ּ�)�� �Է��ϰ�
				Socket myClient = new Socket(IP,8189); // ó���� Ŭ���̾�Ʈ ������ ������ְ�
				
			// 2. I/O ��Ʈ�� ����
				BufferedReader in = null;
				try {
				  in = new BufferedReader(new InputStreamReader(
				                          myClient.getInputStream()));
				} catch (IOException ioe) { ioe.printStackTrace();}

				PrintWriter out = null;
				try {
				  out = new PrintWriter(myClient.getOutputStream(),true); // true�� autoflush
				} catch (IOException ioe1) { ioe1.printStackTrace(); }

			// 3. ����� (GUI�� ��ü ����)
				String decision = null;
				do{
					System.out.println("quit / request_song / album_list");
					decision = scan.next();
					out.println(decision);

					if(decision.equals("request_song")) {
						System.out.println("which song?");
						String song_id = scan.next();
						request_song_info(myClient,song_id,in,out);
					}
					else if(decision.equals("album_list")) {
						request_album_info(in,out);
					}
					
					
				} while(!decision.equals("quit"));
				
				

			// 4. ��Ʈ�� ����
				try {
					out.close();
					in.close();
					myClient.close();
				} catch (IOException io) {
					io.printStackTrace();
				}
		}
		catch(Exception e) {
			
		}
		
}
		
	
	/*
	 * ȸ������ ���� �޼ҵ�� ����
	 * 
	 * */	

	
/*
 * �뷡 ��� ���� �޼ҵ�� ����
 * 
 * */
	public static void request_song_info(Socket socket, String song_id, BufferedReader in, PrintWriter out) {
		request_music(song_id,in,out);
		request_lyrics(song_id,in,out);
		request_image(song_id,in,out);
		System.out.println("�뷡���� ���� �Ϸ�");
	}
	public static void request_music(String song_id, BufferedReader in, PrintWriter out) {
		final int DEFAULT_BUFFER_SIZE = 10000;
        byte[] buffer = new byte[DEFAULT_BUFFER_SIZE];
        int readBytes;
        
        try {
	        // ���ϴ� �뷡�� ���̵� �ְ�,
        	System.out.println(in.readLine()); // ������ �غ�Ǳ���� ��ٸ���
        	
	        String IP = "127.0.0.1"; 
			Socket socket = new Socket(IP,FILE_TRANSFER_PORT_NUM); // ���� ������ �õ��Ѵ�.
			InputStream is = socket.getInputStream();
			FileOutputStream fos = new FileOutputStream("song.wav");
			
			out.println(song_id); // �뷡 ���̵� �����ϰ�
	        
	        System.out.println(in.readLine()); // ������ �����ͺ��̽��� �� ã�� ������ ��ٸ���
	        
	        out.println("�뷡���� �غ�Ϸ�");
	        //�뷡 �ٿ�ε� �ް�
			Thread.sleep(300);
	        while ((readBytes = is.read(buffer)) != -1) {
	            fos.write(buffer, 0, readBytes);
	        } 
	       
	        // ��Ʈ�� �ݱ�
	        
	        //out.println("MUSIC OK!");
	        
	        fos.close();
	        is.close();
	        socket.close();
        }
        catch(Exception e) {
        	e.printStackTrace();	
        }
	}
	
	public static void request_lyrics(String song_id, BufferedReader in, PrintWriter out) {
		final int DEFAULT_BUFFER_SIZE = 10000;
        byte[] buffer = new byte[DEFAULT_BUFFER_SIZE];
        int readBytes;
        
        try {
	        // ���ϴ� �뷡�� ���̵� �ְ�,
	        
        	System.out.println(in.readLine()); // ������ �غ�Ǳ���� ��ٸ���
        	
	        String IP = "127.0.0.1"; 
			Socket socket = new Socket(IP,FILE_TRANSFER_PORT_NUM); // ���� ������ �õ��Ѵ�.
			InputStream is = socket.getInputStream();
			FileOutputStream fos = new FileOutputStream("lyrics.txt");
			
			out.println(song_id); // �뷡 ���̵� �����ϰ�
	        
	        System.out.println(in.readLine()); // ������ �����ͺ��̽��� �� ã�� ������ ��ٸ���
	        
	        out.println("������� �غ�Ϸ�");
	        //�뷡 �ٿ�ε� �ް�
			Thread.sleep(300);
	        while ((readBytes = is.read(buffer)) != -1) {
	            fos.write(buffer, 0, readBytes);
	        } 
	        fos.close();
	        is.close();
	        socket.close();
        }
        catch(Exception e) {
        	e.printStackTrace();
        }
	}
	
	public static void request_image(String song_id, BufferedReader in, PrintWriter out) {
		final int DEFAULT_BUFFER_SIZE = 10000;
        byte[] buffer = new byte[DEFAULT_BUFFER_SIZE];
        int readBytes;
        
        try {
	        // ���ϴ� �뷡�� ���̵� �ְ�,
	        
        	System.out.println(in.readLine()); // ������ �غ�Ǳ���� ��ٸ���
        	
	        String IP = "127.0.0.1"; 
			Socket socket = new Socket(IP,FILE_TRANSFER_PORT_NUM); // ���� ������ �õ��Ѵ�.
			InputStream is = socket.getInputStream();
			FileOutputStream fos = new FileOutputStream("album_image.png");
			
			out.println(song_id); // �뷡 ���̵� �����ϰ�
	        
	        System.out.println(in.readLine()); // ������ �����ͺ��̽��� �� ã�� ������ ��ٸ���
	        
	        out.println("�ٹ� �̹��� ���� �غ�Ϸ�");
	        //�뷡 �ٿ�ε� �ް�
			Thread.sleep(300);
	        while ((readBytes = is.read(buffer)) != -1) {
	            fos.write(buffer, 0, readBytes);
	        } 
	        fos.close();
	        is.close();
	        socket.close();
        }
        catch(Exception e) {
        	e.printStackTrace();
        }
	}
	
	public static String request_song_name(String song_id, BufferedReader in, PrintWriter out) {
		String result = null;
		out.println(song_id);
		try {
			return in.readLine();
		}
		catch(Exception e) {
			return null;
		}
	}
	
	public static void request_album_info( BufferedReader in, PrintWriter out) {
		try {
			int album_max = Integer.parseInt(in.readLine());
			
			for(int i = 1 ; i<=album_max; i++) {
				System.out.println(i);
				request_image_album(i,in,out);
			}
			
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static void request_image_album(int song_id, BufferedReader in, PrintWriter out) {
		final int DEFAULT_BUFFER_SIZE = 10000;
        byte[] buffer = new byte[DEFAULT_BUFFER_SIZE];
        int readBytes;
        
        try {
	        // ���ϴ� �뷡�� ���̵� �ְ�,
	        
        	System.out.println(in.readLine()); // ������ �غ�Ǳ���� ��ٸ���
        	
	        String IP = "127.0.0.1"; 
			Socket socket = new Socket(IP,FILE_TRANSFER_PORT_NUM); // ���� ������ �õ��Ѵ�.
			InputStream is = socket.getInputStream();
			FileOutputStream fos = new FileOutputStream("album_image"+song_id+".png");
			
	        System.out.println(in.readLine()); // ������ �����ͺ��̽��� �� ã�� ������ ��ٸ���
	        
	        out.println("�ٹ� �̹��� ���� �غ�Ϸ�");
	        //�뷡 �ٿ�ε� �ް�
			//Thread.sleep(200);
	        while ((readBytes = is.read(buffer)) != -1) {
	            fos.write(buffer, 0, readBytes);
	        } 
	        fos.close();
	        is.close();
	        socket.close();
        }
        catch(Exception e) {
        	e.printStackTrace();
        }
	}
}