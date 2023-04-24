import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void printMenu() {
        System.out.println("ST2-2023 Assignment 1");
        System.out.println("E - Exit");
        System.out.println("F - Read Flats (Task 1)");
        System.out.println("M - Read Meters(Task 1)");
        System.out.println("C - Compute BC Bill For one Flat (Task 2)");
        System.out.println("A - Compute BC Bill For All Flats (Task 2)");
        System.out.println("S - Sort the meter file into meter order (Task 3)");
        System.out.println("P - Prove meter file sort and find (Task 3)");
        System.out.println("O - Compute Full Bill For One Flat (Task 4)");
        System.out.println("5 - Compute Full Bill For All Flats (Task 5)");
        System.out.println("0 - Set Dev0 environment");
        System.out.println("1 - Set Dev1 environment");
        System.out.println("2 - Set Test environment");
        System.out.println("3 - Set prod environment");
        System.out.println("Select Option:");
    }

    public static void main(String[] args) throws IOException {
        List<Flat> flatList = new ArrayList<>();
        List<Meter> meterList = new ArrayList<>();

        String mode = "Dev0_";
        char op = '.';

        while (Character.toUpperCase(op) != 'E') {
            printMenu();

            BufferedReader brf;

            op = br.readLine().charAt(0);
            switch (Character.toUpperCase(op)) {
                case 'F':
                    try {
                        String path = "data/" + mode + "Flat.txt";
                        brf = new BufferedReader(new FileReader(path));
                        System.out.println("Reading flat file " + path);

                        String sLine = null;
                        int flatsRead = 0, metersRead = 0, checkSum = 0;
                        while ((sLine = brf.readLine()) != null) {
                            String[] data = sLine.split(",");
                            flatList.add(new Flat(data));
                            flatsRead++;
                            metersRead += data.length - 7;
                            checkSum += Integer.parseInt(data[3]);
                        }

                        System.out.println("Number Of Flats  Read in is:" + Integer.toString(flatsRead));
                        System.out.println("Number Of Meters Read in is:" + Integer.toString(metersRead));
                        System.out.println("Total sum (checksum) of all current flats reading is:" + Integer.toString(checkSum) + "\n");

                    } catch (FileNotFoundException e) {
                        e.getStackTrace();
                    }
                    continue;

                case 'M':
                    try {
                        String path = "data/" + mode + "Meter.txt";
                        brf = new BufferedReader(new FileReader(path));
                        System.out.println("Reading meter file " + path);

                        String sLine = null;
                        int metersRead = 0, checkSum = 0;
                        while ((sLine = brf.readLine()) != null) {
                            String[] data = sLine.split(",");
                            if (data.length < 9)
                                break;
                            meterList.add(new Meter(data));
                            metersRead++;
                            checkSum += Integer.parseInt(data[5]);
                        }

                        System.out.println("Number Of Meters Read in is:" + Integer.toString(metersRead));
                        System.out.println("Total sum (checksum) of all current flats reading is:" + Integer.toString(checkSum) + "\n");

                    } catch (FileNotFoundException e) {
                        e.getStackTrace();
                    }
                    continue;

                case 'C':
                    continue;

                case 'A':
                    continue;

                case 'S':
                    continue;

                case 'P':
                    continue;

                case 'O':
                    continue;

                case '5':
                    continue;

                case '0':
                    mode = "Dev0_";
                    continue;

                case '1':
                    mode = "Dev1_";
                    continue;

                case '2':
                    mode = "test_";
                    continue;

                case '3':
                    mode = "prod_";
                    continue;

                default:
                    continue;
            }

//            return;
        }

    }
}
