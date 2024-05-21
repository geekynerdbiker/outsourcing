package com.example.myapplication;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.text.DecimalFormat;

/**
 * The CurrentOrderActivity defines the methods and data associated with viewing the current order.
 * The currentOrder variable allows for other classes to add pizzas to the current order.
 * A ListView is used to display all pizzas in the order as strings.
 * Three TextView instances are used to display the subtotal, tax, and total of the order.
 * Two Button instances are used to allow the user to remove all pizzas, and submit the order.
 *
 * @author Trent Demers, Awad Shawl
 */
public class CurrentOrderActivity extends AppCompatActivity {

    public static Order currentOrder;

    private ListView pizzaListView;
    private Button removeAllPizzasButton, submitOrderButton;
    private TextView subtotalTextView, taxTextView, totalTextView;

    /**
     * Shows the layout of the CurrentOrderActivity as a View before initializing I/O elements.
     * The layout file is activity_current_order.xml.
     * @param savedInstanceState the Bundle used to restore the app when onCreate() is invoked.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_current_order);

        initializeReferences();

        initializePizzaListView();
        initializeRemoveAllPizzasButton();
        initializeSubmitOrderButton();

        updatePizzaListView();
        updatePrice();
    }

    /**
     * Initializes references to elements of the layout that are used for user I/O.
     * The layout file is activity_current_order.xml.
     */
    private void initializeReferences(){
        pizzaListView = findViewById(R.id.currentOrderPizzaListView);
        removeAllPizzasButton = findViewById(R.id.removeAllPizzasButton);
        submitOrderButton = findViewById(R.id.submitOrderButton);
        subtotalTextView = findViewById(R.id.currentOrderSubtotalTextView);
        taxTextView = findViewById(R.id.currentOrderTaxTextView);
        totalTextView = findViewById(R.id.currentOrderTotalTextView);
    }

    /**
     * Sets the onItemClickListener for the pizzaListView to showRemovePizzaAlertDialogue().
     */
    private void initializePizzaListView(){
        pizzaListView.setOnItemClickListener((parent, view, position, id)
                -> showRemovePizzaAlertDialogue(position));
    }

    /**
     * Shows an AlertDialogue to let the user confirm if the selected pizza is to be removed.
     * If yes is selected, the selected pizza is removed by invoking removePizza().
     * Otherwise, nothing occurs.
     * @param position the position of the pizza selected by the user in the ListView.
     */
    private void showRemovePizzaAlertDialogue(int position){
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage(R.string.remove_pizza_warning)
                .setCancelable(false)
                .setPositiveButton(R.string.yes, (dialog, which) -> removePizza(position))
                .setNegativeButton(R.string.no, (dialog, which) -> { });
        AlertDialog alertDialog = builder.create();
        alertDialog.show();
    }

    /**
     * Removes the pizza selected by the user from the order before updating the order display.
     * @param position the position of the pizza selected by the user in the ListView.
     */
    private void removePizza(int position){
        Pizza pizza = currentOrder.getPizzas().get(position);
        currentOrder.remove(pizza);
        updatePizzaListView();
        updatePrice();
        showToast(R.string.removed_selected_pizza_toast);
    }

    /**
     * Sets the onClickListener for the removeAllPizzasButton.
     */
    private void initializeRemoveAllPizzasButton(){
        removeAllPizzasButton.setOnClickListener(v -> showRemoveAllPizzasAlertDialogue());
    }

    /**
     * Shows an AlertDialogue to let the user confirm if all pizzas are to be removed.
     * If there are no pizzas in the current order, the user is prompted to add pizzas to the order.
     * OK must be pressed to acknowledge the alert, and nothing will occur in this case.
     * If there are pizzas in the order and yes is selected, all pizzas are removed by invoking
     * removeAllPizzas(). Otherwise, nothing occurs when No is pressed.
     */
    private void showRemoveAllPizzasAlertDialogue(){
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        if ( currentOrder.getPizzas().isEmpty() ) {
            builder.setMessage(R.string.pizza_remove_prompt)
                    .setCancelable(false)
                    .setPositiveButton(R.string.yes, (dialog, which) -> { });
        } else {
            builder.setMessage(R.string.remove_all_pizzas_warning)
                    .setCancelable(false)
                    .setPositiveButton(R.string.yes, (dialog, which) -> removeAllPizzas())
                    .setNegativeButton(R.string.no, (dialog, which) -> { });
        }
        AlertDialog alertDialog = builder.create();
        alertDialog.show();
    }

