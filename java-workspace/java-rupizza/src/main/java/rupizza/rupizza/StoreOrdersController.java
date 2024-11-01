package rupizza.rupizza;


import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;

import java.io.*;
import java.util.ArrayList;

/**
 * Controller class for Store Orders Menu Window.
 * Allows you to view any selected order as well as delete orders.
 * Allows you to export store orders.
 *
 * @author DONGJIN KIM, HAOPENG LU
 */
public class StoreOrdersController {
    @FXML
    private ListView<String> orderList;
    @FXML
    private TextField orderTotal;
    @FXML
    private ComboBox<Integer> ordersAvailable;
    @FXML
    private Label buttonError;

    /**
     * Initializer function.
     */
    @FXML
    public void initialize() {
        displayOptions();
        orderList.setItems(FXCollections.observableArrayList());
        pickerFunction();
    }

    /**
     * Sets up the combo box with possible orders.
     */
    @FXML
    protected void displayOptions() {
        StoreOrders currentStore = Store.getInstance().getOrderHistory();
        ArrayList<Integer> orders = new ArrayList<>();
        for (int i = 0; i < currentStore.getNumOrders(); i++) {
            if (currentStore.getOrder(i).getSize() != 0) {
                orders.add(i + 1);
            }
        }
        ordersAvailable.setItems(FXCollections.observableArrayList(orders));
    }

    /**
     * Initializes the event listener for the select order combo box.
     */
    @FXML
    protected void pickerFunction() {
        ordersAvailable.valueProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                Order orderToDisplay = Store.getInstance().getOrderHistory().getOrder(newValue - 1);
                orderList.setItems(FXCollections.observableArrayList(orderToDisplay.getList()));
                orderTotal.setText(String.format("%.2f", orderToDisplay.orderPrice()));
            }
        });
    }

    /**
     * Delete store order function.
     */
    @FXML
    protected void delete() {
        if (ordersAvailable.getSelectionModel().getSelectedItem() != null) {
            if (ordersAvailable.getValue() != -1) {
                StoreOrders currentStore = Store.getInstance().getOrderHistory();
                int index = ordersAvailable.getValue();
                currentStore.getOrder(index - 1).clearOrder();
                orderTotal.setText("");
                orderList.setItems(FXCollections.observableArrayList());
                ordersAvailable.setItems(FXCollections.observableArrayList());
                ordersAvailable.getSelectionModel().clearSelection();
                displayOptions();
                buttonError.setText("");
            } else {
                buttonError.setText("Select any order.");
            }
        } else {
            buttonError.setText("Select any order.");
        }
    }

    /**
     * Export total store order data.
     * @throws IOException File not found exception, Buffered writer i/o exception.
     */
    @FXML
    protected void export() throws IOException {
        if (ordersAvailable.getSelectionModel().getSelectedItem() != null) {
            if (ordersAvailable.getValue() != -1) {
                StoreOrders currentStore = Store.getInstance().getOrderHistory();
                ArrayList<Order> toExport = currentStore.getOrderList();

                BufferedWriter bw  = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("order.txt")));
                for (Order order : toExport) {
                    if (order.getOrderItems().size() != 0) {
                        bw.write("[Order Number: " + order.getOrderNumber() + "]\n");
                        for (Pizza p : order.getOrderItems())
                            bw.write("\t" + p + "\n");
                        bw.write("\n");
                    }
                }
                buttonError.setText("Exported.");
                bw.flush();
                bw.close();
            } else {
                buttonError.setText("Select any order.");
            }
        } else {
            buttonError.setText("Select any order.");
        }
    }
}