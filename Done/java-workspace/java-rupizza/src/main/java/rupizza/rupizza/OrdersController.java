package rupizza.rupizza;

import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;

/**
 * Controller class for Current Order Menu Window.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class OrdersController {
    @FXML
    private ListView<String> orderView;
    @FXML
    private TextField orderID;
    @FXML
    private TextField subtotalBox;
    @FXML
    private TextField salesTax;
    @FXML
    private TextField orderTotal;
    @FXML
    Label buttonError;

    /**
     * Initializer function.
     */
    @FXML
    public void initialize() {
        Order currentOrder = Store.getInstance().getCurrentOrder();
        orderView.setItems(FXCollections.observableArrayList(currentOrder.getList()));
        calculatePrice();
        if (Store.getInstance().getOrderHistory().getNextOrder() != 0) {
            orderID.setText(String.valueOf(Store.getInstance().getOrderHistory().getNextOrder()));
        } else {
            orderID.setText("1");
        }
    }

    /**
     * Calculate total order price.
     */
    protected void calculatePrice() {
        Order currentOrder = Store.getInstance().getCurrentOrder();
        double price = 0;
        for (int i = 0; i < currentOrder.orderItems.size(); i++) {
            price += currentOrder.orderItems.get(i).getPrice();
        }
        subtotalBox.setText(String.format("%.2f", price));
        salesTax.setText(String.format("%.2f", price * .0625));
        orderTotal.setText(String.format("%.2f", price * 1.0625));
    }

    /**
     * Confirm button function to save current order to store orders
     */
    @FXML
    protected void confirm() {
        StoreOrders currentStore = Store.getInstance().getOrderHistory();
        Order currentOrder = Store.getInstance().getCurrentOrder();
        if (currentOrder.getOrderItems().isEmpty()) {
            buttonError.setText("There is no order.");
            return;
        }
        if (currentStore.getNumOrders() == 0) {
            currentStore.addOrder(currentOrder);
        }

        orderID.setText("");
        orderView.setItems(FXCollections.observableArrayList());
        subtotalBox.setText("");
        salesTax.setText("");
        orderTotal.setText("");

        Store.getInstance().setNextOrder();
        orderID.setText(String.valueOf(Store.getInstance().getOrderHistory().getNextOrder()));
        buttonError.setText("");

        calculatePrice();
    }

    /**
     * Cancel button function to delete pizza from current order.
     */
    @FXML
    protected void cancel() {
        if (orderView.getSelectionModel().getSelectedIndex() != -1) {
            Order currentOrder = Store.getInstance().getCurrentOrder();
            int index = orderView.getSelectionModel().getSelectedIndex();
            currentOrder.removeItem(index);
            orderView.getItems().remove(index);
            buttonError.setText("");
        } else {
            buttonError.setText("Select any order.");
        }
        calculatePrice();
    }
}
