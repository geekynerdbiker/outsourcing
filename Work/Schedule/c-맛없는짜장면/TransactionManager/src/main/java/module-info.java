module transactionmanager.transactionmanager {
    requires javafx.controls;
    requires javafx.fxml;


    opens transactionmanager to javafx.fxml;
    exports transactionmanager;
}