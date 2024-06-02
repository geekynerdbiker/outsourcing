module org.example.javafxcapstone {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.web;
    requires java.sql;


    opens healthcare to javafx.fxml;
    exports healthcare;
}