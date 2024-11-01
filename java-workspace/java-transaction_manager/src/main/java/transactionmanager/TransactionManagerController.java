package transactionmanager;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.StringTokenizer;

/**
 * Transcation Manager Controller class
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class TransactionManagerController implements Initializable {
    private final static int TYPE_INDEX = 0;
    private final static int FNAME_INDEX = 1;
    private final static int LNAME_INDEX = 2;
    private final static int DATE_INDEX = 3;
    private final static int BALANCE_INDEX = 4;
    private final static int COLLEGE_INDEX = 5;
    private final static int LOYAL_INDEX = 5;

    AccountDatabase accountDatabase = new AccountDatabase();

    @FXML
    private Button openBtn;
    @FXML
    private Button closeBtn;
    @FXML
    private Button depositBtn;
    @FXML
    private Button withdrawBtn;
    @FXML
    private Button printBtn;
    @FXML
    private Button printDetailBtn;
    @FXML
    private Button updateBtn;

    @FXML
    private TextField textField;
    @FXML
    private TextArea textArea;


    /**
     * Initialize event handler functions
     *
     * @param location  The location used to resolve relative paths for the root object, or
     *                  {@code null} if the location is not known.
     * @param resources The resources used to localize the root object, or {@code null} if
     *                  the root object was not localized.
     */
    @Override
    public void initialize(URL location, ResourceBundle resources) {
        openBtn.setOnAction(this::onOpenBtnClick);
        closeBtn.setOnAction(this::onCloseBtnClick);
        depositBtn.setOnAction(this::onDepositBtnClick);
        withdrawBtn.setOnAction(this::onWithdrawBtnClick);
        printBtn.setOnAction(this::onPrintBtnClick);
        printDetailBtn.setOnAction(this::onPrintDetailBtnClick);
        updateBtn.setOnAction(this::onUpdateBtnClick);
        loadData();
    }

    /**
     * Load Data while initialize
     */
    private void loadData() {
        File f = new File("/Users/jacoban/Documents/GitHub/Crebugs/Work/java-workspace/TransactionManager/src/main/java/transactionmanager/bankAccounts.txt");
        StringTokenizer st = new StringTokenizer("");

        try {
            try (BufferedReader br = new BufferedReader(new FileReader(f))) {
                String line;
                while ((line = br.readLine()) != null) {
                    if (line.compareTo("") != 0)
                        openAccounts(st, line);
                }
                textArea.setText("Successfully loaded!");
            }
        } catch (IOException e) {
            textArea.setText("Failed to load: No such file in path.");
        }
    }

    /**
     * Open account button from account
     *
     * @param event
     */
    @FXML
    protected void onOpenBtnClick(ActionEvent event) {
        StringTokenizer st = new StringTokenizer(textField.getText(), ",");
        if (!st.hasMoreTokens()) {
            textArea.setText("Input data.\n");
            return;
        }

        openAccounts(st, "");
    }

    /**
     * Open Account function
     *
     * @param st StringTokenizer for open button
     * @param s  String for load
     */
    private void openAccounts(StringTokenizer st, String s) {
        String[] tokens = new String[6];

        if (s.compareTo("") != 0)
            st = new StringTokenizer(s, ",");

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
            textArea.setText("DOB invalid: " + dob + " under 16.\n");
            return;
        }
        try {
            double balance = Double.parseDouble(tokens[BALANCE_INDEX]);
            if (balance <= 0) {
                textArea.setText("Initial balance cannot be 0 or negative.\n");
                return;
            }
            Profile profile = new Profile(tokens[FNAME_INDEX], tokens[LNAME_INDEX], dob);
            Checking checking;
            CollegeChecking collegeChecking;

            switch (tokens[TYPE_INDEX]) {
                case "C":
                    if (dob.isOver24()) {
                        textArea.setText("DOB invalid: " + dob + " over 24.\n");
                        break;
                    }
                    checking = new Checking(profile, balance);
                    collegeChecking = new CollegeChecking(profile, balance, getCampus(0));
                    if (accountDatabase.contains(checking) || accountDatabase.contains(collegeChecking)) {
                        textArea.setText(checking + " is already in the database.\n");
                        break;
                    }
                    accountDatabase.open(checking);
                    textArea.setText(checking + " opened.\n");
                    break;
                case "CC":
                    if (dob.isOver24()) {
                        textArea.setText("DOB invalid: " + dob + " over 24.\n");
                        break;
                    }
                    Campus campus = getCampus(Integer.parseInt(tokens[COLLEGE_INDEX]));
                    if (campus == null) {
                        textArea.setText("Invalid campus code.\n");
                        break;
                    }

                    checking = new Checking(profile, balance);
                    collegeChecking = new CollegeChecking(profile, balance, campus);
                    if (accountDatabase.contains(checking) || accountDatabase.contains(collegeChecking)) {
                        textArea.setText(collegeChecking + " is already in the database.\n");
                        break;
                    }
                    textArea.setText(collegeChecking + " opened.\n");
                    accountDatabase.open(collegeChecking);
                    break;
                case "S":
                    boolean isLoyal = Integer.parseInt(tokens[LOYAL_INDEX]) == 1;
                    Savings savings = new Savings(profile, balance, isLoyal);
                    if (accountDatabase.contains(savings)) {
                        textArea.setText(savings + " is already in the database.\n");
                        break;
                    }
                    accountDatabase.open(savings);
                    textArea.setText(savings + " opened.\n");
                    break;
                case "MM":
                    if (balance < 2000) {
                        textArea.setText("Minimum of $2000 to open a Money Market account.\n");
                        break;
                    }

                    MoneyMarket moneyMarket = new MoneyMarket(profile, balance);
                    if (accountDatabase.contains(moneyMarket)) {
                        textArea.setText(moneyMarket + " is already in the database.\n");
                        break;
                    }
                    accountDatabase.open(moneyMarket);
                    textArea.setText(moneyMarket + " opened.\n");
                    break;
            }

        } catch (NumberFormatException e) {
            textArea.setText("Not a valid amount.\n");
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
                textArea.setText("Missing data for opening an account.\n");
                return false;
            } else if (index < 5) {
                textArea.setText("Missing data for opening an account.\n");
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
            textArea.setText("DOB invalid: " + dob + " not a valid calendar date!\n");
            return false;
        } else if (dob.isFutureDate()) {
            textArea.setText("DOB invalid: " + dob + " cannot be today or a future day.\n");
            return false;
        }
        return true;
    }

    /**
     * Close account button from account
     *
     * @param event
     */
    protected void onCloseBtnClick(ActionEvent event) {
        StringTokenizer st = new StringTokenizer(textField.getText(), ",\n");
        if (!st.hasMoreTokens()) {
            textArea.setText("Input data.\n");
            return;
        }

        String[] tokens = new String[4];
        int index = 0;
        while (st.hasMoreTokens()) {
            tokens[index] = st.nextToken();
            index++;
        }

        if (index < 4) {
            textArea.setText("Missing data for closing an account.\n");
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
                    textArea.setText(checking + " is not in the database.\n");
                    break;
                }
                accountDatabase.close(checking);
                textArea.setText(checking + " has been closed.\n");
                break;
            case "CC":
                CollegeChecking collegeChecking = new CollegeChecking(profile, 0, getCampus(0));
                if (!accountDatabase.contains(collegeChecking)) {
                    textArea.setText(collegeChecking + " is not in the database.\n");
                    break;
                }
                accountDatabase.close(collegeChecking);
                textArea.setText(collegeChecking + " has been closed.\n");
                break;
            case "S":
                Savings savings = new Savings(profile, 0, false);
                if (!accountDatabase.contains(savings)) {
                    textArea.setText(savings + " is not in the database.\n");
                    break;
                }
                accountDatabase.close(savings);
                textArea.setText(savings + " has been closed.\n");
                break;
            case "MM":
                MoneyMarket moneyMarket = new MoneyMarket(profile, 0);
                if (!accountDatabase.contains(moneyMarket)) {
                    textArea.setText(moneyMarket + " is not in the database.\n");
                    break;
                }
                accountDatabase.close(moneyMarket);
                textArea.setText(moneyMarket + " has been closed.\n");
                break;
        }

    }

    /**
     * Deposit money button from account
     *
     * @param event
     */
    protected void onDepositBtnClick(ActionEvent event) {
        StringTokenizer st = new StringTokenizer(textField.getText(), ",");
        if (!st.hasMoreTokens()) {
            textArea.setText("Input data.\n");
            return;
        }

        String[] tokens = new String[5];

        int index = 0;
        while (st.hasMoreTokens()) {
            tokens[index] = st.nextToken();
            index++;
        }

        if (index < 5) {
            textArea.setText("Missing data for closing an account.\n");
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
                textArea.setText("Deposit - amount cannot be 0 or negative.\n");
                return;
            }

            switch (tokens[TYPE_INDEX]) {
                case "C":
                    Checking checking = new Checking(profile, 0);
                    if (!accountDatabase.contains(checking)) {
                        textArea.setText(checking + " is not in the database.\n");
                        break;
                    }
                    accountDatabase.deposit(checking, amount);
                    textArea.setText(checking + " Deposit - balance updated.\n");
                    break;
                case "CC":
                    CollegeChecking collegeChecking = new CollegeChecking(profile, 0, getCampus(0));
                    if (!accountDatabase.contains(collegeChecking)) {
                        textArea.setText(collegeChecking + " is not in the database.\n");
                        break;
                    }
                    accountDatabase.deposit(collegeChecking, amount);
                    textArea.setText(collegeChecking + " Deposit - balance updated.\n");
                    break;
                case "S":
                    Savings savings = new Savings(profile, 0, false);
                    if (!accountDatabase.contains(savings)) {
                        textArea.setText(savings + " is not in the database.\n");
                        break;
                    }
                    accountDatabase.deposit(savings, amount);
                    textArea.setText(savings + " Deposit - balance updated.\n");
                    break;
                case "MM":
                    MoneyMarket moneyMarket = new MoneyMarket(profile, 0);
                    if (!accountDatabase.contains(moneyMarket)) {
                        textArea.setText(moneyMarket + " is not in the database.\n");
                        break;
                    }
                    accountDatabase.deposit(moneyMarket, amount);
                    textArea.setText(moneyMarket + " Deposit - balance updated.\n");
                    break;
            }
        } catch (NumberFormatException e) {
            textArea.setText("Not a valid amount.\n");
        }
    }

    /**
     * Withdraw money button from account
     *
     * @param event
     */
    protected void onWithdrawBtnClick(ActionEvent event) {
        StringTokenizer st = new StringTokenizer(textField.getText(), ",");
        if (!st.hasMoreTokens()) {
            textArea.setText("Input data.\n");
            return;
        }
        String[] tokens = new String[5];

        int index = 0;
        while (st.hasMoreTokens()) {
            tokens[index] = st.nextToken();
            index++;
        }

        if (index < 5) {
            textArea.setText("Missing data for closing an account.\n");
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
                textArea.setText("Deposit - amount cannot be 0 or negative.\n");
                return;
            }

            boolean withdrawResult;
            switch (tokens[TYPE_INDEX]) {
                case "C":
                    Checking checking = new Checking(profile, 0);
                    if (!accountDatabase.contains(checking)) {
                        textArea.setText(checking + " is not in the database.\n");
                        break;
                    }
                    withdrawResult = accountDatabase.withdraw(checking, amount);
                    if (withdrawResult)
                        textArea.setText(checking + " Withdraw - balance updated.\n");
                    else
                        textArea.setText(checking + " Withdraw - insufficient fund.\n");
                    break;
                case "CC":
                    CollegeChecking collegeChecking = new CollegeChecking(profile, 0, getCampus(0));
                    if (!accountDatabase.contains(collegeChecking)) {
                        textArea.setText(collegeChecking + " is not in the database.\n");
                        break;
                    }
                    withdrawResult = accountDatabase.withdraw(collegeChecking, amount);
                    if (withdrawResult)
                        textArea.setText(collegeChecking + " Withdraw - balance updated.\n");
                    else
                        textArea.setText(collegeChecking + " Withdraw - insufficient fund.\n");
                    break;
                case "S":
                    Savings savings = new Savings(profile, 0, false);
                    if (!accountDatabase.contains(savings)) {
                        textArea.setText(savings + " is not in the database.\n");
                        break;
                    }
                    withdrawResult = accountDatabase.withdraw(savings, amount);
                    if (withdrawResult)
                        textArea.setText(savings + " Withdraw - balance updated.\n");
                    else
                        textArea.setText(savings + " Withdraw - insufficient fund.\n");
                    break;
                case "MM":
                    MoneyMarket moneyMarket = new MoneyMarket(profile, 0);
                    if (!accountDatabase.contains(moneyMarket)) {
                        textArea.setText(moneyMarket + " is not in the database.\n");
                        break;
                    }
                    withdrawResult = accountDatabase.withdraw(moneyMarket, amount);
                    if (withdrawResult)
                        textArea.setText(moneyMarket + " Withdraw - balance updated.\n");
                    else
                        textArea.setText(moneyMarket + " Withdraw - insufficient fund.\n");
                    break;
            }
        } catch (NumberFormatException e) {
            textArea.setText("Not a valid amount.\n");
        }
    }

    /**
     * print account info button from all accounts after sort
     *
     * @param event
     */

    protected void onPrintBtnClick(ActionEvent event) {
        String result = "";
        if (accountDatabase.isEmpty()) textArea.setText("Account Database is empty!\n");
        else {
            accountDatabase.sort();
            Account[] accounts = accountDatabase.print();
            result += ("\n*Accounts sorted by account type and profile.\n");
            for (int i = 0; i < accountDatabase.getNumAccounts(); i++)
                result += (accounts[i].toStringForPrint() + "\n");
            result += ("*end of list.\n\n");
            textArea.setText(result);
        }
    }

    /**
     * print account info button include details from all accounts.
     *
     * @param event
     */
    protected void onPrintDetailBtnClick(ActionEvent event) {
        String result = "";
        if (accountDatabase.isEmpty()) textArea.setText("Account Database is empty!\n");
        else {
            accountDatabase.sort();
            Account[] accounts = accountDatabase.print();
            result += ("\n*list of accounts with fee and monthly interest\n");
            for (int i = 0; i < accountDatabase.getNumAccounts(); i++)
                result += (accounts[i].toStringForPrintFeeAndInterest() + "\n");
            result += ("*end of list.\n\n");
            textArea.setText(result);
        }
    }

    /**
     * update balance button by fee and interest from all accounts.
     *
     * @param event
     */
    protected void onUpdateBtnClick(ActionEvent event) {
        String result = "";
        if (accountDatabase.isEmpty()) textArea.setText("Account Database is empty!\n");
        else {
            accountDatabase.sort();
            Account[] accounts = accountDatabase.print();
            result += ("\n*list of accounts with fees and interests applied.\n");
            for (int i = 0; i < accountDatabase.getNumAccounts(); i++) {
                accounts[i].updateBalance();
                result += (accounts[i].toStringForPrint() + "\n");
            }
            result += ("*end of list.\n\n");
            textArea.setText(result);
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