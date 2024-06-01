package healthcare;

import javafx.beans.InvalidationListener;
import javafx.collections.FXCollections;
import javafx.collections.ListChangeListener;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.sql.SQLException;
import java.util.*;

public class SignupController implements Initializable {
    public TextField idInput;
    public TextField pwInput;
    public Button checkBtn;
    public ComboBox<String> locationBox;
    public Button signupBtn;
    public Label stateLabel;
    public Button cancelBtn;

    @FXML
    protected void onCheckButtonClick() throws SQLException {
        Database db = new Database();

        if (idInput.getText().isEmpty()) {
            db.disconnect();
            return;
        }

        if (db.isIDExist(idInput.getText())) {
            stateLabel.setText("중복된 아이디");
            stateLabel.setStyle("-fx-text-fill: red");
        } else {
            stateLabel.setText("사용가능");
            stateLabel.setStyle("-fx-text-fill: blue");
        }
        db.disconnect();
    }

    @FXML
    protected void onSignupButtonClick() throws SQLException {
        if (stateLabel.getText().equals("사용가능") && !idInput.getText().isEmpty() && !pwInput.getText().isEmpty()) {
            if (locationBox.getSelectionModel().getSelectedItem() == null)
                return;

            Database db = new Database();

            if (db.signUp(idInput.getText(), pwInput.getText(), locationBox.getSelectionModel().getSelectedItem()) == 0)
                return;

            Stage curr = (Stage) signupBtn.getScene().getWindow();
            curr.close();

            db.disconnect();
        }
    }

    @FXML
    protected void onCancelButtonClick() {
        Stage curr = (Stage) cancelBtn.getScene().getWindow();
        curr.close();
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        ObservableList<String> items = FXCollections.observableArrayList("북구", "중구", "남구", "동구", "서구", "강서구", "부산진구", "동래구", "수영구", "해운대구");
        locationBox.setItems(items);
    }
}