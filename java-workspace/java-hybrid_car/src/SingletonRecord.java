public class SingletonRecord {
    private final int calculation;
    private final String[] battery;
    private final String[] mode;
    private final int[] speed;
    private final int[] mb;
    private final int[] bu;
    private int currentIndex;

    public SingletonRecord(int c) {
        this.calculation = c;
        this.battery = new String[c];
        this.mode = new String[c];
        this.speed = new int[c];
        this.mb = new int[c];
        this.bu = new int[c];
        this.currentIndex = 0;
    }

    public void printRecord() {
        System.out.println("=== Black Box Singleton Output ===");
        System.out.println("Number of Mode Calculation: " + calculation);
        System.out.println("Hybrid mode with both electric motor and fuel engine");

        for (int i = 0; i < currentIndex - 1; i++) {
            System.out.print(i + ": Battery: ");
            System.out.print(battery[i] + " -- ");
            System.out.print(mode[i] + " – Speed: ");
            System.out.print(speed[i]);
            System.out.println();
        }
    }

    public void printBattery() {
        System.out.println("\n====================");
        System.out.println("Main Bat. Level Tracked by Mediator Singleton");
        for (int i = 0; i < currentIndex - 1; i++) {
            System.out.print(i + ": " + mb[i] + "\t");

            if (mode[i].equals("Fuel/Gas Mode")) {
                if (battery[i].equals("Short"))
                    System.out.println("Backup Battery Being Used --> BU Battery Level: " + bu[i]);
                else
                    System.out.println("Backup Battery Not Used in Fuel Mode");
            } else if (mode[i].equals("Hybrid Mode")) {
                System.out.println("Backup Battery Not Used in Hybrid Mode");
            } else if (mode[i].equals("Electric Mode")) {
                System.out.println("Backup Battery Not Used in Electric Mode");
            }
        }
        System.out.println("====================");
    }

    public void addData(String b, String m, int s, int mb, int bu) {
        this.battery[currentIndex] = b;
        this.mode[currentIndex] = m;
        this.speed[currentIndex] = s;
        this.mb[currentIndex] = mb;
        this.bu[currentIndex] = bu;
        currentIndex++;
    }
}
