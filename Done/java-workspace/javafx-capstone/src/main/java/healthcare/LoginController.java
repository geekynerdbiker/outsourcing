package healthcare;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.stage.Stage;
import javafx.scene.control.TextField;

import java.io.IOException;
import java.sql.SQLException;

public class LoginController {
    public TextField idInput;
    public TextField pwInput;
    public Label stateLabel;
    public Button loginBtn;
    public Button signupBtn;

    private boolean check(String id, String pw) throws SQLException {
        Database db = new Database();
        boolean result = db.isIDExist(id) && db.isCorrectPW(id, pw);

        db.disconnect();
        return result;
    }

    @FXML
    protected void onLoginButtonClick() throws IOException, SQLException {
        String id = idInput.getText();
        String pw = pwInput.getText();

        if (id.isEmpty() || pw.isEmpty() || !check(id, pw)) {
            stateLabel.setText("아이디 또는 비밀번호를 확인하세요.");
            stateLabel.setStyle("-fx-text-fill: red");
            return;
        }

        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("home-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 320, 320);

        Stage curr = (Stage) loginBtn.getScene().getWindow();
        curr.close();

        Stage stage = new Stage();
        stage.setTitle("국민 건강 체크 프로그램");
        stage.setScene(scene);
        stage.show();

    }

    @FXML
    protected void onSignupButtonClick() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("signup-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 320, 320);

        Stage stage = new Stage();
        stage.setTitle("국민 건강 체크 프로그램");
        stage.setScene(scene);
        stage.show();
    }
}