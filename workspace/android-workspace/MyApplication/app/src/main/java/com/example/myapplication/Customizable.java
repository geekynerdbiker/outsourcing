package com.example.myapplication;

/**
 * The Customizable interface declares the abstract methods add() and remove()
 * @param <E> unused
 *
 * @author Trent Demers, Awad Shawl
 */
public interface Customizable<E> {

    /**
     * add() is an abstract method to add an object to a collection.
     * @param obj the object to be added to the collection.
     * @return the status of the addition.
     */
    boolean add(Object obj);

    /**
     * remove() is an abstract method to remove an object from a collection.
     * @param obj the object to be removed from the collection.
     * @return the status of the removal.
     */
    boolean remove(Object obj);
}
