import java.sql.*;
import java.util.ArrayList;

public class Database {
    private static Connection con = null;

    static public void test() {
        try {
            con = DriverManager.getConnection("jdbc:mysql://localhost?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC&useSSL=false&allowPublicKeyRetrieval=true", "root", "rootroot");
            java.sql.Statement st = null;
            ResultSet rs = null;
            st = con.createStatement();

            rs = st.executeQuery("SHOW DATABASES");
            if (st.execute("SHOW DATABASES")) {
                rs = st.getResultSet();
            }
            while (rs.next()) {
                String str = rs.getNString(1);
                System.out.println(str);
            }
            con.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    static public void deleteDatabase() {
        try {
            con = DriverManager.getConnection("jdbc:mysql://localhost?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC&useSSL=false&allowPublicKeyRetrieval=true", "root", "rootroot");
            java.sql.Statement st = null;
            st = con.createStatement();

            st.executeUpdate("DROP DATABASE music_db");
            con.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    static public void createDatabase() {
        try {
            con = DriverManager.getConnection("jdbc:mysql://localhost?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC&useSSL=false&allowPublicKeyRetrieval=true", "root", "rootroot");
            java.sql.Statement st = null;
            st = con.createStatement();

            st.executeUpdate("CREATE DATABASE music_db");
            con.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    static public void createTable() {
        try {
            con = DriverManager.getConnection("jdbc:mysql://localhost/music_db?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC&useSSL=false&allowPublicKeyRetrieval=true", "root", "rootroot");
            java.sql.Statement st = null;
            st = con.createStatement();

            st.executeUpdate("CREATE TABLE IF NOT EXISTS music_data(ID int, song_name varchar(30), song_dir varchar(100), lyrics_dir varchar(100), image_dir varchar(100), singer varchar(30), PRIMARY KEY(ID))");
            con.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    synchronized static public boolean register_music(int id, String song_name, String song_dir, String lyrics_dir, String image_dir, String Singer) {
        try {
            con = DriverManager.getConnection("jdbc:mysql://localhost/music_db?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC&useSSL=false&allowPublicKeyRetrieval=true", "root", "rootroot");
            java.sql.Statement st = null;
            ResultSet rs = null;
            st = con.createStatement();

            rs = st.executeQuery("select ID from music_data where ID ='" + id + "'");
            if (rs.next()) {
                con.close();
                return false;
            }

            else {
                st.execute("insert into music_data(ID, song_name, song_dir, lyrics_dir, image_dir, singer) Values(" + id + ",'" + song_name + "','" + song_dir + "','" + lyrics_dir  + "','" + image_dir + "','" + Singer + "');");
                System.out.println("song_name : " + song_name + ". ��� �Ϸ�");
                con.close();
                return true;
            }

        } catch (Exception e) {
            e.printStackTrace();
            return true;
        }
    }

    static public ArrayList getSong_info(int id) {
        try {
            con = DriverManager.getConnection("jdbc:mysql://localhost/music_db?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC&useSSL=false&allowPublicKeyRetrieval=true", "root", "rootroot");
            java.sql.Statement st = null;
            ResultSet rs = null;
            st = con.createStatement();
            rs = st.executeQuery("select song_name, song_dir, lyrics_dir, image_dir, singer from music_data where ID ='" + id + "'");

            ArrayList result = new ArrayList();

            if (rs.next()) {
                result.add(rs.getObject(1));
                result.add(rs.getObject(2));
                result.add(rs.getObject(3));
                result.add(rs.getObject(4));
                result.add(rs.getObject(5));
            } else {
                System.out.println("���̵� �� �߰�. null ����");
            }
            con.close();
            return result;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    static public String getSong_name(int id) {
        ArrayList al = getSong_info(id);
        return (String) al.get(0);
    }

    static public String getSong_dir(int id) {
        ArrayList al = getSong_info(id);
        return (String) al.get(1);
    }

    static public String getLyrics_dir(int id) {
        ArrayList al = getSong_info(id);
        return (String) al.get(2);
    }


    static public String getImage_dir(int id) {
        ArrayList al = getSong_info(id);
        return (String) al.get(3);
    }

    static public String getSinger(int id) {
        ArrayList al = getSong_info(id);
        return (String) al.get(4);
    }

    static public int getMusic_len() {
        int result = -1;
        try {
            con = DriverManager.getConnection("jdbc:mysql://localhost/music_db?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC&useSSL=false&allowPublicKeyRetrieval=true", "root", "rootroot");
            java.sql.Statement st = null;
            ResultSet rs = null;
            st = con.createStatement();
            rs = st.executeQuery("select * from music_data");
            if (st.execute("select * from music_data")) {
                rs = st.getResultSet();
            }
            while (rs.next()) {
                result = rs.getInt(1);
            }

        }
        catch(Exception e) {
            e.printStackTrace();
        }

        return result;
    }

    static public void print_all_music() {
        try {
            con = DriverManager.getConnection("jdbc:mysql://localhost/music_db?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC&useSSL=false&allowPublicKeyRetrieval=true", "root", "rootroot");
            java.sql.Statement st = null;
            ResultSet rs = null;
            st = con.createStatement();
            rs = st.executeQuery("select * from music_data");
            if (st.execute("select * from music_data")) {
                rs = st.getResultSet();
            }

            while (rs.next()) {
                int id = rs.getInt(1);
                String song_name = rs.getNString(2);
                String song_dir = rs.getNString(3);
                String lyrics_dir = rs.getNString(4);
                String image_dir = rs.getNString(5);
                String singer = rs.getNString(5);
                System.out.print(id);
                System.out.println(" : " + singer + " - " + song_name);

            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        deleteDatabase();
        createDatabase();
        createTable();

        register_music(1, "Beyond Love", "music/soundfile/Beyond Love.wav", "music/lyrics/Beyond Love.txt" ,  "music/image/Beyond Love.jpg", "BIG Naughty");
        register_music(2, "LOVE DIVE", "music/soundfile/LOVE DIVE.wav", "music/lyrics/LOVE DIVE.txt" ,  "music/image/LOVE DIVE.jpg", "IVE");
        register_music(3, "Love, Maybe", "music/soundfile/Love, Maybe.wav", "music/lyrics/Love, Maybe.txt" ,  "music/image/Love, Maybe.jpg", "MeloMance");
        register_music(4, "That That", "music/soundfile/That That.wav", "music/lyrics/That That.txt" ,  "music/image/That That.jpg", "PSY");
        register_music(5, "TOMBOY", "music/soundfile/TOMBOY.wav", "music/lyrics/TOMBOY.txt" ,  "music/image/TOMBOY.jpg", "I-DLE");

        print_all_music();
    }


}
