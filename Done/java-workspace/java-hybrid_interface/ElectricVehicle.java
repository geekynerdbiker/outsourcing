public class ElectricVehicle extends Car implements HybridInterface {

    public ElectricVehicle(String car_string) {
        super(car_string);
    }

    @Override
    public void startMotor(String mode) {
        switch (mode) {
            case "fuel" -> {
                System.out.println("Convert from Fuel to Electric car mode.");
                System.out.println("(Now Fuel Mode)");
            }
            case "hybrid" -> {
                System.out.println("Convert from Hybrid to Electric car mode.");
                System.out.println("(Now Fuel Mode)");
            }
            case "electric" -> {
                System.out.println("Keep electric car mode.");
                System.out.println("(Now Fuel Mode)");
            }
        }
    }

    @Override
    public void stopMotor() {

    }

    @Override
    public void electricToFrontMotor() {

    }

    @Override
    public void generateElectricPower() {
        System.out.println("Supply electricity to front and rear motors of electric car.");
        System.out.println("Regenerative braking system runs to charge battery.");
    }

    @Override
    public void stopMoving() {

    }

    @Override
    public void speedoMeter(int speed) {
        System.out.println("(Now Electric Mode) Current Speed: " + speed);
    }
}
