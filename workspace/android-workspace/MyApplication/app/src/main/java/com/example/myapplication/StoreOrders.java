package com.example.myapplication;

import java.util.ArrayList;

/**
 * The StoreOrders class defines the behaviors and data fields associated with a list of orders.
 * This includes the ability to add and remove orders, and get an order from its serial number.
 * The orders are represented by an ArrayList.
 *
 * @author Trent Demers, Awad Shawl
 */
public class StoreOrders implements Customizable {

    private final ArrayList<Order> orders;

    /**
     * Initializes an instance of StoreOrders by initializing the ArrayList of orders.
     */
    public StoreOrders(){
        orders = new ArrayList<>();
    }

    /**
     * Adds an order to the list of orders, ensuring that it is an instance of Order.
     * @param obj the instance of Order to be added to the ArrayList of orders for this store.
     * @return true if added, false otherwise.
     */
    @Override
    public boolean add(Object obj) {
        if ( obj instanceof Order ) {
            orders.add((Order) obj);
            return true;
        }
        return false;
    }

    /**
     * Removes an order from the list of orders, ensuring that it is an instance of Order.
     * @param obj the instance of Order to be removed from the ArrayList of orders for this store.
     * @return true if removed, false otherwise.
     */
    @Override
    public boolean remove(Object obj) {
        if ( obj instanceof Order ) {
            orders.remove((Order) obj);
            return true;
        }
        return false;
    }

    /**
     * Returns an instance of Order with a matching serial number.
     * @param serialNumber the serial number to check for.
     * @return the order with a matching serial number.
     */
    public Order getOrderFromSerialNumber(int serialNumber){
        for ( Order order : orders ) {
            if ( serialNumber == order.getSerialNumber() ) {
                return order;
            }
        }
        return null;
    }

    /**
     * Returns the list of orders currently given to the store.
     * @return the list of orders currently given to the store.
     */
    public ArrayList<Order> getOrders() {
        return orders;
    }

    /**
     * Returns the list of serial numbers that correspond to orders given to the store.
     * @return the list of serial numbers that correspond to orders given to the store.
     */
    public ArrayList<Integer> getOrderSerialNumbers(){
        ArrayList<Integer> serialNumbers = new ArrayList<>();
        for ( Order order : orders ) {
            serialNumbers.add(order.getSerialNumber());
        }
        return serialNumbers;
    }


}
