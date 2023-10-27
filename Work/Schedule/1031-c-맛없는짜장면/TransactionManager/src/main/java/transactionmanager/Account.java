package transactionmanager;

/**
 * Account class
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public abstract class Account implements Comparable<Account> {
    protected Profile holder;
    protected double balance;

    /**
     * Returns a double monthly interest
     *
     * @return interest fo this account
     */
    public abstract double monthlyInterest();

    /**
     * Returns a double monthly fee
     *
     * @return fee of this account
     */
    public abstract double monthlyFee();

    /**
     * Returns a Profile
     *
     * @return holder
     */
    public Profile getHolder() {
        return this.holder;
    }

    /**
     * Returns a double balance
     *
     * @return double balance value
     */
    public double getBalance() {
        return this.balance;
    }

    /**
     * Deposit balance
     *
     * @param balance balance to deposit
     */
    public void deposit(double balance) {
        this.balance += balance;
    }

    /**
     * Withdraw balance
     *
     * @param balance balance to withdraw
     */
    public void withdraw(double balance) {
        this.balance -= balance;
    }

    /**
     * Returns a String value of object include detail
     *
     * @return lname, fname, dob, type, balance, loyal status
     */
    public abstract String toStringForPrint();

    /**
     * Returns a String value of object include detail
     *
     * @return lname, fname, dob, type, balance, loyal status, fee, monthly interest
     */
    public abstract String toStringForPrintFeeAndInterest();

    /**
     * General balance updater
     */
    public void updateBalance() {
        balance += monthlyInterest();
        balance -= monthlyFee();
        balance = Math.round(balance * 100) / 100.0;

        if (balance < 0)
            balance = 0;
    }
}