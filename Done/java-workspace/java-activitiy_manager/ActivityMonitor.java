import java.awt.*;

public class ActivityMonitor {
    public static abstract class Value {
        public double value;
        public Color color;

        public Value(double value, Color color) {
            this.value = value;
            this.color = color;
        }

        public String alertText() {
            if (color == Color.RED) {
                return "CRITICAL";
            } else if (color == Color.YELLOW) {
                return "DANGER";
            } else if (color == Color.GREEN) {
                return "OK";
            } else {
                assert false;
                return "";
            }
        }

        public abstract String alertName();
        public abstract double ratio();
    }

    public static class CPUValue extends Value {
        public CPUValue(double value, Color color) {
            super(value, color);
        }

        @Override
        public String alertName() {
            return "CPU Utilization Alert";
        }

        @Override
        public double ratio() {
            return Math.min(this.value / 90, 1);
        }
    }

    public static class DeskValue extends Value {
        public DeskValue(double value, Color color) {
            super(value, color);
        }

        @Override
        public String alertName() {
            return "Desk Usage Alert";
        }

        @Override
        public double ratio() {
            return Math.min(this.value / 900, 1);
        }
    }

    public static class MemoryValue extends Value {
        public MemoryValue(double value, Color color) {
            super(value, color);
        }

        @Override
        public String alertName() {
            return "Memory Usage Alert";
        }

        @Override
        public double ratio() {
            return Math.min(this.value / 13, 1);
        }
    }

    private final CpuUtilizationSensor cpuSensor;
    private final DeskUsageSensor deskSensor;
    private final MemoryUsageSensor memorySensor;

    public ActivityMonitor(
            CpuUtilizationSensor cpuSensor,
            DeskUsageSensor deskSensor,
            MemoryUsageSensor memorySensor
    ) {
        this.cpuSensor = cpuSensor;
        this.deskSensor = deskSensor;
        this.memorySensor = memorySensor;
    }

    public CPUValue cpuValue() {
        return new CPUValue(cpuSensor.readValue(), strToColor(cpuSensor.getReport()));
    }

    public DeskValue deskValue() {
        return new DeskValue(deskSensor.readValue(), strToColor(deskSensor.getReport()));
    }

    public MemoryValue memoryValue() {
        return new MemoryValue(memorySensor.readValue(), strToColor(memorySensor.getReport()));
    }

    private Color strToColor(String s) {
        return switch (s) {
            case "CRITICAL" -> Color.RED;
            case "DANGER" -> Color.YELLOW;
            case "OK" -> Color.GREEN;
            default -> throw new IllegalArgumentException(s);
        };
    }
}