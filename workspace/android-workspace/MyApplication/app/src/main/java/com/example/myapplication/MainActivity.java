package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.ImageButton;

/**
 * The MainActivity defines the methods and references needed for the user to navigate the app.
 * Three imageButtons are used that when pressed take the user to select a pizza to order, view the
 * current order, or view all the orders submitted to the store.
 *
 * @author Trent Demers, Awad Shawl
 */
public class MainActivity extends AppCompatActivity {

    private ImageButton pizzaOrderButton, currentOrderButton, storeOrdersButton;

    /**
     * Shows the layout of the MainActivity as a View before initializing I/O elements.
     * The layout file is activity_main.xml.
     * The public static variables CurrentOrderActivity.currentOrder and
     * StoreOrdersActivity.storesOrders used for keeping an ArrayList of Pizzas and Orders
     * respectively are initialized.
     * @param savedInstanceState the Bundle used to restore the app when onCreate() is invoked.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        CurrentOrderActivity.currentOrder = new Order();
        StoreOrdersActivity.storeOrders = new StoreOrders();
        setImageButtonImages();
        setImageButtonOnClicks();
    }

    /**
     * Sets the images to be displayed on the ImageButtons.
     */
    private void setImageButtonImages(){
        pizzaOrderButton = findViewById(R.id.pizzaOrderButton);
        pizzaOrderButton.setImageResource(R.drawable.main_pizza);
        currentOrderButton = findViewById(R.id.currentOrderButton);
        currentOrderButton.setImageResource(R.drawable.order_main);
        storeOrdersButton = findViewById(R.id.storeOrdersButton);
        storeOrdersButton.setImageResource(R.drawable.store_main);
    }

    /**
     * Sets the onClickListener to take the user a different Activity for each ImageButton.
     * This includes PizzaOrderActivity, CurrentOrderActivity, and StoreOrderActivity.
     */
    private void setImageButtonOnClicks(){

        pizzaOrderButton.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, PizzaOrderActivity.class);
            startActivity(intent);
        });

        currentOrderButton.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, CurrentOrderActivity.class);
            startActivity(intent);
        });

        storeOrdersButton.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, StoreOrdersActivity.class);
            startActivity(intent);
        });
    }
}