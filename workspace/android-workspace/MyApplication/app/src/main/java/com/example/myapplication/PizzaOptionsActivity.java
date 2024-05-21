package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;

import java.text.DecimalFormat;
import java.util.ArrayList;

/**
 * The PizzaOptionsActivity class defines the methods and data associated with customizing a pizza.
 * The information about the pizza being customized, being the image of the pizza as well as its
 * style, flavor, and crust, is displayed.
 * A TextView instance is used to display the subtotal of the pizza being customized.
 * Two TextView instances are used to prompt the user to add or remove toppings if appropriate.
 * A RadioGroup is used to allow the user to select the size of the pizza.
 * Two ListView instances are used to display toppings on the pizza, as well as available to select.
 * A Button instance is used to allow the user to add the pizza to the current order.
 *
 * @author Trent Demers, Awad Shawl
 */
public class PizzaOptionsActivity extends AppCompatActivity {

    private PizzaFactory pizzaFactory;

    private Pizza pizza;

    private ImageView pizzaImageView;
    private TextView styleTextView, flavorTextView, crustTextView, addToppingTextPrompt,
            removeToppingTextPrompt, subtotalTextView;
    private RadioGroup sizeRadioGroup;
    private ListView currentToppingsListView, availableToppingsListView;
    private Button addPizzaToOrderButton;

    private final ArrayList<Topping> availableToppings = new ArrayList<>(Topping.getAllToppings());

    /**
     * Shows the layout of the CurrentOrderActivity as a View before initializing I/O elements.
     * The layout file is activity_pizza_options.xml.
     * If the pizza is an instance of BuildYourOwn, then the ability to add toppings is initialized.
     * Otherwise, the user is kept from being able to modify toppings.
     * @param savedInstanceState the Bundle used to restore the app when onCreate() is invoked.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pizza_options);

        initializeReferences();

        initializePizza();

        initializeSizeRadioGroup();
        initializeAddPizzaToOrderButton();

        updatePrice();

        if ( pizza instanceof BuildYourOwn ) {
            initializeAvailableToppingsListView();
            initializeCurrentToppingsListView();
            updateAvailableToppingsListView();
            updateCurrentToppingsListView();
            addToppingTextPrompt.setText(R.string.add_topping_prompt);
            removeToppingTextPrompt.setText(R.string.cannot_remove_prompt);
        } else {
            availableToppingsListView.setClickable(false);
            currentToppingsListView.setClickable(false);
            updateCurrentToppingsListView();
            addToppingTextPrompt.setText(R.string.cannot_add_prompt);
            removeToppingTextPrompt.setText(R.string.cannot_remove_prompt);
        }
    }

    /**
     * Initializes references to elements of the layout that are used for user I/O.
     * The layout file is activity_pizza_options.xml.
     */
    private void initializeReferences(){
        pizzaImageView = findViewById(R.id.pizzaImageView);
        styleTextView = findViewById(R.id.styleTextView);
        flavorTextView = findViewById(R.id.flavorTextView);
        crustTextView = findViewById(R.id.crustTextView);
        subtotalTextView = findViewById(R.id.pizzaSubtotalTextView);
        sizeRadioGroup = findViewById(R.id.sizeRadioGroup);
        addToppingTextPrompt = findViewById(R.id.addToppingTextPrompt);
        removeToppingTextPrompt = findViewById(R.id.removeToppingTextPrompt);
        availableToppingsListView = findViewById(R.id.availableToppingsListView);
        currentToppingsListView = findViewById(R.id.toppingsListView);
        addPizzaToOrderButton = findViewById(R.id.addToOrderButton);
    }

    /**
     * Initializes the instance of Pizza to be customized as determined by the option selected.
     * Methods are called to initialize the PizzaFactory used to create Pizza objects, and once the
     * Pizza is created, the information about the style, flavor, crust, and toppings of the Pizza
     * are displayed.
     */
    private void initializePizza(){
        Intent intent = getIntent();
        PizzaOption pizzaOption = (PizzaOption) intent.getSerializableExtra("PIZZA_OPTION");
        initializePizzaFactory(pizzaOption);
        switch ( pizzaOption.getPizzaOptionNumber() ) {
            case RUPizzaConstants.NY_BYO:
            case RUPizzaConstants.CH_BYO:
                pizza = pizzaFactory.createBuildYourOwn();
                break;
            case RUPizzaConstants.NY_BBQ:
            case RUPizzaConstants.CH_BBQ:
                pizza = pizzaFactory.createBBQChicken();
                break;
            case RUPizzaConstants.NY_DELUXE:
            case RUPizzaConstants.CH_DELUXE:
                pizza = pizzaFactory.createDeluxe();
                break;
            case RUPizzaConstants.NY_MEATZZA:
            case RUPizzaConstants.CH_MEATZZA:
                pizza = pizzaFactory.createMeatzza();
                break;
            default:
                break;
        }
        initializePizzaOptionInfo(pizzaOption);
        updateCurrentToppingsListView();
    }

