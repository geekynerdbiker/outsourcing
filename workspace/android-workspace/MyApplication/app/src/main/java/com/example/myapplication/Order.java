package com.example.myapplication;

import java.util.ArrayList;

/**
 * The Order class defines the behaviors and data fields associated with an order of pizzas.
 * An order has a unique serial number, which is determined by a static variable that tracks the
 * number of order objects instantiated. It also has an ArrayList of Pizza objects that are in this
 * order. The Customizable interface is implemented to add and remove pizzas to this order.
 *
 * @author Trent Demers, Awad Shawl
 */
public class Order implements Customizable {

    private static int numOrders = 0;
    private final int serialNumber;
    private final ArrayList<Pizza> pizzas;

    /**
     * Instantiates an order object by giving it a serial number and instantiating the ArrayList.
     */
    public Order(){

        serialNumber = numOrders++;
        pizzas = new ArrayList<>();

    }

    /**
     * Adds a pizza to this order, ensuring that it is an instance of Pizza.
     * @param obj the pizza to be added to the ArrayList of pizzas in this order.
     * @return true if added, false otherwise.
     */
    @Override
    public boolean add(Object obj) {
        if ( ! (obj instanceof Pizza ) ) {
            return false;
        }
        return pizzas.add((Pizza) obj);
    }

    /**
     * Removes a pizza from this order, ensuring that it is an instance of Pizza.
     * @param obj the pizza to be removed from the ArrayList of pizzas in this order.
     * @return true if removed, false otherwise.
     */
    @Override
    public boolean remove(Object obj) {
        if ( ! (obj instanceof Pizza ) ) {
            return false;
        }
        return pizzas.remove((Pizza) obj);
    }

    /**
     * Returns the ArrayList of pizzas in this order.
     * @return the ArrayList of pizzas in this order.
     */
    public ArrayList<Pizza> getPizzas() {
        return pizzas;
    }

    /**
     * Returns the serial number of this order.
     * @return the serial number of this order.
     */
    public int getSerialNumber(){
        return serialNumber;
    }

    /**
     * Returns the subtotal of this order.
     * @return the subtotal of this order.
     */
    public double getOrderSubtotal(){
        double subtotal = 0;
        for ( Pizza pizza : pizzas ) {
            subtotal += pizza.price();
        }
        return subtotal;
    }

    /**
     * Returns the tax on this order.
     * @return the tax on this order.
     */
    public double getOrderTax(){
        return getOrderSubtotal() * RUPizzaConstants.TAX_RATE;
    }

    /**
     * Returns the price of an order with tax included.
     * @return the price of an order with tax included.
     */
    public double getOrderTotal(){
        return getOrderSubtotal() + getOrderTax();
    }

    /**
     * Removes all pizzas from the order by clearing its ArrayList.
     */
    public void removeAllPizzas(){
        pizzas.clear();
    }
}

