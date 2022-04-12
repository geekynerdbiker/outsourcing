package bank;

import security.key.BankPublicKey;
import security.key.BankSymmetricKey;
import security.*;

public class MobileApp {

    private String randomUniqueStringGen(){
        return Encryptor.randomUniqueStringGen();
    }
    private final String AppId = randomUniqueStringGen();
    public String getAppId() {
        return AppId;
    }
    private BankSymmetricKey bankSymmetricKey;
    private static int curTransId = 1;

    public void setCurTransId(int id){curTransId=id;}

    private String id, password;
    public MobileApp(String id, String password){
        this.id = id;
        this.password = password;
    }

    public Encrypted<BankSymmetricKey> sendSymKey(BankPublicKey publickey){
        //TODO: Problem 1.2
    }

    public Encrypted<Message> deposit(int amount){
        //TODO: Problem 1.2
    }

    public Encrypted<Message> withdraw(int amount){
        //TODO: Problem 1.2
    }

    public boolean processResponse(Encrypted<Boolean> obj) {
        //TODO: Problem 1.2
    }

    public Encrypted<Message> requestCompensate(String question, String answer, int[] transIdList){
        //TODO: Problem 1.3
    }
}

