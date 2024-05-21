package com.example.myapplication;

import java.io.Serializable;

/**
 * The PizzaOption class defines the properties of a pizza that can be selected by a user to order.
 * This includes the style of the pizza, the flavor of the pizza, and the crust of the pizza, as
 * well as an image of that pizza and the index for the properties of that pizza across the arrays
 * it is stored in.
 *
 * @author Trent Demers, Awad Shawl
 */
public class PizzaOption implements Serializable {

    private final String pizzaStyle;
    private final String pizzaFlavor;
    private final String pizzaCrust;
    private  final int pizzaImage, pizzaOptionNumber;

    /**
     * Constructs a PizzaOption instance using a passed style, flavor, crust, image ID, and index.
     * @param pizzaStyle the style of the pizza option
     * @param pizzaFlavor the flavor of the pizza option
     * @param pizzaCrust the crust of the pizza option
     * @param pizzaImage the image ID of an image of the pizza option
     * @param pizzaOptionNumber the index of the pizza option
     */
    public PizzaOption(String pizzaStyle, String pizzaFlavor, String pizzaCrust,
                       int pizzaImage, int pizzaOptionNumber){
        this.pizzaStyle = pizzaStyle;
        this.pizzaFlavor = pizzaFlavor;
        this.pizzaCrust = pizzaCrust;
        this.pizzaImage = pizzaImage;
        this.pizzaOptionNumber = pizzaOptionNumber;
    }

    /**
     * Returns the style of the pizza option.
     * @return the style of the pizza option.
     */
    public String getPizzaStyle() {
        return pizzaStyle;
    }

    /**
     * Returns the flavor of the pizza option.
     * @return the flavor of the pizza option.
     */
    public String getPizzaFlavor() {
        return pizzaFlavor;
    }

    /**
     * Returns the crust of the pizza option.
     * @return the crust of the pizza option.
     */
    public String getPizzaCrust() {
        return pizzaCrust;
    }

    /**
     * Returns the image ID of the pizza option.
     * @return the image ID of the pizza option.
     */
    public int getPizzaImage() {
        return pizzaImage;
    }

    /**
     * Returns the index of the pizza option.
     * @return the index of the pizza option.
     */
    public int getPizzaOptionNumber() {
        return pizzaOptionNumber;
    }
}
