public class Car {
    private final String string;

    public Car(String car_string) {
        this.string = car_string;
    }

    public void igniteEngine(String mode) {
        if (mode.equals("fuel")) {
            System.out.println("Keep fuel car mode.");
            System.out.println("(Now Fuel Mode)");
        } else if (mode.equals("hybrid")) {
            System.out.println("Convert from Hybrid to Fuel car mode.");
            System.out.println("(Now Fuel Mode)");
        }
        else if (mode.equals("electric")) {
            System.out.println("Convert from Electric to Fuel car mode.");
            System.out.println("(Now Fuel Mode)");
        }
    }

    public void stopEngine() {

    }

    public void measureSpeed(int speed) {
        System.out.println("(Now Fuel Mode) Current Speed: " + speed);
    }

    public void keepRunningEngine() {
        System.out.println("Fuel engine keeps running.");
        System.out.println("Electric Generator is charging battery.");
    }

    public String getString() {
        return string;
    }
}
