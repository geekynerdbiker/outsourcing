package com.example.myapplication;

import java.util.ArrayList;

/**
 * The NYPizza class defines how to make New York Style versions of the four pizza flavors.
 * This is done by implementing the PizzaFactory interface
 *
 * @author Trent Demers, Awad Shawl
 */
public class NYPizza implements PizzaFactory {

    /**
     * createBBQChicken() instantiates a pizza as BBQChicken and sets its crust and toppings.
     * @return a reference to the created pizza.
     */
    @Override
    public Pizza createBBQChicken() {
        Pizza pizza = new BBQChicken();
        pizza.setCrust(Crust.THIN);
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
        pizza.setCrust(Crust.BROOKLYN);
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
        pizza.setCrust(Crust.HAND_TOSSED);
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
        pizza.setCrust(Crust.HAND_TOSSED);
        pizza.setToppings(new ArrayList<>());
        return pizza;
    }

}