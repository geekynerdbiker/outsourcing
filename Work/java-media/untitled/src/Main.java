import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.*;
import java.text.SimpleDateFormat;

public class Main {
    Manager manager;
    String directory;

    public Main() {
        manager = null;
    }

    private void displayMenu() {
        System.out.println("\n   Welcome to Media Rental System");
        System.out.println("1: Load Media Objects...");
        System.out.println("2: Find Media Objects...");
        System.out.println("3: Rent Media Objects...");
        System.out.println("9: Quit\n");
    }

    private void processChoice(int c) {
        switch (c) {
            case (1) -> loadMedia();
            case (2) -> findMedia();
            case (3) -> rentMedia();
            case (9) -> System.out.print("Thank you for using the program. Goodbye!");
        }
    }

    private void loadMedia() {
        Scanner scan = new Scanner(System.in);

        System.out.print("Enter path (directory) where you want to load from: ");
        this.directory = scan.nextLine();

        try {
            manager = new Manager(directory);
        } catch (FileNotFoundException e) {
            System.out.println("File could be opened: " + e.getMessage());
        }
    }

    private void findMedia() {
        Scanner scan = new Scanner(System.in);

        System.out.print("Enter the title: ");
        String title = scan.nextLine();

        ArrayList<Media> matches = manager.findMedia(title);
        if (matches.size() > 0) {
            for (Media match : matches) {
                match.display();
                System.out.println("");
            }
        } else {
            System.out.println("There is no media with this title: " + title);
        }
    }

    private void rentMedia() {
        Scanner scan = new Scanner(System.in);
        double price;
        System.out.print("Enter the id: ");
        if (scan.hasNextInt()) {
            int id = scan.nextInt();
            try {
                price = manager.rentMedia(id, directory);
                if (Double.isNaN(price)) {
                    System.out.println("The media object id=" + id + " is not found.");
                } else {
                    System.out.printf("Media was successfully rented. Rental fee = $%.2f\n", price);
                }
            } catch (IOException e) {
                System.out.println("The media object id=" + id + " is not found.");
            }
        } else {
            System.out.println("Please enter an integer for the ID value.");
        }
    }

    public static void main(String[] args) {
        Date dNow = new Date();
        SimpleDateFormat ft = new SimpleDateFormat("MM/dd/yyyy");

        Scanner scanIn = new Scanner(System.in);
        Main handler = new Main();
        int answer;

        do {
            handler.displayMenu();
            System.out.print("Enter your selection : ");
            if (scanIn.hasNextInt()) {
                answer = scanIn.nextInt();
                System.out.println("");
                handler.processChoice(answer);
            } else {
                answer = 0;
                scanIn.nextLine();
                System.out.println("\nThis is not a valid choice. Please enter a valid menu option.");
            }
        } while (answer != 9);
        scanIn.close();
    }
}