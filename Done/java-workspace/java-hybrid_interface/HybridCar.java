public class HybridCar extends Car implements HybridInterface {

    public HybridCar(String car_string) {
        super(car_string);
    }

    @Override
    public void startMotor(String mode) {
        switch (mode) {
            case "fuel" -> {
                System.out.println("Convert from Fuel to Hybrid car mode.");
                System.out.println("(Now Hybrid Mode)");
            }
            case "hybrid" -> {
                System.out.println("Keep Hybrid car mode.");
                System.out.println("(Now Hybrid Mode)");
            }
            case "electric" -> {
                System.out.println("Convert from Electric to Hybrid car mode.");
                System.out.println("(Now Hybrid Mode)");
            }
        }

        System.out.print("Supply electricity to front motor of hybrid car.");
    }

    @Override
    public void stopMotor() {
    }

    @Override
    public void electricToFrontMotor() {

    }

    @Override
    public void generateElectricPower() {
        System.out.println("Fuel engine keeps running.");
        System.out.println("Regenerative braking system runs to charge battery.");
    }

    @Override
    public void stopMoving() {

    }

    @Override
    public void speedoMeter(int speed) {
        System.out.println("(Now Hybrid Mode) Current Speed: " + speed);
    }
}
