package transactionmanager;

import java.util.Calendar;

/**
 * Date class
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class Date implements Comparable<Date> {
    private int year;
    private int month;
    private int day;

    private static final int FIRST_DAY_OF_MONTH = 1;
    private static final int JAN = 1;
    private static final int FEB = 2;
    private static final int MAR = 3;
    private static final int APR = 4;
    private static final int MAY = 5;
    private static final int JUN = 6;
    private static final int JUL = 7;
    private static final int AUG = 8;
    private static final int SEP = 9;
    private static final int OCT = 10;
    private static final int NOV = 11;
    private static final int DEC = 12;

    private static final int QUAD = 4;
    private static final int CENT = 100;
    private static final int QUAT = 400;
    private static final int FEB_DAYS = 28;
    private static final int LEAP_YEAR = 29;

    /**
     * Creates a Date object
     *
     * @param year  the year in the date of format yyyy
     * @param month the month in the date of format mm
     * @param day   the day in the date of format dd
     */
    public Date(int year, int month, int day) {
        this.year = year;
        this.month = month;
        this.day = day;
    }

    /**
     * Checks whether the year of the event is a leap year or not
     *
     * @return true if leap year, false otherwise
     */
    private boolean isLeapYear() {
        if (this.year % QUAD == 0) {
            if (this.year % CENT == 0) {
                return this.year % QUAT == 0;
            } else {
                return true;
            }
        }
        return false;
    }

    /**
     * Checks if the date is a valid calendar date
     *
     * @return true if valid date, false if not
     */
    public boolean isValid() {
        // Checks if the month is valid
        if (this.month < JAN || this.month > DEC) {
            return false;
        }

        // Checks if the day is valid
        if (this.day < FIRST_DAY_OF_MONTH) {
            return false;
        } else if (this.month == JAN || this.month == MAR || this.month == MAY
                || this.month == JUL || this.month == AUG || this.month == OCT
                || this.month == DEC) {
            return this.day <= 31; // Change 31
        } else if (this.month == APR || this.month == JUN || this.month == SEP
                || this.month == NOV) {
            return this.day <= 30; // Change 30
        } else {
            if (isLeapYear()) {
                return this.day <= LEAP_YEAR;
            } else {
                return this.day <= FEB_DAYS;
            }
        }
    }

    /**
     * Check the age is under 16 from today's date
     *
     * @return true if the age is under 16 from today's date,
     * false if not
     */
    public boolean isUnder16() {
        Calendar c = Calendar.getInstance();
        int yy = c.get(Calendar.YEAR);
        int mm = c.get(Calendar.MONTH) + 1;
        int dd = c.get(Calendar.DATE);

        if (yy - this.year <= 16) {
            if (yy - this.year == 16) {
                if (mm > this.month) {
                    return true;
                } else if (mm == this.month)
                    return dd < this.day;
            }
        } return false;
    }

    /**
     * Check the age is over 24 from today's date
     *
     * @return true if the age is over 24 from today's date,
     * false if not
     */
    public boolean isOver24() {
        Calendar c = Calendar.getInstance();
        int yy = c.get(Calendar.YEAR);
        int mm = c.get(Calendar.MONTH) + 1;
        int dd = c.get(Calendar.DATE);

        if (yy - this.year >= 24) {
            if (yy - this.year == 24) {
                if (mm < this.month) {
                    return true;
                } else if (mm == this.month)
                    return dd > this.day;
            }
        } return false;
    }

    /**
     * Check the date is future date
     *
     * @return true if this date is future date,
     * false if not
     */
    public boolean isFutureDate() {
        Calendar c = Calendar.getInstance();
        int yy = c.get(Calendar.YEAR);
        int mm = c.get(Calendar.MONTH) + 1;
        int dd = c.get(Calendar.DATE);

        Date d = new Date(yy, mm, dd);
        return d.compareTo(this) <= 0;
    }

    /**
     * Compares this date
     *
     * @param date the object to be compared.
     * @return 1 if this date occurs after the specified date,
     * -1 if this date occurs before the specified date,
     * 0 if the dates are the same
     */
    @Override
    public int compareTo(Date date) {
        if (this.year > date.year) {
            return 1;
        } else if (this.year < date.year) {
            return -1;
        } else {
            if (this.month > date.month) {
                return 1;
            } else if (this.month < date.month) {
                return -1;
            } else {
                return Integer.compare(this.day, date.day);
            }
        }
    }

    /**
     * Returns a string representation
     *
     * @return string version of date in format mm/dd/yyyy
     */
    @Override
    public String toString() {
        return "" + this.month + '/' + this.day + '/' + this.year;
    }
}
