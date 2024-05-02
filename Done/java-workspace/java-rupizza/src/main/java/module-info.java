module rupizza.rupizza {
    requires javafx.controls;
    requires javafx.fxml;
    requires org.testng;


    opens rupizza.rupizza to javafx.fxml;
    exports rupizza.rupizza;
}