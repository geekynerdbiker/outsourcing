package healthcare;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.web.WebEngine;
import javafx.scene.web.WebView;
import javafx.stage.Stage;

import java.net.URL;
import java.util.ResourceBundle;

public class HospitalController implements Initializable {
    public WebView webView;
    public Button confirmBtn;

    @FXML
    protected void onConfirmButtonClick() {
        Stage curr = (Stage) confirmBtn.getScene().getWindow();
        curr.close();
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        WebEngine engine = webView.getEngine();
        engine.load("https://www.google.co.kr/maps/place/KMI%ED%95%9C%EA%B5%AD%EC%9D%98%ED%95%99%EC%97%B0%EA%B5%AC%EC%86%8C+%EB%B6%80%EC%82%B0%EA%B2%80%EC%A7%84%EC%84%BC%ED%84%B0/data=!4m6!3m5!1s0x3568eb6effffffff:0x1905166ce8bdb505!8m2!3d35.1386756!4d129.0634282!16s%2Fg%2F11cs6ckq9q?hl=ko&entry=ttu");
    }
}
