package com.example.myapplication;

/**
 * The Deluxe class is a subclass of Pizza, and defines the method for getting the price of a Deluxe pizza.
 *
 * @author Trent Demers, Awad Shawl
 */
public class Deluxe extends Pizza {

    /**
     * price() returns the price of a Deluxe pizza depending on its size.
     * @return a double value corresponding to the price of this pizza.
     */
    @Override
    public double price() {
        if ( getSize() == Size.SMALL ) {
            return RUPizzaConstants.SMALL_DELUXE_PRICE;
        }
        if ( getSize() == Size.MEDIUM ) {
            return RUPizzaConstants.MEDIUM_DELUXE_PRICE;
        }
        if ( getSize() == Size.LARGE ) {
            return RUPizzaConstants.LARGE_DELUXE_PRICE;
        }
        return RUPizzaConstants.NO_PRICE;
    }

}
