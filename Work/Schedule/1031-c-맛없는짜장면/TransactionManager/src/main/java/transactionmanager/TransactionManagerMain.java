package transactionmanager;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

/**
 * Transcaction Manager Main class
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class TransactionManagerMain extends Application {
    public static void main(String[] args) {
        launch();
    }

    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(TransactionManagerMain.class.getResource("TransactionManagerView.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 800, 800);

        stage.setTitle("TRANSACTION MANAGER");
        stage.setScene(scene);
        stage.show();
    }
}