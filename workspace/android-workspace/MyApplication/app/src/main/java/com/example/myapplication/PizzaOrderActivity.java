package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;

import java.util.ArrayList;

/**
 * The PizzaOrderActivity class defines the display of PizzaOption objects the user can customize.
 * A RecyclerView is used to display the PizzaOption objects.
 *
 * @author Trent Demers
 */
public class PizzaOrderActivity extends AppCompatActivity {

    private final ArrayList<PizzaOption> pizzaOptions = new ArrayList<>();

    /**
     * Shows the layout of the PizzaOrderActivity as a View before initializing the RecyclerView.
     * The layout file is activity_pizza_order.xml.
     * @param savedInstanceState the Bundle used to restore the app when onCreate() is invoked.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pizza_order);
        initializePizzaChoices();
        initializeRecyclerView();
    }

    /**
     * Initializes the list of PizzaOption objects to be displayed in the RecyclerView.
     */
    private void initializePizzaChoices(){
        String[] pizzaStyles = getResources().getStringArray(R.array.styles);
        String[] pizzaFlavors = getResources().getStringArray(R.array.flavors);
        String[] pizzaCrusts = getResources().getStringArray(R.array.crusts);
        int[] pizzaImages = {R.drawable.new_york_style_bbq, R.drawable.new_york_style_byo,
                R.drawable.new_york_style_deluxe, R.drawable.new_york_style_meatzza,
                R.drawable.chicago_style_bbq, R.drawable.chicago_style_byo,
                R.drawable.chicago_style_deluxe, R.drawable.chicago_style_meatzza};
        for ( int i = 0; i < RUPizzaConstants.NUMBER_OF_OPTIONS; i++ ){
            pizzaOptions.add(new PizzaOption(pizzaStyles[i], pizzaFlavors[i],
                    pizzaCrusts[i], pizzaImages[i], i));
        }
    }

    /**
     * Initializes the RecyclerView used to display the PizzaOption objects.
     */
    private void initializeRecyclerView(){
        RecyclerView pizzaRecyclerView = findViewById(R.id.pizzaRecyclerView);
        PizzaOptionsAdapter adapter = new PizzaOptionsAdapter(this, pizzaOptions);
        pizzaRecyclerView.setAdapter(adapter);
        pizzaRecyclerView.setLayoutManager(new LinearLayoutManager(this));
    }

}