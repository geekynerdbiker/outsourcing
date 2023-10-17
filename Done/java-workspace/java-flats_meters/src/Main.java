import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

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

    public static void main(String[] args) throws IOException, ParseException {
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
                            if (data.length < 8)
                                break;
                            flatList.add(new Flat(data));
                            flatsRead++;
                            metersRead += data.length - 7;
                            checkSum += Integer.parseInt(data[3]);
                        }

                        int sizeCounter = 0, size = checkSum;
                        while (size > 10) {
                            sizeCounter++;
                            size /= 10;
                        }

                        String s = Integer.toString(checkSum);
                        StringBuilder sb = new StringBuilder();

                        sb.append(s.charAt(0));
                        sb.append('.');
                        sb.append(s.substring(1));
                        sb.append('E');
                        sb.append(sizeCounter);

                        System.out.println("Number Of Flats  Read in is:" + Integer.toString(flatsRead));
                        System.out.println("Number Of Meters Read in is:" + Integer.toString(metersRead));
                        System.out.println("Total sum (checksum) of all current flats reading is:" + sb.toString());
                        System.out.println("Total sum (checksum) of all current flats reading is:\t\t\t" + Integer.toString(checkSum) + "\n");

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

                        int sizeCounter = 0, size = checkSum;
                        while (size > 10) {
                            sizeCounter++;
                            size /= 10;
                        }

                        String s = Integer.toString(checkSum);
                        StringBuilder sb = new StringBuilder();

                        sb.append(s.charAt(0));
                        sb.append('.');
                        sb.append(s.substring(1));
                        sb.append('E');
                        sb.append(sizeCounter);

                        System.out.println("Number Of Meters Read in is:" + Integer.toString(metersRead));
                        System.out.println("Total sum (checksum) of all current flats reading is:" + sb.toString());
                        System.out.println("Total sum (checksum) of all current flats reading is:\t\t\t" + Integer.toString(checkSum) + "\n");

                    } catch (FileNotFoundException e) {
                        e.getStackTrace();
                    }
                    continue;

                case 'C':
                    int streetNumber;
                    String streetName;

                    System.out.println("Compute bill for one Block of flats");
                    System.out.print("enter street Number:");
                    streetNumber = Integer.parseInt(br.readLine());
                    System.out.print("enter street Name:");
                    streetName = br.readLine();

                    System.out.println("Showing Bill for \t" + Integer.toString(streetNumber) + " " + streetName);
                    System.out.println("-----------------------");
                    for (Flat f : flatList) {
                        if (f.street.equals(streetName) && f.buildingNumber == streetNumber) {
                            System.out.printf("Current  meter reading\t%-10d  %s\n", f.currentReading, f.currentReadingDate);
                            System.out.printf("Previous meter reading\t%-10d  %s\n", f.previousReading, f.previousReadingDate);

                            int usage = f.currentReading - f.previousReading;
                            System.out.printf("Usage \t\t\t\t\t%-10d\n", usage);
                            System.out.printf("Rate \t\t\t\t\t\t\t\t%.3f/kwh\n", 0.205);
                            System.out.printf("BillUsage \t\t\t\t%-10c \t%-10.2f\n", '$', usage * 0.205);
                            break;
                        }
                    }
                    continue;

                case 'A':
                    System.out.println("Compute bill for all Block of flats");

                    System.out.println("\t\tTotal for All Flats");
                    System.out.println("-----------------------");

                    double total = 0;
                    int processed = 0;
                    for (Flat f : flatList) {
                        total += f.currentReading - f.previousReading * 0.205;
                        processed++;
                    }
                    System.out.printf("Total           : %30.3f\n", total);
                    System.out.printf("Record Processed: %30d\n", processed);

                    continue;

                case 'S':
                    meterList.sort(new Comparator<Meter>() {
                        @Override
                        public int compare(Meter o1, Meter o2) {
                            if (o1.tenetMeterNumber.compareTo(o2.tenetMeterNumber) > 0)
                                return 1;
                            else if (o1.tenetMeterNumber.compareTo(o2.tenetMeterNumber) < 0)
                                return -1;
                            return 0;
                        }
                    });

                    int index = 0;
                    for (Meter m : meterList) {
                        Calendar c = Calendar.getInstance();
                        c.setTime(new SimpleDateFormat("dd/MM/yyyy").parse(m.currentMeterReadingDate));
                        String day = c.getDisplayName(Calendar.DAY_OF_WEEK, Calendar.SHORT, Locale.US);
                        String month = c.getDisplayName(Calendar.DAY_OF_MONTH, Calendar.SHORT, Locale.US);
                        if (index == 0 || index == 9)
                            System.out.printf("Check\t[ %d] %s %s %s %s %s %s %s\n", index, m.firstName, m.secondName, m.tenetMeterNumber, day, month, m.currentMeterReadingDate.substring(0, 2), "00:00:00 AEST 2022");
                        else if (index == meterList.size() - 1)
                            System.out.printf("last\t[  ] %s %s %s %s %s %s %s\n", m.firstName, m.secondName, m.tenetMeterNumber, day, month, m.currentMeterReadingDate.substring(0, 2), "00:00:00 AEST 2022");
                        index++;
                    }
                    continue;

                case 'P':
                    meterList.sort(new Comparator<Meter>() {
                        @Override
                        public int compare(Meter o1, Meter o2) {
                            if (o1.tenetMeterNumber.compareTo(o2.tenetMeterNumber) > 0)
                                return 1;
                            else if (o1.tenetMeterNumber.compareTo(o2.tenetMeterNumber) < 0)
                                return -1;
                            return 0;
                        }
                    });

                    index = 0;
                    for (Meter m : meterList) {
                        Calendar c = Calendar.getInstance();
                        c.setTime(new SimpleDateFormat("dd/MM/yyyy").parse(m.currentMeterReadingDate));
                        String day = c.getDisplayName(Calendar.DAY_OF_WEEK, Calendar.SHORT, Locale.US);
                        String month = c.getDisplayName(Calendar.DAY_OF_MONTH, Calendar.SHORT, Locale.US);
                        if (index == 0 || index == 9)
                            System.out.printf("Check\t[ %d] %s %s %s %s %s %s %s\n", index, m.firstName, m.secondName, m.tenetMeterNumber, day, month, m.currentMeterReadingDate.substring(0, 2), "00:00:00 AEST 2022");
                        else if (index == meterList.size() - 1)
                            System.out.printf("last\t[  ] %s %s %s %s %s %s %s\n", m.firstName, m.secondName, m.tenetMeterNumber, day, month, m.currentMeterReadingDate.substring(0, 2), "00:00:00 AEST 2022");
                        index++;
                    }

                    long start = System.currentTimeMillis();
                    for (int i = 0; i < 10000; i++) {
                        for (Meter m : meterList)
                            if (m.tenetMeterNumber.equals("m163978"))
                                break;

                        for (Meter m : meterList)
                            if (m.tenetMeterNumber.equals("m163966"))
                                break;

                        for (Meter m : meterList)
                            if (m.tenetMeterNumber.equals("m163973"))
                                break;
                    }
                    long end = System.currentTimeMillis();
                    long diff = end - start;
                    System.out.println("\n\n\nFind Sequential: " + diff + "milliseconds.");

                    start = System.currentTimeMillis();
                    for (int i = 0; i < 10000; i++) {
                        int head = 0, rear = meterList.size() - 1;
                        while (head < rear) {
                            int current = (head + rear) / 2;
                            if (meterList.get(current).tenetMeterNumber.compareTo("m163978") == 0)
                                break;
                            else if (meterList.get(current).tenetMeterNumber.compareTo("m163978") > 0)
                                rear = current - 1;
                            else if (meterList.get(current).tenetMeterNumber.compareTo("m163978") < 0)
                                head = current + 1;
                        }

                        head = 0;
                        rear = meterList.size() - 1;
                        while (head < rear) {
                            int current = (head + rear) / 2;
                            if (meterList.get(current).tenetMeterNumber.compareTo("m163966") == 0)
                                break;
                            else if (meterList.get(current).tenetMeterNumber.compareTo("m163966") > 0)
                                rear = current - 1;
                            else if (meterList.get(current).tenetMeterNumber.compareTo("m163966") < 0)
                                head = current + 1;
                        }

                        head = 0;
                        rear = meterList.size() - 1;
                        while (head < rear) {
                            int current = (head + rear) / 2;
                            if (meterList.get(current).tenetMeterNumber.compareTo("m163973") == 0)
                                break;
                            else if (meterList.get(current).tenetMeterNumber.compareTo("m163973") > 0)
                                rear = current - 1;
                            else if (meterList.get(current).tenetMeterNumber.compareTo("m163973") < 0)
                                head = current + 1;
                        }
                    }
                    end = System.currentTimeMillis();
                    diff = end - start;
                    System.out.println("Find Binary: " + diff + "milliseconds.\n");

                    continue;

                case 'O':
                    System.out.println("Compute Adjusted bill for one Block of flats");
                    System.out.print("enter street Number:");
                    streetNumber = Integer.parseInt(br.readLine());
                    System.out.print("enter street Name:");
                    streetName = br.readLine();

                    System.out.println("Showing Bill for \t" + Integer.toString(streetNumber) + " " + streetName);
                    System.out.println("-----------------------");
                    for (Flat f : flatList) {
                        if (f.street.equals(streetName) && f.buildingNumber == streetNumber) {
                            System.out.printf("Current  meter reading\t%-10d  %s\n", f.currentReading, f.currentReadingDate);
                            System.out.printf("Previous meter reading\t%-10d  %s\n", f.previousReading, f.previousReadingDate);

                            int usage = f.currentReading - f.previousReading;
                            System.out.printf("Usage \t\t\t\t\t%-10d\n", usage);
                            System.out.printf("Rate \t\t\t\t\t\t\t\t%.3f/kwh\n", 0.205);
                            System.out.printf("BillUsage \t\t\t\t%-10c \t%-10.2f\n", '$', usage * 0.205);

                            System.out.println("\nTenant\t\t\t\t\t\tmeter\tcurr\tprev\tusage\tpcnt%\t$base\t$adj\t$total");
                            System.out.println("-----------------------------------------------------------------------------------------------");

                            double totalUsage = 0, totalAdj = 0;
                            for (String s : f.tenetMeters)
                                for (Meter m : meterList) {
                                    if (s.equals(m.tenetMeterNumber)) {
                                        totalUsage += m.currentMeterReading - m.previousMeterReading;
                                    }
                                }

                            totalAdj = usage - totalUsage;
                            for (String s : f.tenetMeters)
                                for (Meter m : meterList) {
                                    if (s.equals(m.tenetMeterNumber)) {
                                        int usagePartial = m.currentMeterReading - m.previousMeterReading;
                                        double pcnt = usagePartial / (double) totalUsage * 100;
                                        double adj = 0;
                                        if (totalAdj > 0)
                                            adj = totalAdj * pcnt / 100 * 0.205;
                                        String name = m.honorific + " " + m.firstName + " " + m.secondName;
                                        System.out.printf("%25s\t%s\t%d\t%d\t%d\t%.2f%%\t%.2f$\t%.2f$\t%.2f$\n", name, m.tenetMeterNumber, m.currentMeterReading, m.previousMeterReading, usagePartial, pcnt, usagePartial * 0.205, adj, usagePartial * 0.205 + adj);
                                    }
                                }

                            System.out.printf("\nTotal Tenant bills (metered)\t%10.2f\n", usage * 0.205);
                            System.out.printf("Total Tenant bills Diff\t\t\t%10.2f\n", totalAdj * 0.205);
                            System.out.printf("Total Tenant bills Adjusted\t\t%10.2f\n", totalUsage * 0.205);
                            break;
                        }
                    }
                    continue;
                case '5':
                    System.out.println("List Adjusted bill for all Block of flats");

                    System.out.println("\nFlat\tAddress\t\t\t\t\t\t\t\tBC Bill\t\tDifference\tDiffAdj\tTenant Bill");
                    System.out.println("---------------------------------------------------------------------------------------");

                    double totalFlatUsage = 0, totalFlatAdj = 0, totalFlatDiff = 0;
                    for (Flat f : flatList) {
                        int usage = f.currentReading - f.previousReading;
                        totalFlatUsage += usage;

                        double totalUsage = 0, totalAdj = 0, totalDiff = 0;
                        for (String s : f.tenetMeters)
                            for (Meter m : meterList) {
                                if (s.equals(m.tenetMeterNumber)) {
                                    totalUsage += m.currentMeterReading - m.previousMeterReading;
                                }
                            }

                        totalAdj = usage - totalUsage;
                        totalFlatAdj += totalAdj;

                        if (totalAdj < 0)
                            totalDiff = 0;
                        else
                            totalDiff = totalAdj;
                        totalFlatDiff += totalDiff;

                        System.out.printf("%5d\t%30s\t%10.2f$\t%10.2f$\t%10.2f$\t%10.2f$\n", f.buildingNumber, f.street, usage * 0.205, totalDiff * 0.205, totalAdj * 0.205, totalUsage * 0.205);
                    }
                    System.out.println("---------------------------------------------------------------------------------------");
                    System.out.printf("%50.2f$\t%10.2f$\t%10.2f$\t%10.2f$\n", totalFlatUsage * 0.205, totalFlatDiff * 0.205, totalFlatAdj * 0.205, (totalFlatUsage + (totalFlatDiff - totalFlatAdj)) * 0.205);
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
