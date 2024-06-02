package healthcare;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.stage.Stage;

import java.io.IOException;

public class CheckController {
    public Button resultBtn;
    public Button cancelBtn;
    public Button hospitalBtn;
    public CheckBox chk1;
    public CheckBox chk2;
    public CheckBox chk3;
    public CheckBox chk4;
    public CheckBox chk5;
    public CheckBox chk6;

    @FXML
    protected void onResultButtonClick() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("result-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 320, 320);

        Stage curr = (Stage) resultBtn.getScene().getWindow();
        curr.close();

        Stage stage = new Stage();
        stage.setTitle("국민 건강 체크 프로그램");
        stage.setScene(scene);
        stage.show();
    }

    @FXML
    protected void onCancelButtonClick() {
        Stage curr = (Stage) cancelBtn.getScene().getWindow();
        curr.close();
    }

    @FXML
    protected void onHospitalButtonClick() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("hospital-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 640, 640);

        Stage stage = new Stage();
        stage.setTitle("국민 건강 체크 프로그램");
        stage.setScene(scene);
        stage.show();
    }
}