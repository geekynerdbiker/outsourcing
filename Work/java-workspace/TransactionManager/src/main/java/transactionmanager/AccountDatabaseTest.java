//package transactionmanager;
//
//import org.junit.jupiter.api.Test;
//
//import static org.junit.jupiter.api.Assertions.*;
//
//class AccountDatabaseTest {
//
//    @Test
//    void close() {
//        AccountDatabase accountDatabase = new AccountDatabase();
//
//        Date d = new Date(2020, 1, 2);
//        Profile p = new Profile("LNAME", "fname", d);
//
//        Checking c = new Checking(p, 0);
//        accountDatabase.open(c);
//
//        accountDatabase.close(c);
//        assertEquals(accountDatabase.getNumAccounts(), 0);
//    }
//}