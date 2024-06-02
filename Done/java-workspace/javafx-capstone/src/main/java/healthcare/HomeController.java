package healthcare;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.stage.Stage;

import java.io.IOException;

public class HomeController {
    public Button hospitalBtn;
    public Button symptomBtn;
    public Button checkBtn;
    public Button returnBtn;

    @FXML
    protected void onHospitalButtonClick() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("hospital-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 640, 640);

        Stage stage = new Stage();
        stage.setTitle("국민 건강 체크 프로그램");
        stage.setScene(scene);
        stage.show();

    }

    @FXML
    protected void onSymptomButtonClick() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("symptom-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 640, 480);

        Stage stage = new Stage();
        stage.setTitle("국민 건강 체크 프로그램");
        stage.setScene(scene);
        stage.show();
    }

    @FXML
    protected void onCheckButtonClick() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("check-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 320, 320);

        Stage stage = new Stage();
        stage.setTitle("국민 건강 체크 프로그램");
        stage.setScene(scene);
        stage.show();

    }

    @FXML
    protected void onReturnButtonClick() {
        Stage curr = (Stage) returnBtn.getScene().getWindow();
        curr.close();
    }
}