package transactionmanager;

import java.text.DecimalFormat;

/**
 * Money Market class
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class MoneyMarket extends Account {
    private int withdrawal;
    private boolean isLoyal;

    /**
     * Creates predefined Checking objects
     *
     * @param profile profile of holder of account
     * @param balance balance of account
     */
    public MoneyMarket(Profile profile, double balance) {
        this.holder = profile;
        this.balance = balance;
        this.isLoyal = true;
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
        if (o instanceof MoneyMarket) return holder.compareTo(o.getHolder());
        else return 1;
    }

    /**
     * Returns a String value of object
     *
     * @return lname, fname, dob, type
     */
    @Override
    public String toString() {
        return holder.toString() + "(MM)";
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
            return "MoneyMarket::" + holder.toString() + "::Balance $" + decimalFormat.format(balance) + "::is loyal::withdrawal: " + withdrawal;
        else
            return "MoneyMarket::" + holder.toString() + "::Balance $" + decimalFormat.format(balance) + "::withdrawal: " + withdrawal;
    }

    /**
     * Overrided withdraw method to update loyal status
     * @param balance balance to withdraw
     */
    @Override
    public void withdraw(double balance) {
        this.balance -= balance;
        withdrawal++;
        updateLoyalState();
    }

    /**
     * Update loyal status by balance
     */
    private void updateLoyalState() {
        this.isLoyal = this.balance >= 2000;
    }

    /**
     * Returns a double monthly fee
     *
     * @return fee of this account
     */
    @Override
    public double monthlyFee() {
        double fee = 25;

        if (balance >= 2000)
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
        double interest = 4.5;

        if (isLoyal)
            interest = 4.75;

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

    @Override
    public void updateBalance() {
        double temp = balance;
        temp += monthlyInterest();
        temp -= monthlyFee();

        if (temp >= 2000)
            isLoyal = true;

        balance += monthlyInterest();
        balance -= monthlyFee();
        if (withdrawal > 3) {
            balance -= 10;
            withdrawal = 0;
        }

    }
}
