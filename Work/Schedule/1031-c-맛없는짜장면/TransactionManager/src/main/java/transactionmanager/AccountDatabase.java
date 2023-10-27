package transactionmanager;

/**
 * Account database class
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class AccountDatabase {
    private static final int CHECKING = 1;
    private static final int COLLEGE_CHECKING = 2;
    private static final int MONEY_MARKET = 3;
    private static final int SAVINGS = 4;
    private static final int NOT_FOUND = -1;
    private static final int CAPACITY = 4;
    private static final int EMPTY = 0;
    private Account[] accounts; // the array holding the list of accounts
    private int numAcct; // current number of accounts in the array


    /**
     * Creates an empty list
     */
    public AccountDatabase() {
        accounts = new Account[CAPACITY];
        numAcct = EMPTY;
    }

    /**
     * Searches for an account to remove
     *
     * @param e the account to be searched
     * @return the index of account if found, -1 if not found
     */
    public int find(Account e) {
        for (int i = 0; i < numAcct; ++i) {
            if (accounts[i].compareTo(e) == 0)
                return i;
        }
        return NOT_FOUND;
    }

    /**
     * Increases the capacity of account list by 4
     */
    private void grow() {
        Account[] increasedAccounts = new Account[numAcct + CAPACITY];
        if (numAcct >= 0) System.arraycopy(accounts, 0, increasedAccounts, 0, numAcct);
        accounts = increasedAccounts;
    }

    /**
     * Checks whether an account exists in the list
     *
     * @param e the account to be searched
     * @return true if list contains specified account, false if not
     */
    public boolean contains(Account e) {
        if (numAcct == EMPTY)
            return false;
        for (int i = 0; i < numAcct; i++) {
            if (accounts[i].compareTo(e) == 0)
                return true;
        }
        return false;
    }

    /**
     * Adds an account to the end of the list
     *
     * @param e the account to be added
     */
    public void open(Account e) {
        if (contains(e))
            return;
        if (numAcct >= accounts.length) {
            grow();
        }
        accounts[numAcct] = e;
        ++numAcct;

    }


    /**
     * Deletes the specified account
     *
     * @param e the account to be deleted
     */
    public void close(Account e) {
        int indexOfAccount = find(e);
        for (int i = indexOfAccount; i < numAcct - 1; ++i)
            accounts[i] = accounts[i + 1];

        --numAcct;
        accounts[numAcct] = null;
    }

    /**
     * Withdraw from an account
     *
     * @param e      the account to be searched
     * @param amount balance amount
     * @return true if successfull
     * false if not
     */
    public boolean withdraw(Account e, double amount) {
        Account target = accounts[find(e)];
        if (target.getBalance() < amount)
            return false;
        accounts[find(e)].withdraw(amount);
        return true;
    }

    /**
     * Deposit from an account
     *
     * @param e      the account to be searched
     * @param amount balance amount
     */
    public void deposit(Account e, double amount) {
        accounts[find(e)].deposit(amount);
    }

    /**
     * Returns the array of accounts to print
     *
     * @return account list
     */
    public Account[] print() {
        if (numAcct == EMPTY)
            return null;
        else
            return accounts;
    }

    /**
     * Sort the array of accounts ordered by account type and profile
     */
    public void sort() {
        for (int i = 1; i < numAcct; ++i) {
            int j = i - 1;
            Account key = accounts[i];

            int key_type = getType(key);
            while (j >= 0 && ((getType(accounts[j]) == key_type && accounts[j].compareTo(key) > 0) || getType(accounts[j]) > key_type)) {
                accounts[j + 1] = accounts[j];
                --j;
            }
            accounts[j + 1] = key;
        }
    }

    /**
     * Get instance type of Account
     *
     * @param o account to check type
     * @return 1 if it is checking account,
     * 2 if it is college checking account,
     * 3 if it is savings account,
     * 4 if it is money market account
     */
    public int getType(Account o) {
        if (o instanceof Checking)
            return CHECKING;
        else if (o instanceof CollegeChecking)
            return COLLEGE_CHECKING;
        else if (o instanceof Savings)
            return SAVINGS;
        else if (o instanceof MoneyMarket)
            return MONEY_MARKET;
        else return -1;
    }

    /**
     * Return number of accounts added
     *
     * @return number of accounts
     */
    public int getNumAccounts() {
        return numAcct;
    }

    /**
     * Check the account list is empty
     *
     * @return true if it is empty
     * false if not
     */
    public boolean isEmpty() {
        return numAcct == EMPTY;
    }
}