    /**
     * Removes all pizzas from the current order before updating the order display.
     */
    private void removeAllPizzas(){
        currentOrder.removeAllPizzas();
        updatePizzaListView();
        updatePrice();
        showToast(R.string.removed_all_pizzas_toast);
    }

    /**
     * Sets the onClickListener for the submitOrderButton depending on if the order has pizzas.
     */
    private void initializeSubmitOrderButton(){
        submitOrderButton.setOnClickListener(v -> {
            if ( currentOrder.getPizzas().isEmpty() ) {
                showAddPizzaDialogue();
            } else {
                showSubmitOrderAlertDialogue();
            }
        });
    }

    /**
     * Shows an AlertDialogue to alert the user to add pizzas to the order before submitting.
     * OK must be selected in order to acknowledge the alert, but nothing will occur afterwards.
     */
    private void showAddPizzaDialogue(){
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage(R.string.pizza_prompt)
                .setCancelable(false)
                .setPositiveButton(R.string.ok, (dialog, which) -> { });
        AlertDialog alertDialog = builder.create();
        alertDialog.show();
    }

    /**
     * Shows an AlertDialogue to let the user confirm if the order is to be submitted.
     * If yes is selected, the order is submitted by invoking submitOrder().
     * Otherwise, nothing occurs.
     */
    private void showSubmitOrderAlertDialogue(){
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage(R.string.submit_order_warning)
                .setCancelable(false)
                .setPositiveButton(R.string.yes, (dialog, which) -> submitOrder())
                .setNegativeButton(R.string.no, (dialog, which) -> { });
        AlertDialog alertDialog = builder.create();
        alertDialog.show();
    }

    /**
     * Submits the current order and updates the order display.
     * The currentOrder is added to StoreOrdersActivity.storeOrders and anew Order object is
     * instantiated for currentOrder.
     * The order display is updated by calling updatePizzaListView() and updatePrice().
     */
    private void submitOrder(){
        StoreOrdersActivity.storeOrders.add(currentOrder);
        currentOrder = new Order();
        updatePizzaListView();
        updatePrice();
        showToast(R.string.submitted_order_toast);
    }

    /**
     * Updates the ListView displaying the pizzas in the current order.
     * This is done by creating a new ArrayAdapter<Pizza> using the ArrayList of pizzas in the
     * current order.
     */
    private void updatePizzaListView(){
        ArrayAdapter<Pizza> arrayAdapter = new ArrayAdapter<>(this,
                android.R.layout.simple_list_item_1, currentOrder.getPizzas());
        pizzaListView.setAdapter(arrayAdapter);
    }

    /**
     * Updates the subtotal, tax, and total of the current order.
     * This is done by making calls on the currentOrder object to obtain its subtotal, tax, and
     * total before formatting it appropriately.
     */
    private void updatePrice(){
        DecimalFormat df = new DecimalFormat("#0.00");
        String subtotal = "Subtotal: $" + df.format(currentOrder.getOrderSubtotal());
        subtotalTextView.setText(subtotal);
        String tax = "Tax: $" + df.format(currentOrder.getOrderTax());
        taxTextView.setText(tax);
        String total = "Total: $" + df.format(currentOrder.getOrderTotal());
        totalTextView.setText(total);
    }

    /**
     * Shows a toast message whose message is specified by the user.
     * @param string the string id of the message to be shown in the toast.
     */
    private void showToast(int string){
        Toast.makeText(this, string, Toast.LENGTH_SHORT).show();
    }

}