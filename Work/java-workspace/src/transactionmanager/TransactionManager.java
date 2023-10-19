package transactionmanager;

import java.util.Scanner;
import java.util.StringTokenizer;

/**
 * Transaction Manager class
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class TransactionManager {
    private final static int TYPE_INDEX = 0;
    private final static int FNAME_INDEX = 1;
    private final static int LNAME_INDEX = 2;
    private final static int DATE_INDEX = 3;
    private final static int BALANCE_INDEX = 4;
    private final static int COLLEGE_INDEX = 5;
    private final static int LOYAL_INDEX = 5;

    /**
     * Runs the program
     */
    public void run() {
        System.out.println("Transaction Manager running...");
        Scanner input = new Scanner(System.in);
        AccountDatabase accountDatabase = new AccountDatabase();

        boolean isRunning = true;
        while (input.hasNextLine() && isRunning) {
            StringTokenizer st = new StringTokenizer(input.nextLine());
            String command;
            if (st.hasMoreTokens()) command = st.nextToken();
            else continue;

            switch (command) {
                case "O":
                    openAccount(accountDatabase, st);
                    break;
                case "C":
                    closeAccount(accountDatabase, st);
                    break;
                case "D":
                    depositMoney(accountDatabase, st);
                    break;
                case "W":
                    withdrawMoney(accountDatabase, st);
                    break;
                case "P":
                    printSortedAccounts(accountDatabase);
                    break;
                case "PI":
                    printAccountsDetails(accountDatabase);
                    break;
                case "UB":
                    updateBalance(accountDatabase);
                    break;
                case "Q":
                    isRunning = false;
                    System.out.println("Transaction Manager terminated.");
                    break;
                default:
                    System.out.println("Invalid command!");
            }
        }
    }

    /**
     * Open account from account
     *
     * @param accountDatabase account database to proceed
     * @param st              stringtokenizer tokenized command
     */

    private void openAccount(AccountDatabase accountDatabase, StringTokenizer st) {
        String[] tokens = new String[6];

        int index = 0;
        while (st.hasMoreTokens()) {
            tokens[index] = st.nextToken();
            index++;
        }

        if (!isValidToken(tokens, index)) return;

        StringTokenizer dateTokens = new StringTokenizer(tokens[3], "/");
        int month = Integer.parseInt(dateTokens.nextToken()), day = Integer.parseInt(dateTokens.nextToken()), year = Integer.parseInt(dateTokens.nextToken());
        Date dob = new Date(year, month, day);

        if (!isValidDob(dob)) return;

        if (dob.isUnder16()) {
            System.out.println("DOB invalid: " + dob + " under 16.");
            return;
        }
        try {
            double balance = Double.parseDouble(tokens[BALANCE_INDEX]);
            if (balance <= 0) {
                System.out.println("Initial balance cannot be 0 or negative.");
                return;
            }
            Profile profile = new Profile(tokens[FNAME_INDEX], tokens[LNAME_INDEX], dob);
            Checking checking;
            CollegeChecking collegeChecking;
            switch (tokens[TYPE_INDEX]) {
                case "C":
                    if (dob.isOver24()) {
                        System.out.println("DOB invalid: " + dob + " over 24.");
                        break;
                    }
                    checking = new Checking(profile, balance);
                    collegeChecking = new CollegeChecking(profile, balance, getCampus(0));
                    if (accountDatabase.contains(checking) || accountDatabase.contains(collegeChecking)) {
                        System.out.println(checking + " is already in the database.");
                        break;
                    }
                    accountDatabase.open(checking);
                    System.out.println(checking + " opened.");
                    break;
                case "CC":
                    if (dob.isOver24()) {
                        System.out.println("DOB invalid: " + dob + " over 24.");
                        break;
                    }
                    Campus campus = getCampus(Integer.parseInt(tokens[COLLEGE_INDEX]));
                    if (campus == null) {
                        System.out.println("Invalid campus code.");
                        break;
                    }

                    checking = new Checking(profile, balance);
                    collegeChecking = new CollegeChecking(profile, balance, campus);
                    if (accountDatabase.contains(checking) || accountDatabase.contains(collegeChecking)) {
                        System.out.println(collegeChecking + " is already in the database.");
                        break;
                    }
                    System.out.println(collegeChecking + " opened.");
                    accountDatabase.open(collegeChecking);
                    break;
                case "S":
                    boolean isLoyal = Integer.parseInt(tokens[LOYAL_INDEX]) == 1;
                    Savings savings = new Savings(profile, balance, isLoyal);
                    if (accountDatabase.contains(savings)) {
                        System.out.println(savings + " is already in the database.");
                        break;
                    }
                    accountDatabase.open(savings);
                    System.out.println(savings + " opened.");
                    break;
                case "MM":
                    if (balance < 2000) {
                        System.out.println("Minimum of $2000 to open a Money Market account.");
                        break;
                    }

                    MoneyMarket moneyMarket = new MoneyMarket(profile, balance);
                    if (accountDatabase.contains(moneyMarket)) {
                        System.out.println(moneyMarket + " is already in the database.");
                        break;
                    }
                    accountDatabase.open(moneyMarket);
                    System.out.println(moneyMarket + " opened.");
                    break;
            }

        } catch (NumberFormatException e) {
            System.out.println("Not a valid amount.");
        }
    }

    /**
     * Check is valid input
     *
     * @param tokens
     * @param index
     * @return true if there is no missing data
     * false if not
     */
    private boolean isValidToken(String[] tokens, int index) {
        if (index < 6) {
            if (tokens[TYPE_INDEX].compareTo("C") != 0 && tokens[TYPE_INDEX].compareTo("MM") != 0) {
                System.out.println("Missing data for opening an account.");
                return false;
            } else if (index < 5) {
                System.out.println("Missing data for opening an account.");
                return false;
            }
        }
        return true;
    }

    /**
     * Check is valid date of birth
     *
     * @param dob
     * @return true if is valid date and not a future date
     * false if not
     */
    private boolean isValidDob(Date dob) {
        if (!dob.isValid()) {
            System.out.println("DOB invalid: " + dob + " not a valid calendar date!");
            return false;
        } else if (dob.isFutureDate()) {
            System.out.println("DOB invalid: " + dob + " cannot be today or a future day.");
            return false;
        }
        return true;
    }

    /**
     * Close account from account
     *
     * @param accountDatabase account database to proceed
     * @param st              stringtokenizer tokenized command
     */
    private void closeAccount(AccountDatabase accountDatabase, StringTokenizer st) {
        String[] tokens = new String[4];

        int index = 0;
        while (st.hasMoreTokens()) {
            tokens[index] = st.nextToken();
            index++;
        }

        if (index < 4) {
            System.out.println("Missing data for closing an account.");
            return;
        }

        StringTokenizer dateTokens = new StringTokenizer(tokens[3], "/");
        int month = Integer.parseInt(dateTokens.nextToken()), day = Integer.parseInt(dateTokens.nextToken()), year = Integer.parseInt(dateTokens.nextToken());
        Date dob = new Date(year, month, day);

        if (!isValidDob(dob)) return;

        Profile profile = new Profile(tokens[FNAME_INDEX], tokens[LNAME_INDEX], dob);

        switch (tokens[TYPE_INDEX]) {
            case "C":
                Checking checking = new Checking(profile, 0);
                if (!accountDatabase.contains(checking)) {
                    System.out.println(checking + " is not in the database.");
                    break;
                }
                accountDatabase.close(checking);
                System.out.println(checking + " has been closed.");
                break;
            case "CC":
                CollegeChecking collegeChecking = new CollegeChecking(profile, 0, getCampus(0));
                if (!accountDatabase.contains(collegeChecking)) {
                    System.out.println(collegeChecking + " is not in the database.");
                    break;
                }
                accountDatabase.close(collegeChecking);
                System.out.println(collegeChecking + " has been closed.");
                break;
            case "S":
                Savings savings = new Savings(profile, 0, false);
                if (!accountDatabase.contains(savings)) {
                    System.out.println(savings + " is not in the database.");
                    break;
                }
                accountDatabase.close(savings);
                System.out.println(savings + " has been closed.");
                break;
            case "MM":
                MoneyMarket moneyMarket = new MoneyMarket(profile, 0);
                if (!accountDatabase.contains(moneyMarket)) {
                    System.out.println(moneyMarket + " is not in the database.");
                    break;
                }
                accountDatabase.close(moneyMarket);
                System.out.println(moneyMarket + " has been closed.");
                break;
        }

    }

    /**
     * Deposit money from account
     *
     * @param accountDatabase account database to proceed
     * @param st              string tokenizer tokenized command
     */
    private void depositMoney(AccountDatabase accountDatabase, StringTokenizer st) {
        String[] tokens = new String[5];

        int index = 0;
        while (st.hasMoreTokens()) {
            tokens[index] = st.nextToken();
            index++;
        }

        if (index < 5) {
            System.out.println("Missing data for closing an account.");
            return;
        }

        StringTokenizer dateTokens = new StringTokenizer(tokens[DATE_INDEX], "/");
        int month = Integer.parseInt(dateTokens.nextToken()), day = Integer.parseInt(dateTokens.nextToken()), year = Integer.parseInt(dateTokens.nextToken());
        Date dob = new Date(year, month, day);

        if (!isValidDob(dob)) return;

        Profile profile = new Profile(tokens[FNAME_INDEX], tokens[LNAME_INDEX], dob);
        try {
            double amount = Double.parseDouble(tokens[BALANCE_INDEX]);
            if (amount <= 0) {
                System.out.println("Deposit - amount cannot be 0 or negative.");
                return;
            }

            switch (tokens[TYPE_INDEX]) {
                case "C":
                    Checking checking = new Checking(profile, 0);
                    if (!accountDatabase.contains(checking)) {
                        System.out.println(checking + " is not in the database.");
                        break;
                    }
                    accountDatabase.deposit(checking, amount);
                    System.out.println(checking + " Deposit - balance updated.");
                    break;
                case "CC":
                    CollegeChecking collegeChecking = new CollegeChecking(profile, 0, getCampus(0));
                    if (!accountDatabase.contains(collegeChecking)) {
                        System.out.println(collegeChecking + " is not in the database.");
                        break;
                    }
                    accountDatabase.deposit(collegeChecking, amount);
                    System.out.println(collegeChecking + " Deposit - balance updated.");
                    break;
                case "S":
                    Savings savings = new Savings(profile, 0, false);
                    if (!accountDatabase.contains(savings)) {
                        System.out.println(savings + " is not in the database.");
                        break;
                    }
                    accountDatabase.deposit(savings, amount);
                    System.out.println(savings + " Deposit - balance updated.");
                    break;
                case "MM":
                    MoneyMarket moneyMarket = new MoneyMarket(profile, 0);
                    if (!accountDatabase.contains(moneyMarket)) {
                        System.out.println(moneyMarket + " is not in the database.");
                        break;
                    }
                    accountDatabase.deposit(moneyMarket, amount);
                    System.out.println(moneyMarket + " Deposit - balance updated.");
                    break;
            }
        } catch (NumberFormatException e) {
            System.out.println("Not a valid amount.");
        }
    }

    /**
     * Withdraw money from account
     *
     * @param accountDatabase account database to proceed
     * @param st              string tokenizer tokenized command
     */
    private void withdrawMoney(AccountDatabase accountDatabase, StringTokenizer st) {
        String[] tokens = new String[5];

        int index = 0;
        while (st.hasMoreTokens()) {
            tokens[index] = st.nextToken();
            index++;
        }

        if (index < 5) {
            System.out.println("Missing data for closing an account.");
            return;
        }

        StringTokenizer dateTokens = new StringTokenizer(tokens[DATE_INDEX], "/");
        int month = Integer.parseInt(dateTokens.nextToken()), day = Integer.parseInt(dateTokens.nextToken()), year = Integer.parseInt(dateTokens.nextToken());
        Date dob = new Date(year, month, day);

        if (!isValidDob(dob)) return;

        Profile profile = new Profile(tokens[FNAME_INDEX], tokens[LNAME_INDEX], dob);
        try {
            double amount = Double.parseDouble(tokens[BALANCE_INDEX]);
            if (amount <= 0) {
                System.out.println("Deposit - amount cannot be 0 or negative.");
                return;
            }

            boolean withdrawResult;
            switch (tokens[TYPE_INDEX]) {
                case "C":
                    Checking checking = new Checking(profile, 0);
                    if (!accountDatabase.contains(checking)) {
                        System.out.println(checking + " is not in the database.");
                        break;
                    }
                    withdrawResult = accountDatabase.withdraw(checking, amount);
                    if (withdrawResult)
                        System.out.println(checking + " Withdraw - balance updated.");
                    else
                        System.out.println(checking + " Withdraw - insufficient fund.");
                    break;
                case "CC":
                    CollegeChecking collegeChecking = new CollegeChecking(profile, 0, getCampus(0));
                    if (!accountDatabase.contains(collegeChecking)) {
                        System.out.println(collegeChecking + " is not in the database.");
                        break;
                    }
                    withdrawResult = accountDatabase.withdraw(collegeChecking, amount);
                    if (withdrawResult)
                        System.out.println(collegeChecking + " Withdraw - balance updated.");
                    else
                        System.out.println(collegeChecking + " Withdraw - insufficient fund.");
                    break;
                case "S":
                    Savings savings = new Savings(profile, 0, false);
                    if (!accountDatabase.contains(savings)) {
                        System.out.println(savings + " is not in the database.");
                        break;
                    }
                    withdrawResult = accountDatabase.withdraw(savings, amount);
                    if (withdrawResult)
                        System.out.println(savings + " Withdraw - balance updated.");
                    else
                        System.out.println(savings + " Withdraw - insufficient fund.");
                    break;
                case "MM":
                    MoneyMarket moneyMarket = new MoneyMarket(profile, 0);
                    if (!accountDatabase.contains(moneyMarket)) {
                        System.out.println(moneyMarket + " is not in the database.");
                        break;
                    }
                    withdrawResult = accountDatabase.withdraw(moneyMarket, amount);
                    if (withdrawResult)
                        System.out.println(moneyMarket + " Withdraw - balance updated.");
                    else
                        System.out.println(moneyMarket + " Withdraw - insufficient fund.");
                    break;
            }
        } catch (NumberFormatException e) {
            System.out.println("Not a valid amount.");
        }
    }

    /**
     * print account info from all accounts after sort
     *
     * @param accountDatabase account database to proceed
     */

    private void printSortedAccounts(AccountDatabase accountDatabase) {
        if (accountDatabase.isEmpty()) System.out.println("Account Database is empty!");
        else {
            accountDatabase.sort();
            Account[] accounts = accountDatabase.print();
            System.out.println("\n*Accounts sorted by account type and profile.");
            for (int i = 0; i < accountDatabase.getNumAccounts(); i++)
                System.out.println(accounts[i].toStringForPrint());
            System.out.println("*end of list.\n");
        }
    }

    /**
     * print account info inclue details from all accounts.
     *
     * @param accountDatabase account database to proceed
     */
    private void printAccountsDetails(AccountDatabase accountDatabase) {
        if (accountDatabase.isEmpty()) System.out.println("Account Database is empty!");
        else {
            accountDatabase.sort();
            Account[] accounts = accountDatabase.print();
            System.out.println("\n*list of accounts with fee and monthly interest");
            for (int i = 0; i < accountDatabase.getNumAccounts(); i++)
                System.out.println(accounts[i].toStringForPrintFeeAndInterest());
            System.out.println("*end of list.\n");
        }
    }

    /**
     * update balance by fee and interest from all accounts.
     *
     * @param accountDatabase account database to proceed
     */
    private void updateBalance(AccountDatabase accountDatabase) {
        if (accountDatabase.isEmpty()) System.out.println("Account Database is empty!");
        else {
            accountDatabase.sort();
            Account[] accounts = accountDatabase.print();
            System.out.println("\n*list of accounts with fees and interests applied.");
            for (int i = 0; i < accountDatabase.getNumAccounts(); i++) {
                accounts[i].updateBalance();
                System.out.println(accounts[i].toStringForPrint());
            }
            System.out.println("*end of list.\n");
        }
    }

    /**
     * Get Campus from string
     *
     * @param collegeCode the current Campus
     * @return Campus class from enum if exist
     */
    private Campus getCampus(int collegeCode) {
        for (Campus campus : Campus.values()) {
            if (campus.getCollegeCode() == collegeCode) {
                return campus;
            }
        }
        return null;
    }
}