package com.example.myapplication;

/**
 * The BBQChicken class is a subclass of Pizza, and defines the method for getting the price of a BBQ Chicken pizza.
 *
 * @author Trent Demers, Awad Shawl
 */
public class BBQChicken extends Pizza {

    /**
     * price() returns the price of a BBQ Chicken pizza depending on its size.
     * @return a double value corresponding to the price of this pizza.
     */
    @Override
    public double price() {
        if ( getSize() == Size.SMALL ) {
            return RUPizzaConstants.SMALL_BBQCHICKEN_PRICE;
        }
        if ( getSize() == Size.MEDIUM ) {
            return RUPizzaConstants.MEDIUM_BBQCHICKEN_PRICE;
        }
        if ( getSize() == Size.LARGE ) {
            return RUPizzaConstants.LARGE_BBQCHICKEN_PRICE;
        }
        return RUPizzaConstants.NO_PRICE;
    }


}