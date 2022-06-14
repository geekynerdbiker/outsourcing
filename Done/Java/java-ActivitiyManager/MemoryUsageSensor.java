import java.util.Random;

public class MemoryUsageSensor {
    private double usedMemoryInGb;

    public MemoryUsageSensor() {
        this.generateNewValue();
    }

    public double readValue() {
        this.generateNewValue();
        return this.usedMemoryInGb;
    }

    private void generateNewValue() {
        this.usedMemoryInGb = (double)(new Random()).nextInt(16);
    }

    public String getReport() {
        if (this.usedMemoryInGb > 13.0) {
            return "DANGER";
        } else {
            return this.usedMemoryInGb > 10.0 ? "CRITICAL" : "OK";
        }
    }

    public String getAlertName() {
        return "Memory Usage Alert";
    }
}
