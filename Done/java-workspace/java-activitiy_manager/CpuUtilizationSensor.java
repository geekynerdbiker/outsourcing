import java.util.Random;

public class CpuUtilizationSensor {
    private double utilizationValue;

    public CpuUtilizationSensor() {
        this.generateNewValue();
    }

    public double readValue() {
        this.generateNewValue();
        return this.utilizationValue;
    }
    private void generateNewValue() {
        this.utilizationValue = (double)(new Random()).nextInt(100);
    }

    public String getReport() {
        if (this.utilizationValue > 90.0) {
            return "DANGER";
        } else {
            return this.utilizationValue > 75.0 ? "CRITICAL" : "OK";
        }
    }

    public String getAlertName() {
        return "CPU Utilization Alert";
    }
}
