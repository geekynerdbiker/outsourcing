package bank;

import bank.event.*;

class BankAccount {
	// Do NOT change access modifier
    private Event[] events = new Event[maxEvents];
    final static int maxEvents = 100;
    private String id;
    private String password;
    private int balance;
    private String question = null;
    private String answer = null;

    private int eventIndex = 0;

    BankAccount(String id, String password, int balance) {
        //TODO: Problem 1.1
    }

    BankAccount(String id, String password, int balance, String question, String answer) {
        //TODO: Problem 1.3
    }


    boolean authenticate(String password) {
        //TODO: Problem 1.1
    }

    void deposit(int amount, int transId) {
        //TODO: Problem 1.1
    }

    boolean withdraw(int amount, int transId) {
        //TODO: Problem 1.1
    }

    void receive(int amount, int transId) {
        //TODO: Problem 1.1
    }

    boolean send(int amount, int transId) {
        //TODO: Problem 1.1
    }

    boolean secondaryAuthenticate(String questionAnswer) {
        //TODO: Problem 1.3
}
