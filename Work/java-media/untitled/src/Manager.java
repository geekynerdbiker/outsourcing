import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Manager {
    private final ArrayList<Media> mediaList;

    public Manager() {
        this.mediaList = new ArrayList<Media>();
    }

    public Manager(String directory) throws FileNotFoundException {
        this.mediaList = new ArrayList<Media>();

        File directoryPath = new File(directory);

        File[] fileList = directoryPath.listFiles();

        if (fileList == null)
            throw new FileNotFoundException("Could not load, no such directory");

        Media media = null;
        String line = null;
        Scanner scan = null;

        for (File file : fileList) {
            if (file.getName().contains("EBook") || file.getName().contains("MovieDVD")
                    || file.getName().contains("MusicCD")) {

                scan = new Scanner(file);
                line = scan.nextLine();
                if (file.getName().contains("EBook-"))
                    media = new EBook(line);

                if (file.getName().contains("MovieDVD-"))
                    media = new MovieDVD(line);

                if (file.getName().contains("MusicCD-"))
                    media = new MusicCD(line);

                mediaList.add(media);
            }
        }
    }

    public void createMediaFiles(String directory) throws IOException {
        PrintWriter out = null;

        for (Media media : mediaList) {
            String filename = directory + "/" + media.getClass().getSimpleName() + "-" + media.getID()
                    + ".txt";
            out = new PrintWriter(new FileWriter(filename));
            out.println(media.toString());
            out.flush();
            out.close();
        }
    }


    public void addMedia(Media media) {
        mediaList.add(media);
    }

    public ArrayList<Media> findMedia(String title) {
        ArrayList<Media> match = new ArrayList<Media>();

        for (Media tmp : mediaList) {
            if (tmp.getTitle().toLowerCase().equals(title.toLowerCase())) {
                match.add(tmp);
            }
        }
        return match;
    }

    public double rentMedia(int id, String directory) throws IOException {
        PrintWriter out = null;

        for (int i = 0; i < mediaList.size(); i++) {
            if (mediaList.get(i).getID() == id) {
                mediaList.get(i).setStatus(true);
                String filename = directory + "/" + mediaList.get(i).getClass().getSimpleName() + "-" + mediaList.get(i).getID()
                        + ".txt";
                out = new PrintWriter(new FileWriter(filename));
                out.println(mediaList.get(i).toString());
                out.flush();
                out.close();
                return mediaList.get(i).calculateRentalFee();
            }
        }

        return Double.NaN;
    }
}
