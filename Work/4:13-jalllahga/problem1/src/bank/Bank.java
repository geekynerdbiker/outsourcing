package bank;

import bank.event.*;
import security.*;
import security.key.*;

public class Bank {
    private int numAccounts = 0;
    final static int maxAccounts = 100;
    private BankAccount[] accounts = new BankAccount[maxAccounts];
    private String[] ids = new String[maxAccounts];

    public void createAccount(String id, String password) {
        //TODO: Problem 1.1
    }

    public void createAccount(String id, String password, int initBalance) {
        //TODO: Problem 1.1
    }

    public boolean deposit(String id, String password, int amount, int transId) {
        //TODO: Problem 1.1
    }

    public boolean withdraw(String id, String password, int amount, int transId) {
        //TODO: Problem 1.1
    }

    public boolean transfer(String sourceId, String password, String targetId, int amount, int transId) {
        //TODO: Problem 1.1
    }

    public Event[] getEvents(String id, String password) {
        //TODO: Problem 1.1
    }

    public int getBalance(String id, String password) {
        //TODO: Problem 1.1
    }

    private static String randomUniqueStringGen(){
        return Encryptor.randomUniqueStringGen();
    }
    private BankAccount find(String id) {
        for (int i = 0; i < numAccounts; i++) {
            if(ids[i].equals(id)){return accounts[i];}
        }
        return null;
    }


    private BankSecretKey secretKey;
    public BankPublicKey getPublicKey(){
        BankKeyPair keypair = Encryptor.publicKeyGen(); // generates two keys : BankPublicKey, BankSecretKey
        secretKey = keypair.deckey; // stores BankSecretKey internally
        return keypair.enckey;
    }

    int maxHandshakes = 10000;
    int numSymmetrickeys = 0;
    BankSymmetricKey[] bankSymmetricKeys = new BankSymmetricKey[maxHandshakes];
    String[] AppIds = new String[maxHandshakes];

    public int getAppIdIndex(String AppId){
        for(int i=0; i<numSymmetrickeys; i++){
            if(AppIds[i].equals(AppId)){
                return i;
            }
        }
        return -1;
    }

    public void fetchSymKey(Encrypted<BankSymmetricKey> encryptedKey, String AppId){
        //TODO: Problem 1.2
    }

    public Encrypted<Boolean> processRequest(Encrypted<Message> messageEnc, String AppId) {
        //TODO: Problem 1.2
    }

    public void createAccount(String id, String password, int initBalance, String question, String answer) {
        //TODO: Problem 1.3
    }

    public boolean compensate(String id, String password, String questionAnswer, int[] transIdList){
        //TODO: Problem 1.3
    }
}
