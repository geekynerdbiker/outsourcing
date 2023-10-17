public interface HybridInterface {
    void startMotor(String mode);
    void stopMotor();
    void electricToFrontMotor();
    void generateElectricPower();
    void stopMoving();
    void speedoMeter(int speed);
}
