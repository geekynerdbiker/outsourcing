package com.example.myapplication;

import java.util.ArrayList;

/**
 * The ChicagoPizza class defines how to make Chicago Style versions of the four pizza flavors.
 * This is done by implementing the PizzaFactory interface
 *
 * @author Trent Demers, Awad Shawl
 */
public class ChicagoPizza implements PizzaFactory {

    /**
     * createBBQChicken() instantiates a pizza as BBQChicken and sets its crust and toppings.
     * @return a reference to the created pizza.
     */
    @Override
    public Pizza createBBQChicken() {
        Pizza pizza = new BBQChicken();
        pizza.setCrust(Crust.PAN);
        pizza.setToppings(Topping.getBBQChickenToppings());
        return pizza;
    }

    /**
     * createDeluxe() instantiates a pizza as Deluxe and sets its crust and toppings.
     * @return a reference to the created pizza.
     */
    @Override
    public Pizza createDeluxe() {
        Pizza pizza = new Deluxe();
        pizza.setCrust(Crust.DEEP_DISH);
        pizza.setToppings(Topping.getDeluxeToppings());
        return pizza;
    }

    /**
     * createMeatzza() instantiates a pizza as Meatzza and sets its crust and toppings.
     * @return a reference to the created pizza.
     */
    @Override
    public Pizza createMeatzza() {
        Pizza pizza = new Meatzza();
        pizza.setCrust(Crust.STUFFED);
        pizza.setToppings(Topping.getMeatzzaToppings());
        return pizza;
    }

    /**
     * createBuildYourOwn() instantiates a pizza as BuildYourOwn and sets its crust and toppings.
     * @return a reference to the created pizza.
     */
    @Override
    public Pizza createBuildYourOwn() {
        Pizza pizza = new BuildYourOwn();
        pizza.setCrust(Crust.PAN);
        pizza.setToppings(new ArrayList<>());
        return pizza;
    }

}

