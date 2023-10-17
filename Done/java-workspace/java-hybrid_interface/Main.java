public class Main {
    public static void main(String[] args) {
        SingletonRecord st = new SingletonRecord(8);
        Mediator m = new Mediator();
        HybridCar hc;
        ElectricVehicle ev;
        Car c;

        String currentMode = "";
        int mainBattery = m.random.nextInt(100);
        int backupBattery = m.requestBackupBattery();
        int speed = m.random.nextInt(20) + 40;

        for (int i = 0; i < 8; i++) {
            if (mainBattery > 75) {
                System.out.println("* Full Battery Level *");
                ev = new ElectricVehicle("electric");

                if (i == 0) {
                    System.out.println("Start with the electric car mode.");
                    currentMode = "electric";
                } else ev.startMotor(currentMode);

                speed = m.random.nextInt(20) + 40;
                ev.generateElectricPower();
                ev.speedoMeter(speed);
                st.addData("Full", "Electric Mode", speed, mainBattery, backupBattery);
            } else if (mainBattery > 50) {
                System.out.println("* Medium Battery Level *");
                hc = new HybridCar("hybrid");

                if (i == 0) {
                    System.out.println("Start with the hybrid car mode.");
                    currentMode = "hybrid";
                } else hc.startMotor(currentMode);

                speed = m.random.nextInt(20) + 40;
                hc.generateElectricPower();
                hc.speedoMeter(speed);
                st.addData("Medium", "Hybrid Mode", speed, mainBattery, backupBattery);
            } else if (mainBattery > 25) {
                System.out.println("* Low Battery Level *");
                c = new Car("fuel");

                if (i == 0) {
                    System.out.println("Start with the fuel car mode.");
                    currentMode = "fuel";
                } else c.igniteEngine(currentMode);

                speed = m.random.nextInt(20) + 40;
                c.keepRunningEngine();
                c.measureSpeed(speed);
                st.addData("Low", "Fuel/Gas Mode", speed, mainBattery, backupBattery);
            } else {
                System.out.println("* Battery Almost Empty Level * Main Battery Level: " + mainBattery);
                System.out.println("Switching to Backup Battery -- BU Battery Level: " + backupBattery);
                c = new Car("fuel");

                if (i == 0) {
                    System.out.println("Start with the fuel car mode.");
                    currentMode = "fuel";
                } else c.igniteEngine(currentMode);

                speed = m.random.nextInt(20) + 40;
                c.keepRunningEngine();
                c.measureSpeed(speed);
                st.addData("Short", "Fuel/Gas Mode", speed, mainBattery, backupBattery);
            }

            System.out.println();
            mainBattery = m.random.nextInt(100);
            backupBattery = m.requestBackupBattery();
        }

        st.printRecord();
        st.printBattery();
    }
}
