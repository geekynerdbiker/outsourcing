package transactionmanager;

import java.text.DecimalFormat;

/**
 * Savings class
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class Savings extends Account {
    private boolean isLoyal;

    /**
     * Creates predefined Savings objects
     *
     * @param profile profile of holder of account
     * @param balance balance of account
     * @param isLoyal true if is loyal account,
     *                false if not
     */
    public Savings(Profile profile, double balance, boolean isLoyal) {
        this.holder = profile;
        this.balance = balance;
        this.isLoyal = isLoyal;
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
        if (o instanceof Savings) return holder.compareTo(o.getHolder());
        else return 1;
    }

    /**
     * Returns a String value of object
     *
     * @return lname, fname, dob, type
     */
    @Override
    public String toString() {
        return holder.toString() + "(S)";
    }

    /**
     * Returns a String value of object include detail
     *
     * @return lname, fname, dob, type, balance, loyal status
     */
    @Override
    public String toStringForPrint() {
        DecimalFormat decimalFormat = new DecimalFormat("###,###.00");
        if (isLoyal)
            return "Savings::" + holder.toString() + "::Balance $" + decimalFormat.format(balance) + "::is loyal";
        else
            return "Savings::" + holder.toString() + "::Balance $" + decimalFormat.format(balance);
    }

    /**
     * Returns a double monthly fee
     *
     * @return fee of this account
     */
    @Override
    public double monthlyFee() {
        double fee = 25;

        if (balance >= 500)
            fee = 0;
        return fee;
    }

    /**
     * Returns a double monthly interest
     *
     * @return interest fo this account
     */
    @Override
    public double monthlyInterest() {
        double interest = 4;

        if (isLoyal)
            interest = 4.25;
        return (balance / 12.0) * (interest / 100.0);
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
