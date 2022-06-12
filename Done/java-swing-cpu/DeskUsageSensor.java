import java.util.Random;

public class DeskUsageSensor {
    private double usedDeskSpaceInGb;

    public DeskUsageSensor() {
        this.generateNewValue();
    }

    public double readValue() {
        this.generateNewValue();
        return this.usedDeskSpaceInGb;
    }

    private void generateNewValue() {
        this.usedDeskSpaceInGb = (double)(new Random()).nextInt(1000);
    }

    public String getReport() {
        if (this.usedDeskSpaceInGb > 900.0) {
            return "DANGER";
        } else {
            return this.usedDeskSpaceInGb > 700.0 ? "CRITICAL" : "OK";
        }
    }

    public String getAlertName() {
        return "Desk Usage Alert";
    }
}