    /**
     * Initializes a PizzaFactory depending on the style of the PizzaOption selected.
     * @param pizzaOption the PizzaOption selected by the user to customize.
     */
    private void initializePizzaFactory(PizzaOption pizzaOption){
        if ( pizzaOption.getPizzaOptionNumber() <= RUPizzaConstants.NY_MEATZZA ) {
            pizzaFactory = new NYPizza();
        } else {
            pizzaFactory = new ChicagoPizza();
        }
    }

    /**
     * Initializes the I/O elements that display information about the PizzaOption selected.
     * @param pizzaOption the PizzaOption selected by the user to customize.
     */
    private void initializePizzaOptionInfo(PizzaOption pizzaOption){
        styleTextView.setText(pizzaOption.getPizzaStyle());
        flavorTextView.setText(pizzaOption.getPizzaFlavor());
        crustTextView.setText(pizzaOption.getPizzaCrust());
        pizzaImageView.setImageResource(pizzaOption.getPizzaImage());
    }

    /**
     * Sets the onCheckedChangeListener for the RadioGroup used to select a Pizza size.
     * Once a size is selected, the price display of the Pizza being customized is updated.
     */
    private void initializeSizeRadioGroup(){
        sizeRadioGroup.setOnCheckedChangeListener((group, checkedId) -> {
            if ( checkedId == R.id.smallSizeButton ) {
                pizza.setSize(Size.SMALL);
            } else if ( checkedId == R.id.mediumSizeButton ){
                pizza.setSize(Size.MEDIUM);
            } else {
                pizza.setSize(Size.LARGE);
            }
            updatePrice();
        });
    }

    /**
     * Sets the onClickListener for the Button used to add the customized Pizza to the order.
     * If the Pizza does not have a size, the showSelectSizeDialogue() is invoked.
     * Otherwise, showAddPizzaToOrderAlertDialogue() is invoked.
     */
    private void initializeAddPizzaToOrderButton(){
        addPizzaToOrderButton.setOnClickListener(v -> {
            if ( pizza.getSize() == null ) {
                showSelectSizeDialogue(v);
            } else {
                showAddPizzaToOrderAlertDialogue(v);
            }
        });
    }

    /**
     * Shows an AlertDialogue to alert the user to select a size before ordering the pizza.
     * OK must be selected in order to acknowledge the alert, but nothing will occur afterwards.
     * @param v the View to display the AlertDialogue in.
     */
    private void showSelectSizeDialogue(View v){
        AlertDialog.Builder builder = new AlertDialog.Builder(v.getContext());
        builder.setMessage(R.string.size_prompt)
                .setCancelable(false)
                .setPositiveButton(R.string.ok, (dialog, which) -> {

                });
        AlertDialog alert = builder.create();
        alert.show();
    }

    /**
     * Shows an AlertDialogue to let the user confirm if the pizza is to be added to the order.
     * If yes is selected, the pizza is added to the order by invoking addPizzaToOrder().
     * Otherwise, nothing occurs.
     */
    private void showAddPizzaToOrderAlertDialogue(View v){
        AlertDialog.Builder builder = new AlertDialog.Builder(v.getContext());
        builder.setMessage(R.string.add_pizza_to_order_warning)
                .setCancelable(false)
                .setPositiveButton("Yes", (dialog, which) -> addPizzaToOrder()).setNegativeButton("No", (dialog, which) -> { });
        AlertDialog alert = builder.create();
        alert.show();
    }

    /**
     * Adds the pizza being customized to the current order.
     * The pizza is added to CurrentOrderActivity.currentOrder.
     * The options selected by the user are not flushed when the pizza is added, so a new instance
     * of Pizza must be created and set to the same settings as the added Pizza. This is done by
     * invoking recreatePizza().
     */
    private void addPizzaToOrder(){
        CurrentOrderActivity.currentOrder.add(pizza);
        recreatePizza();
        showToast(R.string.added_pizza_to_order_toast);
    }

    /**
     * recreatePizza() uses the values selected for the current pizza and creates a clone.
     * After this is done, the pizza variable is reassigned to this clone, as the selections the
     * user made are maintained by the display. This allows a user to continuously add identical
     * pizzas to their order.
     */
    private void recreatePizza(){
        Pizza newPizza;
        if ( pizza instanceof BuildYourOwn ) {
            newPizza = pizzaFactory.createBuildYourOwn();
        } else if ( pizza instanceof BBQChicken ) {
            newPizza = pizzaFactory.createBBQChicken();
        } else if ( pizza instanceof Deluxe ) {
            newPizza = pizzaFactory.createDeluxe();
        } else {
            newPizza = pizzaFactory.createMeatzza();
        }
        newPizza.setSize(pizza.getSize());
        newPizza.setToppings(pizza.getToppings());
        pizza = newPizza;
    }

