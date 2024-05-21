package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.os.Bundle;
import android.view.View;
import android.widget.Adapter;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import java.text.DecimalFormat;

/**
 * The StoreOrdersActivity class defines the methods and data associated with viewing store orders.
 * The storeOrders variable allows for other classes to send orders to the store.
 * A Spinner instance is used to let the user choose which order to display.
 * A ListView instance is used to display the pizzas in the order selected.
 * Three TextView instances are used to display the subtotal, tax, and total of the order selected.
 * A Button instance is used to allow the user to cancel the selected order.
 */
public class StoreOrdersActivity extends AppCompatActivity {

    public static StoreOrders storeOrders;

    private Spinner orderSelectionSpinner;
    private ListView pizzaListView;
    private TextView subtotalTextView, taxTextView, totalTextView;
    private Button cancelOrderButton;

    /**
     * Shows the layout of the StoreOrdersActivity as a View and initializes I/O elements.
     * The layout file is activity_store_orders.xml.
     * @param savedInstanceState the Bundle used to restore the app when onCreate() is invoked.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_store_orders);
        initializeReferences();
        initializeOrderSelectionSpinner();
        initializeCancelOrderButton();
    }

    /**
     * Initializes references to elements of the layout that are used for user I/O.
     * The layout file is activity_store_orders.xml.
     */
    private void initializeReferences(){
        orderSelectionSpinner = findViewById(R.id.orderSelectionSpinner);
        pizzaListView = findViewById(R.id.storeOrdersPizzaListView);
        subtotalTextView = findViewById(R.id.storeOrdersSubtotalTextView);
        taxTextView = findViewById(R.id.storeOrdersTaxTextView);
        totalTextView = findViewById(R.id.storeOrdersTotalTextView);
        cancelOrderButton = findViewById(R.id.cancelOrderButton);
    }

    /**
     * Sets the onItemSelectedListener for the Spinner used to select an order.
     * If an order is selected from the Spinner, the order is displayed to the user and the user
     * gains the ability to cancel the order.
     * If there are no orders selected, the display is flushed of all information and the user loses
     * the ability to cancel the order.
     */
    private void initializeOrderSelectionSpinner(){
        orderSelectionSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                setOrderDisplayEnablement(true);
                fillOrderDisplay();
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
                flushOrderDisplay();
                setOrderDisplayEnablement(false);
            }
        });
        clearOrderSelectionSpinnerSelection();
        updateOrderSelectionSpinner();
    }

    /**
     * Sets the onClickListener for the Button used to cancel a selected order.
     * If the Button is clicked, showCancelOrderAlertDialogue() is invoked.
     */
    private void initializeCancelOrderButton(){
        cancelOrderButton.setOnClickListener(v -> showCancelOrderAlertDialogue());
    }

    /**
     * Shows an AlertDialogue to let the user confirm if and order is to be cancelled.
     * If there are no orders that have been submitted, the user is prompted to submit an order.
     * OK must be pressed to acknowledge the alert, and nothing will occur in this case.
     * If there are orders that have been submitted and yes is selected, the order will be cancelled
     * by invoking cancelOrder().
     * Otherwise, nothing occurs when No is pressed.
     */
    private void showCancelOrderAlertDialogue(){
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        if ( storeOrders.getOrders().isEmpty() ) {
            builder.setMessage(R.string.order_prompt)
                    .setCancelable(false)
                    .setPositiveButton(R.string.ok, (dialog, which) -> { });
        } else {
            builder.setMessage(R.string.cancel_order_warning)
                    .setCancelable(false)
                    .setPositiveButton(R.string.yes, (dialog, which) -> cancelOrder())
                    .setNegativeButton(R.string.no, (dialog, which) -> { });
        }
        AlertDialog alert = builder.create();
        alert.show();
    }

    /**
     * Cancels the selected order by removing it from storeOrders and updating the order display.
     */
    private void cancelOrder(){
        storeOrders.remove(getSelectedOrder());
        clearOrderSelectionSpinnerSelection();
        flushOrderDisplay();
        updateOrderSelectionSpinner();
        showToast(R.string.cancelled_order_toast);
    }

    /**
     * Clears the selection of the Spinner used to select orders.
     */
    private void clearOrderSelectionSpinnerSelection(){
        orderSelectionSpinner.setSelection(Adapter.NO_SELECTION);
    }

    /**
     * Updates the list of orders displayed in the Spinner by creating a new ArrayAdapter.
     * This ArrayAdapter uses the list of serial numbers in storeOrders.
     */
    private void updateOrderSelectionSpinner(){
        ArrayAdapter<Integer> adapter = new ArrayAdapter<>(this,
                android.R.layout.simple_spinner_dropdown_item, storeOrders.getOrderSerialNumbers());
        orderSelectionSpinner.setAdapter(adapter);
    }

    /**
     * Sets the enablement of the elements used to display a selected order.
     * @param state true if the elements are to be enabled, false otherwise.
     */
    private void setOrderDisplayEnablement(boolean state){
        cancelOrderButton.setEnabled(state);
        pizzaListView.setEnabled(state);
        subtotalTextView.setEnabled(state);
        taxTextView.setEnabled(state);
        totalTextView.setEnabled(state);
    }

    /**
     * Fills the order display with information about the selected order.
     * This includes the price of the order, as well as the ListView displaying the pizzas in the
     * order.
     */
    private void fillOrderDisplay(){
        Order order = getSelectedOrder();

        ArrayAdapter<Pizza> adapter = new ArrayAdapter<>(this,
                android.R.layout.simple_list_item_1, order.getPizzas());
        pizzaListView.setAdapter(adapter);

        DecimalFormat df = new DecimalFormat("#0.00");

        String value = "Subtotal: $" + df.format(order.getOrderSubtotal());
        subtotalTextView.setText(value);

        value = "Tax: $" + df.format(order.getOrderTax());
        taxTextView.setText(value);

        value = "Total: $" + df.format(order.getOrderTotal());
        totalTextView.setText(value);
    }

    /**
     * Flushes the order display when there are no orders to display.
     * This includes the price of the order, as well as the ListView displaying the pizzas in the
     * order.
     */
    private void flushOrderDisplay(){
        pizzaListView.setAdapter(null);
        String subtotal = "Subtotal: $0.00";
        subtotalTextView.setText(subtotal);
        String tax = "Tax: $0.00";
        taxTextView.setText(tax);
        String total = "Total: $0.00";
        totalTextView.setText(total);
    }

    /**
     * Gets the serial number of the order selected by the user.
     * @return the serial number of the order selected by the user.
     */
    private int getSelectedOrderNumber(){
        return (Integer) orderSelectionSpinner.getSelectedItem();
    }

    /**
     * Gets the Order associated with the serial number selected by the user.
     * @return the Order associated with the serial number selected by the user.
     */
    private Order getSelectedOrder(){
        return storeOrders.getOrderFromSerialNumber(getSelectedOrderNumber());
    }

    /**
     * Shows a toast message whose message is specified by the user.
     * @param string the string id of the message to be shown in the toast.
     */
    private void showToast(int string){
        Toast.makeText(this, string, Toast.LENGTH_SHORT).show();
    }
}