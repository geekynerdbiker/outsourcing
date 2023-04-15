import java.util.ArrayList;
import java.util.Random;

public class Mediator {
    Random random;
    private int backupBatteryLevel;
    private boolean useBackupBattery;

    public Mediator() {
        this.random = new Random();
        this.backupBatteryLevel = random.nextInt(50) + 50;
        this.useBackupBattery = false;
    }

    public int requestBackupBattery() {
        // Backup Battery Level Checking
        return this.backupBatteryLevel;
    }

    public void setUsingBackUpBattery() {
        // Setter: Use of Backup Battery: TRUE
        this.useBackupBattery = true;
    }

    public void OffUsingBackUpBattery() {
        // Setter: Use of Backup Battery: FALSE
        this.useBackupBattery = false;
    }

    public Boolean UseOfBackUpBattery() {
        // Getter: Use of Backup Battery
        return this.useBackupBattery;
    }
}