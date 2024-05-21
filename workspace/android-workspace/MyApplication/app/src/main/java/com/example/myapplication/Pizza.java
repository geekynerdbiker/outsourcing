package com.example.myapplication;


import androidx.annotation.NonNull;

import java.text.DecimalFormat;
import java.util.ArrayList;

/**
 * The Pizza abstract class determines the methods and data fields associated with an instance or subclass of Pizza.
 * Each instance of Pizza has an ArrayList of toppings, a Size object, a Crust object, and a method to obtain the price.
 * This method is abstract, and depends on what subclass of Pizza it is invoked upon.
 *
 * @author Trent Demers, Awad Shawl
 */
public abstract class Pizza implements Customizable {
    private ArrayList<Topping> toppings;
    private Crust crust;
    private Size size;

    /**
     * price() returns the price of an instance of Pizza.
     * @return the price of an instance of Pizza.
     */
    public abstract double price();

    /**
     * Pizza() instantiates a  Pizza by instantiating an ArrayList to be used for toppings.
     */
    public Pizza(){
        toppings = new ArrayList<>();
    }

    /**
     * Adds a topping from this pizza, ensuring that it is an instance of Topping.
     * @param obj the Topping to be added.
     * @return true if added, false otherwise.
     */
    @Override
    public boolean add(Object obj) {
        if ( obj instanceof Topping ) {
            return toppings.add((Topping) obj);
        }
        return false;
    }

    /**
     * Removes a topping from this pizza, ensuring that it is an instance of Topping.
     * @param obj the Topping to be removed.
     * @return true if removed, false otherwise.
     */
    @Override
    public boolean remove(Object obj) {
        if ( obj instanceof Topping ) {
            return toppings.remove((Topping) obj);
        }
        return false;
    }

    /**
     * Sets the type of crust for this pizza.
     * @param crust the instance of Crust to set this crust to.
     */
    public void setCrust(Crust crust) {
        this.crust = crust;
    }

    /**
     * Sets the size of this pizza.
     * @param size the size to be set for this pizza, an instance of Size.
     */
    public void setSize(Size size) {
        this.size = size;
    }

    /**
     * Returns the size of this pizza.
     * @return the size of this pizza, an instance of Size.
     */
    public Size getSize() {
        return size;
    }

    /**
     * Sets the toppings for this pizza to be equal to the toppings specified by the parameter.
     * @param toppings a list of toppings that are to be set for this pizza.
     */
    public void setToppings(ArrayList<Topping> toppings) {
        this.toppings = toppings;
    }

    /**
     * Returns the list of toppings set for this pizza.
     * @return a list of toppings for this pizza.
     */
    public ArrayList<Topping> getToppings(){
        return new ArrayList<>(toppings);
    }

    /**
     * Returns the number of toppings on this pizza.
     * @return the number of toppings on this pizza.
     */
    public int getNumberOfToppings(){
        return toppings.size();
    }

    /**
     * Indicates whether this pizza has the maximum number of toppings.
     * @return true is this pizza has the maximum number of toppings, false otherwise.
     */
    public boolean hasMaximumToppings(){
        return getNumberOfToppings() == RUPizzaConstants.MAX_TOPPINGS;
    }

    /**
     * Indicates whether this pizza has no toppings
     * @return true is this pizza has no toppings, false otherwise.
     */
    public boolean hasNoToppings(){
        return getNumberOfToppings() == RUPizzaConstants.NO_TOPPINGS;
    }

    /**
     * toString() returns the string representation of this pizza.
     * This includes the type, size, crust, toppings, and price.
     * @return the string representation of this pizza.
     */
    @NonNull
    @Override
    public String toString(){
        String pizzaString = "";
        if ( this instanceof BuildYourOwn ) {
            pizzaString = pizzaString.concat("Build Your Own");
        } else if ( this instanceof BBQChicken ) {
            pizzaString = pizzaString.concat("BBQ Chicken");
        } else if ( this instanceof Deluxe ) {
            pizzaString = pizzaString.concat("Deluxe");
        } else {
            pizzaString = pizzaString.concat("Meatzza");
        }
        pizzaString = pizzaString.concat("\n\tCrust: " + this.crust.getStringRepresentation()
                + "\n\tSize: " + this.size.getStringRepresentation() + "\n\tToppings: ");
        Topping[] toppingsArray = toppings.toArray(new Topping[0]);
        for ( int i = 0; i < toppingsArray.length; i++ ){
            pizzaString = pizzaString.concat("\n\t\t- " + toppingsArray[i].getStringRepresentation());
        }
        DecimalFormat df = new DecimalFormat();
        df.applyPattern("#0.00");
        pizzaString = pizzaString.concat("\n\tPrice: $" + df.format(this.price()) + "\n");
        return pizzaString;
    }

}