    /**
     * Sets the onItemClickListener for the ListView used to add toppings to the Pizza.
     * When an Item is clicked, onAddToppingSelection() is invoked.
     */
    private void initializeAvailableToppingsListView(){
        availableToppingsListView.setOnItemClickListener((parent, view, position, id)
                -> onAddToppingSelection(position));
    }

    /**
     * Sets the onItemClickListener for the ListView used to remove toppings from the Pizza.
     * When an Item is clicked, onRemoveToppingSelection() is invoked.
     */
    private void initializeCurrentToppingsListView(){
        currentToppingsListView.setOnItemClickListener((parent, view, position, id)
                -> onRemoveToppingSelection(position));
    }

    /**
     * Updates the ListView displaying toppings not currently on the Pizza.
     * This is done by creating a new ArrayAdapter using the ArrayList availableToppings.
     */
    private void updateAvailableToppingsListView(){
        ArrayAdapter<Topping> adapter = new ArrayAdapter<>(this,
                android.R.layout.simple_list_item_1, availableToppings);
        availableToppingsListView.setAdapter(adapter);
    }

    /**
     * Updates the ListView displaying toppings currently on the Pizza.
     * This is done by creating a new ArrayAdapter using the toppings currently on the Pizza.
     */
    private void updateCurrentToppingsListView(){
        ArrayAdapter<Topping> adapter = new ArrayAdapter<>(this,
                android.R.layout.simple_list_item_1, pizza.getToppings());
        currentToppingsListView.setAdapter(adapter);
    }

    /**
     * Updates the TextView displaying the subtotal of the Pizza being customized.
     * If the Pizza does not have a size, the subtotal is set as $0.00.
     * Otherwise, the subtotal is gotten from the Pizza using price().
     */
    private void updatePrice(){
        DecimalFormat df = new DecimalFormat("#0.00");
        double subtotal;
        if ( pizza.getSize() == null ){
            subtotal = 0.0;
        } else {
            subtotal = pizza.price();
        }
        String subtotalString = "Subtotal: $" + df.format(subtotal);
        subtotalTextView.setText(subtotalString);
    }

    /**
     * Updates the toppings display/data when a topping is selected to be added to the Pizza.
     * The topping selected is removed from the list of available toppings and added to the Pizza.
     * The ListViews used to display toppings are updated, and the price of the Pizza is updated.
     * If there were no toppings on the pizza before the topping is added, the user regains the
     * ability to remove toppings.
     * If there are the maximum number of toppings on the pizza after the topping is added, the user
     * loses the ability to add toppings.
     * @param position the position of the topping selected in the availableToppingsListView.
     */
    private void onAddToppingSelection(int position){
        boolean hadNoToppings = pizza.hasNoToppings();

        Topping selectedTopping = availableToppings.get(position);
        availableToppings.remove(selectedTopping);
        pizza.add(selectedTopping);

        updateCurrentToppingsListView();
        updateAvailableToppingsListView();
        updatePrice();

        if ( hadNoToppings ) {
            currentToppingsListView.setEnabled(true);
            removeToppingTextPrompt.setText(R.string.remove_topping_prompt);
        }
        if ( pizza.hasMaximumToppings() ) {
            availableToppingsListView.setEnabled(false);
            addToppingTextPrompt.setText(R.string.cannot_add_prompt);
            showToast(R.string.max_toppings_toast);
        }
    }

    /**
     * Updates the toppings display/data when a topping is selected to be removed from the Pizza.
     * The topping selected is added to the list of available toppings and removed from the Pizza.
     * The ListViews used to display toppings are updated, and the price of the Pizza is updated.
     * If there were the maximum number of toppings on the pizza before the topping is removed, the
     * user regains the ability to add toppings.
     * If there are no toppings on the pizza after the topping is removed, the user
     * loses the ability to remove toppings.
     * @param position the position of the topping selected in the currentToppingsListView.
     */
    private void onRemoveToppingSelection(int position){
        boolean hadMaxToppings = pizza.hasMaximumToppings();

        Topping selectedTopping = pizza.getToppings().get(position);
        pizza.remove(selectedTopping);
        availableToppings.add(selectedTopping);

        updateCurrentToppingsListView();
        updateAvailableToppingsListView();
        updatePrice();

        if ( hadMaxToppings ) {
            availableToppingsListView.setEnabled(true);
            addToppingTextPrompt.setText(R.string.add_topping_prompt);
        }
        if ( pizza.hasNoToppings() ) {
            currentToppingsListView.setEnabled(false);
            removeToppingTextPrompt.setText(R.string.cannot_remove_prompt);
        }
    }

    /**
     * Shows a toast message whose message is specified by the user.
     * @param string the string id of the message to be shown in the toast.
     */
    private void showToast(int string){
        Toast.makeText(this, string, Toast.LENGTH_SHORT).show();
    }

}