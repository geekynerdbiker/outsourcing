package healthcare;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.stage.Stage;

public class ResultController {
    public Button confirmBtn;
    @FXML
    protected void onConfirmButtonClick() {
        Stage curr = (Stage) confirmBtn.getScene().getWindow();
        curr.close();
    }
}
