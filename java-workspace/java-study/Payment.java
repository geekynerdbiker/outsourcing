import java.util.Calendar;

public class Payment {
    static int total_Time_Income = 0;
    static int total_Food_Income = 0;
    final int FEE_PER_MINUTE = 100;
    final int FEE_PER_HOUR = 5000;

    int calculateFee(long startTime, long endTime) {
        return (int) ((endTime - startTime) / 3600 * FEE_PER_HOUR + ((endTime - startTime) / 60 + 1) * FEE_PER_MINUTE );
    }

    long setCheckIn() {
        Calendar now = Calendar.getInstance();

        int h = now.get(Calendar.HOUR_OF_DAY);
        int m = now.get(Calendar.MINUTE);
        int s = now.get(Calendar.SECOND);
        long startTime = h * 3600 + m * 60 + s;

        return startTime;
    }

    long setCheckOut() {
        Calendar now = Calendar.getInstance();

        int h = now.get(Calendar.HOUR_OF_DAY);
        int m = now.get(Calendar.MINUTE);
        int s = now.get(Calendar.SECOND);
        long endTime = h * 3600 + m * 60 + s;

        return endTime;
    }
}