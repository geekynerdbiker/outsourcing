package com.example.myapplication;

import androidx.annotation.NonNull;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * The Topping enumerated type defines values for different toppings, and associates them with a string representation.
 *
 * @author Trent Demers, Awad Shawl
 */
public enum Topping {
    BACON("Bacon"),
    BBQ_CHICKEN("BBQ Chicken"),
    BEEF("Beef"),
    CHEDDAR("Cheddar"),
    CHICKEN("Chicken"),
    GREEN_PEPPER("Green Pepper"),
    HAM("Ham"),
    MUSHROOM("Mushroom"),

    ONION("Onion"),
    PEPPER("Pepper"),
    PEPPERONI("Pepperoni"),
    PROVOLONE("Provolone"),
    SAUSAGE("Sausage");

    private final String stringRepresentation;

    /**
     * Topping() is the implicit constructor for an instance of Topping, which necessitates a string representation.
     * @param stringRepresentation the string representation of the instance of Topping.
     */
    Topping(String stringRepresentation){
        this.stringRepresentation = stringRepresentation;
    }

    /**
     * getStringRepresentation() returns the string representation of this instance of Topping.
     * @return the string representation of this instance of Topping.
     */
    public String getStringRepresentation(){
        return this.stringRepresentation;
    }

    /**
     * getBBQChickenToppings() returns a list of toppings in a BBQ Chicken pizza.
     * @return a list of toppings in a BBQ Chicken pizza.
     */
    public static ArrayList<Topping> getBBQChickenToppings(){
        ArrayList<Topping> toppings = new ArrayList<>();
        toppings.add(Topping.BBQ_CHICKEN);
        toppings.add(Topping.GREEN_PEPPER);
        toppings.add(Topping.PROVOLONE);
        toppings.add(Topping.CHEDDAR);
        return toppings;
    }

    /**
     * getDeluxeToppings() returns a list of toppings in a Deluxe pizza.
     * @return a list of toppings in a Deluxe pizza.
     */
    public static ArrayList<Topping> getDeluxeToppings(){
        ArrayList<Topping> toppings = new ArrayList<>();
        toppings.add(Topping.SAUSAGE);
        toppings.add(Topping.ONION);
        toppings.add(Topping.PEPPERONI);
        toppings.add(Topping.GREEN_PEPPER);
        toppings.add(Topping.MUSHROOM);
        return toppings;
    }

    /**
     * getMeatzzaToppings() returns a list of toppings in a Meatzza pizza.
     * @return a list of toppings in a Meatzza pizza.
     */
    public static ArrayList<Topping> getMeatzzaToppings(){
        ArrayList<Topping> toppings = new ArrayList<>();
        toppings.add(Topping.SAUSAGE);
        toppings.add(Topping.PEPPERONI);
        toppings.add(Topping.BEEF);
        toppings.add(Topping.HAM);
        return toppings;
    }

    /**
     * getAllToppingStrings() returns a list all toppings offered by the store.
     * @return a list all toppings offered by the store.
     */
    public static ArrayList<Topping> getAllToppings(){
        return new ArrayList<>(Arrays.asList(Topping.values()));
    }

    /**
     * Returns the string representation of this Topping.
     * @return the string representation of this Topping.
     */
    @NonNull
    @Override
    public String toString(){
        return stringRepresentation;
    }

}
