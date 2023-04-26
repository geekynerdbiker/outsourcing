public class BankAccount {
    private String bankNumber;
    private int pinCode;
    private double balance;
    private User bankUser;

    public BankAccount(String bankNumber, int pinCode, double balance, User bankUser) {
        this.bankNumber = bankNumber;
        this.pinCode = pinCode;
        this.balance = balance;
        this.bankUser = bankUser;
    }

    public String getBankNumber() {
        return bankNumber;
    }

    public void setBankNumber(String bankNumber) {
        this.bankNumber = bankNumber;
    }

    public int getPinCode() {
        return pinCode;
    }

    public void setPinCode(int pinCode) {
        this.pinCode = pinCode;
    }

    public double getBalance() {
        return balance;
    }

    public void setBalance(double balance) {
        this.balance = balance;
    }

    public User getBankUser() {
        return bankUser;
    }

    public void setBankUser(User bankUser) {
        this.bankUser = bankUser;
    }

    public boolean checkPIN(int PIN) {
        return PIN == this.pinCode;
    }

    public boolean withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    public void deposit(double amount) {
        balance += amount;
    }

    public boolean transfer(BankAccount receiver, double amount) {
        if (balance >= amount) {
            receiver.setBalance(receiver.getBalance() + amount);
            balance -= amount;
            return true;
        }
        return false;
    }
}
