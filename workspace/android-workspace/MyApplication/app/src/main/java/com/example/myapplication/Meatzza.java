package com.example.myapplication;

/**
 * The Meatzza class is a subclass of Pizza, and defines the method for getting the price of a Deluxe pizza.
 *
 * @author Trent Demers, Awad Shawl
 */
public class Meatzza extends Pizza {

    /**
     * price() returns the price of a Meatzza pizza depending on its size.
     * @return a double value corresponding to the price of this pizza.
     */
    @Override
    public double price() {
        if ( getSize() == Size.SMALL ) {
            return RUPizzaConstants.SMALL_MEATZZA_PRICE;
        }
        if ( getSize() == Size.MEDIUM ) {
            return RUPizzaConstants.MEDIUM_MEATZZA_PRICE;
        }
        if ( getSize() == Size.LARGE ) {
            return RUPizzaConstants.LARGE_MEATZZA_PRICE;
        }
        return RUPizzaConstants.NO_PRICE;
    }

}
