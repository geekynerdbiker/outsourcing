package rupizza.rupizza;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 * Controller class for Main Menu Window.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class ruPizzaController {

    Store ruPizza = Store.getInstance();

    /**
     * Initializer function.
     */
    public void initialize() {
        Order currentOrder = ruPizza.getCurrentOrder();
        StoreOrders storeOrders = ruPizza.getOrderHistory();
    }

    /**
     * Create Specialty Pizza menu.
     */
    @FXML
    protected void specialty() {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(ruPizzaMain.class.getResource("Specialty.fxml"));
            Scene specialtyScene = new Scene(fxmlLoader.load(), 600, 400);

            Stage stage = new Stage();
            stage.setTitle("Specialty Pizza");
            stage.setScene(specialtyScene);

            stage.show();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Create Build Your Own Pizza menu.
     */
    @FXML
    protected void buildYourOwn() {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(ruPizzaMain.class.getResource("BuildYourOwn.fxml"));
            Scene buildYourOwnScene = new Scene(fxmlLoader.load(), 400, 500);

            Stage stage = new Stage();
            stage.setTitle("Build Your Own Pizza");
            stage.setScene(buildYourOwnScene);

            stage.show();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Create Current Order menu.
     */
    @FXML
    protected void viewCurrentOrder() {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(ruPizzaMain.class.getResource("Orders.fxml"));
            Scene orderScene = new Scene(fxmlLoader.load(), 600, 400);

            Stage stage = new Stage();
            stage.setTitle("Current Order");
            stage.setScene(orderScene);

            stage.show();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Create Store Orders menu.
     */
    @FXML
    protected void viewStoreOrders() {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(ruPizzaMain.class.getResource("StoreOrders.fxml"));
            Scene orderScene = new Scene(fxmlLoader.load(), 600, 400);

            Stage stage = new Stage();
            stage.setTitle("Store Orders");
            stage.setScene(orderScene);

            stage.show();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}