package transactionmanager;

import java.text.DecimalFormat;

/**
 * College Checking class
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class CollegeChecking extends Account {
    private final Campus campus;

    /**
     * Creates predefined College Checking objects
     *
     * @param profile profile of holder of account
     * @param balance balance of account
     * @param campus  information of campus
     */
    public CollegeChecking(Profile profile, double balance, Campus campus) {
        this.holder = profile;
        this.balance = balance;
        this.campus = campus;
    }

    /**
     * Account Comaparator
     *
     * @param o the object to be compared.
     * @return 0 if both have sam holder
     * 1, -1 if not
     */
    @Override
    public int compareTo(Account o) {
        if (o instanceof CollegeChecking)
            return holder.compareTo(o.getHolder());
        else return 1;
    }

    /**
     * Returns a String value of object
     *
     * @return lname, fname, dob, type
     */
    @Override
    public String toString() {
        return holder.toString() + "(CC)";
    }

    /**
     * Returns a String value of object include detail
     *
     * @return lname, fname, dob, type, balance, loyal status
     */
    @Override
    public String toStringForPrint() {
        DecimalFormat decimalFormat = new DecimalFormat("###,###.00");
        return "CollegeChecking::" + holder.toString() + "::Balance $" + decimalFormat.format(balance) + "::" + campus;
    }

    /**
     * Returns a double monthly fee
     *
     * @return fee of this account
     */
    @Override
    public double monthlyFee() {
        return 0;
    }

    /**
     * Returns a double monthly interest
     *
     * @return interest fo this account
     */
    @Override
    public double monthlyInterest() {
        return (balance / 12.0) * (1.0 / 100.0);
    }

    /**
     * Returns a String value of object include detail
     *
     * @return lname, fname, dob, type, balance, loyal status, fee, monthly interest
     */
    @Override
    public String toStringForPrintFeeAndInterest() {
        DecimalFormat decimalFormat = new DecimalFormat("###,##0.00");
        return toStringForPrint() + "::fee $" + decimalFormat.format(monthlyFee()) + "::monthly interest $" + decimalFormat.format(monthlyInterest());
    }
}
