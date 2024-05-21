package com.example.myapplication;

/**
 * The BuildYourOwn class is a subclass of Pizza, and defines the method for getting the price of a BuildYourOwn pizza.
 *
 * @author Trent Demers, Awad Shawl
 */
public class BuildYourOwn extends Pizza {

    /**
     * price() returns the price of a BuildYourOwn pizza depending on its size and number of toppings.
     * @return a double value corresponding to the price of this pizza.
     */
    @Override
    public double price() {
        if ( getSize() == Size.SMALL ) {
            return RUPizzaConstants.SMALL_BUILDYOUROWN_PRICE + getNumberOfToppings() * RUPizzaConstants.TOPPING_PRICE;
        }
        if ( getSize() == Size.MEDIUM ) {
            return RUPizzaConstants.MEDIUM_BUILDYOUROWN_PRICE + getNumberOfToppings() * RUPizzaConstants.TOPPING_PRICE;
        }
        if ( getSize() == Size.LARGE ) {
            return RUPizzaConstants.LARGE_BUILDYOUROWN_PRICE + getNumberOfToppings() * RUPizzaConstants.TOPPING_PRICE;
        }
        return RUPizzaConstants.NO_PRICE;
    }
}

